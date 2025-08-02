#ifndef FILM_H
#define FILM_H

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include "Media.h"
#include "Trailer.h"
#include "EnumClasses.h"
using namespace std;
#include <chrono>
using namespace std::chrono;

/**
 * @class Film
 * @brief Rappresenta un film distribuito al cinema.
 */
class Film : public Media
{
private:
Genere f_genere;
    vector<string> f_attoriPrincipali;
    Classificazione f_target;
    vector<Trailer *> trailers;
    string f_casaDiProduzione;
    unsigned int f_nPostCredit;
    double f_costoBiglietto;
    double f_valutazione;
    int isTrailerIn(Trailer *trailer) const;

public:
    Film(const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
         year_month_day gg_mm_aaFineRilascio, unsigned int durataMinuti, Formato formato, Risoluzione risoluzione,
         Genere genere, const string &casaDiProduzione, unsigned int nPostCredit, double costoBiglietto, 
         const string &autore = "Sconosciuto", const string &path = "immGrigia", Classificazione target = Classificazione::TUTTI);
    
    
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
    // void aggiungiAttore(const string& nomeAttore);
    // void rimuoviAttore(const string& nomeAttore);
    // void setGenere(const string& genere);
    // void setClassificazione(Classificazione classificazione);
    // void setCasaDiProduzione(const string& casaDiProduzione);
    // void setNPostCredit(unsigned int nPostCredit);
    // void setCostoBiglietto(double costoBiglietto);

    // // metodi get
    // string getCasaDiProduzione() const;
    // unsigned int getNPostCredit() const;
    Genere getGenere() const;
    double getValutazione() const;
    Classificazione getClassificazione() const;
    double getCostoBiglietto() const;
    // metodi per aggiungere e togliere i trailer
    void aggiungiTrailer(Trailer *trailer);
    void rimuoviTrailer(Trailer *trailer);

    void disaccoppiaTrailer(Trailer* trailer);
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
};

#endif
