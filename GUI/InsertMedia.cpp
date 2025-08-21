#include "InsertMedia.h"
#include "SearchPanel.h"

InsertMedia::InsertMedia(QWidget *parent): QWidget(parent){
    mediaManagerJson = new MediaManagerJson("");
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0); 
    mainLayout->setSpacing(0);
    
    indietro(mainLayout);
    addPagina(mainLayout);
    annullaSalva(mainLayout);
    mainLayout->setContentsMargins(100,0,100,40);
    
    setLayout(mainLayout);
}






//template

template<class L, class T>
void InsertMedia::addInput(QLabel* label,  L* layout, T* inputWidget){
    QWidget* widget = new QWidget; 
    QVBoxLayout* l = new QVBoxLayout;
    l->addWidget(label,1);
    l->addWidget(inputWidget,4);
    widget->setLayout(l);
    layout->addWidget(widget);
    
    //style
    label->setAlignment(Qt::AlignTop);
    label->setStyleSheet(   "color: #84a0a8;"
                            "font-size: 14pt;"
                            "font-weight: bold;");
    label->setMaximumHeight(30);
    l->setAlignment(Qt::AlignTop);
}

template<class L, class T>
void InsertMedia::addEnumList(L* base, const QString& labelText, const std::vector<T>& items, QListWidget*& listWidget){
    QLabel* label = new QLabel(labelText);
    listWidget = new QListWidget(this);

    listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

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

    connect(listWidget, &QListWidget::itemClicked, this, [=](QListWidgetItem* item){
        item->setCheckState(item->checkState() == Qt::Checked ? Qt::Unchecked : Qt::Checked);
    });


    //style
    listWidget->setStyleSheet( "QListWidget{ border-radius: 10px; " 
                                "background-color: #4e7f8b;"
                                "color: #05313c;"
                                "padding: 10px;"
                                "font-size: 12pt;}"
                                
                                "QScrollBar:vertical { background: #04303b;"       
                                "width: 12px;"              
                                "margin: 0px 0px 0px 0px;"
                                "border: 1px solid #04303b;"
                                "border-radius: 5px; }"

                                "QScrollBar::handle:vertical {background: #285965;"       
                                "min-height: 20px;"
                                "border-radius: 3px;}"

                                "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
                                "background: #04303b;"         
                                "border: 1px solid #04303b;" 
                                "height: 12px;"
                                "border-radius: 5px;"
                                "subcontrol-position: top;"  
                                "subcontrol-origin: margin;}"

                                "QScrollBar::add-line:vertical:hover, QScrollBar::sub-line:vertical:hover {"
                                "background: #04303b;}");

    listWidget->setSelectionMode(QAbstractItemView::NoSelection); 
    listWidget->setFocusPolicy(Qt::NoFocus); 

}

template<class L, class T>
void InsertMedia::addEnumCombo(L* base, const QString& labelText, const std::vector<T>& items, QComboBox*& comboBox) {
    QLabel* label = new QLabel(labelText);
    comboBox = new QComboBox(this);

    for (T e : items) {
        const char* str = toString(e);
        if (QString::fromUtf8(str) == "Non trovato") continue;

        comboBox->addItem(QString::fromUtf8(str), QVariant::fromValue(static_cast<int>(e)));
    }

    comboBox->setCurrentIndex(0);

    addInput(label, base, comboBox);

    //style
    comboBox->setView(new QListView());
    comboBox->view()->setFrameShape(QFrame::NoFrame);
    comboBox->view()->setAttribute(Qt::WA_Hover, true);
    comboBox->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QFont font;
    font.setPointSize(14); 
    comboBox->setFont(font);
    comboBox->view()->setFont(font);
}
                            
template<class L>
QLineEdit* InsertMedia::addLineEdit(const QString& testo, L* ly){
    QLabel* label = new QLabel(testo,this);
    QLineEdit* lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText(testo);
    addInput(label, ly, lineEdit);
    return lineEdit;

    //style
    lineEdit->setMaximumHeight(70);
}
                            
template<class L>
QSpinBox* InsertMedia::addSpin(const QString& testo, int min, int max, int standard, L* ly){
    QLabel* label = new QLabel(testo,this);
    QSpinBox * spin = new QSpinBox (this);
    spin->setRange(min, max);
    spin->setValue(standard);
    addInput(label, ly, spin);
    return spin;
}
                            
