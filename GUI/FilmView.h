#ifndef FILMVIEW_H
#define FILMVIEW_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "../Film.h"
class FilmView : public QWidget
{
    Q_OBJECT
public:
    explicit FilmView(Film* filmPtr, QWidget* parent = nullptr);
private:
    Film* film;
    QVBoxLayout * layoutPage; //tutto il layout
    QWidget * splitter; //crea le due parti della schemata: sinistra e destra
    QHBoxLayout * splitterLayout;
    QWidget * leftSide; //parte sinistra che contiene la copertina del film e i dettagli
    QWidget * rightSide; //parte destra che contiene la sezione dei trailer (scrollable) e i pulsanti Estendi e Elimina
    QHBoxLayout * leftLayout;
    QLabel* endDateLabel; //questa si trova qui per permettere la visualizzazione del cambiamento della data quando si clicca su "Estendi data"
    QVBoxLayout * rightLayout;
    void createHeader();
    void createFilmDetails();
    void createFilmCard();
    void createTrailersSection();
    void createButtons();
signals:
    void trailerSelected(const Trailer* trailer); //segnale emesso quando cliccato su un trailer del film, trailer è il puntatore al trailer cliccato
    void extendMediaClicked(); //segnale emesso quando cliccato su "estendi film"
    void deleteMediaClicked(); //sengale emesso quando cliccato su "elimina film"
    void returnButton(); //segnale emesso quando cliccato il pulsante "Torna indietro"

};
#endif
