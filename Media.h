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
    string m_autore;
    string m_titolo;
    string m_descrizione;
    year_month_day m_dataInizioRilascio;  
    year_month_day m_dataFineRilascio;  
    unsigned int m_visualizzazioni;
    unsigned int m_durataMinuti;
    vector<Lingua> m_lingueDisponibili;
    vector<Lingua> m_sottotitoliDisponibili;
    //aggiungere formato
    //aggiungere risoluzione
    //aggiungere cinema lista
    //aggiungere path
public:

    Media(  const string& autore, const string& titolo, const string& descrizione, year_month_day gg_mm_aaInizioRilascio, 
            year_month_day gg_mm_aaFineRilascio, unsigned int visualizzaioni, unsigned int durataMinuti);

    // //metodi set
    // void setAutore(const string& autore);
    // void setTitolo(const string& titolo);
    // void setDescrizione(const string& descrizione);
    // void setDataInizioRilascio(year_month_day gg_mm_aaInizioRilascio);
    // void setVisualizzazioni(unsigned int visualizzazioni);
    // void setDurataMinuti(unsigned int durata);
    
    // //metodi get
    // string getAutore() const;
    // string getTitolo() const;
    // string getDescrizione() const;
    // unsigned int getDurataMinuti() const;
    // vector<Lingua> getLingue() const;
    // vector<Lingua> getSottotitoli() const;
    
    void aggiungiLingua(Lingua lingua);
    void aggiungiSottotitolo(Lingua lingua);
    void rimuoviLingua(Lingua lingua);
    void rimuoviSottotitolo(Lingua lingua);
    
    // Calcola se il media è fuori produzione, ovvero se la data attuale >= dataFineRilascio
    // @return bool vero se il media è fuori produzione, falso altrimenti
    bool FuoriProduzione() const;
    
    // Ritorna il numero di giorni in cui è durata la campagna del media, ovvero DataFineRilascio-DataInizioRilascio
    // @return unsigned int numero di giorni in cui è durata la campagna del media 
    
    unsigned int DurataCampagna() const;
    
    //metodi get e set
    unsigned int getVisualizzazioni() const;
    year_month_day getDataInizioRilascio() const; 
    year_month_day getDataFineRilascio() const;
    virtual void setDataFineRilascio(year_month_day gg_mm_aaFineRilascio);
    
    
    //metodi astratti 
    virtual ~Media () = 0;
    virtual void estendiDataFineRilascio() = 0;
    virtual double calcolaIncasso() = 0;

};


#endif 

