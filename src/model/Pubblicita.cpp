#include "Pubblicita.h"

Pubblicita::Pubblicita(const string& autore, const string& titolo, const string& descrizione, year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, unsigned int 
    visualizzaioni, unsigned int durataMinuti, Classificazione target):Media(autore,titolo, descrizione, gg_mm_aaInizioRilascio,gg_mm_aaFineRilascio,visualizzaioni,durataMinuti),_target(target){}


Classificazione Pubblicita::getTarget() const{
    return _target;
}
void Pubblicita::getTarget(Classificazione target) {
    _target=target;
}