#include "Podcast.h"
#include "Puntata.h"

Podcast::Podcast(const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
                 Formato formato, Risoluzione risoluzione,
                 const string &autore, const string &path, const string &conduttore) : 
                                    Media(titolo, descrizione, gg_mm_aaInizioRilascio, gg_mm_aaInizioRilascio,
                                    0, formato, risoluzione, autore, path),p_conduttore(conduttore) {}

Podcast::~Podcast()
{
    while (!p_elencoPuntate.empty())
    {
        delete p_elencoPuntate.back();
        p_elencoPuntate.pop_back();
    }
}

void Podcast::aggiungiPuntata(Puntata* puntata){
    if(puntata && isPuntataIn(puntata)==-1){
        if(!p_elencoPuntate.empty()){
            if(puntata->getDataInizioRilascio()<p_elencoPuntate.back()->getDataInizioRilascio()){
                //se si inserisce una puntata con data di inizio inferiore della precedente, allora si corregge
                //la data di inizio con quella della puntata precedente, qui bisognerà lanciare un warning.
                //NOTA: perché non riordinare il vettore? perché bisogna tener conto anche della data di fine, se immaginiamo
                //di avere una data di inizio 10 luglio e fine 14 luglio, poi una di inizio 13 luglio e fine 16 luglio, se provassimo a 
                //mettere una puntata con inizio 8 luglio e fine 18 luglio allora si creerebbero due problemi:
                //1. riordinare e mettere questa nuova puntata come prima, 
                //2. lanciare un eccezione perché la data di fine della nuova prima puntata sarà maggiore di ENTRAMBE
                // le prossime puntate e bisognerebbe correggere queste piuttosto che quella che si sta inserendo, non ha senso
                //infine, se vogliamo pensarla logicamente, non ha senso che una puntata inserire succeddivamente
                //prenda posto prima di una riilasciata precedentemente e qui ha senso mettere un automatico la data di inizio
                //corrispondente alla precedente
                puntata->setDataInizioRilascio(p_elencoPuntate.back()->getDataInizioRilascio());
            }
            if(puntata->getDataFineRilascio() < p_elencoPuntate.back()->getDataFineRilascio()){
                    throw std::invalid_argument("La data di fine è inferiore a quella dell'ultima puntata aggiunta");
                }
        }
        //NOTA1: cosa succede se si usa setDataFineRilascio su una puntata? non ci dovrebbe essere il controllo? però allo stesso tempo, è corretto che uno possa modificare la data se ha sbagliato -> (vedi commento setDataFineRilascio riferito a estendiDataFineRilascio in Trailer)
            //soluzione 1: permettere la modifica ma magari aggiungere un warning a livello di gui
            //soluzione 2: overridare setDataFineRilascio non permettendo 
        //NOTA2: le eccezioni modificano il flusso del programma, in trailer lo ho gestito impostando la data di fine uguale a quella del film. La gui poi si occupava di controllare i valori e avvertire del cambiamento l'utente (avevo chiesto a chatty e mi aveeva assicurato che la suddivisione dei compiti era corretta, ma chissà)
           // SCELTO QUESTO soluzione1: lasciamo l'eccezione perchè, benchè sia diversa la risoluzione del problema in trailer, può aver senso in questo caso perchè non c'è una soluzione intuitivamente logica
            //soluzione2: si forza un ragionamento per una soluzione concreta che non fa uso di eccezioni. Quello che avevo pensato era di impostare la data di fine rilascio dell'ultima puntata, avvertendo l'utente (tramite gui)
            //soluzione3: si tiene l'eccezione e si modifica anche in trailer aggiungendo un'eccezione e chiedendo (tramite gui) di impostare una data di fine corretta per il trailer.           
        puntata->IncrementaVisualizzazioni();
        setVisualizzazioni(getVisualizzazioni() + puntata->getVisualizzazioni());
        setDataFineRilascio(puntata->getDataFineRilascio());
        setDurataMinuti(getDurataMinuti() + puntata->getDurataMinuti());
        p_elencoPuntate.push_back(puntata);
    }
}

 int Podcast::isPuntataIn(Puntata* puntata) const {
    auto it = std::find(p_elencoPuntate.begin(), p_elencoPuntate.end(), puntata);
    if (it != p_elencoPuntate.end()) {
        return std::distance(p_elencoPuntate.begin(), it);
    } else {
        return -1;
    }
}

void Podcast::rimuoviPuntata(Puntata* puntata) {
    int i_puntata = isPuntataIn(puntata);
    if (i_puntata != -1) {
        setVisualizzazioni(getVisualizzazioni() - puntata->getVisualizzazioni());
        setDurataMinuti(getDurataMinuti() - puntata->getDurataMinuti());
        delete puntata;

        p_elencoPuntate.erase(p_elencoPuntate.begin() + i_puntata);

        if (!p_elencoPuntate.empty()) {
            // Aggiorna la data fine rilascio solo se l'ultima puntata è cambiata
            if (getDataFineRilascio() != p_elencoPuntate.back()->getDataFineRilascio()) {
                setDataFineRilascio(p_elencoPuntate.back()->getDataFineRilascio());
            }
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
        std::chrono::sys_days dataFine = std::chrono::sys_days(getDataFineRilascio());
        dataFine += std::chrono::days{1};                          
        setDataFineRilascio(std::chrono::year_month_day{dataFine});
    }
}

vector<Puntata *> Podcast::getElencoPuntate() const
{
    return p_elencoPuntate;
}