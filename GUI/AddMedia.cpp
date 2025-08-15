#include "AddMedia.h"
#include "SearchPanel.h"

//template

template<class L, class T>
void AddMedia::addInput(QLabel* label,  L* layout, T* inputWidget){
    QWidget* widget = new QWidget; 
    QVBoxLayout* l = new QVBoxLayout;
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
QLineEdit* AddMedia::addLineEdit(const QString& testo, L* ly){
    QLabel* label = new QLabel(testo,this);
    QLineEdit* lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText(testo);
    addInput(label, ly, lineEdit);
    return lineEdit;
}

template<class L>
QSpinBox* AddMedia::addSpin(const QString& testo, int min, int max, int standard, L* ly){
    QLabel* label = new QLabel(testo,this);
    QSpinBox * spin = new QSpinBox (this);
    spin->setRange(min, max);
    spin->setValue(standard);
    addInput(label, ly, spin);
    return spin;
}

template<class L>
QDoubleSpinBox* AddMedia::addDoubleSpin(const QString& testo, double min, double max, double standard, L* ly){
    QLabel* label = new QLabel(testo,this);
    QDoubleSpinBox* doubleSpin = new QDoubleSpinBox (this);
    doubleSpin->setRange(min, max);
    doubleSpin->setValue(standard);
    addInput(label, ly, doubleSpin);
    return doubleSpin;
}

//tab Base

void AddMedia::addTipologiaCombo(QHBoxLayout* baseH){
    QLabel* label = new QLabel("Tipologia");
    comboTipologia = new QComboBox(this);
    comboTipologia->addItem("Film");
    comboTipologia->addItem("Trailer");
    comboTipologia->addItem("Podcast");
    comboTipologia->addItem("Puntata");
    comboTipologia->addItem("Inserzione");

    addInput(label, baseH, comboTipologia);

    connect(comboTipologia, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index){
        updateTabTipologia(index);
    });
}

void AddMedia::updateTabTipologia(int index){
    stackTipologia->setCurrentIndex(index);
    switch(index){
        case 0:         resetInputInserzione();
                        resetInputPodcast();
                        resetInputPuntata();
                        resetInputTrailer();
                        break;
        case 1:         resetInputInserzione();
                        resetInputPodcast();
                        resetInputPuntata();
                        resetInputFilm();
                        break;
        case 2:         resetInputInserzione();
                        resetInputFilm();
                        resetInputPuntata();
                        resetInputTrailer();
                        break;
        case 3:         resetInputInserzione();
                        resetInputPodcast();
                        resetInputFilm();
                        resetInputTrailer();
                        break;
        case 4:         resetInputFilm();
                        resetInputPodcast();
                        resetInputPuntata();
                        resetInputTrailer();
                        break;
    }
}
//tab Descrizione

QTextEdit* AddMedia::addDescrizione(QHBoxLayout* baseH){
    QLabel* label = new QLabel("Descrizione");
    QTextEdit* textEdit = new QTextEdit(this);
    textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textEdit->setFixedSize(300,200);
    textEdit->setStyleSheet("margin-bottom: 10px;");
    addInput(label, baseH, textEdit);
    return textEdit;
}

//tab Tipologia

QDateEdit* AddMedia::addDataInizioRilascio(QHBoxLayout* ly) {
    QLabel* label = new QLabel("Data di Inizio Proiezione");

    dataInizio = new QDateEdit(this);
    dataInizio->setCalendarPopup(true);
    dataInizio->setDisplayFormat("dd/MM/yyyy");
    dataInizio->setDate(QDate::currentDate());

    addInput(label, ly, dataInizio);  
    return dataInizio;
}


QDateEdit* AddMedia::addDataFineRilascio(QHBoxLayout* ly) {
    QLabel* label = new QLabel("Data di Fine Proiezione");

    dataFine = new QDateEdit(this);
    dataFine->setCalendarPopup(true);
    dataFine->setDisplayFormat("dd/MM/yyyy");
    dataFine->setDate(QDate::currentDate());

    dataFine->setMinimumDate(dataInizio->date());
    // Aggiorna il minimo ogni volta che dataInizio cambia
    connect(dataInizio, &QDateEdit::dateChanged, this, [this](const QDate &newDate) {
        dataFine->setMinimumDate(newDate);
    });

    addInput(label, ly, dataFine);
    return dataFine;
}



//tipologia Film

