#include "MediaInterface.h"
#include "SearchPanel.h"

MediaInterface::MediaInterface(QList<Media*>& mediaList, QWidget *parent): QWidget(parent), im_mediaList(mediaList),stackTipologia(nullptr),titoloMedia(nullptr), autoreMedia(nullptr), attoriFilm(nullptr), ospitiPuntata(nullptr), CasaProdFilm(nullptr),
                                                conduttorePodcast(nullptr),aziendaInserzInserzione(nullptr),durataMinutiMedia(nullptr),totPostCreditFilm(nullptr),numeroProiezioniTrailer(nullptr),
                                                numeroProiezioniGioInserzione(nullptr),numeroPubblicitaPuntata(nullptr),costoBigliettoFilm(nullptr),costoBaseProiezInserzione(nullptr),descrizioneMedia(nullptr),
                                                comboTipologia(nullptr),framePath(nullptr),listLingue(nullptr),listSottotitoli(nullptr),listGeneri(nullptr),listFasceOrarie(nullptr),comboFormato(nullptr), comboRisoluzione(nullptr),
                                                comboTargetFilm(nullptr),comboTargetInserzioni(nullptr),dataInizio(nullptr),dataFine(nullptr),titoloFilmRiferimento(""), 
                                                autoreFilmRiferimento(""), titoloPodcastRiferimento(""),autorePodcastRiferimento(""),imagePath(""), tab(nullptr),referenceTrailer(nullptr),referencePuntate(nullptr){}

void MediaInterface::initUI(){
    cinemaManager = new CinemaRepositoryJson(); 
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0); 
    mainLayout->setSpacing(0);
    
    mainLayout->addWidget(pulsanteIndietro());
    mainLayout->addWidget(addPagina());
    mainLayout->setContentsMargins(100,0,100,40);
    
    setLayout(mainLayout);
}

//IMPOSTA IL NOME DEL CINEMA
void MediaInterface::getCinemaInfo(Cinema* cinemaSel){
    im_cinemaSelezionato = cinemaSel;
    if(referenceTrailer) referenceTrailer->reloadMedia(QString::fromStdString(im_cinemaSelezionato->getNomeCinema()));
    if(referencePuntate) referencePuntate->reloadMedia(QString::fromStdString(im_cinemaSelezionato->getNomeCinema()));
}






//template

template<class T>
QWidget* MediaInterface::addInput(QLabel* label, T* inputWidget){
    QWidget* widget = new QWidget(this); 
    QVBoxLayout* l = new QVBoxLayout;
    l->addWidget(label,1);
    l->addWidget(inputWidget,4);
    widget->setLayout(l);
    
    //style
    label->setAlignment(Qt::AlignTop);
    label->setStyleSheet(   "color: #84a0a8;"
                            "font-size: 14pt;"
                            "font-weight: bold;");
    label->setMaximumHeight(30);
    l->setAlignment(Qt::AlignTop);

    return widget;
}

template<class T>
QWidget* MediaInterface::addEnumList(const QString& labelText, const std::vector<T>& items, QListWidget* listWidget){
    QLabel* label = new QLabel(labelText, this);

    listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    //lista degli enum
    for (T e : items) {
        const char* str = toString(e);
        if (QString::fromUtf8(str) == "Non trovato" || QString::fromUtf8(str) == "Nessuno") {
            continue; // salto quelli con stringa "Non trovato"
        }
        QListWidgetItem* item = new QListWidgetItem(QString::fromUtf8(str), listWidget);

        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        item->setData(Qt::UserRole, QString::fromUtf8(str));
    }

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
                                "border-radius: 5px;"    
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
                                "background: #04303b;}"
                            
                                "QListWidget:disabled {"
                                "background-color: #365961;"
                                "color: #05313c;"
                                "border-radius: 10px;}");

    listWidget->setSelectionMode(QAbstractItemView::NoSelection); 
    listWidget->setFocusPolicy(Qt::NoFocus); 

    return addInput(label, listWidget);
}

