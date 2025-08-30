#ifndef MEDIA_H
#define MEDIA_H

#include <chrono>
#include <string>
#include <iostream>

#include <vector>
#include <random>
#include "EnumClasses.h"

using namespace std;
using namespace std::chrono;

class MediaVisitor;

/**
 * @class Media
 * @brief Rappresenta un media generico della biblioteca del cinema.
 *
 * Classe base astratta per tutti i tipi di media: film, pubblicità, podcast e puntate.
 */
class Media
{
private:
    string m_titolo;
    string m_descrizione;
    year_month_day m_dataInizioRilascio;
    year_month_day m_dataFineRilascio;
    unsigned int m_durataMinuti;
    Formato m_formato;
    Risoluzione m_risoluzione;
    string m_autore;
    string m_imPath;
    year_month_day m_dataLastViewUpdate;
    unsigned int m_visualizzazioni;
    
    vector<Lingua> m_lingueDisponibili;
    vector<Lingua> m_sottotitoliDisponibili;
public:
    Media(const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
          year_month_day gg_mm_aaFineRilascio, unsigned int durataMinuti, Formato formato, Risoluzione risoluzione,
          const string &autore = "Sconosciuto", const string &imPath = ":/images/default.png");

    
    // //metodi get
    string getAutore() const;
    string getTitolo() const;
    string getDescrizione() const;
    vector<Lingua> getLingue() const;
    vector<Lingua> getSottotitoli() const;
    string getImPath() const;
    
    // modifica lingua e sottotitoli
    virtual void aggiungiLingua(Lingua lingua);
    virtual void aggiungiSottotitolo(Lingua lingua);
    virtual void rimuoviLingua(Lingua lingua);
    virtual void rimuoviSottotitolo(Lingua lingua);
    
    /**
     * @brief Verifca se il media è correntemente distribuito nei canali del cinema.
     * 
     * Il media è fuori produzione se la data di fine rilascio è < della data corrente.
     * 
     * @return True se il media è fuori produzione
     */
    bool FuoriProduzione() const;
    
    /**
     * @brief Indica il numero di giorni in cui il media è distribuito nei canali del cinema.
     * 
     * Il numero di giorni contando i giorni in cui il film non è fuori produzione.
     * 
     * @return Il numero di giorni in cui il media è attivo nei canali.
     */
    unsigned int DurataCampagna() const;
    
    // metodi get e set
    void setPath(const string& path);
    void setFormato(const Formato& formato);
    void setRisoluzione(const Risoluzione& risoluzione);
    void setDescrizione(const string& descrizione);
    void setAutore(const string& autore);
    void setTitolo(const string& titolo);
    unsigned int getVisualizzazioni() const;
    year_month_day getDataInizioRilascio() const;
    year_month_day getDataFineRilascio() const;
    year_month_day getDataLastViewUpdate() const;
    unsigned int getDurataMinuti() const;
    Formato getFormato()const;
    Risoluzione getRisoluzione()const;
    
    void setVisualizzazioni(unsigned int visualizzazioni);
    void setDurataMinuti(unsigned int durata);
    virtual void setDataInizioRilascio(year_month_day gg_mm_aaInizioRilascio);
    virtual void setDataFineRilascio(year_month_day gg_mm_aaFineRilascio);
    
    /**
     * @brief assegna in automatico il numero di visualizzazioni
     * 
     * assegna un numero di visualizzazioni in automatico simulando una reale attività, aggiunge un numero randomico di
     * visualizzazioni per ogni giorno dalla data di InizioRilascio finché il media non raggiunge la data di FineRilascio
     */

    void IncrementaVisualizzazioni();
    
    // metodi astratti
    virtual ~Media() = 0;
    
    /**
     * @brief Estende la data di fine rilascio a seconda del tipo di media e del suo stato corrente.
     * 
     * Questa funzione deve essere implementata dalle classi derivate.
     */
    virtual void estendiDataFineRilascio() = 0;

    /**
     * @brief Calcola l'incasso della distribuzione del media che viene fatta nei canali appropriati del cinema.
     * 
     * Questa funzione deve essere implementata dalle classi derivate.
     * 
     * @return L'incasso calcolato
     */
    virtual double calcolaIncasso() = 0;

    //visitor
    virtual void accept(MediaVisitor* visitor) = 0;

};

#endif
