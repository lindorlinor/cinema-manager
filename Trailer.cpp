#include "Trailer.h"
#include "Film.h"

Trailer::Trailer(const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
                year_month_day gg_mm_aaFineRilascio, unsigned int durataMinuti, Formato formato, Risoluzione risoluzione,
                unsigned int nProiezioniGiornaliere, Film *film, const string &autore, 
                const string &path) : 
                        Pubblicita(titolo, descrizione, gg_mm_aaInizioRilascio, (gg_mm_aaFineRilascio>film->getDataFineRilascio()?film->getDataFineRilascio():gg_mm_aaFineRilascio),
                                    durataMinuti, formato, risoluzione, nProiezioniGiornaliere, autore, path), t_film(film){}


void Trailer::associaFilm(Film* film) {
    if (!film || t_film == film)
        return;
        
    if (t_film){
        t_film->disaccoppiaTrailer(this);
    }
    t_film = film;
    if (getDataFineRilascio() > film->getDataFineRilascio()) {
        setDataFineRilascio(film->getDataFineRilascio());
    }
    film->aggiungiTrailer(this);
}   



void Trailer::setDataFineRilascio(year_month_day gg_mm_aaFineRilascio){ 
    if(gg_mm_aaFineRilascio>t_film->getDataFineRilascio())
        t_film->getDataFineRilascio();
    else 
        Pubblicita::setDataFineRilascio(gg_mm_aaFineRilascio);
}

void Trailer::estendiDataFineRilascio() {
    if (!FuoriProduzione() && t_film) {
        setDataFineRilascio(t_film->getDataFineRilascio());
    }
}

double Trailer::calcolaTassoDiStima() const
{
    double tasso = 0.1;
    if (t_film->getValutazione() > 8.0)
        tasso += 0.03;
    if (t_film->getGenere() == Genere::Azione || t_film->getGenere() == Genere::Supereroi)
        tasso += 0.02;
    if (t_film->getClassificazione() == Classificazione::DICIOTTO_PIU)
        tasso -= 0.02;

    return std::clamp(tasso, 0.05, 0.15); // Limita il valore tra 0.05 e 0.15
}

double Trailer::calcolaIncasso()
{
    if (t_film)
    {
        double tassoDiStima = calcolaTassoDiStima();
        return getVisualizzazioni() * tassoDiStima * t_film->getCostoBiglietto();
    }
    return 0.0;
}


Film* Trailer::getFilm() const {
    return t_film;
}

