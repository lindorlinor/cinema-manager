#ifndef PODCAST_H
#define PODCAST_H

#include "Media.h"

class Puntata; // dichiarazione incompleta

/**
 * @class Podcast
 * @brief Rappresenta un podcast distribuito dal cinema nei canali appropriati.
 * 
 * Un podcast ha un conduttore ed è composto da delle puntate. La durata del podcast corrisponde alla durata complessiva
 * di tutte le puntate che lo compongono. La data di fine rilascio di un podcast coincide con quella dell'ultima puntata pubblicata.
 * Invariante: Le puntate che compongono il podcast possono avere, tra di loro, date di fine rilascio diverse ma queste tra di loro devono sempre essere ordinate.
 */

 //TO DO : L'INVARIANTE É BELLA, VEDI SE CI SONO PROBLEMI DI COERENZA CON I METODI (soprattutto setDataFineRilascio delle puntate!!)
class Podcast : public Media
{
private:
    string p_conduttore;
    vector<Puntata *> p_elencoPuntate;
    int isPuntataIn(Puntata * puntata) const;

public:
    Podcast(const string &autore, const string &titolo, const string &descrizione,
            year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio,
            unsigned int visualizzazioni, unsigned int durataMinuti, const string &path,
            Formato formato, const string &conduttore);

    ~Podcast();
    
    /**
     * @brief Aggiunge una puntata al podcast, modificando opportunamente i campi dati del podcast stesso.
     * 
     * Le visualizzazioni del podcast aumentano di quelle della puntata.
     * La durata viene incrementata di quella della puntata.
     * La data di fine rilascio del podcast viene aggiornata a quella della puntata.
     * L'inserimento di una puntata con DataFineRilascio < della DataFineRilascio del podcast corrente lancia un'eccezione invalid_argument 
     * 
     * @param p Puntatore a puntata esistente associata al Podcast
     */
    //TO DO: DA MODIFICARE FORSE LA DOCUMENTAZIONE su come è gestita la parte con l'eccezione
    void aggiungiPuntata(Puntata * p);
    void rimuoviPuntata(Puntata * p);

    void estendiDataFineRilascio() override;
    double calcolaIncasso() override;

    vector<Puntata *> getElencoPuntate() const;
};

#endif // PODCAST_H