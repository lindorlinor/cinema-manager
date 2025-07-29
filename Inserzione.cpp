#include "Inserzione.h"

Inserzione::Inserzione( const string& regista, const string& titolo, const string& descrizione, 
                        year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, unsigned int 
                        visualizzaioni, unsigned int durataMinuti, const Classificazione& target,
                        unsigned int nProiezioniGiornaliere, const string& aziendaInserzionista, double costoProiezione):
                        
                        Pubblicita(regista, titolo,descrizione, gg_mm_aaInizioRilascio,gg_mm_aaFineRilascio, visualizzaioni, 
                        durataMinuti,target,nProiezioniGiornaliere),i_aziendaInserzionista(aziendaInserzionista),
                        i_costoFissoProiezione(costoProiezione){}


void Inserzione::estendiDataFineRilascio() {
    if (!FuoriProduzione()) {
        // Converti year_month_day a sys_days per sommare giorni
        year_month_day dataFine = getDataFineRilascio() + months{1};
        setDataFineRilascio(year_month_day(dataFine));
    }
}

double Inserzione::calcolaIncasso() {
    return getVisualizzazioni()*i_costoFissoProiezione;
}
