#include "Trailer.h"
#include "Film.h"
Trailer::Trailer(   const string& regista, const string& titolo, const string& descrizione, 
                    year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, unsigned int 
                    visualizzaioni, unsigned int durataMinuti, const string& path, 
                    Formato formato, const Classificazione& target,
                    unsigned int nProiezioniGiornaliere, Film* film):
                    Pubblicita(regista, titolo,descrizione, gg_mm_aaInizioRilascio,gg_mm_aaFineRilascio, 
                    visualizzaioni, durataMinuti,path, formato,target, nProiezioniGiornaliere),t_film(film){}

void Trailer::associaFilm(Film* film){
    t_film=film;
}
//prende la data di fine rilascio del film ad esso associato e imposta quella
void Trailer::estendiDataFineRilascio() {
    if (!FuoriProduzione() && t_film) {
        setDataFineRilascio(t_film->getDataFineRilascio());
    }
}

double Trailer::calcolaTassoDiStima() const {
    double tasso = 0.1; 
    if (t_film->getValutazione() > 8.0) tasso += 0.03;
    if (t_film->getGenere() == "Azione" || t_film->getGenere() == "Supereroi") tasso += 0.02;
    if (t_film->getClassificazione() == Classificazione::DICIOTTO_PIU) tasso -= 0.02;

    
    return std::clamp(tasso, 0.05, 0.15); // Limita il valore tra 0.05 e 0.15
}

double Trailer::calcolaIncasso() {
    if (t_film) {
        double tassoDiStima = calcolaTassoDiStima();
        return getVisualizzazioni() * tassoDiStima * t_film->getCostoBiglietto();
    }
    return 0.0; 
}
