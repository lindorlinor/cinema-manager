#include "CinemaManager.h"

CinemaManager::CinemaManager(const QString& basePath):c_basePath(basePath) {}

void CinemaManager::loadCinema(QList<Cinema*>& c_cinemaList){
    QJsonDocument doc = loadJsonFile("media.json");
    if (!doc.isArray()) return;
    
    for (const auto &val : doc.array()) {
        
        QJsonObject obj = val.toObject();
        if (!obj.contains("tipologia")) {
            QString nome = obj["nomeCinema"].toString();
            QString copertina = obj["copertinaCinema"].toString();
            Cinema* cinema = new Cinema(nome.toStdString(), copertina.toStdString());
        
            c_cinemaList.append(cinema);
        }
    }
    
}

void CinemaManager::loadMedia(QList<Media*>& c_mediaList){
    QJsonDocument doc = loadJsonFile("media.json");
    if (!doc.isArray()) return;
    
    for (const auto &val : doc.array()) {
        
        QJsonObject obj = val.toObject();
        if (obj.contains("tipologia")) {

            if(obj["tipologia"] == "film") c_mediaList.append(createFilm(obj));
            else if(obj["tipologia"] == "trailer"){
                Trailer* t = createTrailer(c_mediaList, obj);
                if(t) c_mediaList.append(t);
            } 
            else if(obj["tipologia"] == "inserzione") c_mediaList.append(createInserzione(obj));
            else if(obj["tipologia"] == "podcast") c_mediaList.append(createPodcast(obj));
            else if(obj["tipologia"] == "puntata"){
                Puntata* p = createPuntata(c_mediaList, obj); 
                if(p) c_mediaList.append(p);
            } 
        }
    }
    
}

void CinemaManager::saveCinemaInJson(Cinema* c_cinema){
    if (!c_cinema) return;

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
            if (obj["nomeCinema"].toString() == QString::fromStdString(c_cinema->getNomeCinema()))
                return; // già presente
        }
    }

    QJsonObject obj;

    obj["nomeCinema"] = QString::fromStdString(c_cinema->getNomeCinema());
    obj["copertinaCinema"] = QString::fromStdString(c_cinema->getCopertinaCinema());

    array.append(obj);

    // salva il JSON aggiornato
    saveJsonFile("media.json", QJsonDocument(array));
}

void CinemaManager::saveMediaInJson(Media* c_media) {
    if (!c_media) return;

    // carico il JSON esistente
    QJsonDocument doc = loadJsonFile("media.json");
    QJsonArray array;

    if (doc.isArray()) {
        array = doc.array();
    }

    // verifico se il media è già presente per il cinema
    for (const auto &val : array) {
        QJsonObject obj = val.toObject();
        if (obj.contains("tipologia")) { // se non c'è tipologia, allora è un cinema 
            if (    obj["titolo"] == QString::fromStdString(c_media->getNomeCinema()) && 
                    obj["titolo"] == QString::fromStdString(c_media->getTitolo()) &&
                    obj["autore"] == QString::fromStdString(c_media->getAutore()))
                return; // già presente
        }
    }

    QJsonObject obj;

    SaveMediaVisitor visitor(c_media, &obj);
    c_media->accept(&visitor);

    array.append(obj);

    // salva il JSON aggiornato
    saveJsonFile("media.json", QJsonDocument(array));
}

//non è necessario il controllo dei duplicati perché sono già stati fatti in precedenza per la modifica, mentre per la rimozione non sono necessari
//perché non si stanno aggiungendo media che possono creare doppioni. Non ci sono altri casi in cui questa funzione può venire chiamata
void CinemaManager::updateJson(QList<Cinema*> c_cinemaList, QList<Media*> c_mediaList){

    //svuoto il file Json
    QFile file("media.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write("[]");
        file.close();
    }

    QJsonArray array;

    for(Cinema* cinema : c_cinemaList){
        QJsonObject obj;
        obj["nomeCinema"] = QString::fromStdString(cinema->getNomeCinema());
        obj["copertinaCinema"] = QString::fromStdString(cinema->getCopertinaCinema());
        array.append(obj);
    }

    for(Media* media : c_mediaList){
        QJsonObject obj;
        SaveMediaVisitor visitor(media, &obj);
        media->accept(&visitor);
        array.append(obj);
    }
    // salva il JSON aggiornato
    saveJsonFile("media.json", QJsonDocument(array));
}

void CinemaManager::updateJson(QList<Media*> c_mediaList){

    QList<Cinema*> c_cinemaList;
    loadCinema(c_cinemaList);
    updateJson(c_cinemaList, c_mediaList);
}

