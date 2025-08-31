#ifndef CINEMASELECTIONPAGE_H
#define CINEMASELECTIONPAGE_H

#include <QMainWindow>
#include <QVector>
#include <QString>
#include "CinemaButton.h"
#include "../DataFiles/CinemaRepositoryJson.h"
#include "../Cinema.h"
#include <QHBoxLayout>
/**
 * @brief Pagina per la selezione del cinema
 * 
 * @details Contiene cinemaButtonsLayout che è il layout dove si trovano i CinemaButtons, 
 * frameLayout che è il layout del frame centrale che contiene tutta la pagina e 
 * la lista di cinema che viene aggiornata ad ogni refreshCinemaButtons.
 * 
 * Il costruttore crea: header, pulsante aggiungi, scrollArea con i CinemaButtons (2 passaggi), pulsante esci.
 * 
 * Il pulsante aggiungi manda un segnale insertCinema che viene catchato da MainWindow (perchè è lei che mantiene le pagine nello stackWidget)
 * arrivando allo slot showInsertCinemaPage che cambia il widget in visualizzazione in InsertCinemaPage
 *
 * @note può essere otimizzato con una sorta di cache per i cinema, poi vengono ricreati i pulsanti sì
 * ma almeno non viene fatto il load di tutti i cinema ogni volta (so dumb) 
 */
class CinemaSelectionPage : public QWidget
{
    Q_OBJECT
private:
    QList<Cinema*>& sp_cinema;
    QHBoxLayout* cinemaButtonsLayout;
    QVBoxLayout *frameLayout;
    void createCinemaButton(Cinema* c);

    /**
     * @brief Crea l'intestazione della pagina
     * 
     * @note qui sono stati impostate delle grandezze per i font che poi dovranno essere messe nel qss così possiamo 
     * toglierle da qui
     */
    void createHeader();

    /**
     * @brief Crea la scroll per la sezione dei pulsanti. 
     * 
     * La scroll è visibile solo quando i pulsanti non hanno abbastanza spazio per essere visualizzati.
     * 
     */
    void createCinemaScroll();
public:
    CinemaSelectionPage(QList<Cinema*>& w_cinema, QWidget *parent);

    /**
     * @brief toglie e ricrea i pulsanti del cinema. 
     * 
     * @details elimina tutti i cinemaButtons del layout cinemaButtonsLayout poi 
     * utilizza @ref MediaManagerJson per scaricare nella lista cinemas di struct Cinema tutti i cinema, 
     * poi scorre la lista e crea per ciascuno il button.
     * 
     * @note il modo in cui vengono cancellati è da rivedere...
     */
    void refreshCinemaButtons();
signals:
    void insertCinema();
    void selectedCinema(Cinema* nomeC);

};


#endif // CINEMASELECTIONPAGE_H
