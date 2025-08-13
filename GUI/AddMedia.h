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
#include <QStringListModel>
#include <QDateEdit>
#include <QDoubleSpinBox>

#include "PathButton.h"
#include "ListPersone.h"

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
    QListWidget* listGeneri;
    QListWidget* listFasceOrarie;
    QComboBox* comboFormato;
    QComboBox* comboRisoluzione;
    QComboBox* comboTarget;
    QDateEdit* dataInizio;
    QDateEdit* dataFine;

    //widget che verranno utilizzati nel tab "tipologia" e intercambiati tramite la selezione
    //della tipologia su un QComboBox. Lo scambio è fatto con l'utilizzo di uno QStackedLayout stackTipologia
    QWidget* TipoFilm;
    QWidget* TipoTrailer;
    QWidget* TipoInserzione;
    QWidget* TipoPodcast;
    QWidget* TipoPuntata;

    //funzioni che costruiscono i widget
    void addTipologiaFilm(QWidget* TipoFilm);
    void addTipologiaTrailer(QWidget* TipoTrailer);
    void addTipologiaInserzione(QWidget* TipoInserzione);
    void addTipologiaPodcast(QWidget* TipoPodcast);
    void addTipologiaPuntate(QWidget* TipoPuntata);
    
    Media* media;

    //inserisce i cambi di input della selezoina della copertina e del tab
    void addPagina(QVBoxLayout* mainLayout);

    //inserisce i vari tab base, di descrizione etipologia
    void addTabs(QHBoxLayout* mainLayout);

    //aggiunge il pulsante per tornare alla scehrmata precedente
    void indietro(QVBoxLayout* mainLayout);

    //cambia il contenuto del tab per la tipologia quando viene selezionata una tipologia diversa
    void updateTabTipologia(int index);
    
    //salva tutti i dati raccolti in un file json
    void salva();
    
    //utilizzando lo stesso pattern più volte, si è preferito costruire un template per aggiungere i seguenti widget:
    // selezione della lingue, seleizone dei sottotitoli, selezione dei generi, selezione delle fasce orarie
    template<class L, class T>
    void addEnumList(L* base, const QString& labelText, const std::vector<T>& items, QListWidget*& listWidget);

    //lo stesso principio ma per le singole selezioni: selezione dei formati, selezione delle risoluzioni
    template<class L, class T>
    void addEnumCombo(L* base, const QString& labelText, const std::vector<T>& items, QComboBox*& comboBox);
    
    //dato che tutti gli input sono nella forma: "label, widget di input" si è preferito utilizzare un template per pulizia
    template<class L, class T>
    void addInput(QLabel* label,  L* layout, T* inputWidget);

    //aggiunge i Widget che contengono un LineEdit
    template<class L>
    void addLineEdit(const QString& testo, L* ly);

    //aggiunge i Widget che contengono uno spin
    template<class L>
    void addSpin(const QString& testo, int min, int max, int standard, L* ly);

    //aggiunge i Widget che contengono un Doublespin
    template<class L>
    void addDoubleSpin(const QString& testo, double min, double max, double standard, L* ly);

    //funzioni per aggiungere i tab base, descrizione e tipologia
    void addBase(QWidget* base);
    void addDescrizione(QWidget* descrizione);
    void addTipologia(QWidget* tipologia);

    //campi da passare comuni a tutti
    void addTipologiaCombo(QHBoxLayout* baseH);
    void addDescrizione(QHBoxLayout* baseH);

    //cambi da passare a seconda del tipo

    void addDataInizioRilascio(QHBoxLayout* ly);   //comuni a tutti tranne a podcast
    void addDataFineRilascio(QHBoxLayout* ly);     //comuni a tutti tranne a podcast
    
    //film e Puntate
    
    void addPersone(QHBoxLayout* filmH);

    //trailer
    void addFilm(QHBoxLayout* trailerH);

    //Puntate
    void Podcast();


    public:
	explicit AddMedia(QWidget *parent);

    signals:
    void tornaIndietro();

};

#endif //AddMedia_H