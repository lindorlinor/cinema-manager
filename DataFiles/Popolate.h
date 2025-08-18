#ifndef POPOLATE_H
#define POPOLATE_H

#include <QString>
#include <QDate>
#include <vector>
#include "../EnumClasses.h"

using namespace std;

struct MediaData {
    QString  titolo;
    QString  descrizione;
    QDate dataInizioRilascio;
    QDate dataFineRilascio;
    unsigned int durataMinuti;
    Formato formato;
    Risoluzione risoluzione;
    QString  autore;
    QString  path;
    vector<Lingua> lingueDisponibili;
    vector<Lingua> sottotitoliDisponibili;
};

struct FilmData : public MediaData {
    vector<Genere> genere;
    vector<QString> attoriPrincipali;
    Classificazione target;
    QString  casaDiProduzione;
    unsigned int nPostCredit;
    double costoBiglietto;
};

struct TrailerData : public MediaData {
    unsigned int nProiezioniGiornaliere;
    QString filmAssociato;
    QString autoreFilmAssociato;
};

struct PubblicitaData : public MediaData{
    unsigned int nProiezioniGiornaliere;
};

struct InserzioniData : public PubblicitaData{
    Classificazione target;
    QString aziendaInserzionista;
    double costoFissoProiezione;
    vector<FasciaOraria> fasceOrarie;
};

struct PodcastData : public MediaData{
    QString conduttore;
};

struct PuntataData : public MediaData{
    vector<QString> ospiti;
    QString podcastAssociato;
    QString autorePodcastAssociato;
    unsigned int numeroPubblicita;
};

#endif// POPOLATE_H