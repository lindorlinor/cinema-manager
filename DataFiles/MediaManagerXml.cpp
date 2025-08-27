#include "MediaManagerXml.h"
#include <QFile>
#include <QFileDialog>
#include <QDomElement>
#include <QMessageBox>

MediaManagerXml::MediaManagerXml(){xmlDocument = QDomDocument("Cinema");}

void MediaManagerXml::setCinemaName(const QString& name) {cinemaName = name;}

void MediaManagerXml::setCinemaCover(const QString& cover) {cinemaCover = cover;}

void MediaManagerXml::setCinemaMediaList(const QList<Media*>& list) {mediaList = list;}

void MediaManagerXml::exportSessionToXml() {
    createDocument();
    saveDocument();
}

QDomDocument MediaManagerXml::createDocument() {
    QDomDocument doc("Cinema");

    QDomElement root = doc.createElement("Cinema");
    doc.appendChild(root);

    QDomElement nome = doc.createElement("Nome");
    nome.appendChild(doc.createTextNode(cinemaName));
    root.appendChild(nome);

    QDomElement copertina = doc.createElement("Copertina");
    copertina.appendChild(doc.createTextNode(cinemaCover));
    root.appendChild(copertina);

    QDomElement mediaListElem = doc.createElement("MediaList");
    root.appendChild(mediaListElem);

    for (Media* media : mediaList) {
        if (!media) continue;

        QDomElement mediaElem;

        if (Film* f = dynamic_cast<Film*>(media)) {
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

        mediaListElem.appendChild(mediaElem);
    }

    xmlDocument = doc;
    return xmlDocument;
}

void MediaManagerXml::saveDocument() {

    QString filePath = QFileDialog::getSaveFileName(nullptr,
        "Salva sessione XML", "", "XML Files (*.xml)");
    if (filePath.isEmpty()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(nullptr, "Errore", "Impossibile aprire il file per la scrittura");
        return;
    }

    QTextStream stream(&file);
    xmlDocument.save(stream, 4); // 4 spazi di indentazione
    file.close();
}