template<class L>
QDoubleSpinBox* InsertMedia::addDoubleSpin(const QString& testo, double min, double max, double standard, L* ly){
    QLabel* label = new QLabel(testo,this);
    QDoubleSpinBox* doubleSpin = new QDoubleSpinBox (this);
    doubleSpin->setRange(min, max);
    doubleSpin->setValue(standard);
    addInput(label, ly, doubleSpin);
    return doubleSpin;
}

template<class L>
void InsertMedia::addReference(const QString& testo, const QString& json, L* ly, SelectMediaReference*& reference){
    QLabel* label = new QLabel(testo);
    reference = new SelectMediaReference(json, this); 

    addInput(label, ly, reference);
    
    connect(reference, &SelectMediaReference::mediaSelected, this, [this, json](MediaFrame* f){
        if(json == "film"){
            titoloFilmRirefimento = f->getTitolo();
            autoreFilmRiferimento = f->getAutore();
        }
        else if(json == "podcast"){
            titoloPodcastRiferimento = f->getTitolo();
            autorePodcastRiferimento = f->getAutore();
        }
        checkMediaNameAvailability();
    });

    connect(this, &InsertMedia::resetReferenceSelection, reference, [reference](){
        reference->setSelectFalse();
    });

    //style
    label->setAlignment(Qt::AlignCenter);
}

template<class EnumType>
vector<EnumType> InsertMedia::getSelectedList(QListWidget* list){
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









//widget di input da aggiungere
ListPersone* InsertMedia::addPersone(const QString& testo, QVBoxLayout* ly){
    QLabel* label = new QLabel(testo);
    ListPersone* lista = new ListPersone(this); 
    addInput(label, ly, lista);
    return lista;
}

void InsertMedia::addTipologiaCombo(QHBoxLayout* baseH){
    QLabel* label = new QLabel("Tipologia");
    comboTipologia = new QComboBox(this);

    comboTipologia->setView(new QListView());
    comboTipologia->view()->setFrameShape(QFrame::NoFrame);
    comboTipologia->view()->setAttribute(Qt::WA_Hover, true);
    QFont font;
    font.setPointSize(14); 
    comboTipologia->setFont(font);
    comboTipologia->view()->setFont(font);

    comboTipologia->addItem("Film");
    comboTipologia->addItem("Trailer");
    comboTipologia->addItem("Podcast");
    comboTipologia->addItem("Puntata");
    comboTipologia->addItem("Inserzione");

    addInput(label, baseH, comboTipologia);

    connect(comboTipologia, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index){
        updateTabTipologia(index);
    });

    comboTipologia->setObjectName("comboTipologia");

}

QTextEdit* InsertMedia::addDescrizione(QHBoxLayout* baseH){
    QLabel* label = new QLabel("Descrizione");
    QTextEdit* textEdit = new QTextEdit(this);
    textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    addInput(label, baseH, textEdit);
    return textEdit;
    
    //style
    textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    textEdit->setMaximumHeight(350);
    textEdit->setAlignment(Qt::AlignTop);

}

QDateEdit* InsertMedia::addDataInizioRilascio(QVBoxLayout* ly) {
    QLabel* label = new QLabel("Data di Inizio Proiezione");

    dataInizio = new QDateEdit(this);
    dataInizio->setCalendarPopup(true);
    dataInizio->setDisplayFormat("dd/MM/yyyy");
    dataInizio->setDate(QDate::currentDate());
    QCalendarWidget* calendar = new QCalendarWidget;
    calendar->setMinimumSize(280,180); 
    dataInizio->setCalendarWidget(calendar);

    addInput(label, ly, dataInizio);  
    return dataInizio;
}

