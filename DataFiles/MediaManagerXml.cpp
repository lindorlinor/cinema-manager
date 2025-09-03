#include "MediaManagerXml.h"
#include "XmlVisitor.h"
#include <QFile>
#include <QFileDialog>
#include <QDomElement>
#include <QMessageBox>

MediaManagerXml::MediaManagerXml():currentCinema(nullptr){}

void MediaManagerXml::setCurrentCinema(Cinema* newCinema){
    currentCinema=newCinema;
}
Cinema*  MediaManagerXml::MediaManagerXml::getCurrentCinema() const{
    return currentCinema;
}
void MediaManagerXml::exportSessionToXml() {
    if(!currentCinema)  return;
    QDomDocument doc;
    QDomElement root = doc.createElement("Cinema");
    doc.appendChild(root);
    createSessionDocument(doc,root);
    xmlDocument = doc;
    saveDocument();
}

void MediaManagerXml::exportMediaListToXml(){
    QDomDocument doc;
    QDomElement mediaListElem = doc.createElement("MediaList");
    doc.appendChild(mediaListElem);
    createMediaListDocument(doc,mediaListElem);
    xmlDocument= doc;
    saveDocument();

}

void MediaManagerXml::createSessionDocument(QDomDocument& doc,QDomElement& root) {

    QDomElement nome = doc.createElement("Nome");
    nome.appendChild(doc.createTextNode(QString::fromStdString(currentCinema->getNomeCinema())));
    root.appendChild(nome);

    QDomElement copertina = doc.createElement("Copertina");
    copertina.appendChild(doc.createTextNode(QString::fromStdString(currentCinema->getCopertinaCinema())));
    root.appendChild(copertina);

    QDomElement mediaListElem = doc.createElement("MediaList");
    root.appendChild(mediaListElem);

    createMediaListDocument(doc,mediaListElem);
}

void MediaManagerXml::createMediaListDocument(QDomDocument& doc,QDomElement& root){
    
    XmlVisitor visitor(&doc);

    for (Media* media : currentCinema->getListaMedia()) {
        if (!media) continue;
        media->accept(&visitor);
        QDomElement mediaElem;

        mediaElem = visitor.getXmlElement();
        root.appendChild(mediaElem);
    }
}
void MediaManagerXml::saveDocument() {

    QString filePath = QFileDialog::getSaveFileName(nullptr,"Salva sessione XML", "", "XML Files (*.xml)");
    if (filePath.isEmpty()) return;

    if (!filePath.endsWith(".xml", Qt::CaseInsensitive)) {
        filePath += ".xml";
    }
    
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(nullptr, "Errore", "Impossibile aprire il file per la scrittura");
        return;
    }

    QTextStream stream(&file);
    xmlDocument.save(stream, 4); 
    file.close();
}

bool MediaManagerXml::importSessionFromXml(CinemaRepositoryJson& jsonManager) {
    QString filePath = QFileDialog::getOpenFileName(
        nullptr, "Apri sessione XML", "", "XML Files (*.xml)");
    if (filePath.isEmpty()) return false;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(nullptr, "Errore", "Impossibile aprire il file XML");
        return false;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        QMessageBox::warning(nullptr, "Errore", "Il file non è valido: errore di formattazione XML. Correggere e riprovare.");
        return false;
    }
    file.close();

    QDomElement root = doc.documentElement();
    if (root.tagName() != "Cinema") {
        QMessageBox::warning(nullptr, "Errore", "Struttura del file non valida: nodo <Cinema> mancante.");
        return false;
    }

    QDomElement nome = root.firstChildElement("Nome");
    QDomElement copertina = root.firstChildElement("Copertina");
    QDomElement mediaListElem = root.firstChildElement("MediaList");
    if (nome.isNull() || copertina.isNull()|| mediaListElem.isNull()) {
        QMessageBox::warning(nullptr, "Errore", "Il cinema non è valido: campo obbligatorio <Nome>/<Copertina>/<MediaList> assente.");
        return false;
    }

    jsonManager.saveCinemaInJson(new Cinema(nome.text().toStdString(), copertina.text().toStdString()));
    
    if (mediaListElem.isNull()) {
        QMessageBox::information(nullptr, "Info", "Cinema importato senza contenuti multimediali.");
        return true;
    }

    QDomElement mediaElem = mediaListElem.firstChildElement();

    importMediaListFromXml(mediaElem,jsonManager,nome.text().toStdString());
    return true;
}


void MediaManagerXml::importMediaListFromXml(QDomElement& mediaElem,CinemaRepositoryJson& jsonManager,const string& cinemaName){  
    list<Media*> supportList; /*la lista serve solo per permettere a trailer (risp puntata) di trovare il film riferito (risp podcast riferito), 
    altrimenti non vengono costruiti i Trailer (risp puntate). Non era possibile usare la lista di currentCinema perchè currentCinema in alcuni casi è null*/
    unsigned int errors =0;
    while (!mediaElem.isNull()) {
        QString tipo = mediaElem.tagName();
        if (tipo=="Film") {
            Film* fd = XmlVisitor::fromXmlFilmElement(mediaElem,errors);
            supportList.push_back(fd);
            jsonManager.saveMediaInJson(fd,QString::fromStdString(cinemaName));
        }else if (tipo=="Trailer") {
            Trailer* td = XmlVisitor::fromXmlTrailerElement(mediaElem,supportList);
            jsonManager.saveMediaInJson(td,QString::fromStdString(cinemaName));
        }else if (tipo=="Inserzione") {
            Inserzione* id = XmlVisitor::fromXmlInserzioneElement(mediaElem);
            jsonManager.saveMediaInJson(id,QString::fromStdString(cinemaName));
        }else if (tipo=="Podcast") {
            Podcast* pdd = XmlVisitor::fromXmlPodcastElement(mediaElem);
            supportList.push_back(pdd);
            jsonManager.saveMediaInJson(pdd,QString::fromStdString(cinemaName));
        } else if (tipo=="Puntata") {
            Puntata* pd = XmlVisitor::fromXmlPuntataElement(mediaElem,supportList);
            jsonManager.saveMediaInJson(pd,QString::fromStdString(cinemaName));
        }else {
            errors++;
        }
        mediaElem = mediaElem.nextSiblingElement();
    }

    if(errors)
         QMessageBox::information(nullptr, "Info", QString::number(errors) + " media non sono stati importati correttamente");
    qDebug() << "esco da importMediaListFromXml"; 
}
bool MediaManagerXml::importMediaListFromXml(CinemaRepositoryJson& jsonManager){
    if(!currentCinema) return false;
    QString filePath = QFileDialog::getOpenFileName(
    nullptr, "Apri sessione XML", "", "XML Files (*.xml)");
    if (filePath.isEmpty()) return false;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(nullptr, "Errore", "Impossibile aprire il file XML");
        return false;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        QMessageBox::warning(nullptr, "Errore", "Il file non è valido: errore di formattazione XML. Correggere e riprovare.");
        return false;
    }
    file.close();

    QDomElement mediaListElem = doc.documentElement();
    if (mediaListElem.tagName() != "MediaList") {
        QMessageBox::warning(nullptr, "Errore", "Struttura del file non valida: nodo <MediaList> mancante.");
        return false;
    }

    if (mediaListElem.isNull()) {
        QMessageBox::information(nullptr, "Info", "Nessun contenturo multimediale importato");
        return true;
    }

    QDomElement mediaElem = mediaListElem.firstChildElement();
    importMediaListFromXml(mediaElem,jsonManager,currentCinema->getNomeCinema());
    return true;
} 