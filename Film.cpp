#include "Film.h"
#include <algorithm>

// Costruttore
Film::Film(const string &regista, const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
           year_month_day gg_mm_aaFineRilascio, unsigned int visualizzazioni, unsigned int durataMinuti,
           const string &genere, Classificazione classificazione, double valutazione, const string &casaDiProduzione,
           unsigned int nPostCredit, double costoBiglietto) :

            Media(regista, titolo, descrizione, gg_mm_aaInizioRilascio, gg_mm_aaFineRilascio, visualizzazioni, durataMinuti),
            f_genere(genere), f_classificazione(classificazione), f_valutazione(valutazione),
            f_casaDiProduzione(casaDiProduzione), f_nPostCredit(nPostCredit), f_costoBiglietto(costoBiglietto)
{}


Film::~Film(){
    while (!trailers.empty()) {
        delete trailers.back();
        trailers.pop_back();
    }
}

double Film::calcolaIncasso() { return getVisualizzazioni() * f_costoBiglietto; }

void Film::estendiDataFineRilascio()
{
    if (!FuoriProduzione())
    {
        // Converti year_month_day a sys_days per sommare giorni
        std::chrono::sys_days dataFine = std::chrono::sys_days(getDataFineRilascio());
        dataFine += std::chrono::days{7};                           // aggiungi 7 giorni
        setDataFineRilascio(std::chrono::year_month_day{dataFine}); // aggiorna
        // Estendi i trailer associati che non sono fuori produzione
        for (Trailer *trailer : trailers)
        {
            if (trailer && !(trailer->FuoriProduzione()))
            {
                trailer->estendiDataFineRilascio();
            }
        }
    }
}

bool Film::isInTrailer(Trailer *trailer) const
{
    if (!trailers.size())
        return false;
    for (vector<Trailer *>::const_iterator cit = trailers.begin(); cit != trailers.end(); ++cit)
    {
        if (((*cit)) == trailer)
            return true;
    }
    return false;
}

void Film::aggiungiTrailer(Trailer *trailer)
{
    if (trailer && !isInTrailer(trailer))
        trailers.push_back(trailer);
}

void Film::rimuoviTrailer(Trailer *trailer)
{
    bool found = false;
    ;
    if ((!trailers.empty()) && trailer)
    for (vector<Trailer *>::iterator it = trailers.begin(); it != trailers.end() && !found; ++it)
    {
        if (((*it)) == trailer)
        {
            trailers.erase(it);
            found = true;
        }
    }
}

//metodi get
double Film::getCostoBiglietto() const {
    return f_costoBiglietto;
}

string Film::getGenere() const {
    return f_genere;
}

Classificazione Film::getClassificazione() const {
    return f_classificazione;
}

double Film::getValutazione() const {
    return f_valutazione;
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

// void Film::setValutazione(double valutazione) {
//     _valutazione = valutazione;
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