template<class T>
QWidget* MediaInterface::addEnumCombo(const QString& labelText, const std::vector<T>& items, QComboBox* comboBox) {
    QLabel* label = new QLabel(labelText,this);

    for (T e : items) {
        const char* str = toString(e);
        if (QString::fromUtf8(str) == "Non trovato") continue;

        comboBox->addItem(QString::fromUtf8(str), QVariant::fromValue(static_cast<int>(e)));
    }

    comboBox->setCurrentIndex(0);
    
    //style
    comboBox->setView(new QListView(comboBox));
    comboBox->view()->setFrameShape(QFrame::NoFrame);
    comboBox->view()->setAttribute(Qt::WA_Hover, true);
    comboBox->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    
    QFont font;
    font.setPointSize(14); 
    comboBox->setFont(font);
    comboBox->view()->setFont(font);

    return addInput(label, comboBox);
}
                 
QWidget* MediaInterface::addLineEdit(const QString& testo, QLineEdit* lineEdit){
    QLabel* label = new QLabel(testo,this);
    lineEdit->setPlaceholderText(testo);
    
    return addInput(label, lineEdit);
}
                      
QWidget* MediaInterface::addSpin(const QString& testo, int min, int max, int standard, QSpinBox * spin){
    QLabel* label = new QLabel(testo,this);
    spin->setRange(min, max);
    spin->setValue(standard);
    return addInput(label, spin);
}
                   
QWidget* MediaInterface::addDoubleSpin(const QString& testo, double min, double max, double standard, QDoubleSpinBox* doubleSpin){
    QLabel* label = new QLabel(testo,this);
    doubleSpin->setRange(min, max);
    doubleSpin->setValue(standard);
    return addInput(label, doubleSpin);
}

QWidget* MediaInterface::addReference(const QString& testo, SelectMediaReference* reference){
    QLabel* label = new QLabel(testo,this);
    
    //style
    label->setAlignment(Qt::AlignCenter);
    return addInput(label, reference);
}

vector<std::string> MediaInterface::getSelectedList(QListWidget* list){
    vector<std::string> risultato;
    if(!list) return risultato;
    for(int i=0; i<list->count(); ++i){
        QListWidgetItem* item = list->item(i);
        if(item->checkState() == Qt::Checked){
            risultato.push_back(item->data(Qt::UserRole).toString().toStdString());
        }
    }

    return risultato;
}









//input widget
QWidget* MediaInterface::addPersone(const QString& testo, ListPersone* lista){
    QLabel* label = new QLabel(testo,this);
    return addInput(label, lista);
}

QWidget* MediaInterface::addTipologiaCombo(){
    QLabel* label = new QLabel("Tipologia",this);
    comboTipologia = new QComboBox(this);

    comboTipologia->setView(new QListView(comboTipologia));
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

    comboTipologia->setObjectName("comboTipologia");
    return addInput(label, comboTipologia);

}

QWidget* MediaInterface::addDescrizioneWidget(QTextEdit* textEdit){
    QLabel* label = new QLabel("Descrizione",this);
    textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    //style
    textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    textEdit->setMaximumHeight(350);
    textEdit->setAlignment(Qt::AlignTop);
    
    return addInput(label, textEdit);
}

QWidget* MediaInterface::addDataInizioRilascio(QDateEdit* dataInizio) {
    QLabel* label = new QLabel("Data di Inizio Proiezione",this);

    dataInizio->setCalendarPopup(true);
    dataInizio->setDisplayFormat("dd/MM/yyyy");
    dataInizio->setDate(QDate::currentDate());
    QCalendarWidget* calendar = new QCalendarWidget;
    calendar->setMinimumSize(280,180); 
    dataInizio->setCalendarWidget(calendar);

    return addInput(label, dataInizio);  
}

