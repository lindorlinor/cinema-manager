#ifndef MEDIAINTERFACE_H
#define MEDIAINTERFACE_H

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
#include <QCalendarWidget>

#include "InsertImageFrame.h"
#include "ListPersone.h"
#include "SelectMediaReference.h"

#include "../Cinema.h"
#include "../Media.h"
#include "../Film.h"
#include "../Inserzione.h"
#include "../Trailer.h"
#include "../Podcast.h"
#include "../Puntata.h"

#include "../DataFiles/CinemaRepositoryJson.h"

class MediaInterface:public QWidget{
    Q_OBJECT

    protected:
    CinemaRepositoryJson* cinemaManager; 
    QStackedLayout* stackTipologia;

    //cinema selezionato
    Cinema* im_cinemaSelezionato;

    //liste di media
    QList<Media*> im_mediaList;

    QLabel* titolo;

    //costruzioni dei diversi widget per la tab "specifiche tipologia", verranno utilizzati nel tab "specifiche tipologia" 
    //e intercambiati tramite la selezione della tipologia su un QComboBox. Lo scambio è fatto con l'utilizzo di uno QStackedLayout stackTipologia
    QWidget* addTipologiaFilm();
    QWidget* addTipologiaTrailer();
    QWidget* addTipologiaInserzione();
    QWidget* addTipologiaPodcast();
    QWidget* addTipologiaPuntate();

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
    QComboBox* comboTargetFilm;
    QComboBox* comboTargetInserzioni;
    QDateEdit* dataInizio;
    QDateEdit* dataFine;
    QString titoloFilmRiferimento; 
    QString autoreFilmRiferimento; 
    QString titoloPodcastRiferimento; 
    QString autorePodcastRiferimento; 
    QString imagePath; 
    
    QPushButton* cancelButton;
    QPushButton* saveButton;
    QTabWidget* tab;
    QLabel* errorLabel;
    QLabel* copertina;
    SelectMediaReference* referenceTrailer;
    SelectMediaReference* referencePuntate;
    QPushButton* indietro;
    
    //aggiunta elementi della pagina MediaInterface
    QWidget* addPagina();                    //pagine principale: viene aggiunta la parte del tab e della "selezione compertina"
    QWidget* pulsanteIndietro();             //aggiunge il pulsante per tornare alla scehrmata precedente
    QWidget* annullaSalva();     //aggiunge i pulsanti per annullare e salvare
    
    QWidget* addTabs();          //inserisce i tab di: base, descrizione e specifiche tipologia
    QVBoxLayout* addBase();
    QHBoxLayout* addDescrizione();
    QWidget* addTipologia();
        
        
    //metodi funzionali per il corretto comportamento della pagina
    virtual void checkMediaNameAvailability();

    //set dei limiti a seconda della tipologia scelta o impostata
    virtual void setLimitTabTipologia(int index) = 0;
    
    //salvataggio degli input su un file Json
    virtual void salvaMedia() = 0;                   //salva tutti i dati raccolti in un file json
    
    //template
    
    template<class T>
    QWidget* addInput(QLabel* label, T* inputWidget);                                                   /* dato che tutti gli input sono nella forma: "label, widget di input" si è preferito utilizzare 
    un template per pulizia del codice */
    template<class T>
    QWidget* addEnumList(const QString& labelText, const std::vector<T>& items, QListWidget* listWidget); /* utilizzando lo stesso pattern più volte, si è preferito costruire un template per aggiungere i 
    seguenti widget:selezione della lingue, seleizone dei sottotitoli, selezione dei generi, selezione 
    delle fasce orarie */
    template<class T>
    QWidget* addEnumCombo(const QString& labelText, const std::vector<T>& items, QComboBox* comboBox);    //lo stesso principio ma per le singole selezioni: selezione dei formati, selezione delle risoluzioni
    
    QWidget* addLineEdit(const QString& testo, QLineEdit* lineEdit);                                                        //aggiunge i Widget che contengono un LineEdit
    QWidget* addSpin(const QString& testo, int min, int max, int standard, QSpinBox * spin);                             //aggiunge i Widget che contengono uno spin
    QWidget* addDoubleSpin(const QString& testo, double min, double max, double standard, QDoubleSpinBox* doubleSpin);        //aggiunge i Widget che contengono un Doublespin
    QWidget* addReference(const QString& testo, const QString& tipo, SelectMediaReference* reference); //aggiunge il widget delle reference a trailer e puntata, per associare film e podcast
    
    vector<std::string> getSelectedList(QListWidget* list);                                                        //ottiene i selezionati di una QListWidget
    
    
    //widget di input da aggiungere, sono stati fatti dei metodi perché utilizzati più volte o per pulizia del codice
    QWidget* addPersone(const QString& testo, ListPersone* lista);                                             //aggiungono il widget di ListPersone, utilizzato in Film e Podcast
    QWidget* addTipologiaCombo();
    QWidget* addDescrizioneWidget(QTextEdit* textEdit);
    QWidget* addDataInizioRilascio(QDateEdit* dataInizio);   //comuni a tutti tranne a podcast
    QWidget* addDataFineRilascio(QDateEdit* dataFine);     //comuni a tutti tranne a podcast


    //HELPER PER CREATE E MODIFIER MEDIA
    //converte da data in chrono
    year_month_day convertDate(const QDate& data);
    void addFasceOrarie(Inserzione* inserzione);
    void addLingue(Media* media);
    void addSottotitoli(Media* media);
    void addGeneri(Film* film);
    void addAttore(Film* film);
    void addOspite(Puntata* puntata);
    Media* findMediaReference(const QString& titolo, const QString& autore, const QString& tipo);

    void initUI();

    public:
	explicit MediaInterface(QWidget *parent);
    virtual ~MediaInterface() = default;
    
    signals:
    void tornaIndietro();
    
    public slots:
    void chooseImage();                      //rimuove l'immagine precedentemente selezionata
    void removeImage();                      //rimuove l'immagine precedentemente selezionata
    void getCinemaInfo(Cinema* data, QList<Media*>);
    
};

#endif //MEDIAINTERFACE_H