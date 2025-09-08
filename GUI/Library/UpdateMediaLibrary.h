#ifndef UPDATEMEDIALIBRARY_H
#define UPDATEMEDIALIBRARY_H

#include <QWidget>
#include <QObject>
#include <QString>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QLayout>

#include "CardVisitor.h"
#include "../Custom/FlowLayout.h"
#include "../MediaViewPages/MediaView.h"
#include "../Custom/MediaFrame.h"
#include "../../Media.h"
#include "../MediaViewPages/DetailPageVisitor.h"

/**
 * @class UpdateMediaLibrary
 * @brief Gestisce l'aggiornamento dinamico della libreria multimediale.
 *
 * Questa classe fornisce il comportamento comune per widget che devono visualizzare
 * una collezione di media filtrati, ordinati e impaginati in layout diversi.
 *
 * Funzionalità principali:
 * - Ordinamento dei media per:
 *   - Numero di visualizzazioni (crescente o decrescente).
 *   - Data di rilascio (più recente o meno recente).
 * - Pulizia del layout attuale (orizzontale o a flusso) e ricostruzione dei widget
 *   in base ai filtri selezionati.
 * - Creazione dinamica di widget `MediaFrame` tramite il pattern Visitor
 *   (`CardVisitor`) in funzione del filtro richiesto.
 * - Gestione di ricerca testuale su titolo e autore dei media.
 * - Connessione del segnale di selezione di un media (`MediaFrame::selected`)
 *   alla richiesta di visualizzazione della pagina di dettaglio (`requestMediaView`).
 *
 * Dettagli di implementazione:
 * - La variabile `chooseLayout` determina se usare un layout orizzontale
 *   (`QHBoxLayout`) o un layout a flusso (`FlowLayout`).
 * - Ogni volta che viene chiamato `update()`, i widget esistenti vengono rimossi
 *   e distrutti per garantire un refresh coerente.
 * - I widget `MediaFrame` creati vengono configurati con dimensioni minime e massime
 *   e con scaling delle immagini.
 *
 * @see Media
 * @see MediaFrame
 * @see CardVisitor
 * @see DetailPageVisitor
 * @see FlowLayout
 */

class UpdateMediaLibrary : public QWidget
{
    Q_OBJECT

protected:
    QWidget *container;
    QHBoxLayout *HorizontalLayoutContainer; // true
    FlowLayout *FlowLayoutContainer;        // false
    int numeroWidget;
    bool chooseLayout;
    void setPreferredLayout(QLayout *layout);

public:
    UpdateMediaLibrary(QWidget *parent = nullptr);
    virtual void update(const bool &view, int comboAttivita, int comboOrdinamento, const QString &filtro, const QString &ricerca, QList<Media *> &mediaList);
    int getNumeroWidgetLayout() const;

signals:
    void requestMediaView(MediaView &widget);
};
#endif // UPDATEMEDIALIBRARY_H