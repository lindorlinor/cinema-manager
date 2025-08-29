#ifndef MEDIAVIEW_H
#define MEDIAVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "../Media.h"

class MediaView : public QWidget{
    Q_OBJECT
public:
    explicit MediaView(Media* mediaPtr, QWidget* parent = nullptr);

protected:
    Media* mediaPtr; //puntatore al Media
    QVBoxLayout* layoutPage; //tutto il layout
    QWidget* splitter; //crea le due parti della schemata: sinistra e destra
    QHBoxLayout* splitterLayout;
    QWidget* leftSide; //parte sinistra che contiene la copertina del film e i dettagli
    QWidget* rightSide; //parte destra che contiene la/l sezione/i scrollable
    QHBoxLayout* leftLayout;
    QLabel* endDateLabel; //questa si trova qui per permettere la visualizzazione del cambiamento della data quando si clicca su "Estendi data"
    QVBoxLayout* rightLayout;

    void createHeader();
    void createMediaCard();
    
    // metodi virtuali puri → obbligano le sottoclassi a definirli
    virtual void createMediaDetails() = 0;
    virtual void createScrollableSection() = 0;
    virtual void createButtons() =0;

signals:
    void extendMediaClicked(); //segnale emesso quando cliccato su "estendi Media"
    void deleteMediaClicked();  //sengale emesso quando cliccato su "elimina Media"
    void returnButton(); //segnale emesso quando cliccato il pulsante "Torna indietro"

};

#endif // MEDIAVIEW_H
