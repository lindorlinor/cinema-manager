#include "JsonConverter.h"

JsonConverter::JsonConverter(){}

void JsonConverter::saveCommonFields(const Media& media, QJsonObject& obj){

    year_month_day ymdInizio = media.getDataInizioRilascio();
    year_month_day ymdFine = media.getDataFineRilascio();

    int yearInizio = static_cast<int>(ymdInizio.year());
    unsigned int monthInizio = static_cast<unsigned int>(ymdInizio.month());
    unsigned int dayInizio = static_cast<unsigned int>(ymdInizio.day());

    int yearFine = static_cast<int>(ymdFine.year());
    unsigned int monthFine = static_cast<unsigned int>(ymdFine.month());
    unsigned int dayFine = static_cast<unsigned int>(ymdFine.day());

    // creo il QDate
    QDate dataInizio(yearInizio, monthInizio, dayInizio);
    QDate dataFine(yearFine, monthFine, dayFine);

    obj["titolo"] = QString::fromStdString(media.getTitolo());
    obj["autore"] = QString::fromStdString(media.getAutore());
    obj["descrizione"] = QString::fromStdString(media.getDescrizione());
    obj["durataMinuti"] = static_cast<int>(media.getDurataMinuti());
    obj["formato"] = QString::fromStdString(toString(media.getFormato()));
    obj["risoluzione"] = QString::fromStdString(toString(media.getRisoluzione()));

    obj["path"] = QString::fromStdString(media.getImPath());

    QJsonArray arrayLingue;
    for (Lingua l : media.getLingue()) {
        arrayLingue.append(QString::fromStdString(toString(l)));
    }
    obj["lingueDisponibili"] = arrayLingue;

    QJsonArray arraySottotitoli;
    for (Lingua l : media.getSottotitoli()) {
        arraySottotitoli.append(QString::fromStdString(toString(l)));
    }
    obj["sottotitoliDisponibili"] = arraySottotitoli;


    obj["dataInizioRilascio"] = dataInizio.toString("yyyy-MM-dd");
    obj["dataFineRilascio"] = dataFine.toString("yyyy-MM-dd");
}

QJsonObject JsonConverter::serialize(Cinema* media){
    QJsonObject obj;

    obj["nomeCinema"] = QString::fromStdString(media->getNomeCinema());
    obj["copertinaCinema"] = QString::fromStdString(media->getCopertinaCinema());

    return obj;
}

QJsonObject JsonConverter::serialize(Film* media){
    QJsonObject obj;

    saveCommonFields(*media, obj);
    
    QJsonArray arrayGeneri;
    for (Genere g : media->getGeneri()) {
        arrayGeneri.append(static_cast<int>(g));
    }
    obj["generi"] = arrayGeneri;
    
    obj["casaDiProduzione"] = QString::fromStdString(media->getCasaDiProduzione());
    obj["nPostCredit"] = static_cast<int>(media->getNPostCredit());
    obj["costoBiglietto"] = media->getCostoBiglietto();

    obj["target"] = QString::fromStdString(toString(media->getTarget()));
    
    QJsonArray arrayAttori;
    for (const string& a : media->getAttoriPrincipali())
        arrayAttori.append(QString::fromStdString(a));
    obj["attoriPrincipali"] = arrayAttori;
    obj["tipologia"] = "film";


    return obj;
}

QJsonObject JsonConverter::serialize(Trailer* media){
    QJsonObject obj;
    
    saveCommonFields(*media, obj);
    
    obj["nProiezioniGiornaliere"] = static_cast<int>(media->getNProiezioniGiornaliere());
    obj["filmAssociato"] = QString::fromStdString(media->getFilm()->getTitolo());
    obj["autoreFilmAssociato"] = QString::fromStdString(media->getFilm()->getAutore());
    obj["tipologia"] = "trailer";

    return obj;
}

QJsonObject JsonConverter::serialize(Inserzione* media){
    QJsonObject obj;
    
    saveCommonFields(*media, obj);
    
    obj["target"] = QString::fromStdString(toString(media->getTarget()));
    obj["aziendaInserzionista"] = QString::fromStdString(media->getAziendaInserzionistica());
    obj["costoFissoProiezione"] = static_cast<double>(media->getCostoFissoProiezione());
    
    QJsonArray arrayFasceOrarie;
    for (FasciaOraria f : media->getFasceOrarie()) {
        arrayFasceOrarie.append(QString::fromStdString(toString(f)));
    }
    obj["fasceOrarie"] = arrayFasceOrarie;
    obj["tipologia"] = "inserzione";

    return obj;
}

