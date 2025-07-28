#ifndef MEDIA_H
#define MEDIA_H


#include <chrono>
#include <string>
#include <iostream>

#include <vector>
#include "EnumClasses.h"

using namespace std;
using namespace std::chrono;


class Media {
private:
    string _autore;
    string _titolo;
    string _descrizione;
    year_month_day _dataInizioRilascio;  
    year_month_day _dataFineRilascio;  
    unsigned int _visualizzazioni;
    unsigned int _durataMinuti;
    vector<Lingua> _lingueDisponibili;
    vector<Lingua> _sottotitoliDisponibili;
    //aggiungere formato
    //aggiungere risoluzione
    //aggiungere cinema lista
public:

    Media(const string& autore, const string& titolo, const string& descrizione, year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio, unsigned int 
    visualizzaioni, unsigned int durataMinuti);

    //metodi set
    void setAutore(const string& autore);
    void setTitolo(const string& titolo);
    void setDescrizione(const string& descrizione);
    void setDataInizioRilascio(year_month_day gg_mm_aaInizioRilascio);
    virtual void setDataFineRilascio(year_month_day gg_mm_aaFineRilascio);
    void setVisualizzazioni(unsigned int visualizzazioni);
    void setDurataMinuti(unsigned int durata);
    void aggiungiLingua(Lingua lingua);
    void aggiungiSottotitolo(Lingua lingua);
    void rimuoviLingua(Lingua lingua);
    void rimuoviSottotitolo(Lingua lingua);

    //metodi get
    string getAutore() const;
    string getTitolo() const;
    string getDescrizione() const;
    year_month_day getDataInizioRilascio() const;
    year_month_day getDataFineRilascio() const;
    unsigned int getVisualizzazioni() const;
    unsigned int getDurataMinuti() const;
    vector<Lingua> getLingue() const;
    vector<Lingua> getSottotitoli() const;
    
    // altri metodi
    
    /** Calcola se il media è fuori produzione, ovvero se la data attuale >= dataFineRilascio
     * @return bool vero se il media è fuori produzione, falso altrimenti
     */
    bool FuoriProduzione() const;

    /** Ritorna il numero di giorni in cui è durata la campagna del media, ovvero DataFineRilascio-DataInizioRilascio
     * @return unsigned int numero di giorni in cui è durata la campagna del media 
    */
    unsigned int DurataCampagna() const;

    /* Astratti */
    virtual ~Media () = 0;
    virtual void estendiDataFineRilascio() = 0;
    virtual double calcolaIncasso() = 0;

};


#endif 