QWidget* MediaInterface::addDataFineRilascio(QDateEdit* dataFine) {
    QLabel* label = new QLabel("Data di Fine Proiezione",this);

    dataFine->setCalendarPopup(true);
    dataFine->setDisplayFormat("dd/MM/yyyy");
    dataFine->setDate(QDate::currentDate());
    QCalendarWidget* calendar = new QCalendarWidget;
    calendar->setMinimumSize(280,180); 
    dataFine->setCalendarWidget(calendar);

    connect(dataInizio, &QDateEdit::dateChanged, dataFine, &QDateEdit::setMinimumDate);

    dataFine->setMinimumDate(dataInizio->date());

    return addInput(label, dataFine);
}






void MediaInterface::checkMediaNameAvailability() {
    QString titolo = titoloMedia->text().trimmed();
    QString autore = autoreMedia->text().trimmed();
    
    bool isAvailable = true;
    errorLabel->setVisible(false);

    if(titolo.isEmpty() || autore.isEmpty()) isAvailable = false;

    for (const Media* m: im_mediaList) {
        if (QString::fromStdString(m->getTitolo()).compare(titolo, Qt::CaseInsensitive) == 0 && QString::fromStdString(m->getAutore()).compare(autore, Qt::CaseInsensitive) == 0) {
            isAvailable = false; 
        }
    }

    if (!isAvailable) {
        if(!titolo.isEmpty()&&!autore.isEmpty()){
            errorLabel->setText("Titolo già presente per questo autore");
            errorLabel->setVisible(true);
        }
        saveButton->setEnabled(false); // disabilita bottone
    } else if(  (comboTipologia->currentIndex()==1 && autoreFilmRiferimento!="" && titoloFilmRiferimento !="")||
                (comboTipologia->currentIndex()==3 && autorePodcastRiferimento != "" && titoloPodcastRiferimento !="")||
                (comboTipologia->currentIndex()!=3 && comboTipologia->currentIndex()!=1)){
        errorLabel->setVisible(false);
        saveButton->setEnabled(true);
    } else {
        errorLabel->setVisible(false);
        saveButton->setEnabled(true);
    }
}





//costruzioni dei diversi widget per la tab "specifiche tipologia"

QWidget* MediaInterface::addTipologiaFilm(){  //tipologia Film
    
        QWidget* TipoFilm = new QWidget(this);

        QHBoxLayout* filmH = new QHBoxLayout;
        QVBoxLayout* filmV1 = new QVBoxLayout;
        QVBoxLayout* filmV2 = new QVBoxLayout;
        QWidget* widgetFilm1 = new QWidget(this);
        QWidget* widgetFilm2 = new QWidget(this);
        
        comboTargetFilm = new QComboBox(this);
        listGeneri = new QListWidget(this);
        attoriFilm = new ListPersone();
        CasaProdFilm = new QLineEdit(this);
        totPostCreditFilm = new QSpinBox(this);
        costoBigliettoFilm = new QDoubleSpinBox(this);

        filmV1->addWidget(addPersone("Attori",attoriFilm));
        filmV1->addWidget(addEnumList("Genere", tuttiIGeneri(), listGeneri));
        filmV2->addWidget(addLineEdit("Casa di Produzione", CasaProdFilm));
        filmV2->addWidget(addEnumCombo("Target",tutteLeClassificazioni(), comboTargetFilm));
        filmV2->addWidget(addSpin("Numero di Post Credit", 0, 5, 0, totPostCreditFilm));
        filmV2->addWidget(addDoubleSpin("Costo Biglietto (€)", 0.0, 15.0, 8.0, costoBigliettoFilm));
            
        widgetFilm1->setLayout(filmV1);
        widgetFilm2->setLayout(filmV2);
            
        filmH->addWidget(widgetFilm1);
        filmH->addWidget(widgetFilm2);
            
        TipoFilm->setLayout(filmH);

            //style    
        CasaProdFilm->setObjectName("CasaProdFilm");
        totPostCreditFilm->setObjectName("totPostCreditFilm");
        costoBigliettoFilm->setObjectName("costoBigliettoFilm");
        comboTargetFilm->setObjectName("comboTargetFilm");

        return TipoFilm;
}

