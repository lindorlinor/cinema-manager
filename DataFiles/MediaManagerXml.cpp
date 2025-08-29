#include "MediaManagerXml.h"
#include "XmlVisitor.h"
#include "ConverterXml.h"
#include <QFile>
#include <QFileDialog>
#include <QDomElement>
#include <QMessageBox>

MediaManagerXml::MediaManagerXml(){}

void MediaManagerXml::setCinemaName(const QString& name) {cinemaName = name;}

void MediaManagerXml::setCinemaCover(const QString& cover) {cinemaCover = cover;}

void MediaManagerXml::setCinemaMediaList(const QList<Media*>& list) {mediaList = list;}

void MediaManagerXml::exportSessionToXml() {
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
    nome.appendChild(doc.createTextNode(cinemaName));
    root.appendChild(nome);

    QDomElement copertina = doc.createElement("Copertina");
    copertina.appendChild(doc.createTextNode(cinemaCover));
    root.appendChild(copertina);

    QDomElement mediaListElem = doc.createElement("MediaList");
    root.appendChild(mediaListElem);

    createMediaListDocument(doc,mediaListElem);
}

void MediaManagerXml::createMediaListDocument(QDomDocument& doc,QDomElement& root){
    
    XmlVisitor visitor(doc);

    for (Media* media : mediaList) {
        if (!media) continue;
        media->accept(&visitor);
        QDomElement mediaElem;

        mediaElem = visitor.getXmlElement();
        /* if (Film* f = dynamic_cast<Film*>(media)) {
            mediaElem = ConverterXml::toXmlElement(f, doc);
        } else if (Trailer* t = dynamic_cast<Trailer*>(media)) {
            mediaElem = ConverterXml::toXmlElement(t, doc);
        } else if (Podcast* p = dynamic_cast<Podcast*>(media)) {
            mediaElem = ConverterXml::toXmlElement(p, doc);
        } else if (Puntata* pt = dynamic_cast<Puntata*>(media)) {
            mediaElem = ConverterXml::toXmlElement(pt, doc);
        } else if (Inserzione* i = dynamic_cast<Inserzione*>(media)) {
            mediaElem = ConverterXml::toXmlElement(i, doc);
        } else {
            mediaElem = ConverterXml::toXmlElement(media, doc);
        }
 */
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

 bool MediaManagerXml::importSessionFromXml(MediaManagerJson& jsonManager) {
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

    CinemaData cinema;
    cinema.nomeCinema = nome.text();
    cinema.copertinaCinema = copertina.text();
    
    jsonManager.saveCinema(&cinema);

    if (mediaListElem.isNull()) {
        QMessageBox::information(nullptr, "Info", "Cinema importato senza contenuti multimediali.");
        return true;
    }

    QDomElement mediaElem = mediaListElem.firstChildElement();

    importMediaListFromXml(mediaElem,jsonManager,cinema.nomeCinema,cinema.copertinaCinema);
    return true;
}


void MediaManagerXml::importMediaListFromXml(QDomElement& mediaElem,MediaManagerJson& jsonManager,const QString& cinemaName, const QString& cinemaCover){
    unsigned int errors =0;
    while (!mediaElem.isNull()) {
        QString tipo = mediaElem.tagName();
        if (tipo=="Film") {
            FilmData* fd = new FilmData(ConverterXml::fromXmlFilmElement(mediaElem));
            fd->nomeCinema=cinemaName;
            fd->copertinaCinema=cinemaCover;
            jsonManager.saveMedia(fd);
        }else if (tipo=="Trailer") {
            TrailerData* td = new TrailerData(ConverterXml::fromXmlTrailerElement(mediaElem));
            td->nomeCinema=cinemaName;
            td->copertinaCinema=cinemaCover;
            jsonManager.saveMedia(td);
        }else if (tipo=="Inserzione") {
            InserzioneData* id = new InserzioneData(ConverterXml::fromXmlInserzioneElement(mediaElem));
            id->nomeCinema=cinemaName;
            id->copertinaCinema=cinemaCover;
            jsonManager.saveMedia(id);
        }else if (tipo=="Podcast") {
            PodcastData* pdd = new PodcastData(ConverterXml::fromXmlPodcastElement(mediaElem));
            pdd->nomeCinema=cinemaName;
            pdd->copertinaCinema=cinemaCover;
            jsonManager.saveMedia(pdd);
        } else if (tipo=="Puntata") {
            PuntataData* pd = new PuntataData(ConverterXml::fromXmlPuntataElement(mediaElem));
            pd->nomeCinema=cinemaName;
            pd->copertinaCinema=cinemaCover;
            jsonManager.saveMedia(pd);
        }else {
            errors++;
        }
        mediaElem = mediaElem.nextSiblingElement();
    }

    if(errors)
         QMessageBox::information(nullptr, "Info", errors+" media non sono stati importati.");

}
bool MediaManagerXml::importMediaListFromXml(MediaManagerJson& jsonManager){
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
    importMediaListFromXml(mediaElem,jsonManager,cinemaName,cinemaCover);
    return true;
} 