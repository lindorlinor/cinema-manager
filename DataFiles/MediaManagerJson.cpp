#include "MediaManagerJson.h"
#include <QDebug>
#include <QFile>
#include <QJsonArray>

MediaManagerJson::MediaManagerJson(const QString &basePath)
    : m_basePath(basePath) {}


void MediaManagerJson::loadCommonFields(MediaData &data, const QJsonObject &obj){
    data.titolo = obj["titolo"].toString();
    data.descrizione = obj["descrizione"].toString();

    data.durataMinuti = obj["durataMinuti"].toInt();
    data.formato = static_cast<Formato>(obj["formato"].toInt());
    data.risoluzione = static_cast<Risoluzione>(obj["risoluzione"].toInt());
    data.path = obj["path"].toString();

    data.lingueDisponibili.clear();
    for (const QJsonValue &v : obj["lingueDisponibili"].toArray()) {
        data.lingueDisponibili.push_back(static_cast<Lingua>(v.toInt()));
    }

    data.sottotitoliDisponibili.clear();
    for (const QJsonValue &v : obj["sottotitoliDisponibili"].toArray()) {
        data.sottotitoliDisponibili.push_back(static_cast<Lingua>(v.toInt()));
    }
}

void MediaManagerJson::saveCommonFields(const MediaData &data, QJsonObject &obj){
    obj["titolo"] = data.titolo;
    obj["descrizione"] = data.descrizione;
    obj["durataMinuti"] = static_cast<int>(data.durataMinuti);
    obj["formato"] = static_cast<int>(data.formato);
    obj["risoluzione"] = static_cast<int>(data.risoluzione);
    obj["path"] = data.path;

    QJsonArray arrayLingue;
    for (Lingua l : data.lingueDisponibili) {
        arrayLingue.append(static_cast<int>(l));  
    }
    obj["lingueDisponibili"] = arrayLingue;

    QJsonArray arraySottotitoli;
    for (Lingua l : data.sottotitoliDisponibili) {
        arraySottotitoli.append(static_cast<int>(l));  
    }
    obj["sottotitoliDisponibili"] = arraySottotitoli;

}

// FILM
QList<FilmData> MediaManagerJson::loadFilms() {
    QList<FilmData> films;
    QJsonDocument doc = loadJsonFile("films.json");
    if (!doc.isArray()) return films;

    
    for (const auto &val : doc.array()) {
        
        QJsonObject obj = val.toObject();
        FilmData film;

        loadCommonFields(film, obj);

        QString s1 = obj["dataInizioRilascio"].toString();         
        film.dataInizioRilascio = QDate::fromString(s1, "yyyy-MM-dd");
        QString s2 = obj["dataFineRilascio"].toString();         
        film.dataFineRilascio = QDate::fromString(s2, "yyyy-MM-dd");

        // generi (vector<Genere>)
        QJsonArray arrayGeneri = obj["genere"].toArray();
        for (const auto &g : arrayGeneri) {
            film.genere.push_back(static_cast<Genere>(g.toInt()));
        }

        film.casaDiProduzione = obj["casaDiProduzione"].toString();
        film.nPostCredit = obj["nPostCredit"].toInt();
        film.costoBiglietto = obj["costoBiglietto"].toDouble();

        film.target = static_cast<Classificazione>(obj["target"].toInt());
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
        saveCommonFields(f, obj);

        obj["dataInizioRilascio"] = f.dataInizioRilascio.toString("yyyy-MM-dd");
        obj["dataFineRilascio"] = f.dataFineRilascio.toString("yyyy-MM-dd");

        // generi (vector<Genere> -> QJsonArray)
        QJsonArray arrayGeneri;
        for (Genere g : f.genere) {
            arrayGeneri.append(static_cast<int>(g));
        }
        obj["genere"] = arrayGeneri;

        obj["casaDiProduzione"] = f.casaDiProduzione;
        obj["nPostCredit"] = static_cast<int>(f.nPostCredit);
        obj["costoBiglietto"] = f.costoBiglietto;

        obj["target"] = static_cast<int>(f.target);

        QJsonArray arrayAttori;
        for (const QString& a : f.attoriPrincipali)
            arrayAttori.append(a);
        obj["attoriPrincipali"] = arrayAttori;

        array.append(obj);
    }

    saveJsonFile("films.json", QJsonDocument(array));
}