QWidget* MediaInterface::addTipologiaTrailer(){        //tipologia Trailer

        QWidget* TipoTrailer = new QWidget(this);

        QHBoxLayout* TrailerH = new QHBoxLayout;
        referenceTrailer = new SelectMediaReference("film",this);
        numeroProiezioniTrailer = new QSpinBox(this);

        TrailerH->addWidget(addSpin("Numero Proiezioni Giornaliere", 0, 20, 0, numeroProiezioniTrailer));
        TrailerH->addWidget(addReference("Film", referenceTrailer));
        TipoTrailer->setLayout(TrailerH);

        connect(referenceTrailer, &SelectMediaReference::mediaSelected, this, [this](MediaFrame* f){
            titoloFilmRiferimento = f->getTitolo();
            autoreFilmRiferimento = f->getAutore();
            checkMediaNameAvailability();
        });

        //style
        numeroProiezioniTrailer->setObjectName("numeroProiezioniTrailer");

        return TipoTrailer;
}


QWidget* MediaInterface::addTipologiaInserzione(){  //tipologia Inserzione

        QWidget* TipoInserzione = new QWidget(this);

        QHBoxLayout* inserzioneH1 = new QHBoxLayout;
        QHBoxLayout* inserzioneH2 = new QHBoxLayout;
        QVBoxLayout* inserzioneV1 = new QVBoxLayout;
        QVBoxLayout* inserzioneV2 = new QVBoxLayout;
        QWidget* WidgetInserzione1 = new QWidget(this);
        QWidget* WidgetInserzione2 = new QWidget(this);
        QWidget* WidgetInserzione3 = new QWidget(this);

        comboTargetInserzioni = new QComboBox(this);
        listFasceOrarie = new QListWidget(this);
        numeroProiezioniGioInserzione = new QSpinBox(this);
        costoBaseProiezInserzione = new QDoubleSpinBox(this);
        aziendaInserzInserzione = new QLineEdit(this);

        inserzioneV1->addWidget(addEnumList("Fasce Orarie", tutteLeFasceOrarie(), listFasceOrarie));
        inserzioneV1->addWidget(addEnumCombo("Target", tutteLeClassificazioni(), comboTargetInserzioni));
        WidgetInserzione1->setLayout(inserzioneV1);
        inserzioneH1->addWidget(WidgetInserzione1);
        inserzioneH2->addWidget(addSpin("Numero Proiezioni Giornaliere", 0, 20, 0, numeroProiezioniGioInserzione));
        inserzioneH2->addWidget(addDoubleSpin("Costo Base per Proieizone (€)", 30.0, 4000.0, 30.0, costoBaseProiezInserzione));
        inserzioneH2->addWidget(addLineEdit("Azienda Inserzionistica", aziendaInserzInserzione));

        WidgetInserzione2->setLayout(inserzioneH1);
        WidgetInserzione3->setLayout(inserzioneH2);
        inserzioneV2->addWidget(WidgetInserzione2);
        inserzioneV2->addWidget(WidgetInserzione3);
        TipoInserzione->setLayout(inserzioneV2);

        //style
        aziendaInserzInserzione->setObjectName("aziendaInserzInserzione");
        numeroProiezioniGioInserzione->setObjectName("numeroProiezioniGioInserzione");
        costoBaseProiezInserzione->setObjectName("costoBaseProiezInserzione");
        comboTargetInserzioni->setObjectName("comboTargetInserzioni");

        return TipoInserzione;
}

