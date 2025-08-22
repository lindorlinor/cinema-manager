#include "MediaManagerJson.h"
#include <QDebug>
#include <QFile>
#include <QJsonArray>


MediaManagerJson::MediaManagerJson(const QString &basePath, QObject *parent)
: QObject(parent), m_basePath(basePath)  {}

MediaManagerJson::~MediaManagerJson() {
    clearMediaList();
}

void MediaManagerJson::clearMediaList() {
    qDeleteAll(m_mediaList);  // cancella tutti gli oggetti puntati dai puntatori
    m_mediaList.clear();      // svuota la lista
}


// LOAD FILE //

void MediaManagerJson::loadFilms() {
    if (!m_mediaList.empty()) return; 
    QList<FilmData*> filmsData = loadFilmsData();
    for (FilmData* data : filmsData) {
        m_mediaList.append(createFilmFromData(*data));
        delete data;
    }
}

void MediaManagerJson::loadTrailers() {
    if (!m_mediaList.empty()) return; 
    QList<TrailerData*> trailersData = loadTrailersData();
    for (TrailerData* data : trailersData) {
        m_mediaList.append(createTrailerFromData(*data));
        delete data;
    }
}

void MediaManagerJson::loadInserzioni() {
    if (!m_mediaList.empty()) return; 
    QList<InserzioniData*> inserzioniData = loadInserzioniData();
    for (InserzioniData* data : inserzioniData) {
        m_mediaList.append(createInserzioneFromData(*data));
        delete data;
    }
}

void MediaManagerJson::loadPodcast() {
    if (!m_mediaList.empty()) return; 
    QList<PodcastData*> podcasdata = loadPodcastData();
    for (PodcastData* data : podcasdata) {
        m_mediaList.append(createPodcastFromData(*data));
        delete data;
    }
}

void MediaManagerJson::loadPuntate() {
    if (!m_mediaList.empty()) return; 
    QList<PuntataData*> puntataData = loadPuntateData();
    for (PuntataData* data : puntataData) {
        m_mediaList.append(createPuntataFromData(*data));
        delete data;
    }
}

void MediaManagerJson::loadAll() {

    loadFilms();
    loadTrailers();
    loadInserzioni();
    loadPodcast();
    loadPuntate();
}

void MediaManagerJson::remove(Media* media) {
    if (!media) return;

    m_mediaList.removeOne(media);
    delete media; // libera memoria

    QList<MediaData*> mediaData = loadAllData();
    for(auto it = mediaData.begin(); it != mediaData.end(); ) {
        if((*it)->titolo == QString::fromStdString(media->getTitolo()) &&
           (*it)->autore == QString::fromStdString(media->getAutore())) {
            it = mediaData.erase(it); // cancella solo questo elemento
        } else {
            ++it;
        }
    }

    // salva tutta la lista aggiornata
    for(MediaData* m : mediaData) {
        saveAll(m);
        delete m; 
    }
}

// TROVA MEDIA PER RIFERIMENTO A PODCAST O FILM //
Media* MediaManagerJson::findMedia(const QString& titolo, const QString& autore, const QString& tipo){
    for(Media* m : m_mediaList){
        if(m->getAutore() == autore.toStdString() && m->getTitolo() == titolo.toStdString())
            if( (tipo =="trailer" && dynamic_cast<Film*>(m) ) || (tipo == "puntata" && dynamic_cast<Podcast*>(m)))
                return m;
    }
    return nullptr; //non ha trovato niente
}

// CONVERTE LA DATA IN CHRONO //
// conversione QDate -> std::chrono::year_month_day
year_month_day MediaManagerJson::convertDate(const QDate& data){
    year_month_day dataConvertita{
        year{data.year()},
        month{static_cast<unsigned>(data.month())},
        day{static_cast<unsigned>(data.day())}
    };
    return dataConvertita;
}

// CREATE MEDIA //

Film* MediaManagerJson::createFilmFromData(const FilmData& data) {

    Film* film = new Film(data.titolo.toStdString(),
                          data.descrizione.toStdString(),
                          convertDate(data.dataInizioRilascio),
                          convertDate(data.dataFineRilascio),
                          data.durataMinuti,
                          data.formato,
                          data.risoluzione,
                          data.nPostCredit,
                          data.costoBiglietto,
                          data.casaDiProduzione.toStdString(),
                          data.autore.toStdString(),
                          data.path.toStdString(),
                          data.target);
    
    for (const QString& a : data.attoriPrincipali) {
        film->aggiungiAttore(a.toStdString());
    }
    
    return film;
}