QJsonObject JsonConverter::serialize(Podcast* media){
    QJsonObject obj;
    
    saveCommonFields(*media, obj);
    
    obj["conduttore"] = QString::fromStdString(media->getConduttore());
    obj["tipologia"] = "podcast";

    return obj;
}

QJsonObject JsonConverter::serialize(Puntata* media){
    QJsonObject obj;

    saveCommonFields(*media, obj);
    
    obj["numeroPubblicita"] = static_cast<int>(media->getNumeroPubblicita());
    obj["autorePodcastAssociato"] = QString::fromStdString(media->getPodcast()->getAutore());
    obj["podcastAssociato"] = QString::fromStdString(media->getPodcast()->getTitolo());
    
    QJsonArray arrayOspiti;
    for (const string& o : media->getOspiti())
    arrayOspiti.append(QString::fromStdString(o));
    obj["ospiti"] = arrayOspiti;
    obj["tipologia"] = "puntata";

    return obj;
}

Cinema* JsonConverter::deserializeCinema(QJsonObject obj){
        QString nome = obj["nomeCinema"].toString();
        QString copertina = obj["copertinaCinema"].toString();
        Cinema* cinema = new Cinema(nome.toStdString(), copertina.toStdString());
        return cinema;
}

Film* JsonConverter::deserializeFilm(QJsonObject obj) {

    
    Film* media = new Film(
        obj["titolo"].toString().toStdString(),
        obj["descrizione"].toString().toStdString(),
        convertDate(obj["dataInizioRilascio"].toString()),
        convertDate(obj["dataFineRilascio"].toString()), 
        static_cast<unsigned int>(obj["durataMinuti"].toInt()),
        toFormato(obj["formato"].toString().toStdString()),
        toRisoluzione(obj["risoluzione"].toString().toStdString()),
        static_cast<unsigned int>(obj["nPostCredit"].toInt()),
        obj["costoBiglietto"].toDouble(),
        obj["casaDiProduzione"].toString().toStdString(),
        obj["autore"].toString().toStdString(),
        obj["path"].toString().toStdString(),
        toClassificazione(obj["target"].toString().toStdString())
    );

    addLingue(media,obj);
    addSottotitoli(media,obj);
    addAttore(media,obj);
    addGeneri(media,obj);
    
    return media;    
}


Trailer* JsonConverter::deserializeTrailer(QList<Media*> c_mediaList, QJsonObject obj) {
    Media* filmAssociato = findMediaReference(obj["filmAssociato"].toString(), obj["autoreFilmAssociato"].toString(), "media", c_mediaList);

    if(!filmAssociato){
        qDebug()<<"Errore!, nessun Film collegato al Trailer "<<obj["titolo"].toString();
        return nullptr;
    } 

    

    Trailer* media = new Trailer(
        obj["titolo"].toString().toStdString(),
        obj["descrizione"].toString().toStdString(),
        convertDate(obj["dataInizioRilascio"].toString()),
        convertDate(obj["dataFineRilascio"].toString()), 
        static_cast<unsigned int>(obj["durataMinuti"].toInt()),
        toFormato(obj["formato"].toString().toStdString()),
        toRisoluzione(obj["risoluzione"].toString().toStdString()),
        static_cast<unsigned int>(obj["nProiezioniGiornaliere"].toInt()),
        static_cast<Film*>(filmAssociato),
        obj["autore"].toString().toStdString(),
        obj["path"].toString().toStdString());

    addLingue(media,obj);
    addSottotitoli(media,obj);

    return media;
}

Inserzione* JsonConverter::deserializeInserzione(QJsonObject obj) {

    Inserzione* media = new Inserzione(
        obj["titolo"].toString().toStdString(),
        obj["descrizione"].toString().toStdString(),
        convertDate(obj["dataInizioRilascio"].toString()),
        convertDate(obj["dataFineRilascio"].toString()), 
        static_cast<unsigned int>(obj["durataMinuti"].toInt()),
        toFormato(obj["formato"].toString().toStdString()),
        toRisoluzione(obj["risoluzione"].toString().toStdString()),
        static_cast<unsigned int>(obj["nProiezioniGiornaliere"].toInt()),
        toClassificazione(obj["target"].toString().toStdString()),
        obj["costoFissoProiezione"].toDouble(),
        obj["aziendaInserzionista"].toString().toStdString(),
        obj["autore"].toString().toStdString(),
        obj["path"].toString().toStdString());

    addLingue(media, obj);
    addSottotitoli(media, obj);
    addFasceOrarie(media, obj);
    
    return media;
}

