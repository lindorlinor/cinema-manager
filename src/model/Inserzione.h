#ifndef INSERZIONE_H
#define INSERZIONE_H

#include "Pubblicita.h"
#include <string>
class Inserzione : public Pubblicita{
    string _aziendaInserzionista;
    int _nProiezioniGiornaliere;
    double calcolaTassoDiStima() const;
public:
    Inserzione(const string& autore, const string& titolo, const string& descrizione, year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, unsigned int 
        visualizzaioni, unsigned int durataMinuti, const Classificazione& target, const string& aziendaInserzionista, int nProiezioniGiornaliere);
    //ha senso che la data di fine rilascio sia uguale a quella del film
    double calcolaIncasso() override;
    void estendiDataFineRilascio() override;
};

#endif 


