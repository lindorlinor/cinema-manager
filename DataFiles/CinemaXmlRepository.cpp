
#include "CinemaXmlRepository.h"
#include <QFile>
#include <QDir>
#include <QDomDocument>
#include <QXmlStreamReader>

CinemaXmlRepository::CinemaXmlRepository(const QString& basePath)
    : m_basePath(basePath) {}

bool CinemaXmlRepository::saveCinema(const Cinema& cinema) {
    QString filePath = QDir(m_basePath).filePath(cinema.nome + ".xml");

    QDomDocument doc;
    QDomElement root = doc.createElement("cinema");
    doc.appendChild(root);

    QDomElement nomeElem = doc.createElement("nome");
    nomeElem.appendChild(doc.createTextNode(cinema.nome));
    root.appendChild(nomeElem);

    QDomElement imgElem = doc.createElement("immagine");
    imgElem.appendChild(doc.createTextNode(cinema.imagePath));
    root.appendChild(imgElem);

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }
    QTextStream stream(&file);
    stream << doc.toString(4);
    file.close();
    return true;
}

QList<Cinema> CinemaXmlRepository::loadAllCinemas() {
    QList<Cinema> cinemas;
    QDir dir(m_basePath);
    QStringList xmlFiles = dir.entryList(QStringList() << "*.xml", QDir::Files);

    for (const QString &fileName : xmlFiles) {
        QFile file(dir.filePath(fileName));
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Impossibile aprire file:" << fileName;
            continue;
        }

        QXmlStreamReader xml(&file);
        Cinema c;
        c.xmlPath = file.fileName();
        while (!xml.atEnd() && !xml.hasError()) {
            xml.readNext();
            if (xml.isStartElement()) {
                if (xml.name().toString() == "nome") {
                    c.nome = xml.readElementText();
                } else if (xml.name().toString() == "immagine") {
                    c.imagePath = xml.readElementText();
                    break;
                }
            }
        }
        if (!c.nome.isEmpty())
            cinemas.append(c);
    }
    return cinemas;
}
