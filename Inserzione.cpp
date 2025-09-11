#include "Inserzione.h"

Inserzione::Inserzione(const string &titolo, const string &descrizione, year_month_day gg_mm_aaInizioRilascio,
                       year_month_day gg_mm_aaFineRilascio, unsigned int durataMinuti, Formato formato, Risoluzione risoluzione, 
                       unsigned int nProiezioniGiornaliere,const Classificazione& target, double costoProiezione, const string &aziendaInserzionista,
                       const string &autore, const string &path) :

                                    Pubblicita(titolo, descrizione, gg_mm_aaInizioRilascio, gg_mm_aaFineRilascio,
                                    durataMinuti, formato, risoluzione, nProiezioniGiornaliere, autore, path),i_target(target),
                                    i_aziendaInserzionista(aziendaInserzionista),i_costoFissoProiezione(costoProiezione){
                                        aggiungiFasciaOraria(FasciaOraria::Mattina);
                                    }


int Inserzione::isFasciaOrariaIn(FasciaOraria fasciaO) const{
    vector<FasciaOraria>::const_iterator cit = std::find(i_fasceOrarie.begin(), i_fasceOrarie.end(), fasciaO);
    if (cit != i_fasceOrarie.end())
            return std::distance(i_fasceOrarie.begin(), cit);
    else
        return -1;
}

void Inserzione::aggiungiFasciaOraria(FasciaOraria fasciaO){
    if (isFasciaOrariaIn(fasciaO) == -1)
        i_fasceOrarie.push_back(fasciaO);
}

void Inserzione::rimuoviFasciaOraria(FasciaOraria fasciaO){
    if(fasciaO!=FasciaOraria::Mattina){
        int i_fasciaO =isFasciaOrariaIn(fasciaO);
        if(i_fasciaO!=-1)
            i_fasceOrarie.erase(i_fasceOrarie.begin()+i_fasciaO);
    }
}

double Inserzione::fattoreVariazionePrezzo() const{
    double percentuale = 1;
    for (FasciaOraria fa : i_fasceOrarie){
        if (fa == FasciaOraria::Pomeriggio)
            percentuale += 0.1;
        if (fa == FasciaOraria::Sera)
            percentuale += 0.2;
    }
    return percentuale;
}

void Inserzione::estendiDataFineRilascio() {
    if (!FuoriProduzione()) {
        setDataFineRilascio(getDataFineRilascio() + months{1});
    }
}

double Inserzione::calcolaIncasso(){
    return DurataCampagna() * getNProiezioniGiornaliere() * i_costoFissoProiezione * fattoreVariazionePrezzo();
}

//metodi get
Classificazione Inserzione::getTarget() const{
    return i_target;
}

string Inserzione::getAziendaInserzionistica() const{
    return i_aziendaInserzionista;
}

double Inserzione::getCostoFissoProiezione() const{
    return i_costoFissoProiezione;
}

//metodi set
void Inserzione::setTarget(const Classificazione& target){
    i_target = target;
}

void Inserzione::setAziendaInserzionistica(const string& nome){
    i_aziendaInserzionista = nome;
}

void Inserzione::setCostoFissoProiezione(const double& costo){
    i_costoFissoProiezione = costo;
}


//visitor
void Inserzione::accept(MediaVisitor* visitor) {
    visitor->visit(this);
}


vector<FasciaOraria> Inserzione::getFasceOrarie() const{
    return i_fasceOrarie;
}
