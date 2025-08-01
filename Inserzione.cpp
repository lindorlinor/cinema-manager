#include "Inserzione.h"

Inserzione::Inserzione(const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
                       year_month_day gg_mm_aaFineRilascio, unsigned int durataMinuti, Formato formato, Risoluzione risoluzione, 
                       unsigned int nProiezioniGiornaliere,const string &aziendaInserzionista, double costoProiezione,
                       const string &autore, const string &path) :

                                    Pubblicita(titolo, descrizione, gg_mm_aaInizioRilascio, gg_mm_aaFineRilascio,
                                    durataMinuti, formato, risoluzione, nProiezioniGiornaliere, autore, path),
                                    i_aziendaInserzionista(aziendaInserzionista),i_costoFissoProiezione(costoProiezione){}

int Inserzione::isFasciaOrariaIn(FasciaOraria fasciaO) const
{
    vector<FasciaOraria>::const_iterator cit = std::find(i_fasceOrarie.begin(), i_fasceOrarie.end(), fasciaO);
    if (cit != i_fasceOrarie.end())
    {
        return std::distance(i_fasceOrarie.begin(), cit);
    }
    else
    {
        return -1;
    }
}

void Inserzione::aggiungiFasciaOraria(FasciaOraria fasciaO)
{
    if (isFasciaOrariaIn(fasciaO) == -1)
        i_fasceOrarie.push_back(fasciaO);
}

void Inserzione::rimuoviFasciaOraria(FasciaOraria fasciaO)
{
    int i_fasciaO = isFasciaOrariaIn(fasciaO);
    if (i_fasciaO != -1)
        i_fasceOrarie.erase(i_fasceOrarie.begin() + i_fasciaO);
}

double Inserzione::fattoreVariazionePrezzo() const
{
    double percentuale = 1;
    for (FasciaOraria fa : i_fasceOrarie)
    {
        if (fa == FasciaOraria::Pomeriggio)
        {
            percentuale += 0.1;
        }
        if (fa == FasciaOraria::Sera)
        {
            percentuale += 0.2;
        }
    }
    return percentuale;
}

void Inserzione::estendiDataFineRilascio()
{
    if (!FuoriProduzione())
    {
        year_month_day dataFine = getDataFineRilascio() + months{1};
        setDataFineRilascio(year_month_day(dataFine));
    }
}

double Inserzione::calcolaIncasso()
{
    return DurataCampagna() * getNProiezioniGiornaliere() * i_costoFissoProiezione * fattoreVariazionePrezzo();
}