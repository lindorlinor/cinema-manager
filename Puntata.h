#ifndef PUNTATA_H
#define PUNTATA_H

#include "Media.h"

class Podcast;

class Puntata : public Media
{
private:
    vector<string> p_ospiti;
    Podcast *p_podcast;
    unsigned int p_numeroPubblicita;

public:
    Puntata(const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
            year_month_day gg_mm_aaFineRilascio, unsigned int durataMinuti,
            Podcast *podcast, unsigned int numeroPubblicita, const string &autore = "Sconosciuto",
            const string &path = "immGrigia");
    void aggiungiOspite(const string &);
    void rimuoviOspite(const string &);
    void estendiDataFineRilascio() override;
    double calcolaIncasso() override;
    vector<string> getOspiti() const;
};

#endif // PUNTATA_H