void CinemaManager::deleteMedia(QList<Media*>& c_mediaList, Media* media){
    if (!media) return;

    c_mediaList.removeOne(media);   //cancello il media da eliminare
    delete media;                   // libera memoria

    //cancello i puntatori nulli che si sono potuti creare
    for(auto it = c_mediaList.begin(); it!=c_mediaList.end(); ++it){
        if(!(*it))                  //se è nullo allora lo cancello
            it = c_mediaList.erase(it);
    }

    updateJson(c_mediaList);
}

void CinemaManager::deleteCinema(QList<Cinema*>& c_cinemaList, Cinema* cinema){
    if(!cinema) return;

    c_cinemaList.removeOne(cinema);
    delete cinema;

    QList<Media*> c_mediaList;
    for(Cinema* c : c_cinemaList){
        for(Media* m : c->getListaMedia()){
            c_mediaList.append(m);
        }
    }

    updateJson(c_cinemaList, c_mediaList);
    
}


//HELPER

QJsonDocument CinemaManager::loadJsonFile(const QString &fileName) {
    QDir dir(c_basePath);
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

void CinemaManager::saveJsonFile(const QString &fileName, const QJsonDocument &doc) {
    QDir dir(c_basePath);                       // cartella base esistente
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


year_month_day CinemaManager::convertDate(const QString& data){
    QDate qdate = QDate::fromString(data, "yyyy-MM-dd");

    return year_month_day{
        std::chrono::year{qdate.year()},
        std::chrono::month{static_cast<unsigned>(qdate.month())},
        std::chrono::day{static_cast<unsigned>(qdate.day())}
    };
}


Film* CinemaManager::createFilm(QJsonObject& obj) {

    
    Film* film = new Film(
        obj["nomeCinema"].toString().toStdString(),
        obj["copertinaCinema"].toString().toStdString(),
        obj["titolo"].toString().toStdString(),
        obj["descrizione"].toString().toStdString(),
        convertDate(obj["dataInizioRilascio"].toString()),
        convertDate(obj["dataFineRilascio"].toString()), 
        static_cast<unsigned int>(obj["durataMinuti"].toInt()),
        static_cast<Formato>(obj["formato"].toInt()),
        static_cast<Risoluzione>(obj["risoluzione"].toInt()),
        static_cast<unsigned int>(obj["nPostCredit"].toInt()),
        obj["costoBiglietto"].toDouble(),
        obj["casaDiProduzione"].toString().toStdString(),
        obj["autore"].toString().toStdString(),
        obj["path"].toString().toStdString(),
        static_cast<Classificazione>(obj["target"].toInt())
    );

    addLingue(film,obj);
    addSottotitoli(film,obj);
    addAttore(film,obj);
    addGeneri(film,obj);
    
    return film;    
}


Trailer* CinemaManager::createTrailer (QList<Media*> c_mediaList, QJsonObject& obj) {
    Media* filmAssociato = findMediaReference(obj["nomeCinema"].toString(), obj["titolo"].toString(), obj["autore"].toString(), "trailer", c_mediaList);

    if(!filmAssociato){
        qDebug()<<"Errore!, nessun Film collegato al Trailer "<<obj["titolo"].toString();
        return nullptr;
    } 

    

    Trailer* trailer = new Trailer(
        obj["nomeCinema"].toString().toStdString(),
        obj["copertinaCinema"].toString().toStdString(),
        obj["titolo"].toString().toStdString(),
        obj["descrizione"].toString().toStdString(),
        convertDate(obj["dataInizioRilascio"].toString()),
        convertDate(obj["dataFineRilascio"].toString()), 
        static_cast<unsigned int>(obj["durataMinuti"].toInt()),
        static_cast<Formato>(obj["formato"].toInt()),
        static_cast<Risoluzione>(obj["risoluzione"].toInt()),
        static_cast<unsigned int>(obj["nProiezioniGiornaliere"].toInt()),
        static_cast<Film*>(filmAssociato),
        obj["autore"].toString().toStdString(),
        obj["path"].toString().toStdString());

    addLingue(trailer,obj);
    addSottotitoli(trailer,obj);

    return trailer;
}

Inserzione* CinemaManager::createInserzione(QJsonObject& obj) {

    Inserzione* inserzione = new Inserzione(
        obj["nomeCinema"].toString().toStdString(),
        obj["copertinaCinema"].toString().toStdString(),
        obj["titolo"].toString().toStdString(),
        obj["descrizione"].toString().toStdString(),
        convertDate(obj["dataInizioRilascio"].toString()),
        convertDate(obj["dataFineRilascio"].toString()), 
        static_cast<unsigned int>(obj["durataMinuti"].toInt()),
        static_cast<Formato>(obj["formato"].toInt()),
        static_cast<Risoluzione>(obj["risoluzione"].toInt()),
        static_cast<unsigned int>(obj["nProiezioniGiornaliere"].toInt()),
        static_cast<Classificazione>(obj["target"].toInt()),
        obj["costoFissoProiezione"].toDouble(),
        obj["aziendaInserzionista"].toString().toStdString(),
        obj["autore"].toString().toStdString(),
        obj["path"].toString().toStdString());

    addLingue(inserzione, obj);
    addSottotitoli(inserzione, obj);
    addFasceOrarie(inserzione, obj);
    
    return inserzione;
}

Podcast* CinemaManager::createPodcast(QJsonObject& obj) {

    Podcast* podcast = new Podcast(
        obj["nomeCinema"].toString().toStdString(),
        obj["copertinaCinema"].toString().toStdString(),
        obj["titolo"].toString().toStdString(),
        obj["descrizione"].toString().toStdString(),
        static_cast<Formato>(obj["formato"].toInt()),
        static_cast<Risoluzione>(obj["risoluzione"].toInt()),
        obj["autore"].toString().toStdString(),
        obj["path"].toString().toStdString(),
        obj["conduttore"].toString().toStdString());
    
    return podcast;
}

Puntata* CinemaManager::createPuntata(QList<Media*> c_mediaList, QJsonObject& obj) {
    Media* podcastAssociato = findMediaReference(obj["nomeCinema"].toString(), obj["titolo"].toString(), obj["autore"].toString(), "trailer", c_mediaList);
    if(!podcastAssociato){
        qDebug()<<"Errore!, nessun Podcast collegato alla Puntata "<<obj["titolo"].toString();
        return nullptr;
    } 

    Puntata* puntata = new Puntata(
        obj["nomeCinema"].toString().toStdString(),
        obj["copertinaCinema"].toString().toStdString(),
        obj["titolo"].toString().toStdString(),
        obj["descrizione"].toString().toStdString(),
        convertDate(obj["dataInizioRilascio"].toString()),
        convertDate(obj["dataFineRilascio"].toString()), 
        static_cast<unsigned int>(obj["durataMinuti"].toInt()),
        static_cast<Podcast*>(podcastAssociato),
        static_cast<unsigned int>(obj["numeroPubblicita"].toInt()),
        obj["autore"].toString().toStdString(),
        obj["path"].toString().toStdString());
    
    addLingue(puntata, obj);
    addSottotitoli(puntata, obj);
    addOspite(puntata, obj);

    return puntata;
}


void CinemaManager::addFasceOrarie(Inserzione* inserzione, QJsonObject& obj){
    QJsonArray fasce = obj["fasceOrarie"].toArray();

    for (const QJsonValue& value : fasce) {
        int fasciaInt = value.toInt();
        FasciaOraria f = static_cast<FasciaOraria>(fasciaInt);
        inserzione->aggiungiFasciaOraria(f);
    }
}

void CinemaManager::addLingue(Media* media, QJsonObject& obj){
    QJsonArray lingue = obj["lingueDisponibili"].toArray();

    for (const QJsonValue& value : lingue) {
        int lingueInt = value.toInt();
        Lingua l = static_cast<Lingua>(lingueInt);
        media->aggiungiLingua(l);
    }
}

void CinemaManager::addSottotitoli(Media* media, QJsonObject& obj){
    QJsonArray sottotitoli = obj["sottotitoliDisponibili"].toArray();

    for (const QJsonValue& value : sottotitoli) {
        int sottotitoliInt = value.toInt();
        Lingua l = static_cast<Lingua>(sottotitoliInt);
        media->aggiungiSottotitolo(l);
    }
}

void CinemaManager::addGeneri(Film* film, QJsonObject& obj){
    QJsonArray generi = obj["generi"].toArray();

    for (const QJsonValue& value : generi) {
        int generiInt = value.toInt();
        Genere g = static_cast<Genere>(generiInt);
        film->aggiungiGenere(g);
    }
}

void CinemaManager::addAttore(Film* film, QJsonObject& obj){
    QJsonArray arrayAttori = obj["attoriPrincipali"].toArray();

    for (const QJsonValue& value : arrayAttori) {
        film->aggiungiAttore(value.toString().toStdString());
    }
}

void CinemaManager::addOspite(Puntata* puntata, QJsonObject& obj){
    QJsonArray arrayOspiti = obj["ospiti"].toArray();

    for (const QJsonValue& value : arrayOspiti) {
        puntata->aggiungiOspite(value.toString().toStdString());
    }
}

// TROVA MEDIA PER RIFERIMENTO A PODCAST O FILM //
Media* CinemaManager::findMediaReference(const QString& cinema, const QString& titolo, const QString& autore, const QString& tipo, QList<Media*>c_mediaList){
    for(Media* m : c_mediaList){
        if(QString::fromStdString(m->getAutore()) == autore && QString::fromStdString(m->getAutore()) == titolo && QString::fromStdString(m->getNomeCinema()) == cinema)
            if( (tipo =="trailer" && dynamic_cast<Film*>(m) ) || (tipo == "puntata" && dynamic_cast<Podcast*>(m)))
                return m;
    }
    return nullptr; //non ha trovato niente
}