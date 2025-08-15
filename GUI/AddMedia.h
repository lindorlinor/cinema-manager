#ifndef ADDMEDIA_H
#define ADDMEDIA_H

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
#include <QStackedLayout>

#include "InsertImageFrame.h"
#include "ListPersone.h"

#include "../Film.h"
#include "../Inserzione.h"
#include "../Trailer.h"
#include "../Podcast.h"
#include "../Puntata.h"
#include "../DataFiles/Popolate.h"
#include "../DataFiles/MediaManagerJson.h"

class AddMedia:public QWidget{
    Q_OBJECT

    private:

    MediaManagerJson* mediaManagerJson;
    //serve per cambiare il widget di input a seconda della tipologia
    QStackedLayout* stackTipologia;

    //per ottenere gli input da passare al json
    QLineEdit* titoloMedia;
    QLineEdit* autoreMedia;
    ListPersone* attoriFilm;
    ListPersone* ospitiPuntata;
    QLineEdit* CasaProdFilm;
    QLineEdit* conduttorePodcast;
    QLineEdit* aziendaInserzInserzione;
    QSpinBox* durataMinutiMedia;
    QSpinBox* totPostCreditFilm;
    QSpinBox* numeroProiezioniTrailer;
    QSpinBox* numeroProiezioniGioInserzione;
    QSpinBox* numeroPubblicitaPuntata;
    QDoubleSpinBox* costoBigliettoFilm;
    QDoubleSpinBox* costoBaseProiezInserzione;
    QTextEdit* descrizioneMedia;
    QString* filmSelezionatoTrailer;
    QString* podcastSelezionatoPuntata;
    QComboBox* comboTipologia;
    InsertImageFrame* framePath;
    QListWidget* listLingue;
    QListWidget* listSottotitoli;
    QListWidget* listGeneri;
    QListWidget* listFasceOrarie;
    QComboBox* comboFormato;
    QComboBox* comboRisoluzione;
    QComboBox* comboTarget;
    QDateEdit* dataInizio;
    QDateEdit* dataFine;
    QString imagePath; 

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

    //funzione che elimina i dati di tutti gli input, serve quando si preme il pulsante annulla
    void resetAllInput();
    void resetInputFilm();
    void resetInputTrailer();
    void resetInputPodcast();
    void resetInputPuntata();
    void resetInputInserzione();
    
    Media* media;
    QPushButton* annulla;
    QPushButton* salva;
    QTabWidget* tab;

    //salva i campi comuni
    void saveCommonFields(MediaData &data);

    //inserisce i cambi di input della selezoina della copertina e del tab
    void addPagina(QVBoxLayout* mainLayout);

    //inserisce i vari tab base, di descrizione etipologia
    void addTabs(QHBoxLayout* mainLayout);

    //aggiunge il pulsante per tornare alla scehrmata precedente
    void indietro(QVBoxLayout* mainLayout);

    //cambia il contenuto del tab per la tipologia quando viene selezionata una tipologia diversa
    void updateTabTipologia(int index);
    
    //salva tutti i dati raccolti in un file json
    void salvaMedia();

    //aggiunge i pulsanti per annullare e salvare
    void annullaSalva(QVBoxLayout* mainLayout);
    
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
    QLineEdit* addLineEdit(const QString& testo, L* ly);

    //aggiunge i Widget che contengono uno spin
    template<class L>
    QSpinBox* addSpin(const QString& testo, int min, int max, int standard, L* ly);

    //aggiunge i Widget che contengono un Doublespin
    template<class L>
    QDoubleSpinBox* addDoubleSpin(const QString& testo, double min, double max, double standard, L* ly);

    //per ottenere i selezionati di una QListWidget
    template<class EnumType>
    vector<EnumType> getSelectedList(QListWidget* list);

    //funzioni per aggiungere i tab base, descrizione e tipologia
    void addBase(QWidget* base);
    void addDescrizione(QWidget* descrizione);
    void addTipologia(QWidget* tipologia);

    //campi da passare comuni a tutti
    void addTipologiaCombo(QHBoxLayout* baseH);
    QTextEdit* addDescrizione(QHBoxLayout* baseH);


    //campi da passare a seconda del tipo

    QDateEdit* addDataInizioRilascio(QHBoxLayout* ly);   //comuni a tutti tranne a podcast
    QDateEdit* addDataFineRilascio(QHBoxLayout* ly);     //comuni a tutti tranne a podcast
    
    //film e Puntate
    
    ListPersone* addPersone(QVBoxLayout* filmH);

    //trailer
    void addFilm(QHBoxLayout* trailerH);

    //Puntate
    void Podcast();

    public:
	explicit AddMedia(QWidget *parent);

    signals:
    void tornaIndietro();

    public slots:
    void chooseImage();

};

#endif //ADDMEDIA_H