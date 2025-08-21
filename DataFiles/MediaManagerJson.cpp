#include "MediaManagerJson.h"
#include <QDebug>
#include <QFile>
#include <QJsonArray>

MediaManagerJson::MediaManagerJson(const QString &basePath)
    : m_basePath(basePath) {}


void MediaManagerJson::loadCommonFields(MediaData &data, const QJsonObject &obj){
    data.titolo = obj["titolo"].toString();
    data.autore = obj["autore"].toString();
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

    QString s1 = obj["dataInizioRilascio"].toString();         
    data.dataInizioRilascio = QDate::fromString(s1, "yyyy-MM-dd");
    QString s2 = obj["dataFineRilascio"].toString();         
    data.dataFineRilascio = QDate::fromString(s2, "yyyy-MM-dd");
    data.tipologia = obj["tipologia"].toString();
}

void MediaManagerJson::saveCommonFields(const MediaData &data, QJsonObject &obj){
    obj["titolo"] = data.titolo;
    obj["autore"] = data.autore;
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

    obj["dataInizioRilascio"] = data.dataInizioRilascio.toString("yyyy-MM-dd");
    obj["dataFineRilascio"] = data.dataFineRilascio.toString("yyyy-MM-dd");

    obj["tipologia"] = data.tipologia;

}

// FILM
QList<FilmData*> MediaManagerJson::loadFilms() {
    QList<FilmData*> films;
    QJsonDocument doc = loadJsonFile("media.json");
    if (!doc.isArray()) return films;

    
    for (const auto &val : doc.array()) {
        
        QJsonObject obj = val.toObject();
        FilmData* film = new FilmData;

        loadCommonFields(*film, obj);

        // generi (vector<Genere>)
        QJsonArray arrayGeneri = obj["genere"].toArray();
        for (const auto &g : arrayGeneri) {
            film->genere.push_back(static_cast<Genere>(g.toInt()));
        }

        film->casaDiProduzione = obj["casaDiProduzione"].toString();
        film->nPostCredit = obj["nPostCredit"].toInt();
        film->costoBiglietto = obj["costoBiglietto"].toDouble();

        film->target = static_cast<Classificazione>(obj["target"].toInt());
        for (const QJsonValue &v : obj["attoriPrincipali"].toArray())
        film->attoriPrincipali.push_back(v.toString());

        films.append(film);
    }
    return films;
}

void MediaManagerJson::saveFilm(FilmData* film) {
    QList<FilmData*> films = loadFilms(); // carica quello che c'è
    films.append(film);

    QJsonArray array;
    for (const FilmData* f : films) {
        QJsonObject obj;
        saveCommonFields(*f, obj);

        QJsonArray arrayGeneri;
        for (Genere g : f->genere) {
            arrayGeneri.append(static_cast<int>(g));
        }
        obj["genere"] = arrayGeneri;

        obj["casaDiProduzione"] = f->casaDiProduzione;
        obj["nPostCredit"] = static_cast<int>(f->nPostCredit);
        obj["costoBiglietto"] = f->costoBiglietto;

        obj["target"] = static_cast<int>(f->target);

        QJsonArray arrayAttori;
        for (const QString& a : f->attoriPrincipali)
            arrayAttori.append(a);
        obj["attoriPrincipali"] = arrayAttori;

        array.append(obj);
    }

    saveJsonFile("media.json", QJsonDocument(array));
}

// TRAILER
QList<TrailerData*>MediaManagerJson::loadTrailers() {
    QList<TrailerData*> trailers;
    QJsonDocument doc = loadJsonFile("media.json");
    if (!doc.isArray()) return trailers;

    
    for (const auto &val : doc.array()) {
        
        QJsonObject obj = val.toObject();
        TrailerData* trailer = new TrailerData;

        loadCommonFields(*trailer, obj);

        trailer->nProiezioniGiornaliere = obj["nProiezioniGiornaliere"].toInt();
        trailer->filmAssociato = obj["filmAssociato"].toString();
        trailer->autoreFilmAssociato = obj["autoreFilmAssociato"].toString();
        
        trailers.append(trailer);
    }
    return trailers;
}

void MediaManagerJson::saveTrailer(TrailerData* trailer) {
    QList<TrailerData*> trailers = loadTrailers(); 
    trailers.append(trailer);

    QJsonArray array;
    for (const TrailerData* t : trailers) {
        QJsonObject obj;
        saveCommonFields(*t, obj);

        obj["nProiezioniGiornaliere"] = static_cast<int>(t->nProiezioniGiornaliere);
        obj["filmAssociato"] = t->filmAssociato;
        obj["autoreFilmAssociato"] = t->autoreFilmAssociato;

        array.append(obj);
    }

    saveJsonFile("media.json", QJsonDocument(array));
}

