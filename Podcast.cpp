#include "Podcast.h"
#include "Puntata.h"

Podcast::Podcast(const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
                 year_month_day gg_mm_aaFineRilascio, Formato formato, Risoluzione risoluzione,
                 const string &autore, const string &path, const string &conduttore) : 
                                    Media(titolo, descrizione, gg_mm_aaInizioRilascio, gg_mm_aaFineRilascio,
                                    0, formato, risoluzione, autore, path),p_conduttore(conduttore) {}

Podcast::~Podcast()
{
    while (!p_elencoPuntate.empty())
    {
        delete p_elencoPuntate.back();
        p_elencoPuntate.pop_back();
    }
}

void Podcast::aggiungiPuntata(Puntata *puntata)
{
    if (puntata && !isInPuntata(puntata))
    {
        if (!p_elencoPuntate.empty())
            if (puntata->getDataFineRilascio() < p_elencoPuntate.back()->getDataFineRilascio())
            {
                throw std::invalid_argument("La data di fine è inferiore a quella dell'ultima puntata aggiunta");
            }
        puntata->IncrementaVisualizzazioni();
        setVisualizzazioni(getVisualizzazioni() + puntata->getVisualizzazioni());
        setDataFineRilascio(puntata->getDataFineRilascio());
        setDurataMinuti(getDurataMinuti() + puntata->getDurataMinuti());
        p_elencoPuntate.push_back(puntata);
    }
}

bool Podcast::isInPuntata(Puntata *puntata) const
{
    if (p_elencoPuntate.empty())
        return false;
    for (Puntata *p : p_elencoPuntate)
    {
        if (p == puntata)
            return true;
    }
    return false;
}

void Podcast::rimuoviPuntata(Puntata *puntata)
{
    if (!p_elencoPuntate.empty())
    {
        auto it = std::find(p_elencoPuntate.begin(), p_elencoPuntate.end(), puntata);
        if (it != p_elencoPuntate.end())
        {
            setVisualizzazioni(getVisualizzazioni() - puntata->getVisualizzazioni());
            setDurataMinuti(getDurataMinuti() - puntata->getDurataMinuti());
            delete *it; // se una puntata viene cancellata dall'elenco, allora viene anche eliminata perché non ha senso che viva senza un film ad essa associato
            p_elencoPuntate.erase(it);
            if (!p_elencoPuntate.empty())
                if (getDataFineRilascio() != p_elencoPuntate.back()->getDataFineRilascio()) // per non assegnare nuovamente lo stesso valore inutilmente
                    setDataFineRilascio(p_elencoPuntate.back()->getDataFineRilascio());
        }
    }
}

double Podcast::calcolaIncasso()
{
    double tot = 0;
    for (Puntata *puntata : p_elencoPuntate)
    {
        if (puntata)
            tot += puntata->calcolaIncasso();
    }
    return tot;
}

void Podcast::estendiDataFineRilascio()
{
    if (!FuoriProduzione())
    {
        // Converti year_month_day a sys_days per sommare giorni
        std::chrono::sys_days dataFine = std::chrono::sys_days(getDataFineRilascio());
        dataFine += std::chrono::days{1};                           
        setDataFineRilascio(std::chrono::year_month_day{dataFine});

        // non ha alcuna azione sulle puntate perché la data di fine rilascio del podcast dipende da quella
        // di fine rilascio delle stesse puntate, quindi non è possibile estendere la fine del podcast senza
        // prima estendere quella delle puntate, il quale metodo richiama questo stesso metodo per aggiornare
        //  la data di fine rilascio del podcast
    }
}

vector<Puntata *> Podcast::getElencoPuntate() const
{
    return p_elencoPuntate;
}
