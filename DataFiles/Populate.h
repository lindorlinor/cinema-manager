#ifndef POPULATE_H
#define POPULATE_H

#include <QString>
#include <QDate>
#include <vector>
#include "../EnumClasses.h"

using namespace std;

struct CinemaData{
    QString nomeCinema;
    QString copertinaCinema;
};

struct MediaData : public CinemaData {
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
    QString tipologia;
};

struct FilmData : public MediaData {
    vector<Genere> generi;
    vector<QString> attoriPrincipali;
    Classificazione target;
    QString  casaDiProduzione;
    unsigned int nPostCredit;
    double costoBiglietto;
};

struct PubblicitaData : public MediaData{
    unsigned int nProiezioniGiornaliere;
};

struct TrailerData : public PubblicitaData {
    QString filmAssociato;
    QString autoreFilmAssociato;
};

struct InserzioneData : public PubblicitaData{
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

#endif// POPULATE_H
