#ifndef PUNTATA_H
#define PUNTATA_H

#include "Media.h"
#include "MediaVisitor.h"

class Podcast;
/**
 * @class Puntata
 * @brief Rappresenta un podcast distribuito dal cinema nei canali appropriati. Deriva direttamente da Media
 *
 * Una podcast ha un conduttore ed è composto da delle puntate. La durata del podcast corrisponde alla durata complessiva
 * di tutte le puntate che lo compongono. La data di fine rilascio di un podcast coincide con quella dell'ultima puntata pubblicata.
 * Invariante: Le puntate che compongono il podcast possono avere, tra di loro, date di fine rilascio diverse ma queste tra di loro devono sempre essere ordinate.
 */
class Puntata : public Media{
private:
    vector<string> p_ospiti;
    Podcast *p_podcast;
    unsigned int p_numeroPubblicita;
    int isOspiteIn(const std::string& ospite) const;

public:
    Puntata(const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
            year_month_day gg_mm_aaFineRilascio, unsigned int durataMinuti,
            Podcast *podcast, unsigned int numeroPubblicita, const string &autore = "Sconosciuto",
            const string &path = ":/images/default_podcast_puntate.png");

    ~Puntata();
    
    void aggiungiOspite(const string &);
    void rimuoviOspite(const string &);
    unsigned int getNumeroPubblicita() const;
    void setNumeroPubblicita(const int& num);

    /**
     * @brief Estende di un giorno la data di fine rilascio dalla puntata corrente
     * 
     * Se il podcast associato non è fuori produzione, estende di un giorno la data di fine rilascio
     * della puntata corrente. Infine richiama il metodo @ref Podcast::aggiornaDate per aggiornare la data di fine 
     * rilascio del podcast stesso
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

    /**
     * @brief oltre ad aggiungere una lingua o un sottotitolo a puntata, lo aggiunge anche a podcast
     *
     */
    void aggiungiLingua(Lingua lingua) override;
    void aggiungiSottotitolo(Lingua lingua) override;

    vector<string> getOspiti() const;

    /**
     * @brief Cambia la data di fine rilascio per puntata
     *
     * Puntata ha la necessità di fare un override su setDataFineRilascio in quanto la mmodifica della data
     * influisce sulla modifica della data di fine del podcast ad essa associato. Richiama il
     * metodo @ref Podcast::aggiornaDate per modificare la data di fine di podcast
     */

    void setDataFineRilascio(year_month_day gg_mm_aaFineRilascio) override;

    /**
     * @brief Cambia la data di inizio rilascio per puntata
     *
     * Puntata ha la necessità di fare un override su setDataInizioRilascio in quanto la mmodifica della data
     * influisce sulla modifica della data di inizio del podcast ad essa associato. Richiama il
     * metodo @ref Podcast::aggiornaDate per modificare la data di inizio di podcast
    */

    void setDataInizioRilascio(year_month_day gg_mm_aaFineRilascio) override;

    /**
     * @brief Cambia la data di inizio rilascio per puntata
     *
     * Puntata ha la necessità di fare un override su setDataFineRilascio in quanto la mmodifica della data
     * influisce sulla modifica della data di fine rilascio delle puntate che seguono. Richiama il
     * metodo @ref Puntata::IteraModificaDataFineRilascioPuntate per permettere la modifica delle puntate che seguono
     */

     void associaPodcast(Podcast* podcast); 

     Podcast* getPodcast()const;

    //visitor
    void accept(MediaVisitor* visitor)override;
};

#endif // PUNTATA_H