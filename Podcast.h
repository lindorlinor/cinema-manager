#ifndef PODCAST_H
#define PODCAST_H

#include "Media.h"

class Puntata; // dichiarazione incompleta

/**
 * @class Podcast
 * @brief Rappresenta un podcast distribuito dal cinema nei canali appropriati. Deriva direttamente da Media
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
     * @brief Aggiunge una puntata al podcast, modificando opportunamente i campi dato del podcast stesso.
     * 
     * Le visualizzazioni del podcast aumentano di quelle della  aggiunta.
     * La durata viene incrementata di quella della puntata aggiunta.
     * La data di fine rilascio del podcast viene aggiornata a quella della puntata aggiunta.
     * L'inserimento di una puntata con DataFineRilascio < della DataFineRilascio del podcast corrente lancia un'eccezione invalid_argument 
     * 
     * @param p Puntatore a puntata esistente
     */
    //TO DO: DA MODIFICARE FORSE LA DOCUMENTAZIONE su come è gestita la parte con l'eccezione
    void aggiungiPuntata(Puntata * p);

    /**
     * @brief Rimuove una puntata al podcast, modificando opportunamente i campi dato del podcast stesso.
     * 
     * Le visualizzazioni del podcast diminuiscono di quelle della puntata rimossa.
     * La durata viene decrementata di quella della puntata rimossa.
     * La data di fine rilascio viene aggiornata solo se la puntata rimossa era l’ultima del podcast. In tal caso, la nuova data di fine rilascio sarà quella dell’ultima puntata rimasta dopo la rimozione.
     * Se, invece, dopo la rimozione non ci sono più puntate, la data di fine rilascio rimane invariata.
     * 
     * @param p Puntatore a puntata esistente
     */
    void rimuoviPuntata(Puntata * p);


    /**
     * @brief Estende di 7 giorni la data di fine rilascio del podcast, se non è ancora fuori produzione.
     *
     * non ha alcuna azione sulle puntate perché la data di fine rilascio del podcast dipende da quella
     * di fine rilascio delle stesse puntate, quindi non è possibile estendere la fine del podcast senza 
     * prima estendere quella delle puntate, il quale metodo richiama questo stesso metodo per aggiornare
     * la data di fine rilascio del podcast
     */

    // TO DO: preferisco cambiare la logica, non 7 giorni ma magari 3? 2? 1? idkkkkk però potremmo cambiarlo,
    // inoltre preferirei che se fai estendi allora estende la data dell'ultima puntata (così rimane valido che 
    //la data di fine rilascio dell'ultima puntata del podcast = data fine rilascio podcast, logica espressa in aggiungiPuntata e (circa) in rimuoviPuntata)
    // il commento doxy diventerebbe:
    /* 
    * @brief Estende di 2 giorni la data di fine rilascio del podcast, se non è ancora fuori produzione.
    * 
    * L'estensione della data di fine rilascio ha effetto di aumentare dello stesso numero di giorni la data di fine rilascio dell'ultima puntata inserita.
    */
    void estendiDataFineRilascio() override;

    /**
     * @brief Calcola l'incasso totale generato dal podcast.
     * 
     * Somma gli incassi di tutte le puntate presenti nella lista del podcast richiamando @ref Puntata::calcolaIncasso
     * Le puntate null eventualmente presenti vengono ignorate.
     * 
     * @return L'incasso totale del podcast.
     */

    double calcolaIncasso() override;

    vector<Puntata *> getElencoPuntate() const;
};

#endif // PODCAST_H