QWidget* MediaInterface::addTipologiaPodcast(){    //tipologia Podcast

        QWidget* TipoPodcast = new QWidget(this);
        conduttorePodcast = new QLineEdit(this);

        QHBoxLayout* podcastH = new QHBoxLayout;
        podcastH->addWidget(addLineEdit("Conduttore", conduttorePodcast));
        TipoPodcast->setLayout(podcastH);

        //style
        conduttorePodcast->setObjectName("conduttorePodcast");

        return TipoPodcast;
}

QWidget* MediaInterface::addTipologiaPuntate(){    //tipologia Puntata

        QWidget* TipoPuntata = new QWidget(this);

        QHBoxLayout* puntataH = new QHBoxLayout();
        QVBoxLayout* puntataV = new QVBoxLayout();
        QWidget* widgetPuntata = new QWidget(this);

        referencePuntate = new SelectMediaReference("podcast",this);
        ospitiPuntata = new ListPersone(this);
        numeroPubblicitaPuntata = new QSpinBox(this);

        puntataV->addWidget(addPersone("Ospiti",ospitiPuntata)); 
        puntataV->addWidget(addSpin("Numero Pubblicità", 0, 20, 4,numeroPubblicitaPuntata));
        widgetPuntata->setLayout(puntataV);

        puntataH->addWidget(widgetPuntata);
        puntataH->addWidget(addReference("Podcast",referencePuntate));

        TipoPuntata->setLayout(puntataH);

        connect(referencePuntate, &SelectMediaReference::mediaSelected, this, [this](MediaFrame* f){
            titoloPodcastRiferimento = f->getTitolo();
            autorePodcastRiferimento = f->getAutore();
            checkMediaNameAvailability();
        });

        //style
        numeroPubblicitaPuntata->setObjectName("numeroPubblicitaPuntata");

        return TipoPuntata;
}












QWidget* MediaInterface::addTabs(){
    QVBoxLayout* annullaSalvaLy = new QVBoxLayout;
    QWidget* WidgetTabAnnullaSalva = new QWidget(this);

    tab = new QTabWidget(this);
    
    QWidget* base = new QWidget(this);
    QWidget* descrizione = new QWidget(this);
    QWidget* tipologia = new QWidget(this);
    
    base->setLayout(addBase());
    descrizione->setLayout(addDescrizione());
    tipologia = (addTipologia());

    tab->addTab(base, "Informazioni Base");
    tab->addTab(descrizione, "Descrizione");
    tab->addTab(tipologia, "Specifiche Tipologia");

    annullaSalvaLy->addWidget(tab);
    annullaSalvaLy->addWidget(annullaSalva());
    WidgetTabAnnullaSalva->setLayout(annullaSalvaLy);
    
    //style
    base->setContentsMargins(20,50,20,100);
    descrizione->setContentsMargins(20,50,20,50);
    descrizione->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    descrizione->setMaximumHeight(650);
    tipologia->setContentsMargins(20,50,20,50);
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
    return WidgetTabAnnullaSalva;
}
















//creazione della pagina MediaInterface

QWidget* MediaInterface::addPagina(){
    QVBoxLayout* paginaV1 = new QVBoxLayout();
    QVBoxLayout* paginaV2 = new QVBoxLayout();
    QVBoxLayout* paginaV3 = new QVBoxLayout();
    QHBoxLayout* paginaH = new QHBoxLayout();
    QWidget* widgetPagina1 = new QWidget(this);
    QWidget* widgetPagina2 = new QWidget(this);
    QWidget* widgetPagina3 = new QWidget(this);
    QWidget* widgetPagina4 = new QWidget(this);

    titolo = new QLabel(this);
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
    paginaH->addWidget(addTabs());
    widgetPagina3->setLayout(paginaH);
    paginaV3->addWidget(titolo);
    paginaV3->addWidget(widgetPagina3);
    widgetPagina4->setLayout(paginaV3);
    
    connect(framePath,&InsertImageFrame::clicked,this,&MediaInterface::chooseImage);
    connect(framePath, &InsertImageFrame::removeImage, this, &MediaInterface::removeImage);
    
    //style
    widgetPagina2->setContentsMargins(0,14,30,67);
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

    return widgetPagina4;
}


