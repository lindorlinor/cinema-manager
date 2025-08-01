#include "Puntata.h"
#include "POdcast.h"

Puntata::Puntata(const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
                 year_month_day gg_mm_aaFineRilascio, unsigned int durataMinuti,
                 Podcast *podcast, unsigned int numeroPubblicita, const string &autore,
                 const string &path) : 
                            Media(titolo, descrizione, gg_mm_aaInizioRilascio, gg_mm_aaFineRilascio,
                            durataMinuti, podcast->getFormato(), podcast->getRisoluzione(), autore, path),p_podcast(podcast), 
                            p_numeroPubblicita(numeroPubblicita) {}

void Puntata::aggiungiOspite(const string &ospite)
{
    p_ospiti.push_back(ospite);
}

void Puntata::rimuoviOspite(const string &ospite)
{
    if (!p_ospiti.empty())
    {
        auto it = std::find(p_ospiti.begin(), p_ospiti.end(), ospite);
        if (it != p_ospiti.end())
            p_ospiti.erase(it);
    }
}

double Puntata::calcolaIncasso()
{
    return getVisualizzazioni() * (p_numeroPubblicita * 0.05); // 5 centesimi per ogni visualizzazione si una pubblicità
}

// aggiorna tutte le data fine rilascio dalla puntata chiamata alle successive, infine estende la data anche sul podcast a cui punta
void Puntata::estendiDataFineRilascio()
{
    if (!FuoriProduzione() && p_podcast)
    {
        const vector<Puntata *> &elenco = p_podcast->getElencoPuntate(); // per evitare la copia dell'intero vettore
        auto it = std::find(elenco.begin(), elenco.end(), this);
        while (it != elenco.end())
        {
            auto dataFine = std::chrono::sys_days((*it)->getDataFineRilascio());
            dataFine += std::chrono::days{7};                                  // aggiungi 7 giorni
            (*it)->setDataFineRilascio(std::chrono::year_month_day{dataFine}); // aggiorna
            it++;
        }
        p_podcast->estendiDataFineRilascio();
    }
}

vector<string> Puntata::getOspiti() const
{
    return p_ospiti;
};