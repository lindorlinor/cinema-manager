#include "AddMedia.h"
#include "SearchPanel.h"

//template

template<class L, class T>
void AddMedia::addInput(QLabel* label,  L* layout, T* inputWidget){
    QWidget* widget = new QWidget; 
    QVBoxLayout* l = new QVBoxLayout(this);
    label->setAlignment(Qt::AlignTop);
    l->addWidget(label,1);
    l->addWidget(inputWidget,4);
    widget->setLayout(l);
    layout->addWidget(widget);
}

template<class L, class T>
void AddMedia::addEnumList(L* base, const QString& labelText, const std::vector<T>& items, QListWidget*& listWidget){
    QLabel* label = new QLabel(labelText);
    listWidget = new QListWidget(this);

    //lista degli enum
    for (T e : items) {
        const char* str = toString(e);
        if (QString::fromUtf8(str) == "Non trovato") {
            continue; // salto quelli con stringa "Non trovato"
        }
        QListWidgetItem* item = new QListWidgetItem(QString::fromUtf8(str), listWidget);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        item->setData(Qt::UserRole, static_cast<int>(e));
    }

    addInput(label, base, listWidget);
}

template<class L, class T>
void AddMedia::addEnumCombo(L* base, const QString& labelText, const std::vector<T>& items, QComboBox*& comboBox) {
    QLabel* label = new QLabel(labelText);
    comboBox = new QComboBox(this);

    for (T e : items) {
        const char* str = toString(e);
        if (QString::fromUtf8(str) == "Non trovato") continue;

        comboBox->addItem(QString::fromUtf8(str), QVariant::fromValue(static_cast<int>(e)));
    }

    addInput(label, base, comboBox);
}

template<class L>
void AddMedia::addLineEdit(const QString& testo, L* ly){
    QLabel* label = new QLabel(testo,this);
    QLineEdit* lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText(testo);
    addInput(label, ly, lineEdit);
}

template<class L>
void AddMedia::addSpin(const QString& testo, int min, int max, int standard, L* ly){
    QLabel* label = new QLabel(testo,this);
    QSpinBox * spin = new QSpinBox (this);
    spin->setRange(min, max);
    spin->setValue(standard);
    addInput(label, ly, spin);
}

template<class L>
void AddMedia::addDoubleSpin(const QString& testo, double min, double max, double standard, L* ly){
    QLabel* label = new QLabel(testo,this);
    QDoubleSpinBox* doubleSpin = new QDoubleSpinBox (this);
    doubleSpin->setRange(min, max);
    doubleSpin->setValue(standard);
    addInput(label, ly, doubleSpin);
}

//tab Base

void AddMedia::addTipologiaCombo(QHBoxLayout* baseH){
    QLabel* label = new QLabel("Tipologia");
    QComboBox* combo = new QComboBox(this);
    combo->addItem("Film");
    combo->addItem("Trailer");
    combo->addItem("Podcast");
    combo->addItem("Puntata");
    combo->addItem("Inserzione");

    addInput(label, baseH, combo);

    connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index){
        updateTabTipologia(index);
    });
}

void AddMedia::updateTabTipologia(int index){
    stackTipologia->setCurrentIndex(index);
}
//tab Descrizione

void AddMedia::addDescrizione(QHBoxLayout* baseH){
    QLabel* label = new QLabel("Descrizione");
    QTextEdit* textEdit = new QTextEdit(this);
    textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textEdit->setFixedSize(300,200);
    textEdit->setStyleSheet("margin-bottom: 10px;");
    addInput(label, baseH, textEdit);
}

//tab Tipologia

void AddMedia::addDataInizioRilascio(QHBoxLayout* ly){
    QLabel* label = new QLabel("Data di Inizio Proiezione");
    dataInizio = new QDateEdit;
    dataInizio->setCalendarPopup(true);
    dataInizio->setDisplayFormat("dd/MM/yyyy");
    dataInizio->setDate(QDate::currentDate());
    addInput(label, ly, dataInizio);
}

void AddMedia::addDataFineRilascio(QHBoxLayout* ly){
    QLabel* label = new QLabel("Data di Fine Proiezione");
    dataFine = new QDateEdit;
    dataFine->setCalendarPopup(true);
    dataFine->setDisplayFormat("dd/MM/yyyy");
    dataFine->setDate(QDate::currentDate());
    dataFine->setMinimumDate(dataInizio->date());
    addInput(label, ly, dataFine);
}

//tipologia Film

