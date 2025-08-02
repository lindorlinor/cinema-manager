#ifndef TRAILER_H
#define TRAILER_H

#include "Pubblicita.h"
class Film; //forward declaration


/**
 * @class Trailer
 * @brief Rappresenta un trailer proiettato al cinema.
 * 
 * Un trailer è una pubblicità proiettata nelle sale del cinema. Un trailer è sempre associato ad un film esistente del cinema.
 */
class Trailer : public Pubblicita{
    Film* t_film;
    double calcolaTassoDiStima() const;
public:
    Trailer(    const string& autore, const string& titolo, const string& descrizione, year_month_day gg_mm_aaInizioRilascio, 
                year_month_day gg_mm_aaFineRilascio, unsigned int visualizzaioni,  unsigned int durataMinuti, const string& path, 
                Formato formato, unsigned int nProiezioniGiornaliere, Film* film);

    /**
     * @brief assegna un film ad un Trailer
     * 
     * @param film 
     * @note non è necessario alcun "dissocia film" perchè un trailer non può esistere senza film. La gui lo permetterà richiamando nuovamente associaFilm e fornendo un film esistente
     */
    void associaFilm(Film* film); 

     /**
     * @brief Imposta la data di fine rilascio del trailer.
     *
     * Imposta la data di fine rilascio del trailer verificando 
     * che questa non sia superiore a quella del film associato. In caso
     * negativo imposta la data di fine del trailer
     * 
     * @param gg_mm_aaFineRilascio La data di fine rilascio del trailer
     * @note non si controlla se il trailer non è fuori produzione perchè non è richiesto per "contratto del metodo", quello è compito di estendi
     * @note nella gui ovviamente dovrà essere avvisato l'utente che la data è maggiore e quindi viene messa quella del film.  
     */ 
    void setDataFineRilascio(year_month_day gg_mm_aaFineRilascio) override; 
   
    /**
     * @brief Aggiorna la data di fine rilascio del trailer con quella del film associato, se non è fuori produzione.
     *
     * Estende la validità del trailer assegnandogli la stessa data di fine rilascio
     * del film associato, a condizione che il trailer non sia contrassegnato come fuori produzione.
     */
    void estendiDataFineRilascio() override;

    /**
     * @brief Calcola l'incasso della distribuzione del trailer al cinema.
     * 
     * L'incasso calcolato è una stima che si basa sulle visualizzazioni del trailer e sulle caratteristiche del flim associato. Il metodo fa uso
     * di @ref calcolaTassoDiStima.
     * @return L'incasso calcolato.
     * @note fare documentazione calcolaTassoDiStima
     */
    double calcolaIncasso() override;
    
};

#endif 


