#ifndef PODCAST_H
#define PODCAST_H

#include "Media.h"
#include "MediaVisitor.h"

class Puntata; // dichiarazione incompleta

/**
 * @class Podcast
 * @brief Rappresenta un podcast distribuito dal cinema nei canali appropriati. Deriva direttamente da Media
 * 
 * Un podcast ha un conduttore ed è composto da delle puntate. La durata del podcast corrisponde alla durata complessiva
 * di tutte le puntate che lo compongono. La data di fine rilascio di un podcast coincide con quella dell'ultima puntata pubblicata.
 * Invariante: Le puntate che compongono il podcast possono avere, tra di loro, date di fine rilascio diverse ma queste tra di loro devono sempre essere ordinate.
 * @note L'INVARIANTE É BELLA, VEDI SE CI SONO PROBLEMI DI COERENZA CON I METODI (soprattutto setDataFineRilascio delle puntate!!)
 */

class Podcast : public Media
{
private:
    string p_conduttore;
    vector<Puntata *> p_elencoPuntate;
    int isPuntataIn(Puntata * puntata) const;

public:
    Podcast(const string &titolo, const string &descrizione,
            Formato formato, Risoluzione risoluzione,
            const string &autore = "Sconosciuto", const string &path = "immGrigia", const string &conduttore="Sconosciuto");

    ~Podcast();
    
    /**
     * @brief Aggiunge una puntata al podcast, modificando opportunamente i campi dato del podcast stesso.
     * 
     * Le visualizzazioni del podcast aumentano di quelle della puntata aggiunta.
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
     * La data di fine rilascio viene aggiornata richiamando il metodo @ref aggiornaDate, in questo modo 
     * la nuova data di fine rilascio sarà quella dell’ultima puntata rimasta dopo la rimozione.
     * 
     * @param p Puntatore a puntata esistente
     */
    void rimuoviPuntata(Puntata * p);


    /**
     * @brief Metodi override per gestire i sottotitoli e le lingue del podcast
     * 
     * Le lingue e i sottotitoli del podcast sono relative a quelli presenti nelle puntate, quindi
     * deve essere impossibile aggiungere lingue o sottotitoli non presenti in quest'ultime. Si è deciso di overridare
     * aggiungiSottotitolo, aggiungiLingua, rimuoriSottotiolo e rimuoriLingua per mantenere le corrispondenze con le puntate:
     * una lingua può essere aggiunta solo se presente in almeno una puntata, mentre può essere rimossa solo se non appartiene a nessuna,
     * lo stesso vale per i sottotitoli. 
     */

    void aggiungiLingua(Lingua lingua) override;
    void aggiungiSottotitolo(Lingua lingua) override;
    void rimuoviLingua(Lingua lingua) override;
    void rimuoviSottotitolo(Lingua lingua) override;

    /**
     * @brief Estende di 1 giorno la data di fine rilascio del podcast, se non è ancora fuori produzione.
     *
     * estende di un giorno tutte le puntate che non sono fuori produzione, infine richiama il metodo
     * @ref aggiornaDate per aggiornare la data di fine 
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
    void disaccoppiaPuntata(Puntata* puntata);

    /**
     * @brief Aggiorna la data di fine e di inizio
     * 
     * Se la lista delle puntate non è vuota, riordina in base alla data di inizio e 
     * acquisisce come data di fine la più recente, mentre come data di inizio la meno recente 
     * 
     */
    void aggiornaDate();

    //visitor
    void accept(MediaVisitor* visitor)override;
};

#endif // PODCAST_H