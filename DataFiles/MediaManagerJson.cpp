#include "MediaManagerJson.h"
#include "MediaUpdateVisitor.h"
#include <QDebug>
#include <QFile>
#include <QJsonArray>


MediaManagerJson::MediaManagerJson(QList<Media*>& mediaList, const QString &basePath, QObject *parent)
: QObject(parent), m_basePath(basePath), mediaList(mediaList)  {}


// LOAD FILE //

void MediaManagerJson::loadFilms() {
    
    QList<FilmData*> films;
    loadFilmsData(films);
    for (FilmData* data : films) {
        if(data->nomeCinema == cinemaAttuale)
            mediaList.append(createFilmFromData(*data));
        delete data;
    }
}

void MediaManagerJson::loadTrailers() {
    
    QList<TrailerData*> trailers;
    loadTrailersData(trailers);
    for (TrailerData* data : trailers) {
        if(data->nomeCinema == cinemaAttuale){
            Trailer* t = createTrailerFromData(*data);
            if(t) mediaList.append(t);
        }
            
        delete data;
    }
}

void MediaManagerJson::loadInserzioni() {
    
    QList<InserzioneData*> inserzioni;
    loadInserzioniData(inserzioni);
    for (InserzioneData* data : inserzioni) {
        if(data->nomeCinema == cinemaAttuale)
            mediaList.append(createInserzioneFromData(*data));
        delete data;
    }
}

void MediaManagerJson::loadPodcast() {
    
    QList<PodcastData*> podcast;
    loadPodcastData(podcast);
    for (PodcastData* data : podcast) {
        if(data->nomeCinema == cinemaAttuale)
            mediaList.append(createPodcastFromData(*data));
        delete data;
    }
}

