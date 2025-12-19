#include "CinemaRepositoryJson.h"

CinemaRepositoryJson::CinemaRepositoryJson(const QString& basePath):c_basePath(basePath) {}

void CinemaRepositoryJson::loadCinema(QList<Cinema*>& c_cinemaList){
    QJsonDocument doc = loadJsonFile("media.json");
    if (!doc.isArray()) return;
    bool flag = false;
    for (const auto &val : doc.array()) {
        QJsonObject obj = val.toObject();
        if (!obj.contains("tipologia")) {
            for(Cinema* c : c_cinemaList){
                flag = false;
                if(obj["nomeCinema"]==QString::fromStdString(c->getNomeCinema())) flag = true;
            }
            if(!flag) c_cinemaList.append(converter->deserializeCinema(obj));
        }
    }
}



void CinemaRepositoryJson::loadMedia(QList<Media*>& c_mediaList, const QString& nomeCinema){
    QJsonDocument doc = loadJsonFile("media.json");
    if (!doc.isArray()) return;

    bool flag = false;
    
    // prima carico tutti i film, podcast e inserzioni
    for (const auto &val : doc.array()) {
        QJsonObject obj = val.toObject();
        if (obj.contains("tipologia") && obj["nomeCinema"] == nomeCinema) {
            
            for(Media* m : c_mediaList){
                flag = false;
                if( obj["titolo"] == QString::fromStdString(m->getTitolo()) &&
                    obj["autore"] == QString::fromStdString(m->getAutore())) flag = true;
            }

            if(!flag){
                if(obj["tipologia"] == "film"){
                    Film* film = converter->deserializeFilm(obj);
                    if(film) c_mediaList.append(film);
                }
                else if(obj["tipologia"] == "inserzione"){
                    Inserzione* inserzione = converter->deserializeInserzione(obj);
                    if(inserzione) c_mediaList.append(inserzione);
                } 
                else if(obj["tipologia"] == "podcast"){
                    Podcast* podcast = converter->deserializePodcast(obj);
                    if(podcast) c_mediaList.append(podcast);
                }
            }

        }
    }

    //poi carico le puntate e i trailer perché non possono essere creati se non esiste il relativo Podcast o Film
    for (const auto &val : doc.array()) {
        QJsonObject obj = val.toObject();
        if (obj.contains("tipologia") && obj["nomeCinema"] == nomeCinema) {
            
            for(Media* m : c_mediaList){
                flag = false;
                if( obj["titolo"] == QString::fromStdString(m->getTitolo()) &&
                    obj["autore"] == QString::fromStdString(m->getAutore())) flag = true;
            }

            if(!flag){
                if(obj["tipologia"] == "trailer"){
                    Trailer* trailer = converter->deserializeTrailer(c_mediaList, obj);
                    if(trailer) c_mediaList.append(trailer);
                }
                else if(obj["tipologia"] == "puntata"){
                    Puntata* puntata = converter->deserializePuntata(c_mediaList, obj); 
                    if(puntata) c_mediaList.append(puntata);
                }
            }

        }
    }
    
}

void CinemaRepositoryJson::saveCinemaInJson(Cinema* c_cinema){
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

    array.append(converter->serialize(c_cinema));

    // salva il JSON aggiornato
    saveJsonFile("media.json", QJsonDocument(array));
}

void CinemaRepositoryJson::saveMediaInJson(Media* c_media, const QString& nomeCinema) {
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
            if (    obj["nomeCinema"] == nomeCinema && 
                    obj["titolo"] == QString::fromStdString(c_media->getTitolo()) &&
                    obj["autore"] == QString::fromStdString(c_media->getAutore()))
                return; // già presente
        }
    }


    JsonVisitor visitor(nomeCinema);
    c_media->accept(&visitor);

    array.append(visitor.getObj());

    // salva il JSON aggiornato
    saveJsonFile("media.json", QJsonDocument(array));
}