//PODCAST
QList<PodcastData*> MediaManagerJson::loadPodcast() {
    QList<PodcastData*> podcasts;
    QJsonDocument doc = loadJsonFile("media.json");
    if (!doc.isArray()) return podcasts;

    
    for (const auto &val : doc.array()) {
        
        QJsonObject obj = val.toObject();
        PodcastData* podcast = new PodcastData;

        loadCommonFields(*podcast, obj);

        podcast->conduttore = obj["conduttore"].toString();

        podcasts.append(podcast);
    }
    return podcasts;
}

void MediaManagerJson::savePodcast(PodcastData* podcast) {
    QList<PodcastData*> podcasts = loadPodcast(); 
    podcasts.append(podcast);

    QJsonArray array;
    for (const PodcastData* p : podcasts) {
        QJsonObject obj;
        saveCommonFields(*p, obj);

        obj["conduttore"] = p->conduttore;

        array.append(obj);
    }

    saveJsonFile("media.json", QJsonDocument(array));
}

//PUNTATA
QList<PuntataData*> MediaManagerJson::loadPuntate() {
    QList<PuntataData*> puntate;
    QJsonDocument doc = loadJsonFile("media.json");
    if (!doc.isArray()) return puntate;

    
    for (const auto &val : doc.array()) {
        
        QJsonObject obj = val.toObject();
        PuntataData* puntata = new PuntataData;

        loadCommonFields(*puntata, obj);

        puntata->numeroPubblicita = obj["numeroPubblicita"].toInt();
        puntata->autorePodcastAssociato = obj["autorePodcastAssociato"].toString();
        puntata->podcastAssociato = obj["podcastAssociato"].toString();
        
        for (const QJsonValue &v : obj["ospiti"].toArray())
        puntata->ospiti.push_back(v.toString());

        puntate.append(puntata);
    }
    return puntate;
}

void MediaManagerJson::savePuntata(PuntataData* puntata) {
    QList<PuntataData*> puntate = loadPuntate(); 
    puntate.append(puntata);

    QJsonArray array;
    for (const PuntataData* p : puntate) {
        QJsonObject obj;
        saveCommonFields(*p, obj);

        obj["numeroPubblicita"] = static_cast<int>(p->numeroPubblicita);
        obj["autorePodcastAssociato"] = p->autorePodcastAssociato;
        obj["podcastAssociato"] = p->podcastAssociato;

        QJsonArray arrayOspiti;
        for (const QString& o : p->ospiti)
            arrayOspiti.append(o);
        obj["ospiti"] = arrayOspiti;

        array.append(obj);
    }

    saveJsonFile("media.json", QJsonDocument(array));
}

//INSERZIONE
QList<InserzioniData*> MediaManagerJson::loadInserzioni() {
    QList<InserzioniData*> inserzioni;
    QJsonDocument doc = loadJsonFile("media.json");
    if (!doc.isArray()) return inserzioni;

    for (const auto &val : doc.array()) {
        
        QJsonObject obj = val.toObject();
        InserzioniData* inserzione = new InserzioniData;

        loadCommonFields(*inserzione, obj);

        inserzione->target = static_cast<Classificazione>(obj["target"].toInt());
        inserzione->aziendaInserzionista = obj["aziendaInserzionista"].toString();
        inserzione->costoFissoProiezione = obj["costoFissoProiezione"].toDouble();

        QJsonArray arrayFasceOrarie = obj["fasceOrarie"].toArray();
        for (const auto &f : arrayFasceOrarie) {
            inserzione->fasceOrarie.push_back(static_cast<FasciaOraria>(f.toInt()));
        }

        inserzioni.append(inserzione);
    }
    return inserzioni;
}

void MediaManagerJson::saveInserzione(InserzioniData* inserzione) {
    QList<InserzioniData*> inserzioni = loadInserzioni(); 
    inserzioni.append(inserzione);

    QJsonArray array;
    for (const InserzioniData* i : inserzioni) {
        QJsonObject obj;
        saveCommonFields(*i, obj);

        obj["target"] = static_cast<int>(i->target);
        obj["aziendaInserzionista"] = i->aziendaInserzionista;
        obj["costoFissoProiezione"] = static_cast<double>(i->costoFissoProiezione);

        QJsonArray arrayFasceOrarie;
        for (FasciaOraria f : i->fasceOrarie) {
            arrayFasceOrarie.append(static_cast<int>(f));
        }
        obj["fasceOrarie"] = arrayFasceOrarie;

        array.append(obj);
    }

    saveJsonFile("media.json", QJsonDocument(array));
}

QList<MediaData*> MediaManagerJson::loadAll() {
    QList<MediaData*> all;

    for (FilmData* f : loadFilms())
        all.append(f);

    for (TrailerData* t : loadTrailers())
        all.append(t);

    for (PodcastData* p : loadPodcast())
        all.append(p);

    for (PuntataData* pt : loadPuntate())
        all.append(pt);

    for (InserzioniData* i : loadInserzioni())
        all.append(i);

    return all;
}



// HELPERS 
void MediaManagerJson::saveJsonFile(const QString &fileName, const QJsonDocument &doc) {
    QDir dir(m_basePath);                       // cartella base esistente
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
