#ifndef INSERZIONE_H
#define INSERZIONE_H
#include "Pubblicita.h"
#include <string>
#include <EnumClasses.h>
class Inserzione : public Pubblicita
{
    string i_aziendaInserzionista;
    const double i_costoFissoProiezione;
    vector<FasciaOraria> i_fasceOrarie;
    double fattoreVariazionePrezzo() const;
    int isFasciaOrariaIn(FasciaOraria fasciaO) const;

public:
    Inserzione(const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
               year_month_day gg_mm_aaFineRilascio, unsigned int durataMinuti, Formato formato, Risoluzione risoluzione,
               unsigned int nProiezioniGiornaliere, const string &aziendaInserzionista, double costoProiezione,
               const string &autore = "Sconosciuto", const string &path = "immGrigia");
    double calcolaIncasso() override;
    void estendiDataFineRilascio() override;
    void aggiungiFasciaOraria(FasciaOraria fasciaO);
    void rimuoviFasciaOraria(FasciaOraria fasciaO);

    friend vector<FasciaOraria> getFasceOrarie(const Inserzione &);
};

#endif