//PODCAST
QList<PodcastData> MediaManagerJson::loadPodcast() {
    QList<PodcastData> podcasts;
    QJsonDocument doc = loadJsonFile("poadcasts.json");
    if (!doc.isArray()) return podcasts;

    
    for (const auto &val : doc.array()) {
        
        QJsonObject obj = val.toObject();
        PodcastData podcast;

        loadCommonFields(podcast, obj);

        podcast.conduttore = obj["conduttore"].toString();

        podcasts.append(podcast);
    }
    return podcasts;
}

void MediaManagerJson::savePodcast(const PodcastData &podcast) {
    QList<PodcastData> podcasts = loadPodcast(); 
    podcasts.append(podcast);

    QJsonArray array;
    for (const PodcastData &p : podcasts) {
        QJsonObject obj;
        saveCommonFields(p, obj);

        obj["conduttore"] = p.conduttore;

        array.append(obj);
    }

    saveJsonFile("podcasts.json", QJsonDocument(array));
}

//INSERZIONE
QList<InserzioniData> MediaManagerJson::loadInserzioni() {
    QList<InserzioniData> inserzioni;
    QJsonDocument doc = loadJsonFile("inserzioni.json");
    if (!doc.isArray()) return inserzioni;

    
    for (const auto &val : doc.array()) {
        
        QJsonObject obj = val.toObject();
        InserzioniData inserzione;

        loadCommonFields(inserzione, obj);

        QString s1 = obj["dataInizioRilascio"].toString();         
        inserzione.dataInizioRilascio = QDate::fromString(s1, "yyyy-MM-dd");
        QString s2 = obj["dataFineRilascio"].toString();         
        inserzione.dataFineRilascio = QDate::fromString(s2, "yyyy-MM-dd");

        inserzione.target = static_cast<Classificazione>(obj["target"].toInt());
        inserzione.aziendaInserzionista = obj["aziendaInserzionista"].toString();
        inserzione.costoFissoProiezione = obj["costoFissoProiezione"].toDouble();

        QJsonArray arrayFasceOrarie = obj["fasceOrarie"].toArray();
        for (const auto &f : arrayFasceOrarie) {
            inserzione.fasceOrarie.push_back(static_cast<FasciaOraria>(f.toInt()));
        }

        inserzioni.append(inserzione);
    }
    return inserzioni;
}

void MediaManagerJson::saveInserzione(const InserzioniData &inserzione) {
    QList<InserzioniData> inserzioni = loadInserzioni(); 
    inserzioni.append(inserzione);

    QJsonArray array;
    for (const InserzioniData &i : inserzioni) {
        QJsonObject obj;
        saveCommonFields(i, obj);

        obj["dataInizioRilascio"] = i.dataInizioRilascio.toString("yyyy-MM-dd");
        obj["dataFineRilascio"] = i.dataFineRilascio.toString("yyyy-MM-dd");

        obj["target"] = static_cast<int>(i.target);
        obj["aziendaInserzionista"] = i.aziendaInserzionista;
        obj["costoFissoProiezione"] = static_cast<double>(i.costoFissoProiezione);

        QJsonArray arrayFasceOrarie;
        for (FasciaOraria f : i.fasceOrarie) {
            arrayFasceOrarie.append(static_cast<int>(f));
        }
        obj["fasceOrarie"] = arrayFasceOrarie;

        array.append(obj);
    }

    saveJsonFile("inserzioni.json", QJsonDocument(array));
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

