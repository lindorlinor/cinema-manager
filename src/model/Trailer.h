#ifndef TRAILER_H
#define TRAILER_H

#include "Pubblicita.h"
class Film; //forward declaration

class Trailer : public Pubblicita{
    Film* _film;
    double calcolaTassoDiStima() const;
public:
    Trailer(const string& autore, const string& titolo, const string& descrizione, year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, unsigned int 
        visualizzaioni, unsigned int durataMinuti, const Classificazione& target, Film* f);
    ~Trailer();
    void associaFilm(Film* film);
    //ha senso che la data di fine rilascio sia uguale a quella del film
    double calcolaIncasso() override;
    void estendiDataFineRilascio() override;
};

#endif 