void AddMedia::addTipologiaFilm(QWidget* TipoFilm){
    QHBoxLayout* filmH1 = new QHBoxLayout;
    QHBoxLayout* filmH2 = new QHBoxLayout;
    QHBoxLayout* filmH3 = new QHBoxLayout;
    QHBoxLayout* filmH4 = new QHBoxLayout;
    QVBoxLayout* filmV1 = new QVBoxLayout;
    QVBoxLayout* filmV2 = new QVBoxLayout;
    QWidget* widgetFilm1 = new QWidget;
    QWidget* widgetFilm2 = new QWidget;
    QWidget* widgetFilm3 = new QWidget;
    QWidget* widgetFilm4 = new QWidget;
    QWidget* widgetFilm5 = new QWidget;

    attoriFilm = addPersone(filmV1);
    addEnumCombo(filmV1,"Target",tutteLeClassificazioni(), comboTarget);
    widgetFilm1->setLayout(filmV1);
    dataInizio = addDataInizioRilascio(filmH1);
    dataFine = addDataFineRilascio(filmH1);
    addEnumList(filmH2, "Genere", tuttiIGeneri(), listGeneri);
    CasaProdFilm = addLineEdit("Casa di Produzione",filmH2);
    totPostCreditFilm = addSpin("Numero di Post Credit", 0, 5, 0, filmH3);
    costoBigliettoFilm = addDoubleSpin("Costo Biglietto (€)", 0.0, 15.0, 8.0, filmH3);

    widgetFilm2->setLayout(filmH1);
    widgetFilm3->setLayout(filmH2);
    widgetFilm4->setLayout(filmH3);
    filmV2->addWidget(widgetFilm2);
    filmV2->addWidget(widgetFilm3);
    filmV2->addWidget(widgetFilm4);
    widgetFilm5->setLayout(filmV2);
    filmH4->addWidget(widgetFilm1);
    filmH4->addWidget(widgetFilm5);
    TipoFilm->setLayout(filmH4);
}

ListPersone* AddMedia::addPersone(QVBoxLayout* filmH){
    QLabel* label = new QLabel("Attori");
    ListPersone* lista = new ListPersone(this); 
    addInput(label, filmH, lista);
    return lista;
}

//tipologia Inserzione
void AddMedia::addTipologiaInserzione(QWidget* TipoInserzione){
    QHBoxLayout* inserzioneH1 = new QHBoxLayout;
    QHBoxLayout* inserzioneH2 = new QHBoxLayout;
    QVBoxLayout* inserzioneV1 = new QVBoxLayout;
    QVBoxLayout* inserzioneV2 = new QVBoxLayout;
    QWidget* WidgetInserzione1 = new QWidget(this);
    QWidget* WidgetInserzione2 = new QWidget(this);
    QWidget* WidgetInserzione3 = new QWidget(this);

    addEnumList(inserzioneV1, "Fasce Orarie", tutteLeFasceOrarie(), listFasceOrarie);
    addEnumCombo(inserzioneV1, "Target", tutteLeClassificazioni(), comboTarget);
    WidgetInserzione1->setLayout(inserzioneV1);
    inserzioneH1 ->addWidget(WidgetInserzione1);
    dataInizio = addDataInizioRilascio(inserzioneH1);
    dataFine = addDataFineRilascio(inserzioneH1);
    numeroProiezioniGioInserzione = addSpin("Numero Proiezioni Giornaliere", 0, 20, 0, inserzioneH2);
    costoBaseProiezInserzione = addDoubleSpin("Costo Base per Proieizone (€)", 30.0, 4000.0, 30.0, inserzioneH2);
    aziendaInserzInserzione = addLineEdit("Azienda Inserzionistica", inserzioneH2);

    WidgetInserzione2->setLayout(inserzioneH1);
    WidgetInserzione3->setLayout(inserzioneH2);
    inserzioneV2->addWidget(WidgetInserzione2);
    inserzioneV2->addWidget(WidgetInserzione3);
    TipoInserzione->setLayout(inserzioneV2);
}

//tipologia Podcast
void AddMedia::addTipologiaPodcast(QWidget* TipoPodcast){
    QHBoxLayout* podcastH = new QHBoxLayout;
    conduttorePodcast = addLineEdit("Conduttore", podcastH);
    TipoPodcast->setLayout(podcastH);
}



//aggiunta dei Tab

void AddMedia::addBase(QWidget* base){
    QVBoxLayout* baseV = new QVBoxLayout;
    QHBoxLayout* baseH1 = new QHBoxLayout;
    QHBoxLayout* baseH2 = new QHBoxLayout;
    QWidget* widget1 = new QWidget;
    QWidget* widget2 = new QWidget;
    
    titoloMedia = addLineEdit("Titolo", baseH1);
    autoreMedia = addLineEdit("Autore", baseH1);
    addTipologiaCombo(baseH1);
    widget1->setLayout(baseH1);
    
    durataMinutiMedia = addSpin("Durata",0,500,0,baseH2);
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
    descrizioneMedia = addDescrizione(descrizioneH);
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
    QHBoxLayout* bottone = new QHBoxLayout;
    QPushButton* indietro = new QPushButton("←");
    QWidget* indietroW = new QWidget;
    bottone->addWidget(indietro);
    bottone->setAlignment(Qt::AlignLeft);
    indietroW->setLayout(bottone);
    mainLayout->addWidget(indietroW);

    connect(indietro, &QPushButton::clicked, this, &AddMedia::tornaIndietro);
}

