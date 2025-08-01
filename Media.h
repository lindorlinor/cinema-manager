#ifndef MEDIA_H
#define MEDIA_H

#include <chrono>
#include <string>
#include <iostream>

#include <vector>
#include "EnumClasses.h"

using namespace std;
using namespace std::chrono;

/**
 * @class Media
 * @brief Rappresenta un media generico della biblioteca del cinema.
 *
 * Classe base astratta per tutti i tipi di media: film, pubblicità, podcast e puntate.
 */
class Media
{
private:
    string m_autore;
    string m_titolo;
    string m_descrizione;
    year_month_day m_dataInizioRilascio;
    year_month_day m_dataFineRilascio;
    unsigned int m_visualizzazioni;
    vector<Lingua> m_lingueDisponibili;
    vector<Lingua> m_sottotitoliDisponibili;
    unsigned int m_durataMinuti;
    string m_path;
    Formato m_formato;
    // aggiungere risoluzione
public:
    Media(const string &autore, const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
          year_month_day gg_mm_aaFineRilascio, unsigned int visualizzaioni, unsigned int durataMinuti, const string &path,
          Formato formato);

    // //metodi set
    // void setAutore(const string& autore);
    // void setTitolo(const string& titolo);
    // void setD
    // //metodi getescrizione(const string& descrizione);
    // void setDataInizioRilascio(year_month_day gg_mm_aaInizioRilascio);
    // void setVisualizzazioni(unsigned int visualizzazioni);

    // string getAutore() const;
    // string getTitolo() const;
    // string getDescrizione() const;
    // vector<Lingua> getLingue() const;
    // vector<Lingua> getSottotitoli() const;

    void aggiungiLingua(Lingua lingua);
    void aggiungiSottotitolo(Lingua lingua);
    void rimuoviLingua(Lingua lingua);
    void rimuoviSottotitolo(Lingua lingua);


    /**
     * @brief Verifca se il media è correntemente distribuito nei canali del cinema.
     * Il media è fuori produzione se la data di fine rilascio è < della data corrente.
     * @return True se il media è fuori produzione
     */
    bool FuoriProduzione() const;

    /**
     * @brief Indica il numero di giorni in cui il media è distribuito nei canali del cinema.
     * Il numero di giorni contando i giorni in cui il film non è fuori produzione.
     * @return Il numero di giorni in cui il media è attivo nei canali.
     */
    unsigned int DurataCampagna() const;

    // metodi get e set
    unsigned int getVisualizzazioni() const;
    year_month_day getDataInizioRilascio() const;
    year_month_day getDataFineRilascio() const;
    virtual void setDataFineRilascio(year_month_day gg_mm_aaFineRilascio);
    unsigned int getDurataMinuti() const;
    void setDurataMinuti(unsigned int durata);

    // metodi astratti
    virtual ~Media() = 0;

    /**
     * @brief Estende la data di fine rilascio a seconda del tipo di media e del suo stato corrente.
     * Questa funzione deve essere implementata dalle classi derivate.
     */
    virtual void estendiDataFineRilascio() = 0;

    /**
     * @brief Calcola l'incasso della distribuzione del media che viene fatta nei canali appropriati del cinema.
     * @return L'incasso calcolato
     * Questa funzione deve essere implementata dalle classi derivate.
     */
    virtual double calcolaIncasso() = 0;
};

#endif