Trailer* MediaManagerJson::createTrailerFromData (const TrailerData& data) {

    Trailer* trailer = new Trailer(data.titolo.toStdString(),
                          data.descrizione.toStdString(),
                          convertDate(data.dataInizioRilascio),
                          convertDate(data.dataFineRilascio),
                          data.durataMinuti,
                          data.formato,
                          data.risoluzione,
                          data.nProiezioniGiornaliere,
                          static_cast<Film*>(findMedia(data.titolo, data.autore,data.tipologia)),
                          data.autore.toStdString(),
                          data.path.toStdString());

    for (const Lingua& l : data.lingueDisponibili) {
        trailer->aggiungiLingua(l);
    }

    for (const Lingua& l : data.sottotitoliDisponibili) {
        trailer->aggiungiSottotitolo(l);
    }
    
    return trailer;
}

Inserzione* MediaManagerJson::createInserzioneFromData(const InserzioniData& data) {

    Inserzione* inserzione =    new Inserzione(data.titolo.toStdString(),
                                data.descrizione.toStdString(),
                                convertDate(data.dataInizioRilascio),
                                convertDate(data.dataFineRilascio),
                                data.durataMinuti,
                                data.formato,
                                data.risoluzione,
                                data.nProiezioniGiornaliere,
                                data.target,
                                data.costoFissoProiezione,
                                data.aziendaInserzionista.toStdString(),
                                data.autore.toStdString(),
                                data.path.toStdString());

    for (const FasciaOraria& o : data.fasceOrarie) {
        inserzione->aggiungiFasciaOraria(o);
    }
    
    for (const Lingua& l : data.lingueDisponibili) {
        inserzione->aggiungiLingua(l);
    }

    for (const Lingua& l : data.sottotitoliDisponibili) {
        inserzione->aggiungiSottotitolo(l);
    }
    
    return inserzione;
}

Podcast* MediaManagerJson::createPodcastFromData(const PodcastData& data) {

    Podcast* podcast =      new Podcast(data.titolo.toStdString(),
                            data.descrizione.toStdString(),
                            data.formato,
                            data.risoluzione,
                            data.autore.toStdString(),
                            data.path.toStdString());

    for (const Lingua& l : data.lingueDisponibili) {
        podcast->aggiungiLingua(l);
    }

    for (const Lingua& l : data.sottotitoliDisponibili) {
        podcast->aggiungiSottotitolo(l);
    }
    
    return podcast;
}

Puntata* MediaManagerJson::createPuntataFromData(const PuntataData& data) {

    Puntata* puntata = new Puntata(data.titolo.toStdString(),
                          data.descrizione.toStdString(),
                          convertDate(data.dataInizioRilascio),
                          convertDate(data.dataFineRilascio),
                          data.durataMinuti,
                          static_cast<Podcast*>(findMedia(data.titolo, data.autore,data.tipologia)),
                          data.numeroPubblicita,
                          data.autore.toStdString(),
                          data.path.toStdString());
    
    for (const QString& o : data.ospiti) {
        puntata->aggiungiOspite(o.toStdString());
    }

    return puntata;
}














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

void MediaManagerJson::saveAll(MediaData* media){
    if(!media) return;

    if(media->tipologia=="film") saveFilm(static_cast<FilmData*>(media));
    else if(media->tipologia=="trailer") saveTrailer(static_cast<TrailerData*>(media));
    else if(media->tipologia=="inserzione") saveInserzione(static_cast<InserzioniData*>(media));
    else if(media->tipologia=="podcast") savePodcast(static_cast<PodcastData*>(media));
    else if(media->tipologia=="puntata") savePuntata(static_cast<PuntataData*>(media));
}

// FILM
QList<FilmData*> MediaManagerJson::loadFilmsData() {
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
    if(!film) return;

    QList<FilmData*> films = loadFilmsData(); // carica quello che c'è
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
QList<TrailerData*>MediaManagerJson::loadTrailersData() {
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
    if(!trailer) return;
    QList<TrailerData*> trailers = loadTrailersData(); 
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
QList<PodcastData*> MediaManagerJson::loadPodcastData() {
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
    if(!podcast) return;

    QList<PodcastData*> podcasts = loadPodcastData(); 
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
QList<PuntataData*> MediaManagerJson::loadPuntateData() {
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
    if(!puntata) return;

    QList<PuntataData*> puntate = loadPuntateData(); 
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
QList<InserzioniData*> MediaManagerJson::loadInserzioniData() {
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
    if(!inserzione) return;

    QList<InserzioniData*> inserzioni = loadInserzioniData(); 
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

QList<MediaData*> MediaManagerJson::loadAllData() {
    QList<MediaData*> all;

    for (FilmData* f : loadFilmsData())
        all.append(f);

    for (TrailerData* t : loadTrailersData())
        all.append(t);

    for (PodcastData* p : loadPodcastData())
        all.append(p);

    for (PuntataData* pt : loadPuntateData())
        all.append(pt);

    for (InserzioniData* i : loadInserzioniData())
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
