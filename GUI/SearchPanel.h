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
#include <QMessageBox>

#include "../Cinema.h"
#include "CinemaSelectionPage.h"
#include "InsertMedia.h"
#include "DataFiles/CinemaRepositoryJson.h"
#include "../DataFiles/MediaManagerXml.h"
#include "MediaLibraryTutto.h"
#include "MediaLibraryGenerale.h"
#include "CinemaModifier.h"

class LibraryObserver;

class SearchPanel:public QWidget{
    Q_OBJECT
    private:

    Cinema* s_cinemaSelezionato;
    CinemaRepositoryJson* s_jsonManager;
    MediaManagerXml* s_xmlManager;
    vector<LibraryObserver*> s_libraryObservers;
    QList<Media*> s_MediaListOfCinema;

    MediaLibraryGenerale* libreriaMediaGenerale;
    MediaLibraryTutto* libreriaMediaTutto;

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
    QToolButton* puntata;

    QComboBox* attivita;
    QComboBox* ordinamento;

    //valori da passarea ll'observer
    int comboAttivita = 0;   
    int comboOrdinamento = 0; 
    QString filtroBottone = "Film"; 
    QString ricerca = "";

    //media che sto visualizzando
    MediaView* detailPage;
   
   //salva il nome del cinema
   /**
   * @brief nome del cinema selezionato
   */
    QString p_nomeCinema;
    
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

    /**
     * @brief abbastanza autoesplicativo il nome XD
     * 
     */
    void metodoTemporaneoPerPagineDiVisualizzazione();

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

    //metodi che svolgono le attività necessarie che prevengono la chiamata all'update
    void updateFiltroTutto();
    void updateFiltroMedia(const QString& filtro);
    void preUpdate();
    /**
    * @brief aggiorna la lista di supporto per visualizzare i media presenti nel cinema
    */
    void updateMediaList();
    
    public:
	explicit SearchPanel(CinemaRepositoryJson* jsonManager, MediaManagerXml* xmlManager,QWidget *parent);
    void addObserver(LibraryObserver* obs);
    void update(int comboAttivita, int comboOrdinamento, const QString& filtro, const QString& ricerca);


    public slots:
    void updateModifierPanel(int index);
    void updateInfoCinema(Cinema* cinemaSel);
    void resetSearchPanel();    //resetta tutte le impostazioni di searchPanel
    void showMediaView(MediaView& detailPage);
    void removeMediaView();
    void acceptEditCinema();
    void acceptDeleteCinema();
    
    
    signals:
    void resetPages();
    void giveCinemaInfoToIP(Cinema* cinemaSel, QList<Media*> mediaList);
    void selectedFilterButton(const QString& filtro);
    void escSearchPanel();
    void deleteCinemaInSearchPanel(Cinema* s_cinemaSelezionato);
};

#endif //SEARCHPANEL_H