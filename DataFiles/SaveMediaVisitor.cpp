#include "SaveMediaVisitor.h"
#include "SaveMediaVisitor.h"

SaveMediaVisitor::SaveMediaVisitor(Media* media, QJsonObject* obj): v_media(media), v_obj(obj){}

SaveMediaVisitor::~SaveMediaVisitor() {}

void SaveMediaVisitor::visit(Film* film){
    saveFilm(film, *v_obj);
}

void SaveMediaVisitor::visit(Trailer* trailer){
    saveTrailer(trailer, *v_obj);
}

void SaveMediaVisitor::visit(Inserzione* inserzione){
    saveInserzione(inserzione, *v_obj);
}

void SaveMediaVisitor::visit(Podcast* podcast){
    savePodcast(podcast, *v_obj);
}

void SaveMediaVisitor::visit(Puntata* puntata){
   savePuntata(puntata, *v_obj);
}

void SaveMediaVisitor::saveCommonFields(const Media* media, QJsonObject &obj){

    year_month_day ymdInizio = media->getDataInizioRilascio();
    year_month_day ymdFine = media->getDataFineRilascio();

    int yearInizio = static_cast<int>(ymdInizio.year());
    unsigned int monthInizio = static_cast<unsigned int>(ymdInizio.month());
    unsigned int dayInizio = static_cast<unsigned int>(ymdInizio.day());

    int yearFine = static_cast<int>(ymdFine.year());
    unsigned int monthFine = static_cast<unsigned int>(ymdFine.month());
    unsigned int dayFine = static_cast<unsigned int>(ymdFine.day());

    // creo il QDate
    QDate dataInizio(yearInizio, monthInizio, dayInizio);
    QDate dataFine(yearFine, monthFine, dayFine);

    obj["titolo"] = QString::fromStdString(media->getTitolo());
    obj["autore"] = QString::fromStdString(media->getAutore());
    obj["descrizione"] = QString::fromStdString(media->getDescrizione());
    obj["durataMinuti"] = static_cast<int>(media->getDurataMinuti());
    obj["formato"] = static_cast<int>(media->getFormato());
    obj["risoluzione"] = static_cast<int>(media->getRisoluzione());

    obj["path"] = QString::fromStdString(media->getImPath());

    QJsonArray arrayLingue;
    for (Lingua l : media->getLingue()) {
        arrayLingue.append(static_cast<int>(l));  
    }
    obj["lingueDisponibili"] = arrayLingue;

    QJsonArray arraySottotitoli;
    for (Lingua l : media->getSottotitoli()) {
        arraySottotitoli.append(static_cast<int>(l));  
    }
    obj["sottotitoliDisponibili"] = arraySottotitoli;

    obj["dataInizioRilascio"] = dataInizio.toString("yyyy-MM-dd");
    obj["dataFineRilascio"] = dataFine.toString("yyyy-MM-dd");

    obj["nomeCinema"] =QString::fromStdString(media->getNomeCinema());
    obj["copertinaCinema"] = QString::fromStdString(media->getCopertinaCinema());
    
}


void SaveMediaVisitor::saveFilm(Film* film, QJsonObject& obj) {
    if(!film) return;

    saveCommonFields(film, obj);
    
    QJsonArray arrayGeneri;
    for (Genere g : film->getGeneri()) {
        arrayGeneri.append(static_cast<int>(g));
    }
    obj["generi"] = arrayGeneri;
    
    obj["casaDiProduzione"] = QString::fromStdString(film->getCasaDiProduzione());
    obj["nPostCredit"] = static_cast<int>(film->getNPostCredit());
    obj["costoBiglietto"] = film->getCostoBiglietto();

    obj["target"] = static_cast<int>(film->getTarget());
    
    QJsonArray arrayAttori;
    for (const string& a : film->getAttoriPrincipali())
        arrayAttori.append(QString::fromStdString(a));
    obj["attoriPrincipali"] = arrayAttori;
    obj["tipologia"] = "film";
}

// TRAILER

void SaveMediaVisitor::saveTrailer(Trailer* trailer, QJsonObject& obj) {
    if(!trailer) return;
    
    saveCommonFields(trailer, obj);
    
    obj["nProiezioniGiornaliere"] = static_cast<int>(trailer->getNProiezioniGiornaliere());
    obj["filmAssociato"] = QString::fromStdString(trailer->getFilm()->getTitolo());
    obj["autoreFilmAssociato"] = QString::fromStdString(trailer->getFilm()->getAutore());
    obj["tipologia"] = "trailer";
}

//PODCAST

void SaveMediaVisitor::savePodcast(Podcast* podcast, QJsonObject& obj) {
    if(!podcast) return;
    
    saveCommonFields(podcast, obj);
    
    obj["conduttore"] = QString::fromStdString(podcast->getConduttore());
    obj["tipologia"] = "podcast";
}

//PUNTATA

void SaveMediaVisitor::savePuntata(Puntata* puntata, QJsonObject& obj) {
    if(!puntata) return;

    saveCommonFields(puntata, obj);
    
    obj["numeroPubblicita"] = static_cast<int>(puntata->getNumeroPubblicita());
    obj["autorePodcastAssociato"] = QString::fromStdString(puntata->getPodcast()->getAutore());
    obj["podcastAssociato"] = QString::fromStdString(puntata->getPodcast()->getTitolo());
    
    QJsonArray arrayOspiti;
    for (const string& o : puntata->getOspiti())
    arrayOspiti.append(QString::fromStdString(o));
    obj["ospiti"] = arrayOspiti;
    obj["tipologia"] = "puntata";
    
}

//INSERZIONE

void SaveMediaVisitor::saveInserzione(Inserzione* inserzione, QJsonObject& obj) {
    if(!inserzione) return;
    
    saveCommonFields(inserzione, obj);
    
    obj["target"] = static_cast<int>(inserzione->getTarget());
    obj["aziendaInserzionista"] = QString::fromStdString(inserzione->getAziendaInserzionistica());
    obj["costoFissoProiezione"] = static_cast<double>(inserzione->getCostoFissoProiezione());
    
    QJsonArray arrayFasceOrarie;
    for (FasciaOraria f : inserzione->getFasceOrarie()) {
        arrayFasceOrarie.append(static_cast<int>(f));
    }
    obj["fasceOrarie"] = arrayFasceOrarie;
    obj["tipologia"] = "inserzione";
}

