#include "Inserzione.h"

Inserzione::Inserzione(const string& regista, const string& titolo, const string& descrizione, year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, unsigned int 
    visualizzaioni, unsigned int durataMinuti, const Classificazione& target,const string& aziendaInserzionista, int nProiezioniGiornaliere ):Pubblicita(regista, titolo,descrizione, gg_mm_aaInizioRilascio,gg_mm_aaFineRilascio, visualizzaioni, durataMinuti,target),_aziendaInserzionista(aziendaInserzionista),_nProiezioniGiornaliere(nProiezioniGiornaliere){}


//TODO da implementare
void Inserzione::estendiDataFineRilascio() {
   
}


double Inserzione::calcolaIncasso() {
    //TO DO da implementare
}
