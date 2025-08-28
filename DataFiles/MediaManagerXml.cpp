#include "MediaManagerXml.h"
#include "XmlVisitor.h"
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

