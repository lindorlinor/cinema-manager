#include "Pubblicita.h"

Pubblicita::Pubblicita(     const string& autore, const string& titolo, const string& descrizione, 
                            year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, 
                            unsigned int visualizzaioni, unsigned int durataMinuti, Classificazione target, 
                            unsigned int nProiezioniGiornaliere):
                            
                            Media(autore,titolo, descrizione, gg_mm_aaInizioRilascio,gg_mm_aaFineRilascio,
                            visualizzaioni,durataMinuti),p_target(target), p_nProiezioniGiornaliere(nProiezioniGiornaliere){}

// Classificazione Pubblicita::getTarget() const{
//     return p_target;
// }
// void Pubblicita::setTarget(Classificazione target) {
//     p_target=target;
// }