void AddMedia::addTipologiaFilm(QWidget* TipoFilm){
    QHBoxLayout* filmH1 = new QHBoxLayout;
    QHBoxLayout* filmH2 = new QHBoxLayout;
    QHBoxLayout* filmH3 = new QHBoxLayout;
    QHBoxLayout* filmH4 = new QHBoxLayout;
    QVBoxLayout* filmV = new QVBoxLayout;
    QWidget* widgetFilm1 = new QWidget;
    QWidget* widgetFilm2 = new QWidget;
    QWidget* widgetFilm3 = new QWidget;
    QWidget* widgetFilm4 = new QWidget;

    addDataInizioRilascio(filmH1);
    addDataFineRilascio(filmH1);
    addEnumList(filmH2, "Genere", tuttiIGeneri(), listGeneri);
    addLineEdit("Casa di Produzione",filmH2);
    addSpin("Numero di Post Credit", 0, 5, 0, filmH3);
    addDoubleSpin("Costo Biglietto (€)", 0.0, 15.0, 8.0, filmH3);
    widgetFilm1->setLayout(filmH1);
    widgetFilm2->setLayout(filmH2);
    widgetFilm3->setLayout(filmH3);
    filmV->addWidget(widgetFilm1);
    filmV->addWidget(widgetFilm2);
    filmV->addWidget(widgetFilm3);
    widgetFilm4->setLayout(filmV);
    addPersone(filmH4);
    filmH4->addWidget(widgetFilm4);
    TipoFilm->setLayout(filmH4);
}


void AddMedia::addPersone(QHBoxLayout* filmH){
    QLabel* label = new QLabel("Attori");
    ListPersone* lista = new ListPersone(this); 
    addInput(label, filmH, lista);
}


//tipologia Inserzione
void AddMedia::addTipologiaInserzione(QWidget* TipoInserzione){
    QHBoxLayout* inserzioneH1 = new QHBoxLayout;
    QHBoxLayout* inserzioneH2 = new QHBoxLayout;
    QVBoxLayout* inserzioneV = new QVBoxLayout;
    QWidget* WidgetInserzione1 = new QWidget(this);
    QWidget* WidgetInserzione2 = new QWidget(this);

    addEnumList(inserzioneH1, "Fasce Orarie", tutteLeFasceOrarie(), listFasceOrarie);
    addDataInizioRilascio(inserzioneH1);
    addDataFineRilascio(inserzioneH1);
    addSpin("Numero Proiezioni Giornaliere", 0, 20, 0, inserzioneH2);
    addDoubleSpin("Costo Base oer Proieizone (€)", 30.0, 4000.0, 30.0, inserzioneH2);
    addLineEdit("Azienda Inserzionistica", inserzioneH2);

    WidgetInserzione1->setLayout(inserzioneH1);
    WidgetInserzione2->setLayout(inserzioneH2);
    inserzioneV->addWidget(WidgetInserzione1);
    inserzioneV->addWidget(WidgetInserzione2);
    TipoInserzione->setLayout(inserzioneV);
}

//tipologia Podcast
void AddMedia::addTipologiaPodcast(QWidget* TipoPodcast){
    QHBoxLayout* podcastH = new QHBoxLayout;
    addLineEdit("Conduttore", podcastH);
    TipoPodcast->setLayout(podcastH);
}





//aggiunta dei Tab

void AddMedia::addBase(QWidget* base){
    QVBoxLayout* baseV = new QVBoxLayout;
    QHBoxLayout* baseH1 = new QHBoxLayout;
    QHBoxLayout* baseH2 = new QHBoxLayout;
    QWidget* widget1 = new QWidget;
    QWidget* widget2 = new QWidget;
    
    addLineEdit("Titolo", baseH1);
    addLineEdit("Autore", baseH1);
    addTipologiaCombo(baseH1);
    widget1->setLayout(baseH1);
    
    addSpin("Durata",0,500,0,baseH2);
    addEnumList(baseH2, "Lingue", tutteLeLingue(), listLingue);
    addEnumList(baseH2, "Sottotitoli", tutteLeLingue(), listSottotitoli);
    widget2->setLayout(baseH2);
    
    baseV->addWidget(widget1,2);
    baseV->addWidget(widget2,2);
    
    base->setLayout(baseV);
}

