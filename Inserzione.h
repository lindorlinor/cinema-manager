#ifndef INSERZIONE_H
#define INSERZIONE_H
#include "Pubblicita.h"
#include "MediaVisitor.h"
#include <string>
#include <EnumClasses.h>
/**
 * @class Inserzione
 * @brief Rappresenta un'inserzione pubblicitaria proiettata al cinema.
 * 
 * Un'inserzione è una pubblicità commissionata da un'azienda per essere riprodotta al cinema nelle fasce orarie indicate. L'autore di una pubblicità è
 * il regista della pubblicità. Da contratto un'inserzione include sempre la fascia oraria mattutina. 
 * Le altre fasce orarie richiedono un pagamento di un'incremento sul costo base.
 * @note l'inclusione della fascia oraria mattutina è una novità.
 */
class Inserzione : public Pubblicita{
    Classificazione i_target;
    string i_aziendaInserzionista;
    double i_costoFissoProiezione;
    vector<FasciaOraria> i_fasceOrarie;
    double fattoreVariazionePrezzo() const;
    int isFasciaOrariaIn(FasciaOraria fasciaO) const;

public:
    Inserzione(const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
               year_month_day gg_mm_aaFineRilascio, unsigned int durataMinuti, Formato formato, Risoluzione risoluzione,
               unsigned int nProiezioniGiornaliere, const Classificazione& target, double costoProiezione,const string &aziendaInserzionista = "Sconosciuto", 
               const string &autore = "Sconosciuto", const string &path = "immGrigia");

    
    
    void aggiungiFasciaOraria(FasciaOraria fasciaO);
    void rimuoviFasciaOraria(FasciaOraria fasciaO);
    Classificazione getTarget() const;
    string getAziendaInserzionistica() const;
    double getCostoFissoProiezione() const;
    void setTarget(const Classificazione& target);
    void setAziendaInserzionistica(const string& nome);
    void setCostoFissoProiezione(const double& nome);

    //void setTarget(Classificazione target);
    
    /**
     * @brief Se la pubblicita non è fuori produzione, estende la data di fine rilascio dell'inserzione di un mese.
     */
    void estendiDataFineRilascio() override;

    /**
     * @brief Calcola l'incasso della proiezione della pubblicità al cinema.
     * 
     * L'incasso è calcolato moltiplicando i giorni in cui la pubblicità è stata proiettata per il numero di proiezioni concordate per contratto. 
     * Il valore dell'incasso inoltre varia a seconda delle fasce orarie in cui l'inserzione viene proiettata. La variazione fa uso del metodo @ref fattoreVariazionePrezzo.
     * 
     * @return L'incasso calcolato.
     * @note non ho ancora fatto la documentazione di del metodo @ref fattoreVariazionePrezzo
     */
    double calcolaIncasso() override;

    friend vector<FasciaOraria> getFasceOrarie(const Inserzione&); //ha friend perchè è solo per i test! (al momento)

    //visitor
    void accept(MediaVisitor* visitor)override;
};

#endif