Podcast* JsonConverter::deserializePodcast(QJsonObject obj) {

    Podcast* media = new Podcast(
        obj["titolo"].toString().toStdString(),
        obj["descrizione"].toString().toStdString(),
        toFormato(obj["formato"].toString().toStdString()),
        toRisoluzione(obj["risoluzione"].toString().toStdString()),
        obj["autore"].toString().toStdString(),
        obj["path"].toString().toStdString(),
        obj["conduttore"].toString().toStdString());
    
    return media;
}

Puntata* JsonConverter::deserializePuntata(QList<Media*> c_mediaList, QJsonObject obj) {
    Media* podcastAssociato = findMediaReference(obj["podcastAssociato"].toString(), obj["autorePodcastAssociato"].toString(), "media", c_mediaList);
    if(!podcastAssociato){
        qDebug()<<"Errore!, nessun Podcast collegato alla Puntata "<<obj["titolo"].toString();
        return nullptr;
    } 

    Puntata* media = new Puntata(
        obj["titolo"].toString().toStdString(),
        obj["descrizione"].toString().toStdString(),
        convertDate(obj["dataInizioRilascio"].toString()),
        convertDate(obj["dataFineRilascio"].toString()), 
        static_cast<unsigned int>(obj["durataMinuti"].toInt()),
        static_cast<Podcast*>(podcastAssociato),
        static_cast<unsigned int>(obj["numeroPubblicita"].toInt()),
        obj["autore"].toString().toStdString(),
        obj["path"].toString().toStdString());
    
    addLingue(media, obj);
    addSottotitoli(media, obj);
    addOspite(media, obj);

    return media;
}


void JsonConverter::addFasceOrarie(Inserzione* media, QJsonObject obj){
    QJsonArray fasce = obj["fasceOrarie"].toArray();

    for (const QJsonValue& value : fasce) {
        int fasciaInt = value.toInt();
        FasciaOraria f = static_cast<FasciaOraria>(fasciaInt);
        media->aggiungiFasciaOraria(f);
    }
}

void JsonConverter::addLingue(Media* media, QJsonObject obj){
    QJsonArray lingue = obj["lingueDisponibili"].toArray();

    for (const QJsonValue& value : lingue) {
        int lingueInt = value.toInt();
        Lingua l = static_cast<Lingua>(lingueInt);
        media->aggiungiLingua(l);
    }
}

void JsonConverter::addSottotitoli(Media* media, QJsonObject obj){
    QJsonArray sottotitoli = obj["sottotitoliDisponibili"].toArray();

    for (const QJsonValue& value : sottotitoli) {
        int sottotitoliInt = value.toInt();
        Lingua l = static_cast<Lingua>(sottotitoliInt);
        media->aggiungiSottotitolo(l);
    }
}

void JsonConverter::addGeneri(Film* media, QJsonObject obj){
    QJsonArray generi = obj["generi"].toArray();

    for (const QJsonValue& value : generi) {
        int generiInt = value.toInt();
        Genere g = static_cast<Genere>(generiInt);
        media->aggiungiGenere(g);
    }
}

void JsonConverter::addAttore(Film* media, QJsonObject obj){
    QJsonArray arrayAttori = obj["attoriPrincipali"].toArray();

    for (const QJsonValue& value : arrayAttori) {
        media->aggiungiAttore(value.toString().toStdString());
    }
}

void JsonConverter::addOspite(Puntata* media, QJsonObject obj){
    QJsonArray arrayOspiti = obj["ospiti"].toArray();

    for (const QJsonValue& value : arrayOspiti) {
        media->aggiungiOspite(value.toString().toStdString());
    }
}

year_month_day JsonConverter::convertDate(const QString& data){
    QDate qdate = QDate::fromString(data, "yyyy-MM-dd");

    return year_month_day{
        std::chrono::year{qdate.year()},
        std::chrono::month{static_cast<unsigned>(qdate.month())},
        std::chrono::day{static_cast<unsigned>(qdate.day())}
    };
}

// TROVA MEDIA PER RIFERIMENTO A PODCAST O FILM //

//nota: non c'è il controllo sul cinema perché nella lista di oggetti passata, tutti gli oggetti riguardano lo stesso cinema
Media* JsonConverter::findMediaReference(const QString& titolo, const QString& autore, const QString& tipo, QList<Media*>c_mediaList){
    for(Media* m : c_mediaList){
        if(QString::fromStdString(m->getAutore()) == autore && QString::fromStdString(m->getTitolo()) == titolo)
            if( (tipo =="trailer" && dynamic_cast<Film*>(m) ) || (tipo == "puntata" && dynamic_cast<Podcast*>(m)))
                return m;
    }
    return nullptr; //non ha trovato niente
}