QVBoxLayout* MediaInterface::addBase(){
    QVBoxLayout* baseV1 = new QVBoxLayout;
    QVBoxLayout* baseV2 = new QVBoxLayout;
    QHBoxLayout* baseH1 = new QHBoxLayout;
    QHBoxLayout* baseH2 = new QHBoxLayout;
    QWidget* widget1 = new QWidget(this);
    QWidget* widget2 = new QWidget(this);
    QWidget* widget3 = new QWidget(this);

    //Messaggio di errore
    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color: red; font-size: 12pt;");
    errorLabel->setText("");
    errorLabel->setVisible(false);
    errorLabel->setAlignment(Qt::AlignCenter);

    titoloMedia = new QLineEdit(this);
    autoreMedia = new QLineEdit(this);
    durataMinutiMedia = new QSpinBox(this);
    listLingue = new QListWidget(this);
    listSottotitoli = new QListWidget(this);
    dataInizio = new QDateEdit(this);
    dataFine = new QDateEdit(this);
    
    baseH1->addWidget(addLineEdit("Titolo*", titoloMedia));
    baseH1->addWidget(addLineEdit("Autore*", autoreMedia));
    baseH1->addWidget(addTipologiaCombo());
    widget1->setLayout(baseH1);
    
    baseH2->addWidget(addSpin("Durata (min)",0,500,0,durataMinutiMedia));
    baseH2->addWidget(addEnumList("Lingue", tutteLeLingue(), listLingue));
    baseH2->addWidget(addEnumList("Sottotitoli", tutteLeLingue(), listSottotitoli));
    baseV1->addWidget(addDataInizioRilascio(dataInizio));
    baseV1->addWidget(addDataFineRilascio(dataFine));
    widget2->setLayout(baseV1);
    baseH2->addWidget(widget2);
    widget3->setLayout(baseH2);
    
    baseV2->addWidget(widget1);
    baseV2->addWidget(errorLabel);
    baseV2->addWidget(widget3);

    connect(titoloMedia, &QLineEdit::textChanged, this, &MediaInterface::checkMediaNameAvailability);
    connect(autoreMedia, &QLineEdit::textChanged, this, &MediaInterface::checkMediaNameAvailability);

    //style
    titoloMedia->setObjectName("titoloMedia");
    autoreMedia->setObjectName("autoreMedia");
    durataMinutiMedia->setObjectName("durataMinutiMedia");
    dataInizio->setObjectName("dataInizio");
    dataFine->setObjectName("dataFine");
    baseV1->setAlignment(Qt::AlignTop);

    return baseV2;
}

QHBoxLayout* MediaInterface::addDescrizione(){
    QVBoxLayout* descrizioneV = new QVBoxLayout;
    QHBoxLayout* descrizioneH = new QHBoxLayout;
    QWidget* widget = new QWidget(this);

    comboRisoluzione = new QComboBox(this);
    comboFormato = new QComboBox(this);
    descrizioneMedia = new QTextEdit(this);

    descrizioneV->addWidget(addEnumCombo("Formato", tuttiIFormati(), comboFormato));
    descrizioneV->addWidget(addEnumCombo("Risoluzione", tutteLeRisoluzioni(), comboRisoluzione));
    widget->setLayout(descrizioneV);
    descrizioneH->addWidget(widget);
    descrizioneH->addWidget(addDescrizioneWidget(descrizioneMedia));

    //style
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

    return descrizioneH;
}

