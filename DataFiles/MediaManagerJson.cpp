#include "MediaManagerJson.h"
#include <QDebug>
#include <QFile>
#include <QJsonArray>

MediaManagerJson::MediaManagerJson(const QString &basePath)
    : m_basePath(basePath) {}

// FILM
QList<FilmData> MediaManagerJson::loadFilms() {
    QList<FilmData> films;
    QJsonDocument doc = loadJsonFile("films.json");
    if (!doc.isArray()) return films;

    for (const auto &val : doc.array()) {
        QJsonObject obj = val.toObject();
        FilmData film;
        film.titolo = obj["titolo"].toString();
        film.casaDiProduzione = obj["casaDiProduzione"].toString();
        film.nPostCredit = obj["nPostCredit"].toInt();
        film.costoBiglietto = obj["costoBiglietto"].toDouble();

        // generi (vector<Genere>)
        QJsonArray arrayGeneri = obj["genere"].toArray();
        for (const auto &g : arrayGeneri) {
            film.genere.push_back(static_cast<Genere>(g.toInt()));
        }

        for (const QJsonValue &v : obj["attoriPrincipali"].toArray())
        film.attoriPrincipali.push_back(v.toString());


        films.append(film);
    }
    return films;
}

void MediaManagerJson::saveFilm(const FilmData &film) {
    QList<FilmData> films = loadFilms(); // carica quello che c'è
    films.append(film);

    QJsonArray array;
    for (const FilmData &f : films) {
        QJsonObject obj;
        obj["titolo"] = f.titolo;
        obj["casaDiProduzione"] = f.casaDiProduzione;
        obj["nPostCredit"] = static_cast<int>(f.nPostCredit);
        obj["costoBiglietto"] = f.costoBiglietto;

        // generi (vector<Genere> -> QJsonArray)
        QJsonArray arrayGeneri;
        for (Genere g : f.genere) {
            arrayGeneri.append(static_cast<int>(g));
        }
        obj["genere"] = arrayGeneri;

        QJsonArray arrayAttori;
        for (const QString& a : f.attoriPrincipali)
            arrayAttori.append(a);
        obj["attoriPrincipali"] = arrayAttori;


        array.append(obj);
    }

    saveJsonFile("films.json", QJsonDocument(array));
}



// HELPERS 
void MediaManagerJson::saveJsonFile(const QString &fileName, const QJsonDocument &doc) {
    QDir dir(m_basePath);                    // cartella base esistente
    QString filePath = dir.filePath(fileName);  // combina basePath + fileName correttamente

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Impossibile scrivere" << filePath;
        return;
    }

    file.write(doc.toJson());
    file.close();
    qDebug() << "File JSON creato o sovrascritto:" << filePath;
    qDebug() << "Current working directory:" << QDir::currentPath();
}


QJsonDocument MediaManagerJson::loadJsonFile(const QString &fileName) {
    QDir dir(m_basePath);
    QString filePath = dir.filePath(fileName);

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Impossibile aprire" << filePath;
        return QJsonDocument();
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    return doc;
}

