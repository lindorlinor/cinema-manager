#ifndef TRAILER_H
#define TRAILER_H

#include "Pubblicita.h"
class Film; //forward declaration


/**
 * @class Pubblicità
 * @brief Rappresenta un trailer proiettato al cinema.
 * 
 * Un trailer è una pubblicità proiettata nelle sale del cinema. Un trailer è sempre associato ad un film esistente del cinema
 */
class Trailer : public Pubblicita{
    Film* t_film;
    double calcolaTassoDiStima() const;
public:
    Trailer(    const string& autore, const string& titolo, const string& descrizione, year_month_day gg_mm_aaInizioRilascio, 
                year_month_day gg_mm_aaFineRilascio, unsigned int visualizzaioni,  unsigned int durataMinuti, const string& path, 
                Formato formato, const Classificazione& target, unsigned int nProiezioniGiornaliere, Film* film);
    void associaFilm(Film* film);
    double calcolaIncasso() override;
    void estendiDataFineRilascio() override;
};

#endif 