void CinemaRepositoryJson::updateMediaInJson(Cinema* cinemaSelezionato){

    QJsonArray array;
    QList<Cinema*> c_cinemaList;
    loadCinema(c_cinemaList);

    for(Cinema* c : c_cinemaList){
        array.append(converter->serialize(c));
        if(c->getNomeCinema() == cinemaSelezionato->getNomeCinema()){
            for(Media* m : cinemaSelezionato->getListaMedia()){
                JsonVisitor visitor(QString::fromStdString(c->getNomeCinema()));
                m->accept(&visitor);
                array.append(visitor.getObj());
            }
        }
        else{
            QList<Media*> mediaList;
            loadMedia(mediaList, QString::fromStdString(c->getNomeCinema()));
            
            for(Media* m : mediaList){
                JsonVisitor visitor(QString::fromStdString(c->getNomeCinema()));
                m->accept(&visitor);
                array.append(visitor.getObj());
            }

            deleteMediaPointer(mediaList);
        }
    }

    for(Cinema* c : c_cinemaList) delete c;

    // salva il JSON aggiornato
    saveJsonFile("media.json", QJsonDocument(array));
}

//non è necessario il controllo dei duplicati perché sono già stati fatti in precedenza per la modifica, mentre per la rimozione non sono necessari
//perché non si stanno aggiungendo media che possono creare doppioni. Non ci sono altri casi in cui questa funzione può venire chiamata
void CinemaRepositoryJson::deleteCinemaInJson(QList<Cinema*> c_cinemaList){

    QJsonArray array;
    
    //carico tutti i cinema presenti nella lista passata
    for(Cinema* c : c_cinemaList){
        array.append(converter->serialize(c));
        QList<Media*> mediaList;
        loadMedia(mediaList, QString::fromStdString(c->getNomeCinema()));
        
        for(Media* m : mediaList){
            JsonVisitor visitor(QString::fromStdString(c->getNomeCinema()));
            m->accept(&visitor);
            array.append(visitor.getObj());
        }
            
        deleteMediaPointer(mediaList);
    }


    // salva il JSON aggiornato
    saveJsonFile("media.json", QJsonDocument(array));
}

void CinemaRepositoryJson::updateCinemaInJson(const QString& nomeCinemaVecchio, Cinema* cinemaAggiornato){

    QJsonDocument doc = loadJsonFile("media.json");
    QJsonArray array;

    if (doc.isArray()) {
        array = doc.array();
    }

    for (int i = 0; i < array.size(); ++i) {
       QJsonObject obj = array[i].toObject();
        if (obj["nomeCinema"].toString() == nomeCinemaVecchio) { 
            obj["nomeCinema"] =  QString::fromStdString(cinemaAggiornato->getNomeCinema());

            if(obj.contains("copertinaCinema")) obj["copertinaCinema"] =  QString::fromStdString(cinemaAggiornato->getCopertinaCinema());
        }
        array[i] = obj;
    }

    //salvo il JSON aggiornato
    saveJsonFile("media.json", QJsonDocument(array));
}

//HELPER

QJsonDocument CinemaRepositoryJson::loadJsonFile(const QString &fileName) {
    QDir dir(c_basePath);

    QString filePath = dir.filePath(fileName);


    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return QJsonDocument();
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    return doc;
}

void CinemaRepositoryJson::saveJsonFile(const QString &fileName, const QJsonDocument &doc) {
    QDir dir(c_basePath);                       // cartella base esistente
    QString filePath = dir.filePath(fileName);  // combina basePath + fileName correttamente

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        qWarning() << "Impossibile scrivere" << filePath;
        return;
    }



    file.write(doc.toJson());
    file.close();
}

void CinemaRepositoryJson::deleteMediaPointer(QList<Media*>& c_mediaList){

    for(Media* m : c_mediaList){

    if(Film* film = dynamic_cast<Film*>(m)) //disaccoppio tutti i trailer prima di eliminarli
        for(Trailer* t : film->getTrailers())
        film->disaccoppiaTrailer(t);

    if(Podcast* podcast = dynamic_cast<Podcast*>(m)) //disaccoppio tutte le puntate prima di eliminarle
        for(Puntata* p : podcast->getElencoPuntate())
        podcast->disaccoppiaPuntata(p);
    }

    for(Media* m : c_mediaList) delete m;
    c_mediaList.clear();
}