QWidget* MediaInterface::addTipologia(){
    QWidget* container = new QWidget(this);
    stackTipologia = new QStackedLayout(this);

    stackTipologia->addWidget(addTipologiaFilm());
    stackTipologia->addWidget(addTipologiaTrailer());
    stackTipologia->addWidget(addTipologiaPodcast());
    stackTipologia->addWidget(addTipologiaPuntate());
    stackTipologia->addWidget(addTipologiaInserzione());

    stackTipologia->setCurrentIndex(0);
    container->setLayout(stackTipologia);
    //style

    return container;
}











//pulsanti
QWidget* MediaInterface::pulsanteIndietro(){        //pulsante indietro
    QHBoxLayout* bottone = new QHBoxLayout;
    indietro = new QPushButton("← indietro",this);
    QWidget* indietroW = new QWidget(this);
    bottone->addWidget(indietro);
    bottone->setAlignment(Qt::AlignLeft);
    indietroW->setLayout(bottone);

    indietro->setCursor(Qt::PointingHandCursor);

    //style
    indietro->setObjectName("indietro");

    return indietroW;
}

QWidget* MediaInterface::annullaSalva(){
    cancelButton = new QPushButton("annulla",this);
    saveButton = new QPushButton("salva",this);
    QWidget* asWidget = new QWidget(this);
    QHBoxLayout* asH = new QHBoxLayout;
    asH->addSpacing(600);
    asH->addWidget(cancelButton);
    asH->addWidget(saveButton);
    asWidget->setLayout(asH);

    saveButton->setEnabled(false);

    //style
    cancelButton->setCursor(Qt::PointingHandCursor);
    saveButton->setCursor(Qt::PointingHandCursor);
    cancelButton->setObjectName("cancelButton");
    saveButton->setObjectName("saveButton");

    return asWidget;
}











//slots
void MediaInterface::chooseImage(){
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

void MediaInterface::removeImage(){
    QPixmap pixmap(":/images/default.png"); 
    copertina->setPixmap(pixmap.scaled(280,330, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imagePath.clear();
}









//HELPER PER CREATE MEDIA

// CONVERTE LA DATA IN CHRONO //
// conversione QDate -> std::chrono::year_month_day
year_month_day MediaInterface::convertDate(const QDate& data){
    year_month_day dataConvertita{
        year{data.year()},
        month{static_cast<unsigned>(data.month())},
        day{static_cast<unsigned>(data.day())}
    };
    return dataConvertita;
}

void MediaInterface::addFasceOrarie(Inserzione* inserzione){
    for (const std::string& f : getSelectedList(listFasceOrarie)) {
        inserzione->aggiungiFasciaOraria(toFasciaOraria(f));
    }
}

void MediaInterface::addLingue(Media* media){
    for (const std::string& l : getSelectedList(listLingue)) {
        media->aggiungiLingua(toLingua(l));
    }
}

void MediaInterface::addSottotitoli(Media* media){
    for (const std::string& s : getSelectedList(listSottotitoli)) {
        media->aggiungiSottotitolo(toLingua(s));
    }
}

void MediaInterface::addGeneri(Film* film){
    for (const std::string& g : getSelectedList(listGeneri)) {
        film->aggiungiGenere(toGenere(g));
    }
}

void MediaInterface::addAttore(Film* film){
    for (const QString& a : attoriFilm->getListaPersone()) {
        film->aggiungiAttore(a.toStdString());
    }
}

void MediaInterface::addOspite(Puntata* puntata){
    for (const QString& o : ospitiPuntata->getListaPersone()) {
        puntata->aggiungiOspite(o.toStdString());
    }
}

Media* MediaInterface::findMediaReference(const QString& titolo, const QString& autore, const QString& tipo){
    for(Media* m : im_mediaList){
        if(QString::fromStdString(m->getAutore()) == autore && QString::fromStdString(m->getTitolo()) == titolo)
            if( (tipo =="trailer" && dynamic_cast<Film*>(m) ) || (tipo == "puntata" && dynamic_cast<Podcast*>(m)))
                return m;
    }
    return nullptr; //non ha trovato niente
}