template<class EnumType>
vector<EnumType> AddMedia::getSelectedList(QListWidget* list){
    vector<EnumType> risultato;
    if(!list) return risultato;
    for(int i=0; i<list->count(); ++i){
        QListWidgetItem* item = list->item(i);
        if(item->checkState() == Qt::Checked){
            risultato.push_back(static_cast<EnumType>(item->data(Qt::UserRole).toInt()));
        }
    }

    return risultato;
}

//funzione per salvare i dati comuni
void AddMedia::saveCommonFields(MediaData &data) {
    data.titolo = titoloMedia->text();
    data.autore = autoreMedia->text();
    data.descrizione = descrizioneMedia->toPlainText();
    data.durataMinuti = durataMinutiMedia->value();
    data.lingueDisponibili = getSelectedList<Lingua>(listLingue);
    data.sottotitoliDisponibili = getSelectedList<Lingua>(listSottotitoli);
    data.formato = static_cast<Formato>(comboFormato->currentData().toInt());
    data.risoluzione = static_cast<Risoluzione>(comboRisoluzione->currentData().toInt());
    data.path = imagePath;
}

//funzione per salvare gli input in un json
void AddMedia::salvaMedia(){

    //film
    if(stackTipologia->currentIndex()==0){

        FilmData film;
        saveCommonFields(film);

        film.genere = getSelectedList<Genere>(listGeneri);
        film.casaDiProduzione = CasaProdFilm->text();
        film.attoriPrincipali = attoriFilm->getListaPersone();
        film.nPostCredit = totPostCreditFilm->value();
        film.costoBiglietto = costoBigliettoFilm->value();
        film.dataInizioRilascio = dataInizio->date();
        film.dataFineRilascio = dataFine->date();

        mediaManagerJson->saveFilm(film);
    }
    //trailer
    else if(stackTipologia->currentIndex()==1){
        

    }
    //podcast
    else if(stackTipologia->currentIndex()==2){
        
        PodcastData podcast;
        saveCommonFields(podcast);

        podcast.conduttore = conduttorePodcast->text();

        mediaManagerJson->savePodcast(podcast);
    }   
    //puntata
    else if(stackTipologia->currentIndex()==3){
    }   
    //inserzione
    else if(stackTipologia->currentIndex()==4){

        InserzioniData inserzione;
        saveCommonFields(inserzione);

        inserzione.nProiezioniGiornaliere = numeroProiezioniGioInserzione->value();
        inserzione.costoFissoProiezione = costoBaseProiezInserzione->value();
        inserzione.aziendaInserzionista = aziendaInserzInserzione->text();
        inserzione.fasceOrarie = getSelectedList<FasciaOraria>(listFasceOrarie);
        inserzione.dataInizioRilascio = dataInizio->date();
        inserzione.dataFineRilascio = dataFine->date();

        mediaManagerJson->saveInserzione(inserzione);
    }   

}

void AddMedia::chooseImage(){
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Seleziona un'immagine"),
        QString(),
        tr("Immagini (*.png *.jpg *.jpeg *.bmp *.gif)")
    );

    if (!fileName.isEmpty()) {
        imagePath = fileName;
        framePath->setText(QFileInfo(fileName).fileName());
    }
}

void AddMedia::addPagina(QVBoxLayout* mainLayout){
    QLabel* titolo = new QLabel("Aggiungi un elemento alla libreria");
    titolo->setAlignment(Qt::AlignTop);
    framePath = new InsertImageFrame;
    QVBoxLayout* sinistra = new QVBoxLayout();
    QHBoxLayout* layout = new QHBoxLayout();
    QWidget* widgetSinistra = new QWidget();
    QWidget* widgetLayout = new QWidget();

    QFont font = titolo->font();
    font.setPointSize(14);
    font.setBold(true);
    titolo->setFont(font);

    sinistra->addWidget(titolo);
    sinistra->addWidget(framePath);
    widgetSinistra->setLayout(sinistra);
    layout->addWidget(widgetSinistra);
    addTabs(layout);
    widgetLayout->setLayout(layout);
    mainLayout->addWidget(widgetLayout);

    connect(framePath,&InsertImageFrame::clicked,this,&AddMedia::chooseImage);
}

