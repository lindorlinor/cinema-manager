#ifndef SEARCHPANEL_H
#define SEARCHPANEL_H

#include <QWidget>
#include <QMenu>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QApplication>
#include <QIcon>
#include <QFile>
#include <QToolButton>

#include "CinemaSelectionPage.h"

class SearchPanel:public QWidget{
    Q_OBJECT
    private:
    //menu
    void addMenus(QVBoxLayout* mainLayout);

    //selezione media
    /**
    * @brief Pulsanti per filtrare i contenuti dei Media
    * 
    * filtrano i Media tra: tutto, film, trailer, inserzione, podcast
    */
    
    QToolButton* tutto;
    QToolButton* film;
    QToolButton* trailer;
    QToolButton* inserzione;
    QToolButton* podcast;
    
    //torna alla selezione del cinema
    /**
    * @brief Pulsante per tornare alla selezione del cinema
    */
    QToolButton* cinema;
    
    //aggiunta media
    /**
    * @brief Pulsante per aggiungere un Media
    * 
    */
   QPushButton* addMedia;
   
   //barra du ricerca
    QLineEdit* cerca;

    /**
    * @brief aggiornamento barra di ricerca
    * 
    * in base al pulsante di filtraggio che si clicca, cambia il
    * PlaceholderText con la selezione cercata 
    */
    void updateCerca(const QString& filtro);


    /**
    * @brief metodi per creare la gui della pagina
    */
    void addPagina(QVBoxLayout* mainLayout);                //"contenitore" principale
    void addLatoFiltri(QWidget* widgetSinistra);             //lato di sinistra con i pulsanti
    void addLatoDestra(QStackedWidget* stackModifiche);     //lato di destra con lo stackLibreria


    //cambio pagina

    /**
    * @brief QStackedWidget per la libreria 
    * cambia il widget di libreria in base al filtro applicato: tutto, film, trailer, podcast, inserzioni
    */
    QStackedWidget* stackLibreria;

    /**
    * @brief QStackedWidget per gli edit ai media
    * cambia il widget di destra per la ricerca nella libreria (il widget stackLibreria) con le diverse pagine per: 
    * - l'aggiunta di un media
    * - la modifica di un media
    * - la visualizzazione di un media
    */
    QStackedWidget* stackModifiche;

    //indice per tenere traccia dell'ultima pagina presentata nello stackModifiche e poter tornare indietro
    int previousIndex;

    public:
	explicit SearchPanel(QWidget *parent);

    /**
    * @brief slot per modificare stackModifiche
    * aggiorna lo stackModifiche
    */
    public slots:
    void updateModifierPanel(int index);
    void updateNomeCinema(const QString& nome);
    
    
    signals:
    void setFullScreen();
    void escFullScreen();
    void escSearchPanel();
    void resetPages();
};

#endif //SEARCHPANEL_H