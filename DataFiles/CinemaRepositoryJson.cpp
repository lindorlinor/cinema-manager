#include "CinemaRepositoryJson.h"

CinemaRepositoryJson::CinemaRepositoryJson(const QString& basePath):c_basePath(basePath) {}

void CinemaRepositoryJson::loadCinema(QList<Cinema*>& c_cinemaList){
    QJsonDocument doc = loadJsonFile("media.json");
    if (!doc.isArray()) return;
    
    for (const auto &val : doc.array()) {
        
        QJsonObject obj = val.toObject();
        if (!obj.contains("tipologia")) {
            c_cinemaList.append(converter->deserializeCinema(obj));
        }
    }
    
}

void CinemaRepositoryJson::loadMedia(QList<Media*>& c_mediaList, const QString& nomeCinema){
    QJsonDocument doc = loadJsonFile("media.json");
    if (!doc.isArray()) return;
    
    for (const auto &val : doc.array()) {
        
        QJsonObject obj = val.toObject();
        if (obj.contains("tipologia") && obj["nomeCinema"] == nomeCinema) {


            if(obj["tipologia"] == "film") c_mediaList.append(converter->deserializeFilm(obj));
            else if(obj["tipologia"] == "trailer") c_mediaList.append(converter->deserializeTrailer(c_mediaList, obj));
            else if(obj["tipologia"] == "inserzione") c_mediaList.append(converter->deserializeInserzione(obj));
            else if(obj["tipologia"] == "podcast") c_mediaList.append(converter->deserializePodcast(obj));
            else if(obj["tipologia"] == "puntata") c_mediaList.append(converter->deserializePuntata(c_mediaList, obj));
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
    qDebug()<<"gli passo media.json, che vuoi";
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


    JsonVisitor visitor(c_media);
    c_media->accept(&visitor);

    array.append(visitor.getObj());

    // salva il JSON aggiornato
    saveJsonFile("media.json", QJsonDocument(array));
}

//non è necessario il controllo dei duplicati perché sono già stati fatti in precedenza per la modifica, mentre per la rimozione non sono necessari
//perché non si stanno aggiungendo media che possono creare doppioni. Non ci sono altri casi in cui questa funzione può venire chiamata
void CinemaRepositoryJson::updateJson(QList<Cinema*> c_cinemaList){

    //svuoto il file Json
    QFile file("media.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write("[]");
        file.close();
    }

    //carico nella lista m_mediaList tutti i media
    QList<Media*> c_mediaList;
    for(Cinema* c : c_cinemaList){
        for(Media* m : c->getListaMedia()){
            c_mediaList.append(m);
        }
    }

    QJsonArray array;

    for(Cinema* cinema : c_cinemaList){
        array.append(converter->serialize(cinema));
    }

    for(Media* media : c_mediaList){
        JsonVisitor visitor(media);
        media->accept(&visitor);
        array.append(visitor.getObj());
    }
    // salva il JSON aggiornato
    saveJsonFile("media.json", QJsonDocument(array));
}

void CinemaRepositoryJson::deleteCinema(QList<Cinema*>& c_cinemaList, Cinema* cinema){
    if(!cinema) return;

    //una volta che cancello il cinema con delete, tutti i suoi media vengono distrutti, questo è il comportamento del distruttore
    //di Cinema
    c_cinemaList.removeOne(cinema);
    delete cinema;

    updateJson(c_cinemaList);
    
}


//HELPER

QJsonDocument CinemaRepositoryJson::loadJsonFile(const QString &fileName) {
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

void CinemaRepositoryJson::saveJsonFile(const QString &fileName, const QJsonDocument &doc) {
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
