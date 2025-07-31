#ifndef PODCAST_H
#define PODCAST_H

#include "Media.h"

class Puntata; // dichiarazione incompleta

class Podcast : public Media
{
private:
    string p_conduttore;
    vector<Puntata *> p_elencoPuntate;
    bool isInPuntata(Puntata * puntata) const;

public:
    Podcast(const string &autore, const string &titolo, const string &descrizione,
            year_month_day gg_mm_aaInizioRilascio, year_month_day gg_mm_aaFineRilascio,
            unsigned int visualizzazioni, unsigned int durataMinuti, const string &path,
            Formato formato, const string &conduttore);

    ~Podcast();

    void aggiungiPuntata(Puntata *);
    void rimuoviPuntata(Puntata *);

    void estendiDataFineRilascio() override;
    double calcolaIncasso() override;

    vector<Puntata *> getElencoPuntate() const;
};

#endif // PODCAST_H