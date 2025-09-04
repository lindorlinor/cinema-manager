#ifndef MEDIALIBRARYTUTTO_H
#define MEDIALIBRARYTUTTO_H

#include <QWidget>
#include <QList>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>

#include "ScrollListWidget.h"
/**
 * @class MediaLibraryTutto
 * @brief Pagina della libreria multimediale che mostra tutti i contenuti disponibili.
 *
 * Questa classe implementa una pagina Qt che visualizza una panoramica di tutti i media
 * (Film, Trailer, Inserzioni, Podcast, Puntate) presenti nella libreria.
 * 
 * La struttura della pagina è composta da:
 * - Un titolo ("Tutto") in alto.
 * - Un'area scrollabile che contiene varie sezioni, una per ciascun tipo di contenuto.
 * 
 * Ogni sezione mostra i media corrispondenti tramite uno ScrollListWidget personalizzato,
 * aggiornato in base ai filtri selezionati (attività, ordinamento, ricerca).
 *
 * Funzionalità principali:
 * - Creazione e gestione del layout grafico con titoli e contenitori scrollabili.
 * - Aggiornamento dinamico della lista dei contenuti quando cambiano i parametri di filtro.
 * - Emissione del segnale `requestMediaView` per richiedere la visualizzazione dettagliata
 *   di un media selezionato.
 *
 * @see ScrollListWidget
 * @see MediaView
 */

class MediaLibraryTutto: public QWidget{
    Q_OBJECT
    private:
    QVBoxLayout* layoutContainer;
    QWidget* container;
    QScrollArea* scrollArea;
    
    public:
    explicit MediaLibraryTutto(QWidget* parent = nullptr);
    void update(int comboAttivita, int comboOrdinamento, const QString& ricerca, QList<Media*>& mediaList);

    signals: 
    void requestMediaView(MediaView& widget);

    public slots:
    void reciveRequestMediaView(MediaView& widget);

};

#endif //MEDIALIBRARYTUTTO_H