QDateEdit* InsertMedia::addDataFineRilascio(QVBoxLayout* ly) {
    QLabel* label = new QLabel("Data di Fine Proiezione");

    dataFine = new QDateEdit(this);
    dataFine->setCalendarPopup(true);
    dataFine->setDisplayFormat("dd/MM/yyyy");
    dataFine->setDate(QDate::currentDate());
    QCalendarWidget* calendar = new QCalendarWidget;
    calendar->setMinimumSize(280,180); 
    dataFine->setCalendarWidget(calendar);

    connect(dataInizio, &QDateEdit::dateChanged, dataFine, &QDateEdit::setMinimumDate);

    dataFine->setMinimumDate(dataInizio->date());

    addInput(label, ly, dataFine);
    return dataFine;
}







//metodi funzionali per il corretto comportamento della pagina
void InsertMedia::updateTabTipologia(int index){
    
    //per resettare tutto ad eccezione dei campi comuni
    resetInputFilm();
    resetInputTrailer();
    resetInputInserzione();
    resetInputPodcast();
    resetInputPuntata();

    bool disableDate = (index == 2);

    // Blocca la modifica dall'utente
    dataInizio->setEnabled(!disableDate);
    dataFine->setEnabled(!disableDate);

    if(disableDate){
        dataInizio->setDate(QDate::currentDate());
        dataFine->setDate(QDate::currentDate());
    }

    if(index == 1 || index == 3){
        saveButton->setEnabled(false);
    }
    else checkMediaNameAvailability();

    stackTipologia->setCurrentIndex(index);
}

void InsertMedia::checkMediaNameAvailability() {
    QString titolo = titoloMedia->text().trimmed();
    QString autore = autoreMedia->text().trimmed();

    // Carico la lista dei cinema esistenti
    MediaManagerJson manager(QDir(QCoreApplication::applicationDirPath()).filePath(".."));
    QList<MediaData*> listInsertMedia = manager.loadAll();
    
    bool isAvailable = true;

    if(titolo.isEmpty() || autore.isEmpty()) isAvailable = false;

    for (const MediaData* m: listInsertMedia) {
        if (m->titolo.compare(titolo, Qt::CaseInsensitive) == 0 && m->autore.compare(autore, Qt::CaseInsensitive) == 0) {
            isAvailable = false;
            break;
        }
    }

    if (!isAvailable) {
        if(!titolo.isEmpty()&&!autore.isEmpty()){
            errorLabel->setText("Titolo già presente per questo autore");
            errorLabel->setVisible(true);
        }
        saveButton->setEnabled(false); // disabilita bottone
    } else if(  (stackTipologia->currentIndex()==1 && autoreFilmRiferimento!="" && titoloFilmRirefimento !="")||
                (stackTipologia->currentIndex()==3 && autorePodcastRiferimento != "" && titoloPodcastRiferimento !="")||
                (stackTipologia->currentIndex()!=3 && stackTipologia->currentIndex()!=1)){
        errorLabel->setVisible(false);
        saveButton->setEnabled(true);
    }
}





//costruzioni dei diversi widget per la tab "specifiche tipologia"

void InsertMedia::addTipologiaFilm(QWidget* TipoFilm){              //tipologia Film
    QHBoxLayout* filmH = new QHBoxLayout;
    QVBoxLayout* filmV1 = new QVBoxLayout;
    QVBoxLayout* filmV2 = new QVBoxLayout;
    QWidget* widgetFilm1 = new QWidget;
    QWidget* widgetFilm2 = new QWidget;

    attoriFilm = addPersone("Attori",filmV1);
    addEnumList(filmV1, "Genere", tuttiIGeneri(), listGeneri);
    CasaProdFilm = addLineEdit("Casa di Produzione",filmV2);
    addEnumCombo(filmV2,"Target",tutteLeClassificazioni(), comboTarget);
    totPostCreditFilm = addSpin("Numero di Post Credit", 0, 5, 0, filmV2);
    costoBigliettoFilm = addDoubleSpin("Costo Biglietto (€)", 0.0, 15.0, 8.0, filmV2);

    
    widgetFilm1->setLayout(filmV1);
    widgetFilm2->setLayout(filmV2);
    
    filmH->addWidget(widgetFilm1);
    filmH->addWidget(widgetFilm2);
    
    TipoFilm->setLayout(filmH);

    //style    
    CasaProdFilm->setObjectName("CasaProdFilm");
    totPostCreditFilm->setObjectName("totPostCreditFilm");
    costoBigliettoFilm->setObjectName("costoBigliettoFilm");
    comboTarget->setObjectName("comboTarget");
}

