#include "Trailer.h"
#include "Film.h"

Trailer::Trailer(const string& regista, const string& titolo, const string& descrizione, year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, unsigned int 
    visualizzaioni, unsigned int durataMinuti, const Classificazione& target, Film* film):Pubblicita(regista, titolo,descrizione, gg_mm_aaInizioRilascio,gg_mm_aaInizioRilascio, visualizzaioni, durataMinuti,target),_film(film){}

Trailer::~Trailer(){
    delete _film;
}

void Trailer::associaFilm(Film* film){
    _film=film;
}
//mi fa strano che sia uguale a film
void Trailer::estendiDataFineRilascio(){
    if(!FuoriProduzione()){
        year_month_day data = getDataFineRilascio();
        setDataFineRilascio(data.year()/data.month()/(data.day()+days{7}));
    }
}

double Trailer::calcolaTassoDiStima() const {
    double tasso = 0.1; 
    if (_film->getValutazione() > 8.0) tasso += 0.03;
    if (_film->getGenere() == "Azione" || _film->getGenere() == "Supereroi") tasso += 0.02;
    if (_film->getClassificazione() == Classificazione::DICIOTTO_PIU) tasso -= 0.02;

    
    return std::clamp(tasso, 0.05, 0.15); // Limita il valore tra 0.05 e 0.15
}


double Trailer::calcolaIncasso() {
    if (_film) {
        double tassoDiStima = calcolaTassoDiStima();
        return getVisualizzazioni() * tassoDiStima * _film->getCostoBiglietto();
    }
    return 0.0; 
}
