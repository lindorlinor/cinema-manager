#include "Inserzione.h"

Inserzione::Inserzione(const string& regista, const string& titolo, const string& descrizione, year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, unsigned int 
    visualizzaioni, unsigned int durataMinuti, const Classificazione& target,unsigned int nProiezioniGiornaliere, const string& aziendaInserzionista, int costoProiezione):Pubblicita(regista, titolo,descrizione, gg_mm_aaInizioRilascio,gg_mm_aaFineRilascio, visualizzaioni, durataMinuti,target,nProiezioniGiornaliere),_aziendaInserzionista(aziendaInserzionista),COSTO_FISSO_PROIEZIONE(costoProiezione){}



void Inserzione::estendiDataFineRilascio() {
    if (!FuoriProduzione()) {
        year_month_day dataFine = getDataFineRilascio() + months{1};
        setDataFineRilascio(year_month_day(dataFine));
    }
}


double Inserzione::calcolaIncasso() {
    return DurataCampagna()*getNProiezioniGiornaliere()*COSTO_FISSO_PROIEZIONE;
}
