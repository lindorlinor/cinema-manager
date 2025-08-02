#include "Pubblicita.h"

Pubblicita::Pubblicita(     const string& autore, const string& titolo, const string& descrizione, 
                            year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, 
                            unsigned int visualizzaioni, unsigned int durataMinuti, const string& path, 
                            Formato formato, 
                            unsigned int nProiezioniGiornaliere):
                            
                            Media(autore,titolo, descrizione, gg_mm_aaInizioRilascio,gg_mm_aaFineRilascio,
                            visualizzaioni,durataMinuti, path, formato), 
                            p_nProiezioniGiornaliere(nProiezioniGiornaliere){}


unsigned int Pubblicita::getNProiezioniGiornaliere() const{
    return p_nProiezioniGiornaliere;
}
