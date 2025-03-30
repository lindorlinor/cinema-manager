#include "Film.h"
#include <algorithm> 

// Costruttore
Film::Film(const string& regista, const string& titolo, const string& descrizione, year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, 
    unsigned int visualizzazioni, unsigned int durataMinuti, const string& genere, Classificazione classificazione, double valutazione, 
    const string& casaDiProduzione,unsigned int nPostCredit,double costoBiglietto):
    Media(regista, titolo, descrizione, gg_mm_aaInizioRilascio, gg_mm_aaFineRilascio, visualizzazioni, durataMinuti),
    _genere(genere), _classificazione(classificazione), _valutazione(valutazione), _casaDiProduzione(casaDiProduzione),
    _nPostCredit(nPostCredit), _costoBiglietto(costoBiglietto) {}

//metodi set
void Film::aggiungiAttore(const string& nomeAttore) {
    _attoriPrincipali.push_back(nomeAttore);
}

void Film::rimuoviAttore(const string& nomeAttore) {
    if (!_attoriPrincipali.empty()) { 
        auto it = std::find(_attoriPrincipali.begin(), _attoriPrincipali.end(), nomeAttore);
        if (it != _attoriPrincipali.end()) {
            _attoriPrincipali.erase(it);
        }
    }
}

void Film::setGenere(const string& genere) {
    _genere = genere;
}

void Film::setClassificazione(Classificazione classificazione) {
    _classificazione = classificazione;
}

void Film::setValutazione(double valutazione) {
    _valutazione = valutazione;
}

void Film::setCasaDiProduzione(const string& casaDiProduzione) {
    _casaDiProduzione = casaDiProduzione;
}

void Film::setNPostCredit(unsigned int nPostCredit) {
    _nPostCredit = nPostCredit;
}

void Film::setCostoBiglietto(double costoBiglietto) {
    _costoBiglietto = costoBiglietto;
}

// mtodi get
string Film::getGenere() const {
    return _genere;
}

Classificazione Film::getClassificazione() const {
    return _classificazione;
}

double Film::getValutazione() const {
    return _valutazione;
}

string Film::getCasaDiProduzione() const {
    return _casaDiProduzione;
}

unsigned int Film::getNPostCredit() const {
    return _nPostCredit;
}

double Film::getCostoBiglietto() const {
    return _costoBiglietto;
}


double Film::calcolaIncasso(){
    return getVisualizzazioni() * _costoBiglietto;
}

void Film::estendiDataFineRilascio(){
    if(!FuoriProduzione()){
        year_month_day data = getDataFineRilascio();
        setDataFineRilascio(data.year()/data.month()/(data.day()+days{7}));
    }
}
bool Film::isInTrailer(Trailer * trailer) const{
    if(!trailers.size()) return false;
    for(vector<Trailer*>::const_iterator cit = trailers.begin();cit!=trailers.end();++cit){
        if(((*cit))==trailer) return true;
    }
    return false;
}
void Film::aggiungiTrailer(Trailer* trailer){
    if(trailer && !isInTrailer(trailer))
    trailers.push_back(trailer);
}

void Film::rimuoviTrailer(Trailer* trailer){
    bool found = false;;
    if((!trailers.empty()) && trailer)
        for(vector<Trailer*>::iterator it = trailers.begin();it!=trailers.end() && !found;++it){
            if(((*it))==trailer) {
                trailers.erase(it);
                found =true;
            }
        }
}

void Film::setDataFineRilascio(year_month_day gg_mm_aaFineRilascio) {
    Media::setDataFineRilascio(gg_mm_aaFineRilascio);
    for (auto it = trailers.begin(); it != trailers.end(); ++it) {
        if (*it) {
            (*it)->setDataFineRilascio(gg_mm_aaFineRilascio);
        }
    }
}

