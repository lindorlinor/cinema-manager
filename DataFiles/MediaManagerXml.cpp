#include "MediaManagerXml.h"
#include "XmlVisitor.h"
#include <QFile>
#include <QFileDialog>
#include <QDomElement>
#include <QMessageBox>
#include <QDebug>

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

bool MediaManagerXml::importSessionFromXml(CinemaRepositoryJson& jsonManager){
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

/**
 * @brief Metodo di utilità per l'importazione dei media, richiamato da importSessionFromXml e importMediaListFromXml.
 * 
 * Questo metodo gestisce l'importazione dei media nei JSON. 
 * Quando è richiamato da importSessionFromXml, currentCinema è nullptr, perché l'importazione dei media non avviene all'interno di un cinema esistente.
 * Quando è richiamato da importMediaListFromXml, il metodo aggiorna anche la lista dei media del cinema corrente, permettendo il corretto aggiornamento della pagina.
 * 
 * @details La lista supportList serve solo come riferimento per Trailer e Puntata, permettendo loro di trovare i Film o Podcast associati.
 * In assenza di currentCinema, la lista del cinema non viene aggiornata, perché il JSON gestisce la creazione iniziale del cinema.
 * 
 * @param mediaElem L'elemento XML contenente i dati dei media.
 * @param jsonManager Riferimento al gestore JSON per salvare i media.
 * @param cinemaName Nome del cinema associato all'importazione.
 */

void MediaManagerXml::importMediaListFromXml(QDomElement& mediaElem, CinemaRepositoryJson& jsonManager, const string& cinemaName) {  
    list<Media*> supportList;  
    unsigned int errors = 0;

    while (!mediaElem.isNull()) {
        QString tipo = mediaElem.tagName(); 
        Media* ptrMedia = nullptr;

        if (tipo == "Film") {
            ptrMedia = XmlVisitor::fromXmlFilmElement(mediaElem, errors);
        } else if (tipo == "Trailer") {
            ptrMedia = XmlVisitor::fromXmlTrailerElement(mediaElem, currentCinema ? currentCinema->getListaMedia() : supportList);
        } else if (tipo == "Inserzione") {
            ptrMedia = XmlVisitor::fromXmlInserzioneElement(mediaElem);
        } else if (tipo == "Podcast") {
            ptrMedia = XmlVisitor::fromXmlPodcastElement(mediaElem);
        } else if (tipo == "Puntata") {
            ptrMedia = XmlVisitor::fromXmlPuntataElement(mediaElem, currentCinema ? currentCinema->getListaMedia() : supportList);
        } else {
            errors++;
        }

        if (ptrMedia) {
            if (currentCinema) {
                currentCinema->addMedia(ptrMedia); 
            } else if (tipo == "Film" || tipo=="Podcast") { //
                supportList.push_back(ptrMedia);
            }

            jsonManager.saveMediaInJson(ptrMedia, QString::fromStdString(cinemaName));
        }

        mediaElem = mediaElem.nextSiblingElement();
    }

    if (errors)
        QMessageBox::information(nullptr, "Info", QString::number(errors) + " media non sono stati importati correttamente");
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