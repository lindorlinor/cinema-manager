#ifndef INSERZIONE_H
#define INSERZIONE_H

#include "Pubblicita.h"
#include <string>
class Inserzione : public Pubblicita{
private:
    string _aziendaInserzionista;
    const int COSTO_FISSO_PROIEZIONE;
public:
    Inserzione(const string& autore, const string& titolo, const string& descrizione, year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, unsigned int 
        visualizzaioni, unsigned int durataMinuti, const Classificazione& target, unsigned int nProiezioniGiornaliere, const string& aziendaInserzionista, int costoProiezione);
    double calcolaIncasso() override;
    void estendiDataFineRilascio() override;
};

#endif 


