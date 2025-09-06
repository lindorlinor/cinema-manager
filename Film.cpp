#include "Film.h"
#include <algorithm>
#include <QDebug>

// Costruttore
Film::Film( const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
            year_month_day gg_mm_aaFineRilascio, unsigned int durataMinuti, Formato formato, Risoluzione risoluzione, 
            unsigned int nPostCredit, double costoBiglietto, const string &casaDiProduzione,
            const string &autore, const string &path, Classificazione target):
            Media(titolo, descrizione, gg_mm_aaInizioRilascio, gg_mm_aaFineRilascio,
            durataMinuti, formato, risoluzione, autore, path),f_nPostCredit(nPostCredit),
            f_costoBiglietto(costoBiglietto),f_casaDiProduzione(casaDiProduzione),
            f_target(target), f_valutazione(0){setValutazione();}

Film::~Film(){
    for (auto it = trailers.begin(); it!= trailers.end(); ++it) {
        delete *it;
        *it = nullptr;
    }
    trailers.clear();
}

double Film::calcolaIncasso() { return getVisualizzazioni() * f_costoBiglietto; }

void Film::setDataFineRilascio(year_month_day gg_mm_aaFineRilascio){
    Media::setDataFineRilascio(gg_mm_aaFineRilascio);
    for (Trailer *trailer : trailers) {
        if (trailer && !(trailer->FuoriProduzione())){
            trailer->estendiDataFineRilascio();
        }
    }
}

void Film::estendiDataFineRilascio(){
    if (!FuoriProduzione()) {
        std::chrono::sys_days dataFine = std::chrono::sys_days(getDataFineRilascio());
        setDataFineRilascio(dataFine+days{7});
    }
}


int Film::isTrailerIn(Trailer* trailer) const {
    auto it = std::find(trailers.begin(), trailers.end(), trailer);
    if (it != trailers.end()) {
        return std::distance(trailers.begin(), it);
    } else {
        return -1;
    }
}

void Film::aggiungiTrailer(Trailer* trailer) {
    if (trailer &&  trailer->getFilm() == this && isTrailerIn(trailer) == -1) {
        trailers.push_back(trailer);
    }
}


void Film::rimuoviTrailer(Trailer* trailer) {
    int i_trailer = isTrailerIn(trailer);
    if (i_trailer != -1) {
        delete trailers[i_trailer];
        trailers.erase(trailers.begin() + i_trailer);
    }
}

void Film::disaccoppiaTrailer(Trailer* trailer){
    int i_trailer= isTrailerIn(trailer);
    if (i_trailer != -1) {
        trailers.erase(trailers.begin() + i_trailer);
    }
}

void Film::setValutazione(){
    sys_days inizio = getDataInizioRilascio();
    sys_days fine = getDataLastViewUpdate();
    unsigned int giorni = (fine-inizio).count() + 1;

    if (giorni == 0 || getVisualizzazioni() == 0){
        f_valutazione = 0.0;
    }
    else{
        double proporzione = getVisualizzazioni()/(giorni*1200.0); 
        f_valutazione = std::round((proporzione*5+1.55)>5? 5 : (proporzione*5+1.55)*10)/10.0;
    }
}

void Film::aggiungiAttore(const string& nomeAttore){
    f_attoriPrincipali.push_back(nomeAttore);
}

void Film::rimuoviAttore(const string& nomeAttore){
    auto it = find(f_attoriPrincipali.begin(), f_attoriPrincipali.end(), nomeAttore);
    if (it != f_attoriPrincipali.end()){
        f_attoriPrincipali.erase(it);
    }
}

void Film::aggiungiGenere(const Genere& genere) {
    f_genere.push_back(genere);
}

void Film::rimuoviGenere(const Genere& genere) {
    auto it = find(f_genere.begin(), f_genere.end(), genere);
    if (it != f_genere.end()){
        f_genere.erase(it);
    }
}

void Film::setTarget(Classificazione target) {
    f_target = target;
}

void Film::setCasaDiProduzione(const string& casaDiProduzione) {
    f_casaDiProduzione = casaDiProduzione;
}

void Film::setNPostCredit(unsigned int nPostCredit) {
    f_nPostCredit = nPostCredit;
}

void Film::setCostoBiglietto(double costoBiglietto) {
    f_costoBiglietto = costoBiglietto;
}


//visitor
void Film::accept(MediaVisitor* visitor) {
    visitor->visit(this);
}


// // metodi get

string Film::getCasaDiProduzione() const {
    return f_casaDiProduzione;
}

Classificazione Film::getTarget() const {
    return f_target;
}

unsigned int Film::getNPostCredit() const {
    return f_nPostCredit;
}

const std::vector<std::string>& Film::getAttoriPrincipali() const {
    return f_attoriPrincipali;
}
const vector<Trailer*>& Film::getTrailers() const {
    return trailers;
}

double Film::getCostoBiglietto() const {
    return f_costoBiglietto;
}

vector<Genere> Film::getGeneri() const {
    return f_genere;
}

double Film::getValutazione() const {
    return f_valutazione;
}
