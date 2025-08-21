#ifndef INSERTMEDIA_H
#define INSERTMEDIA_H

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
#include <QScrollBar>

#include "InsertImageFrame.h"
#include "ListPersone.h"
#include "SelectMediaReference.h"

#include "../Film.h"
#include "../Inserzione.h"
#include "../Trailer.h"
#include "../Podcast.h"
#include "../Puntata.h"
#include "../DataFiles/Popolate.h"
#include "../DataFiles/MediaManagerJson.h"

class InsertMedia:public QWidget{
    Q_OBJECT

    private:

    MediaManagerJson* mediaManagerJson; //serve per salvare i dati raccolti nel json
    QStackedLayout* stackTipologia; //serve per cambiare il widget di input del tab "specifiche tipologia" a seconda della tipologia selezionata nella QComboBox

    //widget che verranno utilizzati nel tab "specifiche tipologia" e intercambiati tramite la selezione
    //della tipologia su un QComboBox. Lo scambio è fatto con l'utilizzo di uno QStackedLayout stackTipologia
    QWidget* TipoFilm;
    QWidget* TipoTrailer;
    QWidget* TipoInserzione;
    QWidget* TipoPodcast;
    QWidget* TipoPuntata;

    //costruzioni dei diversi widget per la tab "specifiche tipologia"
    void addTipologiaFilm(QWidget* TipoFilm);
    void addTipologiaTrailer(QWidget* TipoTrailer);
    void addTipologiaInserzione(QWidget* TipoInserzione);
    void addTipologiaPodcast(QWidget* TipoPodcast);
    void addTipologiaPuntate(QWidget* TipoPuntata);

    //variabili necessarie per raccogliere i dati di input
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
    QString titoloFilmRirefimento; 
    QString autoreFilmRiferimento; 
    QString titoloPodcastRiferimento; 
    QString autorePodcastRiferimento; 
    QString imagePath; 

    //reset dell'input messo sui widget, divisi per tipologia. Sono necessari quando si premono i pulsanti: salva, annulla, indietro o quando si cambia tipologia
    void resetAllInput();
    void resetInputFilm();
    void resetInputTrailer();
    void resetInputPodcast();
    void resetInputPuntata();
    void resetInputInserzione();
    
    QPushButton* cancelButton;
    QPushButton* saveButton;
    QTabWidget* tab;
    QLabel* errorLabel;
    QLabel* copertina;
    SelectMediaReference* referenceTrailer;
    SelectMediaReference* referencePuntate;

   //aggiunta elementi della pagina InsertMedia
    void addPagina(QVBoxLayout* mainLayout);        //pagine principale: viene aggiunta la parte del tab e della "selezione compertina"
    void indietro(QVBoxLayout* mainLayout);         //aggiunge il pulsante per tornare alla scehrmata precedente
    void annullaSalva(QVBoxLayout* mainLayout);     //aggiunge i pulsanti per annullare e salvare

    void addTabs(QHBoxLayout* mainLayout);          //inserisce i tab di: base, descrizione e specifiche tipologia
        void addBase(QWidget* base);
        void addDescrizione(QWidget* descrizione);
        void addTipologia(QWidget* tipologia);
        
        
    //metodi funzionali per il corretto comportamento della pagina
    void updateTabTipologia(int index);     //cambia il contenuto del tab "selezione tipologia" quando viene selezionata una tipologia diversa
    void checkMediaNameAvailability();
   
   
    //salvataggio degli input su un file Json
    void salvaMedia();                       //salva tutti i dati raccolti in un file json
    void saveCommonFields(MediaData &data);  //salva i campi comuni alle varie tipologie (richiamato da salvaMedia)
   
   
    //template
    
    template<class L, class T>
    void addInput(QLabel* label,  L* layout, T* inputWidget);                                                   /* dato che tutti gli input sono nella forma: "label, widget di input" si è preferito utilizzare 
                                                                                                                un template per pulizia del codice */
    template<class L, class T>
    void addEnumList(L* base, const QString& labelText, const std::vector<T>& items, QListWidget*& listWidget); /* utilizzando lo stesso pattern più volte, si è preferito costruire un template per aggiungere i 
                                                                                                                seguenti widget:selezione della lingue, seleizone dei sottotitoli, selezione dei generi, selezione 
                                                                                                                delle fasce orarie */
    template<class L, class T>
    void addEnumCombo(L* base, const QString& labelText, const std::vector<T>& items, QComboBox*& comboBox);    //lo stesso principio ma per le singole selezioni: selezione dei formati, selezione delle risoluzioni
    
    template<class L>
    QLineEdit* addLineEdit(const QString& testo, L* ly);                                                        //aggiunge i Widget che contengono un LineEdit
    
    template<class L>
    QSpinBox* addSpin(const QString& testo, int min, int max, int standard, L* ly);                             //aggiunge i Widget che contengono uno spin

    template<class L>
    QDoubleSpinBox* addDoubleSpin(const QString& testo, double min, double max, double standard, L* ly);        //aggiunge i Widget che contengono un Doublespin
    
    template<class L>
    void addReference(const QString& testo, const QString& json, L* ly, SelectMediaReference*& reference);       //aggiunge il widget delle reference a trailer e puntata, per associare film e podcast
    
    template<class EnumType>
    vector<EnumType> getSelectedList(QListWidget* list);                                                        //ottiene i selezionati di una QListWidget
    

    //widget di input da aggiungere, sono stati fatti dei metodi perché utilizzati più volte o per pulizia del codice
    ListPersone* addPersone(const QString& testo, QVBoxLayout* ly);                                             //aggiungono il widget di ListPersone, utilizzato in Film e Podcast
    void addTipologiaCombo(QHBoxLayout* baseH);
    QTextEdit* addDescrizione(QHBoxLayout* baseH);
    QDateEdit* addDataInizioRilascio(QVBoxLayout* ly);   //comuni a tutti tranne a podcast
    QDateEdit* addDataFineRilascio(QVBoxLayout* ly);     //comuni a tutti tranne a podcast
    

    public:
	explicit InsertMedia(QWidget *parent);

    signals:
    void tornaAllaLibreria();
    void tornaIndietro();
    void resetReferenceSelection();

    public slots:
    void chooseImage();

};

#endif //INSERTMEDIA_H