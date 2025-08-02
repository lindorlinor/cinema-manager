#include "Film.h"
#include <algorithm>

// Costruttore
Film::Film( const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
            year_month_day gg_mm_aaFineRilascio, unsigned int durataMinuti, Formato formato, Risoluzione risoluzione,
            Genere genere, const string &casaDiProduzione, unsigned int nPostCredit, double costoBiglietto, 
            const string &autore, const string &path, Classificazione target):

                    Media(titolo, descrizione, gg_mm_aaInizioRilascio, gg_mm_aaFineRilascio,
                    durataMinuti, formato, risoluzione, autore, path), f_genere(genere), 
                    f_target(target),f_casaDiProduzione(casaDiProduzione), f_nPostCredit(nPostCredit), 
                    f_costoBiglietto(costoBiglietto),f_valutazione(0){}


Film::~Film(){
    while (!trailers.empty()) {
        delete trailers.back();
        trailers.pop_back();
    }
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

//metodi get
double Film::getCostoBiglietto() const {
    return f_costoBiglietto;
}

Genere Film::getGenere() const {
    return f_genere;
}

Classificazione Film::getClassificazione() const {
    return f_target;
}

double Film::getValutazione() const {
    return f_valutazione;
}

void Film::setValutazione(){
    sys_days inizio = getDataInizioRilascio();
    sys_days fine = getDataLastViewUpdate();
    unsigned int giorni = (fine-inizio).count()+1;

    if (giorni == 0 || getVisualizzazioni() == 0){
        f_valutazione = 0.0;
    }
    else{
        double proporzione = getVisualizzazioni()/(giorni*1200.0); 
        f_valutazione = std::round((proporzione*5)>5? 5 : (proporzione*5)*10)/10.0;
    }
}

// //metodi set
// void Film::aggiungiAttore(const string& nomeAttore) {
    //     _attoriPrincipali.push_back(nomeAttore);
    // }
    
    // void Film::rimuoviAttore(const string& nomeAttore) {
//     if (!_attoriPrincipali.empty()) {
//         auto it = std::find(_attoriPrincipali.begin(), _attoriPrincipali.end(), nomeAttore);
//         if (it != _attoriPrincipali.end()) {
//             _attoriPrincipali.erase(it);
//         }
//     }
// }

// void Film::setGenere(const string& genere) {
//     _genere = genere;
// }

// void Film::setClassificazione(Classificazione classificazione) {
//     _classificazione = classificazione;
// }

// void Film::setCasaDiProduzione(const string& casaDiProduzione) {
//     _casaDiProduzione = casaDiProduzione;
// }

// void Film::setNPostCredit(unsigned int nPostCredit) {
//     _nPostCredit = nPostCredit;
// }

// void Film::setCostoBiglietto(double costoBiglietto) {
//     _costoBiglietto = costoBiglietto;
// }

// // mtodi get

// string Film::getCasaDiProduzione() const {
//     return _casaDiProduzione;
// }

// unsigned int Film::getNPostCredit() const {
//     return _nPostCredit;
// }

