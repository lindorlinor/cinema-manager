#ifndef FILM_H
#define FILM_H

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include "Media.h"
#include "Trailer.h"
#include "EnumClasses.h"
#include "MediaVisitor.h"
using namespace std;
#include <chrono>
using namespace std::chrono;

/**
 * @class Film
 * @brief Rappresenta un film distribuito al cinema.
 *
 * Un film possiede un vettore di trailer. L'associazione tra film e trailer è sempre bidirezionale:
 * il trailer è collegato al film e il film al trailer. L'invariante è soddisfatta in ogni stato stabile del programma.
 * @see Trailer
 */
class Film : public Media
{
private:
    unsigned int f_nPostCredit;
    double f_costoBiglietto;
    string f_casaDiProduzione;
    Classificazione f_target;
    double f_valutazione;
    vector<Genere> f_genere;
    vector<string> f_attoriPrincipali;
    vector<Trailer *> trailers;
    int isTrailerIn(Trailer *trailer) const;

public:
    Film(const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
         year_month_day gg_mm_aaFineRilascio, unsigned int durataMinuti, Formato formato, Risoluzione risoluzione,
         unsigned int nPostCredit, double costoBiglietto, const string &casaDiProduzione = "Sconosciuto",
         const string &autore = "Sconosciuto", const string &path = ":/images/default_film.png", Classificazione target = Classificazione::TUTTI);

    // //metodi set

    /**
     * @brief Imposta una specifica data di fine rilascio del film e aggiorna quella dei trailer associati.
     *
     * Imposta una nuova data di fine rilascio per il film e assegna la stessa data
     * a tutti i trailer associati che non sono fuori produzione.
     *
     * @param gg_mm_aaFineRilascio La nuova data di fine rilascio del film.
     *
     */
    void setDataFineRilascio(year_month_day gg_mm_aaFineRilascio) override;
    void aggiungiGenere(const Genere &genere);
    void rimuoviGenere(const Genere &genere);
    void setTarget(Classificazione target);
    void setCasaDiProduzione(const string &casaDiProduzione);
    void setNPostCredit(unsigned int nPostCredit);
    void setCostoBiglietto(double costoBiglietto);
    void aggiungiAttore(const string &nomeAttore);
    void rimuoviAttore(const string &nomeAttore);

    // // metodi get
    Classificazione getTarget() const;
    string getCasaDiProduzione() const;
    unsigned int getNPostCredit() const;
    vector<Genere> getGeneri() const;
    double getValutazione() const;
    double getCostoBiglietto() const;
    const vector<string> &getAttoriPrincipali() const;
    // metodi per aggiungere e togliere i trailer
    void aggiungiTrailer(Trailer *trailer);

    const vector<Trailer *> &getTrailers() const;
    /**
     * @brief Disaccoppia un trailer dal film ed elimina definitivamennte il trailer
     *
     * @see disaccoppiaTrailer
     *
     * @param trailer
     * @note Duplicazione di codice tra @ref rimuoviTrailer e @ref disaccoppiaTrailer perchè è minimo
     */
    void rimuoviTrailer(Trailer *trailer);

    /**
     * @brief Disaccoppia un trailer dal film
     *
     * @param trailer
     */
    void disaccoppiaTrailer(Trailer *trailer);

    // i metodi puri
    /**
     * @brief  Estende di 7 giorni la data di fine rilascio del film, se non è ancora fuori produzione. Modifica la data dei trailer associati che non sono fuori produzione.
     * Estende la data dei trailer associati richiamando il metodo @ref setDataFineRilascio
     */
    void estendiDataFineRilascio() override;

    /**
     * @brief Calcola l'incasso della distribuzione del film al cinema.
     *
     * L'incasso del film si calcola moltiplicando le visualizzazioni per il costo del biglietto del film.
     *
     * @return L'incasso calcolato.
     */
    double calcolaIncasso() override;

    void setValutazione();

    ~Film();

    // visitor
    void accept(MediaVisitor *visitor) override;
};

#endif
