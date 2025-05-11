#ifndef FILM_H
#define FILM_H


#include <string>
#include <vector>
#include <map>
#include <chrono>
#include "Media.h"
#include "Trailer.h"
#include "../include/EnumClasses.h"
using namespace std;
using namespace std::chrono;



class Film: public Media{
private:
    vector<string> _attoriPrincipali;
    string _genere;
    Classificazione _classificazione;
    vector<Trailer*> trailers;
    double _valutazione;
    string _casaDiProduzione;
    unsigned int _nPostCredit;
    double _costoBiglietto;

    //ritorna vero se il trailer è già all'interno della lista, falso altrimenti
    bool isInTrailer(Trailer * trailer) const;
public:
    Film(const string& regista, const string& titolo, const string& descrizione, year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, unsigned int visualizzazioni, unsigned int durataMinuti, const string& genere, Classificazione classificazione, double valutazione, const string& casaDiProduzione,unsigned int nPostCredit,double costoBiglietto);
    
    //metodi set
    // void setDataFineRilascio(year_month_day gg_mm_aaFineRilascio) override;
    void aggiungiAttore(const string& nomeAttore);
    void rimuoviAttore(const string& nomeAttore);
    void setGenere(const string& genere);
    void setClassificazione(Classificazione classificazione);
    void setValutazione(double valutazione);
    void setCasaDiProduzione(const string& casaDiProduzione);
    void setNPostCredit(unsigned int nPostCredit);
    void setCostoBiglietto(double costoBiglietto);
    
    // metodi get
    string getGenere() const;
    Classificazione getClassificazione() const;
    double getValutazione() const;
    string getCasaDiProduzione() const;
    unsigned int getNPostCredit() const;
    double getCostoBiglietto() const;

    //metodi per aggiungere e togliere i trailer
    void aggiungiTrailer(Trailer* trailer);
    void rimuoviTrailer(Trailer* trailer);
    //i metodi puri
    double calcolaIncasso() override;
    void estendiDataFineRilascio() override;



};

#endif 