void MediaManagerJson::loadPuntate() {
    
    QList<PuntataData*> puntata;
    loadPuntateData(puntata);
    for (PuntataData* data : puntata) {
        if(data->nomeCinema == cinemaAttuale){
            Puntata* p = createPuntataFromData(*data);
            if(p) mediaList.append(p);}
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

void MediaManagerJson::removeAll() {

    if(!mediaList.isEmpty()){
        for(Media* m : mediaList){
            delete m;
        }
    
        mediaList.clear();
    }

}

void MediaManagerJson::removeMedia(Media* media) {
    if (!media) return;

    mediaList.removeOne(media);
    delete media; // libera memoria

    QList<MediaData*> mediaData;
    QList<CinemaData*> cinemaList;
    loadAllData(mediaData);
    loadCinemaData(cinemaList);
    for(auto it = mediaData.begin(); it != mediaData.end(); ) {
        
        if( (*it)->titolo == QString::fromStdString(media->getTitolo()) &&
            (*it)->autore == QString::fromStdString(media->getAutore())) {
                delete *it;
                it = mediaData.erase(it); // cancella solo questo elemento
        } else ++it;
        
    }

    // salva tutta la lista aggiornata
    saveList(mediaData);

    for(CinemaData* c : cinemaList){
        saveCinema(c);
    }

    for(MediaData* m : mediaData) {
        delete m; 
    }
}

//modifica un oggetto
void MediaManagerJson::modified(Media& media, MediaData* data) {
    if (!data) return;

    QList<MediaData*> mediaData;
    QList<CinemaData*> cinemaList;
    loadAllData(mediaData);
    loadCinemaData(cinemaList);

    for (MediaData* c : mediaData) {
        if (c->titolo == QString::fromStdString(media.getTitolo()) &&
            c->autore == QString::fromStdString(media.getAutore())) {

            // lo sostituisco con quello aggiornato
            MediaUpdateVisitor visitor(data, c, this);
            media.accept(&visitor);
        }
    }

    saveList(mediaData);

    for(CinemaData* c : cinemaList){
        saveCinema(c);
    }

    for (MediaData* m : mediaData)
        delete m;
}

void MediaManagerJson::updateCommonField(Media& media, const MediaData* data){
    media.setTitolo(data->titolo.toStdString());
    media.setAutore(data->autore.toStdString());
    media.setDescrizione(data->descrizione.toStdString());
    media.setDurataMinuti(data->durataMinuti);
    media.setFormato(data->formato);
    media.setRisoluzione(data->risoluzione);

    media.setPath(data->path.toStdString());

    //lingue
    for(Lingua l : media.getLingue()){
        media.rimuoviLingua(l);
    }

    for(Lingua l : data->lingueDisponibili){
        media.aggiungiLingua(l);
    }
    //sottotitoli
    for(Lingua l : media.getSottotitoli()){
        media.rimuoviSottotitolo(l);
    }

    for(Lingua l : data->sottotitoliDisponibili){
        media.aggiungiSottotitolo(l);
    }

    media.setDataInizioRilascio(convertDate(data->dataInizioRilascio));
    media.setDataFineRilascio(convertDate(data->dataFineRilascio));
}

// toMediData CONVERTE DA OGGETTO MEDIA A DATA (struct)
void MediaManagerJson::updateFilm(Film& media, const FilmData* data){
    if(!data) return;

    updateCommonField(media, data);

    media.setGenere(data->generi);
    media.setCasaDiProduzione(data->casaDiProduzione.toStdString());
    media.setNPostCredit(data->nPostCredit);
    media.setCostoBiglietto(data->costoBiglietto);
    media.setTarget(data->target);

    for(string a : media.getAttoriPrincipali()){
        media.rimuoviAttore(a);
    }
    for(QString a : data->attoriPrincipali){
        media.aggiungiAttore(a.toStdString());
    }

}

void MediaManagerJson::updateTrailer(Trailer& media, const TrailerData* data){
    if(!data) return;

    updateCommonField(media, data);
    
    media.setNProiezioniGiornaliere(data->nProiezioniGiornaliere);
    for(Media* m : mediaList){
        Film* f = dynamic_cast<Film*>(m); 
        if(f && f->getTitolo() == data->filmAssociato.toStdString() && f->getAutore() == data->autoreFilmAssociato.toStdString())
            if(media.getFilm() != f)
                media.associaFilm(f);
    }
}

void MediaManagerJson::updateInserzione(Inserzione& media, const InserzioneData* data){
    if(!data) return;

    updateCommonField(media, data);

    media.setTarget(data->target);
    media.setAziendaInserzionistica(data->aziendaInserzionista.toStdString());
    media.setCostoFissoProiezione(data->costoFissoProiezione);
}

void MediaManagerJson::updatePodcast(Podcast& media, const PodcastData* data){
    if(!data) return;

    updateCommonField(media, data);

    media.setConduttore(data->conduttore.toStdString());
    
}

void MediaManagerJson::updatePuntata(Puntata& media, const PuntataData* data){
    if(!data) return;

    updateCommonField(media, data);
    
    media.setNumeroPubblicita(data->numeroPubblicita);

    for(string o : media.getOspiti()){
        media.rimuoviOspite(o);
    }

    for(QString o : data->ospiti){
        media.aggiungiOspite(o.toStdString());
    }

    for(Media* m : mediaList){
        Podcast* p = dynamic_cast<Podcast*>(m); 
        if(p && p->getTitolo() == data->podcastAssociato.toStdString() && p->getAutore() == data->autorePodcastAssociato.toStdString())
            if(media.getPodcast() != p)
                media.associaPodcast(p);
    }
}



// TROVA MEDIA PER RIFERIMENTO A PODCAST O FILM //
Media* MediaManagerJson::findMediaReference(const QString& titolo, const QString& autore, const QString& tipo){
    for(Media* m : mediaList){
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

void MediaManagerJson::createMedia(const MediaData& data){
    if(data.tipologia == "film") mediaList.append(createFilmFromData(static_cast<const FilmData&>(data)));
    else if(data.tipologia == "trailer"){
        Trailer* t = createTrailerFromData(static_cast<const TrailerData&>(data));
        if(t) mediaList.append(t);
    } 
    else if(data.tipologia == "inserzione") mediaList.append(createInserzioneFromData(static_cast<const InserzioneData&>(data)));
    else if(data.tipologia == "podcast") mediaList.append(createPodcastFromData(static_cast<const PodcastData&>(data)));
    else if(data.tipologia == "puntata"){
        Puntata* p = createPuntataFromData(static_cast<const PuntataData&>(data)); 
        if(p) mediaList.append(p);
    } 
}

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
    Media* filmAssociato = findMediaReference(data.filmAssociato, data.autoreFilmAssociato, data.tipologia);

    if(!filmAssociato){
        qDebug()<<"Errore!, nessun Film collegato al Trailer "<<data.titolo;
        return nullptr;
    } 

    Trailer* trailer = new Trailer(data.titolo.toStdString(),
                          data.descrizione.toStdString(),
                          convertDate(data.dataInizioRilascio),
                          convertDate(data.dataFineRilascio),
                          data.durataMinuti,
                          data.formato,
                          data.risoluzione,
                          data.nProiezioniGiornaliere,
                          static_cast<Film*>(filmAssociato),
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

Inserzione* MediaManagerJson::createInserzioneFromData(const InserzioneData& data) {

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
    Media* podcast = findMediaReference(data.podcastAssociato, data.autorePodcastAssociato, data.tipologia); 
    if(!podcast){
        qDebug()<<"Errore!, nessun Podcast collegato alla Puntata "<<data.titolo;
        return nullptr;
    } 

    Puntata* puntata = new Puntata(data.titolo.toStdString(),
                          data.descrizione.toStdString(),
                          convertDate(data.dataInizioRilascio),
                          convertDate(data.dataFineRilascio),
                          data.durataMinuti,
                          static_cast<Podcast*>(podcast),
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
    data.nomeCinema = obj["nomeCinema"].toString();
    data.copertinaCinema = obj["copertinaCinema"].toString();

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
    obj["nomeCinema"] =data.nomeCinema;
    obj["copertinaCinema"] = data.copertinaCinema;

}


void MediaManagerJson::saveList(QList<MediaData*>& mediaList){
    if(mediaList.isEmpty()) return;
    QJsonArray array;

    for (MediaData* media : mediaList) {
        QJsonObject obj;

        if(media->tipologia=="film") saveFilm(static_cast<FilmData*>(media), obj);
        else if(media->tipologia=="trailer") saveTrailer(static_cast<TrailerData*>(media), obj);
        else if(media->tipologia=="inserzione") saveInserzione(static_cast<InserzioneData*>(media), obj);
        else if(media->tipologia=="podcast") savePodcast(static_cast<PodcastData*>(media), obj);
        else if(media->tipologia=="puntata") savePuntata(static_cast<PuntataData*>(media), obj);

        array.append(obj);
    }

    saveJsonFile("media.json", QJsonDocument(array));
}

void MediaManagerJson::saveMedia(MediaData* media) {
    if (!media) return;
    if(media->nomeCinema != cinemaAttuale) return;
    
    QList<MediaData*> mediaList;
    QList<CinemaData*> cinemaList;

    loadCinemaData(cinemaList);
    loadAllData(mediaList); // carica quello che c'è
    for(MediaData* m : mediaList)
        if( m->autore == media->autore 
            && m->titolo == media->titolo 
            && m->nomeCinema == cinemaAttuale) return;
    
    mediaList.append(media);
    saveList(mediaList);

    createMedia(*media);

    for(CinemaData* c : cinemaList){
        saveCinema(c);
    }

    for(MediaData* m : mediaList)
        if(m!=media) delete m;
}

// FILM
void MediaManagerJson::loadFilmsData(QList<FilmData*>& films) {
    QJsonDocument doc = loadJsonFile("media.json");
    if (!doc.isArray()) return;

    
    for (const auto &val : doc.array()) {
        
        QJsonObject obj = val.toObject();

        if( obj["tipologia"].toString() == "film" && 
            obj["nomeCinema"].toString() == cinemaAttuale){

            FilmData* film = new FilmData();
    
            loadCommonFields(*film, obj);
    
            // generi (vector<Genere>)
            QJsonArray arrayGeneri = obj["generi"].toArray();
            for (const auto &g : arrayGeneri) {
                film->generi.push_back(static_cast<Genere>(g.toInt()));
            }
    
            film->casaDiProduzione = obj["casaDiProduzione"].toString();
            film->nPostCredit = obj["nPostCredit"].toInt();
            film->costoBiglietto = obj["costoBiglietto"].toDouble();
    
            film->target = static_cast<Classificazione>(obj["target"].toInt());
            for (const QJsonValue &v : obj["attoriPrincipali"].toArray())
            film->attoriPrincipali.push_back(v.toString());
    
            films.append(film);
        }
    }
}

void MediaManagerJson::saveFilm(FilmData* film, QJsonObject& obj) {
    if(!film) return;

    saveCommonFields(*film, obj);

    QJsonArray arrayGeneri;
    for (Genere g : film->generi) {
        arrayGeneri.append(static_cast<int>(g));
    }
    obj["generi"] = arrayGeneri;

    obj["casaDiProduzione"] = film->casaDiProduzione;
    obj["nPostCredit"] = static_cast<int>(film->nPostCredit);
    obj["costoBiglietto"] = film->costoBiglietto;

    obj["target"] = static_cast<int>(film->target);

    QJsonArray arrayAttori;
    for (const QString& a : film->attoriPrincipali)
        arrayAttori.append(a);
    obj["attoriPrincipali"] = arrayAttori;
}

// TRAILER
void MediaManagerJson::loadTrailersData(QList<TrailerData*>& trailers) {
    QJsonDocument doc = loadJsonFile("media.json");
    if (!doc.isArray()) return;

    for (const auto &val : doc.array()) {
        
        QJsonObject obj = val.toObject();

        if( obj["tipologia"].toString() == "trailer" && 
            obj["nomeCinema"].toString() == cinemaAttuale){

            TrailerData* trailer = new TrailerData();
    
            loadCommonFields(*trailer, obj);
    
            trailer->nProiezioniGiornaliere = obj["nProiezioniGiornaliere"].toInt();
            trailer->filmAssociato = obj["filmAssociato"].toString();
            trailer->autoreFilmAssociato = obj["autoreFilmAssociato"].toString();
            
            trailers.append(trailer);
        }
    }
}

void MediaManagerJson::saveTrailer(TrailerData* trailer, QJsonObject& obj) {
    if(!trailer) return;

    saveCommonFields(*trailer, obj);

    obj["nProiezioniGiornaliere"] = static_cast<int>(trailer->nProiezioniGiornaliere);
    obj["filmAssociato"] = trailer->filmAssociato;
    obj["autoreFilmAssociato"] = trailer->autoreFilmAssociato;

}

//PODCAST
void MediaManagerJson::loadPodcastData(QList<PodcastData*>& podcasts) {
    QJsonDocument doc = loadJsonFile("media.json");
    if (!doc.isArray()) return;

    
    for (const auto &val : doc.array()) {
        
        QJsonObject obj = val.toObject();

        if( obj["tipologia"].toString()=="podcast" && 
            obj["nomeCinema"].toString() == cinemaAttuale){
            
            PodcastData* podcast = new PodcastData();
    
            loadCommonFields(*podcast, obj);
    
            podcast->conduttore = obj["conduttore"].toString();
    
            podcasts.append(podcast);
        }
    }
}

void MediaManagerJson::savePodcast(PodcastData* podcast, QJsonObject& obj) {
    if(!podcast) return;

    saveCommonFields(*podcast, obj);

    obj["conduttore"] = podcast->conduttore;
}

//PUNTATA
void MediaManagerJson::loadPuntateData(QList<PuntataData*>& puntate) {
    QJsonDocument doc = loadJsonFile("media.json");
    if (!doc.isArray()) return;

    
    for (const auto &val : doc.array()) {
        
        QJsonObject obj = val.toObject();

        if( obj["tipologia"].toString() == "puntata" && 
            obj["nomeCinema"].toString() == cinemaAttuale){
            PuntataData* puntata = new PuntataData();
    
            loadCommonFields(*puntata, obj);
    
            puntata->numeroPubblicita = obj["numeroPubblicita"].toInt();
            puntata->autorePodcastAssociato = obj["autorePodcastAssociato"].toString();
            puntata->podcastAssociato = obj["podcastAssociato"].toString();
            
            for (const QJsonValue &v : obj["ospiti"].toArray())
            puntata->ospiti.push_back(v.toString());
    
            puntate.append(puntata);
        } 

    }
}

void MediaManagerJson::savePuntata(PuntataData* puntata, QJsonObject& obj) {
    if(!puntata) return;

    saveCommonFields(*puntata, obj);

    obj["numeroPubblicita"] = static_cast<int>(puntata->numeroPubblicita);
    obj["autorePodcastAssociato"] = puntata->autorePodcastAssociato;
    obj["podcastAssociato"] = puntata->podcastAssociato;

    QJsonArray arrayOspiti;
    for (const QString& o : puntata->ospiti)
        arrayOspiti.append(o);
    obj["ospiti"] = arrayOspiti;

}

//INSERZIONE
void MediaManagerJson::loadInserzioniData(QList<InserzioneData*>& inserzioni) {
    QJsonDocument doc = loadJsonFile("media.json");
    if (!doc.isArray()) return;

    for (const auto &val : doc.array()) {
        
        QJsonObject obj = val.toObject();

        if(obj["tipologia"].toString() == "inserzione"){
            InserzioneData* inserzione = new InserzioneData();
    
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
    }
}

void MediaManagerJson::saveInserzione(InserzioneData* inserzione, QJsonObject& obj) {
    if(!inserzione) return;

    saveCommonFields(*inserzione, obj);

    obj["target"] = static_cast<int>(inserzione->target);
    obj["aziendaInserzionista"] = inserzione->aziendaInserzionista;
    obj["costoFissoProiezione"] = static_cast<double>(inserzione->costoFissoProiezione);

    QJsonArray arrayFasceOrarie;
    for (FasciaOraria f : inserzione->fasceOrarie) {
        arrayFasceOrarie.append(static_cast<int>(f));
    }
    obj["fasceOrarie"] = arrayFasceOrarie;
}

//CINEMA
void MediaManagerJson::loadCinemaData(QList<CinemaData*>& cinemas) {
    QJsonDocument doc = loadJsonFile("media.json");
    if (!doc.isArray()) return;

    for (const auto &val : doc.array()) {
        
        QJsonObject obj = val.toObject();
        if (!obj.contains("tipologia")) {
            CinemaData* cinema = new CinemaData();
        
            cinema->nomeCinema = obj["nomeCinema"].toString();
            cinema->copertinaCinema = obj["copertinaCinema"].toString();
            cinemas.append(cinema);
        }
    }
}


void MediaManagerJson::saveCinema(CinemaData* cinema) {
    if (!cinema) return;

    // carico il JSON esistente
    QJsonDocument doc = loadJsonFile("media.json");
    QJsonArray array;

    if (doc.isArray()) {
        array = doc.array();
    }

    // verifico se il cinema è già presente
    for (const auto &val : array) {
        QJsonObject obj = val.toObject();
        if (!obj.contains("tipologia")) { // se non c'è tipologia, allora è un cinema 
            if (obj["nomeCinema"].toString() == cinema->nomeCinema)
                return; // già presente
        }
    }

    // creo l'oggetto cinema
    QJsonObject obj;

    obj["nomeCinema"] = cinema->nomeCinema;
    obj["copertinaCinema"] = cinema->copertinaCinema;

    array.append(obj);

    // salva il JSON aggiornato
    saveJsonFile("media.json", QJsonDocument(array));
}

void MediaManagerJson::loadAllData(QList<MediaData*>& media) {
    QList<FilmData*> films;
    loadFilmsData(films);
    for (FilmData* f : films)
    media.append(f);
    
    QList<TrailerData*> trailers;
    loadTrailersData(trailers);
    for (TrailerData* t : trailers)
    media.append(t);
    
    QList<PodcastData*> podcast;
    loadPodcastData(podcast);
    for (PodcastData* p : podcast)
    media.append(p);
    
    QList<PuntataData*> puntate;
    loadPuntateData(puntate);
    for (PuntataData* pt : puntate)
    media.append(pt);
    
    QList<InserzioneData*> inserzioni;
    loadInserzioniData(inserzioni);
    for (InserzioneData* i : inserzioni)
    media.append(i);
}

// HELPERS 
void MediaManagerJson::setCinemaNome(const QString& nomeCinema){
    cinemaAttuale = nomeCinema;
}

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