void InsertMedia::addTipologiaTrailer(QWidget* TipoTrailer){        //tipologia Trailer
    QHBoxLayout* TrailerH = new QHBoxLayout;

    numeroProiezioniTrailer = addSpin("Numero Proiezioni Giornaliere", 0, 20, 0, TrailerH);
    addReference("Film", "film", TrailerH, referenceTrailer);

    TipoTrailer->setLayout(TrailerH);

    //style
    numeroProiezioniTrailer->setObjectName("numeroProiezioniTrailer");
}


void InsertMedia::addTipologiaInserzione(QWidget* TipoInserzione){  //tipologia Inserzione
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
    numeroProiezioniGioInserzione = addSpin("Numero Proiezioni Giornaliere", 0, 20, 0, inserzioneH2);
    costoBaseProiezInserzione = addDoubleSpin("Costo Base per Proieizone (€)", 30.0, 4000.0, 30.0, inserzioneH2);
    aziendaInserzInserzione = addLineEdit("Azienda Inserzionistica", inserzioneH2);

    WidgetInserzione2->setLayout(inserzioneH1);
    WidgetInserzione3->setLayout(inserzioneH2);
    inserzioneV2->addWidget(WidgetInserzione2);
    inserzioneV2->addWidget(WidgetInserzione3);
    TipoInserzione->setLayout(inserzioneV2);

    //style
    aziendaInserzInserzione->setObjectName("aziendaInserzInserzione");
    numeroProiezioniGioInserzione->setObjectName("numeroProiezioniGioInserzione");
    costoBaseProiezInserzione->setObjectName("costoBaseProiezInserzione");
    comboTarget->setObjectName("comboTarget");
}

void InsertMedia::addTipologiaPodcast(QWidget* TipoPodcast){    //tipologia Podcast
    QHBoxLayout* podcastH = new QHBoxLayout;
    conduttorePodcast = addLineEdit("Conduttore", podcastH);
    TipoPodcast->setLayout(podcastH);

    //style
    conduttorePodcast->setObjectName("conduttorePodcast");
}

void InsertMedia::addTipologiaPuntate(QWidget* TipoPuntata){    //tipologia Puntata
    QHBoxLayout* puntataH = new QHBoxLayout();
    QVBoxLayout* puntataV = new QVBoxLayout();
    QWidget* widgetPuntata = new QWidget();

    
    ospitiPuntata = addPersone("Ospiti",puntataV); 
    numeroPubblicitaPuntata = addSpin("Numero Pubblicità", 0, 20, 4, puntataV);
    widgetPuntata->setLayout(puntataV);

    puntataH->addWidget(widgetPuntata);
    addReference("Podcast","podcast",puntataH, referencePuntate);

    TipoPuntata->setLayout(puntataH);

    //style
    numeroPubblicitaPuntata->setObjectName("numeroPubblicitaPuntata");
}






//aggiunta elementi alla pagina InsertMedia