void AddMedia::addDescrizione(QWidget* descrizione){
    QVBoxLayout* descrizioneV = new QVBoxLayout;
    QHBoxLayout* descrizioneH = new QHBoxLayout;
    QWidget* widget = new QWidget;

    addEnumCombo(descrizioneV, "Formato", tuttiIFormati(), comboFormato);
    addEnumCombo(descrizioneV, "Risoluzione", tutteLeRisoluzioni(), comboRisoluzione);
    widget->setLayout(descrizioneV);
    descrizioneH->addWidget(widget);
    addDescrizione(descrizioneH);
    descrizione->setLayout(descrizioneH);
}

void AddMedia::addTipologia(QWidget* tipologia){
    stackTipologia = new QStackedLayout;

    TipoFilm = new QWidget;
    TipoTrailer = new QWidget;
    TipoInserzione = new QWidget;
    TipoPodcast = new QWidget;
    TipoPuntata = new QWidget;

    addTipologiaFilm(TipoFilm);
   // addTipologiaTrailer(TipoTrailer);
    addTipologiaInserzione(TipoInserzione);
    addTipologiaPodcast(TipoPodcast);
   // addTipologiaPuntate(TipoPuntata);

    stackTipologia->addWidget(TipoFilm);
    stackTipologia->addWidget(TipoTrailer);
    stackTipologia->addWidget(TipoPodcast);
    stackTipologia->addWidget(TipoPuntata);
    stackTipologia->addWidget(TipoInserzione);

    stackTipologia->setCurrentIndex(0);
    tipologia->setLayout(stackTipologia);
}

void AddMedia::addTabs(QHBoxLayout* layout){
    QTabWidget* tab = new QTabWidget(this);
    tab->setFixedSize(800,500);
    
    QWidget* base = new QWidget;
    QWidget* descrizione = new QWidget;
    QWidget* tipologia = new QWidget;
    
    addBase(base);
    addDescrizione(descrizione);
    addTipologia(tipologia);

    tab->addTab(base, "Informazioni Base");
    tab->addTab(descrizione, "Descrizione");
    tab->addTab(tipologia, "Specifiche Tipologia");

    layout->addWidget(tab,2);
}

//pulsante indietro

void AddMedia::indietro(QVBoxLayout* mainLayout){
    QHBoxLayout* bottone = new QHBoxLayout(this);
    QPushButton* indietro = new QPushButton("←");
    QWidget* indietroW = new QWidget;
    bottone->addWidget(indietro);
    bottone->setAlignment(Qt::AlignLeft);
    indietroW->setLayout(bottone);
    mainLayout->addWidget(indietroW);

    connect(indietro, &QPushButton::clicked, this, &AddMedia::tornaIndietro);
}

//funzione per salvare gli input in un json

void AddMedia::salva(){

    //salva l'immagine
    
    
    //imposta le lingue selezionate
    for (int i = 0; i < listLingue->count(); ++i) {
        QListWidgetItem* item = listLingue->item(i);
        if (item->checkState() == Qt::Checked) {
            int val = item->data(Qt::UserRole).toInt();
            //aggiunge le lingue selezionate
            media->aggiungiLingua(static_cast<Lingua>(val));
        }
    }

    //imposta i sottotitoli selezionati
    for (int i = 0; i < listSottotitoli->count(); ++i) {
        QListWidgetItem* item = listSottotitoli->item(i);
        if (item->checkState() == Qt::Checked) {
            int val = item->data(Qt::UserRole).toInt();
            //aggiunge le lingue selezionate
            media->aggiungiSottotitolo(static_cast<Lingua>(val));
        }
    }
}

void AddMedia::addPagina(QVBoxLayout* mainLayout){
    QLabel* titolo = new QLabel("Aggiungi un elemento alla libreria");
    titolo->setAlignment(Qt::AlignTop);
    widgetPath = new PathButton;
    QVBoxLayout* sinistra = new QVBoxLayout();
    QHBoxLayout* layout = new QHBoxLayout();
    QWidget* widgetSinistra = new QWidget();
    QWidget* widgetLayout = new QWidget();

    QFont font = titolo->font();
    font.setPointSize(14);
    font.setBold(true);
    titolo->setFont(font);

    sinistra->addWidget(titolo);
    sinistra->addWidget(widgetPath);
    widgetSinistra->setLayout(sinistra);
    layout->addWidget(widgetSinistra);
    addTabs(layout);
    widgetLayout->setLayout(layout);
    mainLayout->addWidget(widgetLayout);
}

AddMedia::AddMedia(QWidget *parent): QWidget(parent){
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0); 
    mainLayout->setSpacing(0);
    
    indietro(mainLayout);
    addPagina(mainLayout);
    
    setLayout(mainLayout);
}