void AddMedia::resetInputFilm(){
    if(CasaProdFilm) CasaProdFilm->clear();
    if(attoriFilm) attoriFilm->resetWidget();
    if(totPostCreditFilm) totPostCreditFilm->setValue(0);
    if(costoBigliettoFilm) costoBigliettoFilm->setValue(8.0);

    if(listGeneri)
    for(int i = 0; i < listGeneri->count(); ++i) {
        QListWidgetItem* item = listGeneri->item(i);
        item->setCheckState(Qt::Unchecked);
    }

    if(comboTarget) comboTarget->setCurrentIndex(0);
    if(dataInizio) dataInizio->setDate(QDate::currentDate());
    if(dataFine) dataFine->setDate(QDate::currentDate());
}
void AddMedia::resetInputTrailer(){

}
void AddMedia::resetInputPodcast(){
    if(conduttorePodcast) conduttorePodcast->clear();
}
void AddMedia::resetInputPuntata(){

}
void AddMedia::resetInputInserzione(){
    if(aziendaInserzInserzione) aziendaInserzInserzione->clear();
    if(costoBaseProiezInserzione) costoBaseProiezInserzione->setValue(30.0);
    if(numeroProiezioniGioInserzione) numeroProiezioniGioInserzione->setValue(0);

    if(listFasceOrarie)
    for(int i = 0; i < listFasceOrarie->count(); ++i) {
        QListWidgetItem* item = listFasceOrarie->item(i);
        item->setCheckState(Qt::Unchecked);
    }

    if(dataInizio) dataInizio->setDate(QDate::currentDate());
    if(dataFine) dataFine->setDate(QDate::currentDate());
}

void AddMedia::resetAllInput(){

    resetInputFilm();
    resetInputInserzione();
    resetInputPodcast();
    resetInputPuntata();
    resetInputTrailer();

    // LineEdit
    if(titoloMedia) titoloMedia->clear();
    if(autoreMedia) autoreMedia->clear();

    // ListPersone
 /*    if(ospitiPuntata) ospitiPuntata->resetWidget(); */

    // SpinBox
    if(durataMinutiMedia) durataMinutiMedia->setValue(0);
/*     if(numeroProiezioniTrailer) numeroProiezioniTrailer->setValue(0);
    if(numeroPubblicitaPuntata) numeroPubblicitaPuntata->setValue(0); */

    // QTextEdit
    if(descrizioneMedia) descrizioneMedia->clear();

    // QString*
/*     if(filmSelezionatoTrailer) *filmSelezionatoTrailer = "";
    if(podcastSelezionatoPuntata) *podcastSelezionatoPuntata = ""; */

    // InsertImageFrame
    if(framePath) framePath->setText("Clicca per inserire un'immagine"); 

    // QListWidget
    if(listLingue) 
    for(int i = 0; i < listLingue->count(); ++i) {
        QListWidgetItem* item = listLingue->item(i);
        item->setCheckState(Qt::Unchecked);
    }

    if(listSottotitoli) 
    for(int i = 0; i < listSottotitoli->count(); ++i) {
        QListWidgetItem* item = listSottotitoli->item(i);
        item->setCheckState(Qt::Unchecked);
    }

    // QComboBox
    if(comboTipologia) comboTipologia->setCurrentIndex(0);
    if(comboFormato) comboFormato->setCurrentIndex(0);
    if(comboRisoluzione) comboRisoluzione->setCurrentIndex(0);

    // QString
    imagePath.clear();
}

void AddMedia::annullaSalva(QVBoxLayout* mainLayout){
    annulla = new QPushButton("annulla",this);
    salva = new QPushButton("salva",this);
    QWidget* asWidget = new QWidget;
    QHBoxLayout* asH = new QHBoxLayout;
    asH->addWidget(annulla);
    asH->addWidget(salva);
    asWidget->setLayout(asH);
    mainLayout->addWidget(asWidget);

    connect(annulla, &QPushButton::clicked, this, [this](){
        this->resetAllInput();
        stackTipologia->setCurrentIndex(0);
        this->tornaIndietro(); 
    });//poi da modificare facendolo tornare alla pagina della libreria di default
    connect(salva, &QPushButton::clicked, this, [this]() {
        this->salvaMedia();
        this->tornaIndietro();
    });

}

AddMedia::AddMedia(QWidget *parent): QWidget(parent){
    mediaManagerJson = new MediaManagerJson("FileJson");
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0); 
    mainLayout->setSpacing(0);
    
    indietro(mainLayout);
    addPagina(mainLayout);
    annullaSalva(mainLayout);
    
    setLayout(mainLayout);
}