#ifndef PUBBLICITA_H
#define PUBBLICITA_H

#include <string>
#include "Media.h"

/**
 * @class Pubblicita
 * @brief Rappresenta una pubblicità distribuita dal cinema nei canali appropriati.
 * 
 * Classe astratta derivata dalla classe base astratta Media. Una pubblicità riporta
 * in più il numero di proiezioni giornaliere del media nei canali adatti del cinema.
 */
class Pubblicita : public Media
{
private:
   
    unsigned int p_nProiezioniGiornaliere;

public:
    Pubblicita(     const string &autore, const string &titolo, const string &descrizione, 
                    year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, 
                    unsigned int visualizzaioni, unsigned int durataMinuti, const string& path, 
                    Formato formato, unsigned int nProiezioniGiornaliere);

    unsigned int getNProiezioniGiornaliere() const; 
   

};

#endif
