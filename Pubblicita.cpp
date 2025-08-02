#include "Pubblicita.h"

Pubblicita::Pubblicita(const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
                       year_month_day gg_mm_aaFineRilascio, unsigned int durataMinuti, Formato formato, Risoluzione risoluzione,
                       unsigned int nProiezioniGiornaliere, const string &autore, const string &path) :

                                    Media(titolo, descrizione, gg_mm_aaInizioRilascio, gg_mm_aaFineRilascio,
                                    durataMinuti, formato, risoluzione, autore, path),
                                    p_nProiezioniGiornaliere(nProiezioniGiornaliere){}


unsigned int Pubblicita::getNProiezioniGiornaliere() const
{
    return p_nProiezioniGiornaliere;
}
