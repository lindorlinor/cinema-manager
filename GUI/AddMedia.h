#ifndef AddMedia_H
#define AddMedia_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QString>
#include <QPixmap>
#include <QPushButton>
#include <QStandardPaths>
#include <QTabWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QListWidget>
#include <QSpinBox>
#include <QFont>
#include <QTextEdit>

#include "PathButton.h"

#include "../Film.h"
#include "../Inserzione.h"
#include "../Trailer.h"
#include "../Podcast.h"
#include "../Puntata.h"

class AddMedia:public QWidget{
    Q_OBJECT

    private:
    //serve per cambiare il widget di input a seconda della tipologia
    QStackedLayout* stackTipologia;

    //per ottenere gli input da passare al json
    PathButton* widgetPath;
    QListWidget* listLingue;
    QListWidget* listSottotitoli;
    QListWidget* listFormato;
    QListWidget* listRisoluzione;

    //widget che verranno utilizzati nel tab "tipologia" e intercambiati tramite la selezione
    //della tipologia su un QComboBox. Lo scambio è fatto con l'utilizzo di uno QStackedLayout stackTipologia
    QWidget* TipoFilm;
    QWidget* TipoTrailer;
    QWidget* TipoInserzione;
    QWidget* TipoPodcast;
    QWidget* TipoPuntata;
    
    Media* media;

    //inserisce i cambi di input della selezoina della copertina e del tab
    void addPagina(QVBoxLayout* mainLayout);

    //inserisce i vari tab base, di descrizione etipologia
    void addTab(QHBoxLayout* mainLayout);

    //aggiunge il pulsante per tornare alla scehrmata precedente
    void indietro(QVBoxLayout* mainLayout);

    //cambia il contenuto del tab per la tipologia quando viene selezionata una tipologia diversa
    void updateTabTipologia(int index);
    
    //salva tutti i dati raccolti in un file json
    void salva();
    
    //utilizzando lo stesso pattern più volte, si è preferito costruire un template per aggiungere i seguenti widget:
    // selezione della lingue, seleizone dei sottotitoli, selezione dei formati, selezione delle risoluzioni, selezione dei generi
    // selezione delle fasce orarie
    template<class L, class T>
    void addEnumList(L* base, const QString& labelText, const std::vector<T>& items, QListWidget*& listWidget);
    
    //dato che tutti gli input sono nella forma: "label, widget di input" si è preferito utilizzare un template per pulizia
    template<class L, class T>
    void addInput(QLabel* label,  L* layout, T* inputWidget);

    //funzioni per aggiungere i tab base, descrizione e tipologia
    void addBase(QWidget* base);
    void addDescrizione(QWidget* descrizione);
    void addTipologia(QWidget* tipologia);

    //campi da passare comuni a tutti
    void addTitolo(QHBoxLayout* baseH);
    void addTipologia(QHBoxLayout* baseH);
    void addAutore(QHBoxLayout* baseH);
    void addDurata(QHBoxLayout* baseH);
    void addDescrizione(QHBoxLayout* baseH);

    //cambi da passare a seconda del tipo

    void addDataInizioRilascio();   //comuni a tutti tranne a podcast
    void addDataFineRilascio();     //comuni a tutti tranne a podcast
    
    //film
    
    void addAttori();
    void addTarget(); //anche Inserzione
    void addGenere();
    void addCasaProd();
    void addCostoBiglietto();

    //trailer
    void addNumeroProiezioni(); //anche Inserzione
    void addFilm();

    //inserzione
    void addAzienzaInserzionistica();
    void addCostoBaseProiez();
    void addFasceOrarie();

    //Podcast
    void addConduttore();

    //Puntate
    void addOspiti();
    void NumeroPubblicita();
    void Podcast();


    public:
	explicit AddMedia(QWidget *parent);

    signals:
    void tornaIndietro();

};

#endif //AddMedia_H