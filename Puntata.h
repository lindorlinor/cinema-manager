#ifndef PUNTATA_H
#define PUNTATA_H

#include "Media.h"

class Podcast;
/**
 * @class Puntata
 * @brief Rappresenta un podcast distribuito dal cinema nei canali appropriati. Deriva direttamente da Media
 *
 * Una podcast ha un conduttore ed è composto da delle puntate. La durata del podcast corrisponde alla durata complessiva
 * di tutte le puntate che lo compongono. La data di fine rilascio di un podcast coincide con quella dell'ultima puntata pubblicata.
 * Invariante: Le puntate che compongono il podcast possono avere, tra di loro, date di fine rilascio diverse ma queste tra di loro devono sempre essere ordinate.
 */
class Puntata : public Media
{
private:
    vector<string> p_ospiti;
    Podcast *p_podcast;
    unsigned int p_numeroPubblicita;
    int isOspiteIn(const std::string& ospite) const;

public:
    Puntata(const string &autore, const string &titolo, const string &descrizione,
            year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio,
            unsigned int visualizzazioni, unsigned int durataMinuti, const string &path,
            Formato formato, Podcast *podcast, unsigned int numeroPubblicita);
    void aggiungiOspite(const string &);
    void rimuoviOspite(const string &);

    /**
     * @brief Estende di 7 giorni la data di fine rilascio dalla puntata corrente in poi.
     * 
     * Se il podcast associato non è fuori produzione, estende di 7 giorni la data di fine rilascio
     * della puntata corrente e di tutte quelle successive nell'elenco del podcast. Infine,
     * richiama il metodo @ref Podcast::estendiDataFineRilascio per aggiornare la data di fine rilascio del podcast stesso.
     * 
     * @note Il metodo non ha effetto se il podcast è fuori produzione o non esiste.
     */
    void estendiDataFineRilascio() override;

    /**
     * @brief Calcola l'incasso generato dalla puntata.
     *
     * L'incasso è calcolato moltiplicando il numero di visualizzazioni per il numero di pubblicità
     * presenti nella puntata, considerando un guadagno fisso di 0.05€ per ogni visualizzazione di una pubblicità.
     *
     * @return L'incasso totale della puntata in euro.
     */
    double calcolaIncasso() override;
    vector<string> getOspiti() const;
};

#endif // PUNTATA_H