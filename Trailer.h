#ifndef TRAILER_H
#define TRAILER_H

#include "Pubblicita.h"
class Film; // forward declaration

class Trailer : public Pubblicita
{
    Film *t_film;
    double calcolaTassoDiStima() const;

public:
    Trailer(const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
            year_month_day gg_mm_aaFineRilascio, unsigned int durataMinuti, Formato formato, Risoluzione risoluzione,
            unsigned int nProiezioniGiornaliere, Film *film, const string &autore = "Sconosciuto", 
            const string &path = "immGrigia");
    void associaFilm(Film *film);
    // ha senso che la data di fine rilascio sia uguale a quella del film
    double calcolaIncasso() override;
    void estendiDataFineRilascio() override;
};

#endif
