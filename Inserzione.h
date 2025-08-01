#ifndef INSERZIONE_H
#define INSERZIONE_H
#include "Pubblicita.h"
#include <string>
#include <EnumClasses.h>
/**
 * @class Inserzione
 * @brief Rappresenta un'inserzione pubblicitaria proiettata al cinema.
 * 
 * Un'inserzione è una pubblicità commissionata da un'azienda per essere riprodotta al cinema nelle fasce orarie indicate. L'autore di una pubblicità è
 * il regista della pubblicità. Da contratto un'inserzione include sempre la fascia oraria mattutina. 
 * Le altre fasce orarie richiedono un pagamento di un'incremento sul costo base.
 */
class Inserzione : public Pubblicita{
    string i_aziendaInserzionista;
    const double i_costoFissoProiezione;
    vector<FasciaOraria> i_fasceOrarie;
    double fattoreVariazionePrezzo() const;
    int isFasciaOrariaIn(FasciaOraria fasciaO) const;
public:
    Inserzione( const string& autore, const string& titolo, const string& descrizione, year_month_day gg_mm_aaInizioRilascio, 
                year_month_day gg_mm_aaFineRilascio, unsigned int visualizzaioni, unsigned int durataMinuti,const string& path, 
                Formato formato, const Classificazione& target, unsigned int nProiezioniGiornaliere, const string& aziendaInserzionista, 
                double costoFissoProiezione);
    
    
    void aggiungiFasciaOraria(FasciaOraria fasciaO);
    void rimuoviFasciaOraria(FasciaOraria fasciaO);
    
    /**
     * @brief Estende la data di fine rilascio dell'inserzione di un mese.
     */
    void estendiDataFineRilascio() override;

    /**
     * @brief Calcola l'incasso della proiezione della pubblicità al cinema.
     * 
     * L'incasso è calcolato moltiplicando i giorni in cui la pubblicità è stata proiettata per il numero di proiezioni concordate per contratto. 
     * Il valore dell'incasso inoltre varia a seconda delle fasce orarie in cui l'inserzione viene proiettata.
     * 
     * @return L'incasso calcolato.
     */
    double calcolaIncasso() override;

    friend vector<FasciaOraria> getFasceOrarie(const Inserzione&); //ha friend perchè è solo per i test! (al momento)
};

#endif 


