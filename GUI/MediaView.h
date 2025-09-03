#ifndef MEDIAVIEW_H
#define MEDIAVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "../DetailPageVisitor.h"
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
    QHBoxLayout* leftLayout;
    QFrame * details; //frame dettagli
    QVBoxLayout * detailsLayout; //layout frame dettagli
    QLabel* endDateLabel; //questa si trova qui per permettere la visualizzazione del cambiamento della data quando si clicca su "Estendi data"
    QWidget* rightSide; //parte destra che contiene la/l sezione/i scrollable
    QVBoxLayout* rightLayout;
    QWidget * card;
    QVBoxLayout * cardLayout;
    void createHeader();
    void createMediaCard();
    void createRowDetails();

    virtual void createMediaDetails() = 0;
    virtual void createScrollableSection() = 0;
    virtual void createButtons() =0;

signals:
    void editMediaClicked(Media* mPtr); //segnale emesso quando cliccato sull'icona di modifica media
    void extendMediaClicked(); //segnale emesso quando cliccato su "estendi Media"
    void deleteMediaClicked();  //sengale emesso quando cliccato su "elimina Media"
    void returnButton(); //segnale emesso quando cliccato il pulsante "Torna indietro"
    void requestMediaView(MediaView& widget);
};

#endif // MEDIAVIEW_H
