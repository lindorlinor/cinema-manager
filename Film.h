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
    vector<string> f_attoriPrincipali;
    Genere f_genere;
    Classificazione f_classificazione;
    vector<Trailer *> trailers;
    double f_valutazione;
    string f_casaDiProduzione;
    unsigned int f_nPostCredit;
    double f_costoBiglietto;
    int isTrailerIn(Trailer *trailer) const;

public:
    Film(const string &regista, const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
         year_month_day gg_mm_aaFineRilascio, unsigned int visualizzazioni, unsigned int durataMinuti, const string &path,
         Formato formato, Genere genere, Classificazione classificazione, double valutazione, const string &casaDiProduzione,
         unsigned int nPostCredit, double costoBiglietto);

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
    // void setValutazione(double valutazione);
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

        
    // i metodi puri

    /**
     * @brief Estende la data di fine rilascio del film aggiungendo 7 giorni. Modifica la data dei trailer associati che non sono fuori produzione.
     * Estende la data dei trailer associati richiamando il metodo @ref setDataFineRilascio(chrono::year_month_day) "setDataFineRilascio(year_month_day gg_mm_aaFineRilascio)"
     */
    void estendiDataFineRilascio() override;

    /**
     * @brief Calcola l'incasso della distribuzione del film al cinema.
     * @return L'incasso calcolato.
     * L'incasso del film si calcola moltiplicando le visualizzazioni per il costo del biglietto del film.
     */
    double calcolaIncasso() override;

    ~Film();
};

#endif