void InsertMedia::addPagina(QVBoxLayout* mainLayout){
    QVBoxLayout* paginaV1 = new QVBoxLayout();
    QVBoxLayout* paginaV2 = new QVBoxLayout();
    QVBoxLayout* paginaV3 = new QVBoxLayout();
    QVBoxLayout* paginaV4 = new QVBoxLayout();
    QHBoxLayout* paginaH = new QHBoxLayout();
    QWidget* widgetPagina1 = new QWidget();
    QWidget* widgetPagina2 = new QWidget();
    QWidget* widgetPagina3 = new QWidget();
    QWidget* widgetPagina4 = new QWidget();

    QLabel* titolo = new QLabel("Aggiungi un elemento alla libreria");
    framePath = new InsertImageFrame(   "<span style='color:#05313c; font-size:16px;'><b> +<u>Aggiungi copertina</u></b></span><br>"
                                        "<span style='color:#05313c;; font-size:16px;'> oppure rilasciala</span>",
                                        "#frame { border: 3px dashed #05313c; border-radius: 12px; } "
                                        "QLabel { qproperty-alignment: AlignCenter; }" 
                                        "QToolButton { border: none; color: #073c47; font-weight: bold; } "
                                        "QToolButton:hover { color: #ffffffff; }", this);
    QPixmap pixmap(":/images/default.png");
    copertina = new QLabel(this);
    QLabel* anteprima = new QLabel("Anteprima immagine",this);
    
    paginaV1->addSpacing(25);
    paginaV1->addWidget(copertina);
    paginaV1->addSpacing(25);
    paginaV1->addWidget(framePath);
    widgetPagina1->setLayout(paginaV1);
    paginaV2->addWidget(anteprima);
    paginaV2->addWidget(widgetPagina1);

    widgetPagina2->setLayout(paginaV2);
    paginaH->addWidget(widgetPagina2);
    addTabs(paginaH);
    widgetPagina3->setLayout(paginaH);
    paginaV3->addWidget(titolo);
    paginaV3->addWidget(widgetPagina3);
    widgetPagina4->setLayout(paginaV3);
    
    mainLayout->addWidget(widgetPagina4);
    
    connect(framePath,&InsertImageFrame::clicked,this,&InsertMedia::chooseImage);
    connect(framePath, &InsertImageFrame::removeImage, this, &InsertMedia::removeImage);
    
    //style
    widgetPagina2->setContentsMargins(0,0,30,0);
    widgetPagina1->setObjectName("anteprima");
    widgetPagina1->setMaximumWidth(370);
    paginaV2->setAlignment(Qt::AlignCenter);
    titolo->setAlignment(Qt::AlignTop);
    titolo->setContentsMargins(0,0,0,80);
    anteprima->setAlignment(Qt::AlignLeft);
    titolo->setContentsMargins(0,0,0,10);
    anteprima->setStyleSheet("color: #bdced3");

    QFont fontAnteprima = anteprima->font();
    fontAnteprima.setPointSize(12);
    fontAnteprima.setBold(true);
    anteprima->setFont(fontAnteprima);

    QFont fontTitolo = titolo->font();
    fontTitolo.setPointSize(20);
    fontTitolo.setBold(true);
    titolo->setFont(fontTitolo);

    titolo->setStyleSheet("color: #fed36a;");
    framePath->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    framePath->setMaximumSize(450, 155);
    framePath->setMinimumSize(200, 150);
    framePath->setCursor(Qt::PointingHandCursor);
    
    copertina->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    copertina->setMaximumSize(300, 430);
    copertina->setAlignment(Qt::AlignCenter);
    copertina->setPixmap(pixmap.scaled(280,330, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void InsertMedia::indietro(QVBoxLayout* mainLayout){        //pulsante indietro
    QHBoxLayout* bottone = new QHBoxLayout;
    QPushButton* indietro = new QPushButton("← indietro",this);
    QWidget* indietroW = new QWidget;
    bottone->addWidget(indietro);
    bottone->setAlignment(Qt::AlignLeft);
    indietroW->setLayout(bottone);
    mainLayout->addWidget(indietroW);

    indietro->setCursor(Qt::PointingHandCursor);

    connect(indietro, &QPushButton::clicked, this, [this](){
        this->resetAllInput();
        this->tornaIndietro();
    }); 

    //style
    indietro->setObjectName("indietro");
}

void InsertMedia::annullaSalva(QVBoxLayout* mainLayout){
    cancelButton = new QPushButton("annulla",this);
    saveButton = new QPushButton("salva",this);
    QWidget* asWidget = new QWidget;
    QHBoxLayout* asH = new QHBoxLayout;
    asH->addWidget(cancelButton);
    asH->addSpacing(100);
    asH->addWidget(saveButton);
    asWidget->setLayout(asH);
    mainLayout->addWidget(asWidget);

    saveButton->setEnabled(false);

    connect(cancelButton, &QPushButton::clicked, this, [this](){
        this->resetAllInput();
        this->tornaAllaLibreria(); 
    });//poi da modificare facendolo tornare alla pagina della libreria di default
    connect(saveButton, &QPushButton::clicked, this, [this]() {
        this->salvaMedia();
        this->resetAllInput();
        this->tornaAllaLibreria();
        if(referencePuntate)referencePuntate->reloadMedia();
        if(referenceTrailer)referenceTrailer->reloadMedia();
    });

    //style
    cancelButton->setCursor(Qt::PointingHandCursor);
    saveButton->setCursor(Qt::PointingHandCursor);
    cancelButton->setObjectName("cancelButton");
    saveButton->setObjectName("saveButton");
}

void InsertMedia::addTabs(QHBoxLayout* layout){
    tab = new QTabWidget(this);
    
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
    
    //style
    tab->tabBar()->setCursor(Qt::PointingHandCursor);
    tab->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tab->setMaximumSize(950,850);
    tab->setMinimumWidth(500);
    tab->setStyleSheet(
                        "QTabWidget::pane {border: none; background-color: #05313c;}"
                        "QTabBar::tab {"
                        "    background-color: #073c47;"
                        "    color: #4e7f8b;"
                        "    border-right: 5px solid #05313c;"
                        "    border-top: 5px solid #05313c;"
                        "    border-top-left-radius: 10px; "
                        "    border-top-right-radius: 10px; "
                        "    min-width: 100px;"
                        "    padding: 5px 12px;"
                        "    font-size: 14pt;"
                        "}"
                        "QTabBar QToolButton{"
                        "background-color: #4e7f8b; border:2px solid #05313c; border-top-left-radius: 5px; border-top-right-radius: 5px;}"
                        "QTabBar QToolButton::left-arrow {image: url(:/icons/arrow_left.png);} QTabBar QToolButton::right-arrow{image: url(:/icons/arrow_right.png);}"
                        "QTabBar::tab:selected {"
                        "    background-color: #05313c;"
                        "    color: #afc5cc;"
                        "}"
                        "QTabBar::tab:first{"
                        "margin-left: 20px;}"
                    );

}





void InsertMedia::addBase(QWidget* base){
    QVBoxLayout* baseV1 = new QVBoxLayout;
    QVBoxLayout* baseV2 = new QVBoxLayout;
    QHBoxLayout* baseH1 = new QHBoxLayout;
    QHBoxLayout* baseH2 = new QHBoxLayout;
    QWidget* widget1 = new QWidget;
    QWidget* widget2 = new QWidget;
    QWidget* widget3 = new QWidget;

    //Messaggio di errore
    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color: red; font-size: 12pt;");
    errorLabel->setText("");
    errorLabel->setVisible(false);
    errorLabel->setAlignment(Qt::AlignCenter);
    
    titoloMedia = addLineEdit("Titolo*", baseH1);
    autoreMedia = addLineEdit("Autore*", baseH1);
    addTipologiaCombo(baseH1);
    widget1->setLayout(baseH1);
    
    durataMinutiMedia = addSpin("Durata (min)",0,500,0,baseH2);
    addEnumList(baseH2, "Lingue", tutteLeLingue(), listLingue);
    addEnumList(baseH2, "Sottotitoli", tutteLeLingue(), listSottotitoli);
    dataInizio = addDataInizioRilascio(baseV1);
    dataFine = addDataFineRilascio(baseV1);
    widget2->setLayout(baseV1);
    baseH2->addWidget(widget2);
    widget3->setLayout(baseH2);
    
    baseV2->addWidget(widget1);
    baseV2->addWidget(errorLabel);
    baseV2->addWidget(widget3);
    
    base->setLayout(baseV2);

    connect(titoloMedia, &QLineEdit::textChanged, this, &InsertMedia::checkMediaNameAvailability);
    connect(autoreMedia, &QLineEdit::textChanged, this, &InsertMedia::checkMediaNameAvailability);

    //style
    titoloMedia->setObjectName("titoloMedia");
    autoreMedia->setObjectName("autoreMedia");
    durataMinutiMedia->setObjectName("durataMinutiMedia");
    dataInizio->setObjectName("dataInizio");
    dataFine->setObjectName("dataFine");
    base->setContentsMargins(20,50,20,100);
    baseV1->setAlignment(Qt::AlignTop);
}

void InsertMedia::addDescrizione(QWidget* descrizione){
    QVBoxLayout* descrizioneV = new QVBoxLayout;
    QHBoxLayout* descrizioneH = new QHBoxLayout;
    QWidget* widget = new QWidget;

    addEnumCombo(descrizioneV, "Formato", tuttiIFormati(), comboFormato);
    addEnumCombo(descrizioneV, "Risoluzione", tutteLeRisoluzioni(), comboRisoluzione);
    widget->setLayout(descrizioneV);
    descrizioneH->addWidget(widget);
    descrizioneMedia = addDescrizione(descrizioneH);
    descrizione->setLayout(descrizioneH);

    //style
    descrizione->setContentsMargins(20,50,20,50);
    comboFormato->setObjectName("comboFormato");
    comboRisoluzione->setObjectName("comboRisoluzione");
    descrizioneMedia->setObjectName("descrizioneMedia");
    descrizioneMedia->setStyleSheet( 
                                "QScrollBar:vertical { background: #04303b;"       
                                "width: 12px;"              
                                "margin: 0px 0px 0px 0px;"
                                "border: 1px solid #04303b;"
                                "border-radius: 5px; }"

                                "QScrollBar::handle:vertical {background: #285965;"       
                                "min-height: 20px;"
                                "border-radius: 3px;}"

                                "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
                                "background: #04303b;"         
                                "border: 1px solid #04303b;" 
                                "height: 12px;"
                                "border-radius: 5px;"
                                "subcontrol-position: top;"  
                                "subcontrol-origin: margin;}"

                                "QScrollBar::add-line:vertical:hover, QScrollBar::sub-line:vertical:hover {"
                                "background: #04303b;}");
    descrizione->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    descrizione->setMaximumHeight(650);
}

void InsertMedia::addTipologia(QWidget* tipologia){
    stackTipologia = new QStackedLayout;

    TipoFilm = new QWidget;
    TipoTrailer = new QWidget;
    TipoInserzione = new QWidget;
    TipoPodcast = new QWidget;
    TipoPuntata = new QWidget;

    addTipologiaFilm(TipoFilm);
    addTipologiaTrailer(TipoTrailer);
    addTipologiaInserzione(TipoInserzione);
    addTipologiaPodcast(TipoPodcast);
    addTipologiaPuntate(TipoPuntata);

    stackTipologia->addWidget(TipoFilm);
    stackTipologia->addWidget(TipoTrailer);
    stackTipologia->addWidget(TipoPodcast);
    stackTipologia->addWidget(TipoPuntata);
    stackTipologia->addWidget(TipoInserzione);

    stackTipologia->setCurrentIndex(0);
    tipologia->setLayout(stackTipologia);

    //style
    tipologia->setContentsMargins(20,50,20,50);
}






//salvataggio degli input su un file Json

void InsertMedia::saveCommonFields(MediaData &data) {       //funzione per salvare i dati comuni
    data.titolo = titoloMedia->text();
    data.autore = autoreMedia->text();
    data.descrizione = descrizioneMedia->toPlainText();
    data.durataMinuti = durataMinutiMedia->value();
    data.lingueDisponibili = getSelectedList<Lingua>(listLingue);
    data.sottotitoliDisponibili = getSelectedList<Lingua>(listSottotitoli);
    data.formato = static_cast<Formato>(comboFormato->currentData().toInt());
    data.risoluzione = static_cast<Risoluzione>(comboRisoluzione->currentData().toInt());
    data.path = imagePath==""?":/images/default.png":imagePath;
}


void InsertMedia::salvaMedia(){                         //funzione per salvare gli input in un json

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
        film.target = static_cast<Classificazione>(comboTarget->currentData().toInt());
        film.tipologia = "film";
        
        mediaManagerJson->saveFilm(&film);
    }
    //trailer
    else if(stackTipologia->currentIndex()==1){
        
        TrailerData trailer;
        saveCommonFields(trailer);

        trailer.nProiezioniGiornaliere = numeroProiezioniTrailer->value();
        trailer.filmAssociato = titoloFilmRirefimento;
        trailer.autoreFilmAssociato = autoreFilmRiferimento;
        trailer.tipologia = "trailer";
    
        mediaManagerJson->saveTrailer(&trailer);
    }
    //podcast
    else if(stackTipologia->currentIndex()==2){
        
        PodcastData podcast;
        saveCommonFields(podcast);

        podcast.conduttore = conduttorePodcast->text();
        podcast.tipologia = "podcast";

        mediaManagerJson->savePodcast(&podcast);
    }   
    //puntata
    else if(stackTipologia->currentIndex()==3){

        PuntataData puntata;
        saveCommonFields(puntata);

        puntata.ospiti = ospitiPuntata->getListaPersone();
        puntata.numeroPubblicita = numeroPubblicitaPuntata->value();
        puntata.podcastAssociato = titoloPodcastRiferimento; 
        puntata.autorePodcastAssociato = autorePodcastRiferimento; 
        puntata.tipologia = "puntata";

        mediaManagerJson->savePuntata(&puntata);

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
        inserzione.target = static_cast<Classificazione>(comboTarget->currentData().toInt());

        mediaManagerJson->saveInserzione(&inserzione);
    }   

}


//slots
void InsertMedia::chooseImage(){
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Seleziona un'immagine"),
        QString(),
        tr("Immagini (*.png *.jpg *.jpeg *.bmp *.gif)")
    );

    if (!fileName.isEmpty()) {
        imagePath = ":/images/" + QFileInfo(fileName).fileName();
        QPixmap pixmap(imagePath);
        copertina->setAlignment(Qt::AlignCenter);
        copertina->setPixmap(pixmap.scaled(280,330, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        framePath->insertImage(QFileInfo(fileName).fileName());
    }
}

void InsertMedia::removeImage(){
    QPixmap pixmap(":/images/default.png"); 
    copertina->setPixmap(pixmap.scaled(280,330, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imagePath.clear();
}






//reset dell'input messo sui widget, divisi per tipologia

void InsertMedia::resetInputFilm(){

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
    
}

void InsertMedia::resetInputTrailer(){
    if(numeroProiezioniTrailer) numeroProiezioniTrailer->setValue(0);
    if(titoloFilmRirefimento!="") titoloFilmRirefimento = "";
    if(autoreFilmRiferimento!="") autoreFilmRiferimento = "";
    emit resetReferenceSelection();
}
void InsertMedia::resetInputPodcast(){
    if(conduttorePodcast) conduttorePodcast->clear();
}
void InsertMedia::resetInputPuntata(){
    if(numeroPubblicitaPuntata) numeroPubblicitaPuntata->setValue(0);
    if(titoloPodcastRiferimento!="") titoloPodcastRiferimento = "";
    if(autorePodcastRiferimento!="") autorePodcastRiferimento = "";
    if(ospitiPuntata) ospitiPuntata->resetWidget();
    emit resetReferenceSelection();
}
void InsertMedia::resetInputInserzione(){
    if(aziendaInserzInserzione) aziendaInserzInserzione->clear();
    if(costoBaseProiezInserzione) costoBaseProiezInserzione->setValue(30.0);
    if(numeroProiezioniGioInserzione) numeroProiezioniGioInserzione->setValue(0);

    if(listFasceOrarie)
    for(int i = 0; i < listFasceOrarie->count(); ++i) {
        QListWidgetItem* item = listFasceOrarie->item(i);
        item->setCheckState(Qt::Unchecked);
    }

}

void InsertMedia::resetAllInput(){

    resetInputFilm();
    resetInputInserzione();
    resetInputPodcast();
    resetInputPuntata();
    resetInputTrailer();
    
    // LineEdit
    if(titoloMedia) titoloMedia->clear();
    if(autoreMedia) autoreMedia->clear();
    
    // SpinBox
    if(durataMinutiMedia) durataMinutiMedia->setValue(0);

    // QTextEdit
    if(descrizioneMedia) descrizioneMedia->clear();

    // InsertImageFrame
    if(framePath)        framePath->reset();

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
    if(comboFormato) comboFormato->setCurrentIndex(0);
    if(comboRisoluzione) comboRisoluzione->setCurrentIndex(0);
    
    //QDate
    if(dataInizio) dataInizio->setDate(QDate::currentDate());
    if(dataFine) dataFine->setDate(QDate::currentDate());
    
    QPixmap pixmap(":/images/default.png"); 
    copertina->setPixmap(pixmap.scaled(280,330, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    checkMediaNameAvailability();
    stackTipologia->setCurrentIndex(0);
    tab->setCurrentIndex(0);
    comboTipologia->setCurrentIndex(0);

    // QString
    imagePath.clear();
}


