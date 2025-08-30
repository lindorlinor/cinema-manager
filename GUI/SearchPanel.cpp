#include "SearchPanel.h"
#include "FilmView.h"
#include "TrailerView.h"
#include "DetailPageVisitor.h"
#include "LibraryObserver.h"

void SearchPanel::addMenus(QVBoxLayout* mainLayout){

    //gestione del json
    manager = new MediaManagerJson(mediaList, QDir(QCoreApplication::applicationDirPath()).filePath("../Json_XML"),this);
    xmlManager = new MediaManagerXml();

    QMenuBar* menuBar = new QMenuBar(this);
    
    QMenu* file = new QMenu("File", menuBar);
    QMenu* modifica = new QMenu("Modifica", menuBar);
    QMenu* visualizza = new QMenu("Visualizza", menuBar);
    QMenu* altro = new QMenu("Altro", menuBar);
    
    menuBar->addMenu(file);
    menuBar->addMenu(modifica);
    menuBar->addMenu(visualizza);
    menuBar->addMenu(altro);
    
    //Menu "File"
    file->addAction(new QAction("Aggiungi Media", file));
    file->addAction(new QAction("Importa Media", file));
    file->addAction(new QAction("Esporta Media", file));
    file->addAction(new QAction("Importa Sessione", file));
    file->addAction(new QAction("Esporta Sessione", file));
    file->addAction(new QAction("Torna a seleziona Cinema", file));
    file->addAction(new QAction("Esci", file));
    
    //Menu "Modifica"
    modifica->addAction(new QAction("Modifica Media", modifica));
    modifica->addAction(new QAction("Rimuovi Media", modifica));
    //Menu "Visualizza"
    visualizza->addAction(new QAction("Visualizza Film", visualizza));
    visualizza->addAction(new QAction("Visualizza Trailer", visualizza));
    visualizza->addAction(new QAction("Visualizza Inserzioni", visualizza));
    visualizza->addAction(new QAction("Visualizza Podcast", visualizza));
    //Menu "Altro"
    altro->addAction(new QAction("Cambia Vista", altro));
    altro->addAction(new QAction("Full Screen", altro));
    altro->addAction(new QAction("Exit Full Screen", altro));
    connect(file->actions()[5],&QAction::triggered, this, [this](){ emit escSearchPanel(); 
                                                                    if(stackModifiche->currentIndex()==1) emit resetPages();
                                                                    stackModifiche->setCurrentIndex(0);
                                                                    manager->removeAll();
                                                                    preUpdate();});
    connect(file->actions()[6], &QAction::triggered, qApp, &QApplication::quit);
    connect(altro->actions()[1], &QAction::triggered, this, &SearchPanel::setFullScreen);
    connect(altro->actions()[2], &QAction::triggered, this, &SearchPanel::escFullScreen);

    metodoTemporaneoPerPagineDiVisualizzazione();
    connect(file->actions()[4], &QAction::triggered, this,
        [this](){
            xmlManager->setCinemaName("Cinema Aurora");
            xmlManager->setCinemaCover(":/images/default.png");
            xmlManager->setCinemaMediaList(mediaList);
            xmlManager->exportSessionToXml();
            // manager.exportMediaListToXml();
        });
    connect(file->actions()[3], &QAction::triggered, this,
        [this](){
            xmlManager->setCinemaName("Cinema Aurora");
            xmlManager->setCinemaCover(":/images/default.png");
            xmlManager->setCinemaMediaList(mediaList);
            xmlManager->importSessionFromXml(*manager);
            // manager.importMediaListFromXml(jsonManager);
        });
    mainLayout->addWidget(menuBar);
    
    //style
    menuBar->setContentsMargins(0, 0, 0, 0); 
    menuBar->setObjectName("menuBar");
    file->setObjectName("file");
    modifica->setObjectName("modifica");
    visualizza->setObjectName("visualizza");
    altro->setObjectName("altro");
}

void SearchPanel::updateModifierPanel(int index){
    if(stackModifiche->currentIndex()!=index){
        previousIndex = stackModifiche->currentIndex();
        stackModifiche->setCurrentIndex(index);
    } 
}

void SearchPanel::addLatoFiltri(QWidget* widgetFiltri){
    //agginta ricerca LatoFiltri
    QVBoxLayout* latoFiltri = new QVBoxLayout;
    QVBoxLayout* selezioneMedia = new QVBoxLayout;
    QWidget* widegetMedia = new QWidget(this);
    
    //selezione Media
    tutto = new QToolButton(this);
    film = new QToolButton(this);
    trailer = new QToolButton(this);
    inserzione = new QToolButton(this);
    podcast = new QToolButton(this);
    puntata = new QToolButton(this);
    tutto->setText("Tutto");
    film->setText("Film");
    trailer->setText("Trailer");
    inserzione->setText("Inserzioni");
    podcast->setText("Podcast");
    puntata->setText("Puntate");
    
    selezioneMedia->addWidget(tutto);
    selezioneMedia->addWidget(film);
    selezioneMedia->addWidget(trailer);
    selezioneMedia->addWidget(inserzione);
    selezioneMedia->addWidget(podcast);
    selezioneMedia->addWidget(puntata);
    widegetMedia->setLayout(selezioneMedia);
    
    //aggiungi Media
    addMedia = new QPushButton("+ Aggiungi",this);
    
    //aggiungi pulsante cinema
    cinema = new QToolButton(this);
    
    //pannello latoFiltri completo
    latoFiltri->addSpacing(60);
    latoFiltri->addWidget(addMedia);
    latoFiltri->addSpacing(60);
    latoFiltri->addWidget(widegetMedia);
    latoFiltri->addSpacing(370);
    latoFiltri->addWidget(cinema);
    widgetFiltri->setLayout(latoFiltri);
    

    connect(cinema, &QToolButton::clicked, this, [this](){ emit escSearchPanel(); 
                                                                    if(stackModifiche->currentIndex()==1) emit resetPages();
                                                                    stackModifiche->setCurrentIndex(0);
                                                                    manager->removeAll();
                                                                    preUpdate();});

    //style

    addMedia->setObjectName("addMedia");
    widegetMedia->setObjectName("widegetMedia");
    cinema->setObjectName("cinema");
    tutto->setObjectName("tutto");
    film->setObjectName("film");
    trailer->setObjectName("trailer");
    inserzione->setObjectName("inserzione");
    podcast->setObjectName("podcast");
    puntata->setObjectName("puntata");
    cinema->setCursor(Qt::PointingHandCursor);
    addMedia->setCursor(Qt::PointingHandCursor);
    tutto->setCursor(Qt::PointingHandCursor);
    film->setCursor(Qt::PointingHandCursor);
    trailer->setCursor(Qt::PointingHandCursor);
    inserzione->setCursor(Qt::PointingHandCursor);
    podcast->setCursor(Qt::PointingHandCursor);
    puntata->setCursor(Qt::PointingHandCursor);
    tutto->setCheckable(true);
    film->setCheckable(true);
    trailer->setCheckable(true);
    inserzione->setCheckable(true);
    podcast->setCheckable(true);
    puntata->setCheckable(true);
    tutto->setChecked(true);
    
    //set icone
    QIcon iconaCinema(":/icons/exit.png");
    QIcon iconaFilm(":/icons/Film.png");
    QIcon iconaTrailer(":/icons/trailer.png");
    QIcon iconaPodcast(":/icons/podcast.png");
    QIcon iconaPuntata(":/icons/puntata.png");
    QIcon iconaInserzione(":/icons/inserzione.png");
    QIcon iconaTutto(":/icons/tutto.png");
    cinema->setIcon(iconaCinema);
    film->setIcon(iconaFilm);
    trailer->setIcon(iconaTrailer);
    inserzione->setIcon(iconaInserzione);
    podcast->setIcon(iconaPodcast);
    puntata->setIcon(iconaPuntata);
    tutto->setIcon(iconaTutto);
    
    cinema->setIconSize(QSize(35,35));
    film->setIconSize(QSize(40,30));
    trailer->setIconSize(QSize(40,20));
    inserzione->setIconSize(QSize(40,30));
    podcast->setIconSize(QSize(40,30));
    puntata->setIconSize(QSize(40,30));
    tutto->setIconSize(QSize(40,30));
    cinema->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    film->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    trailer->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    inserzione->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    podcast->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    puntata->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    tutto->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
}

void SearchPanel::addLatoDestra(QStackedWidget* stackModifiche){
    //aggiunta ricerca superiore
    QVBoxLayout* latoDestra = new QVBoxLayout;
    QHBoxLayout* barraFiltri = new QHBoxLayout;
    QWidget* widgetSelezioneFiltri = new QWidget(this);
    
    //barra di ricerca
    cerca = new QLineEdit(this);
    cerca->setPlaceholderText("Cerca in Tutto...");
    
    //barra dei filtri
    attivita = new QComboBox(this);
    ordinamento = new QComboBox(this);
    QWidget* widgetDestra = new QWidget(this);
    
    QToolButton* filtri = new QToolButton(this);
    QToolButton* vista = new QToolButton(this);

    attivita->addItem("Attivi");
    attivita->addItem("Non Attivi");
    attivita->addItem("Tutti");
    ordinamento->addItem("Popolari");
    ordinamento->addItem("Non Popolari");
    ordinamento->addItem("Recenti");
    ordinamento->addItem("Meno Recenti");
    
    barraFiltri->addWidget(attivita);
    barraFiltri->addSpacing(10);
    barraFiltri->addWidget(ordinamento);
    barraFiltri->addSpacing(10);
    barraFiltri->addWidget(filtri);
    barraFiltri->addSpacing(750);
    barraFiltri->addWidget(vista,Qt::AlignRight);
    widgetSelezioneFiltri->setLayout(barraFiltri);
    
    stackLibreria = new QStackedWidget(this);
    
    latoDestra->addWidget(cerca);
    latoDestra->addWidget(widgetSelezioneFiltri);
    latoDestra->addWidget(stackLibreria);
    widgetDestra->setLayout(latoDestra);
    
    stackModifiche->addWidget(widgetDestra);
    
    
    //pannello per la libreria
    // stackModifiche->setCurrentIndex(0);
    previousIndex=0;
    
    
    //pannello di aggiunta media
    InsertMedia* nuovoMedia = new InsertMedia(manager, this);
    stackModifiche->addWidget(nuovoMedia);
    
    

    //pannello per la libreria dei media
/*     MediaLibraryTutto* libreriaMediaTutto = new MediaLibraryTutto(this); */
    MediaLibraryGenerale* libreriaMediaGenerale = new MediaLibraryGenerale(mediaList, film->objectName() ,this);

    this->addObserver(libreriaMediaGenerale);

/*     stackLibreria->addWidget(libreriaMediaTutto); */
    stackLibreria->addWidget(libreriaMediaGenerale);
    stackLibreria->setCurrentIndex(0);
    
    //GESTIONE PULSANTI
    connect(cerca, &QLineEdit::textChanged, this, [this](const QString &testo){ ricerca = testo; 
                                                                                for(auto o : libraryObservers) 
                                                                                    o->update(comboAttivita, comboOrdinamento, filtroBottone, ricerca);});
    connect(addMedia, &QPushButton::clicked, this, [this](){updateModifierPanel(1);});
/*     connect(tutto, &QToolButton::clicked, this, [this](){SearchPanel::updateCerca("Tutto"); stackLibreria->setCurrentIndex(0);}); */
    connect(film, &QToolButton::clicked, this, [this](){updateFiltroMedia("Film");});
    connect(trailer, &QToolButton::clicked, this, [this](){updateFiltroMedia("Trailer");});
    connect(inserzione, &QToolButton::clicked, this, [this](){updateFiltroMedia("Inserzione");});
    connect(podcast, &QToolButton::clicked, this, [this](){updateFiltroMedia("Podcast");});
    connect(puntata, &QToolButton::clicked, this, [this](){updateFiltroMedia("Puntata");});


    connect(this, &SearchPanel::giveCinemaInfoToIP, nuovoMedia, &InsertMedia::getCinemaInfo);
    connect(this, &SearchPanel::resetPages, nuovoMedia, &InsertMedia::resetAllInput);
    connect(nuovoMedia, &InsertMedia::tornaIndietro, this, [this](){
        updateModifierPanel(previousIndex);
    });
    connect(nuovoMedia, &InsertMedia::tornaAllaLibreria, this, [this](){
        updateModifierPanel(0);
    });

    
    
    //style
    attivita->setView(new QListView(attivita));
    attivita->view()->setFrameShape(QFrame::NoFrame);
    attivita->view()->setAttribute(Qt::WA_Hover, true);
    ordinamento->setView(new QListView(ordinamento));
    ordinamento->view()->setFrameShape(QFrame::NoFrame);
    ordinamento->view()->setAttribute(Qt::WA_Hover, true);

    filtri->setObjectName("filtri");
    vista->setObjectName("vista");
    cerca->setObjectName("cerca");
    attivita->setObjectName("attivita");
    ordinamento->setObjectName("ordinamento");
    attivita->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    ordinamento->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    filtri->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    vista->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    cerca->setContentsMargins(50, 10, 100, 0);
    barraFiltri->setContentsMargins(50, 10, 50, 0);
    filtri->setCursor(Qt::PointingHandCursor);
    vista->setCursor(Qt::PointingHandCursor);
    widgetSelezioneFiltri->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    //icone
    QIcon iconaVista(":/icons/vista.png");
    QIcon iconaFiltri(":/icons/filtri.png");
    vista->setIcon(iconaVista);
    filtri->setIcon(iconaFiltri);
    vista->setIconSize(QSize(40,40));
    filtri->setIconSize(QSize(35,35));
}


void SearchPanel::updateCerca(const QString& filtro){
    cerca->setPlaceholderText("Cerca in "+filtro+"...");

    tutto->setChecked(filtro == "Tutto");
    film->setChecked(filtro == "Film");
    trailer->setChecked(filtro == "Trailer");
    inserzione->setChecked(filtro == "Inserzioni");
    podcast->setChecked(filtro == "Podcast");
    puntata->setChecked(filtro == "Puntata");
}

void SearchPanel::addPagina(QVBoxLayout* mainLayout){
    QWidget* widgetFiltri = new QWidget(this);

    
    QHBoxLayout* ricerca = new QHBoxLayout;
    
    addLatoFiltri(widgetFiltri); 
    addLatoDestra(stackModifiche); 
    
    ricerca->addWidget(widgetFiltri);
    ricerca->addWidget(stackModifiche);
    mainLayout->addLayout(ricerca);

    connect(attivita, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index){ comboAttivita = index; preUpdate();});
    connect(ordinamento, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index){comboOrdinamento = index; preUpdate();});

    //style
    widgetFiltri->setObjectName("widgetFiltri");
    stackModifiche->setObjectName("stackModifiche");
    ricerca->setSpacing(0);
    ricerca->setContentsMargins(0, 0, 0, 0); 
    widgetFiltri->setMinimumWidth(200);
    widgetFiltri->setMaximumWidth(350);
    widgetFiltri->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    stackModifiche->setMinimumWidth(800);
    stackModifiche->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

} 

SearchPanel::SearchPanel(QWidget *parent): QWidget(parent),stackModifiche(new QStackedWidget(this)){
    QVBoxLayout* mainLayout = new QVBoxLayout;
    
    addMenus(mainLayout);
    addPagina(mainLayout);
    
    setLayout(mainLayout);
    
    //style
    mainLayout->setContentsMargins(0, 0, 0, 0); 
    mainLayout->setSpacing(0);
}

void SearchPanel::updateInfoCinema(const CinemaData& data){
    //selezione Cinema
    cinema->setText("Cinema "+data.nomeCinema);
    manager->setCinemaNome(data.nomeCinema);
    manager->loadAll();
    emit giveCinemaInfoToIP(data);
}

void SearchPanel::addObserver(LibraryObserver* obs){
    libraryObservers.push_back(obs);
}

void SearchPanel::update(int comboAttivita, int comboOrdinamento, const QString& filtroBottone, const QString& ricerca){
    for(auto obs : libraryObservers){
        obs->update(comboAttivita, comboOrdinamento, filtroBottone, ricerca);
    }
}

void SearchPanel::updateFiltroMedia(const QString& filtro){
    updateCerca(filtro);
    stackLibreria->setCurrentIndex(0);
    filtroBottone = filtro;
    preUpdate();
}

void SearchPanel::preUpdate(){
    for(auto o : libraryObservers)
        o->update(comboAttivita, comboOrdinamento, filtroBottone, ricerca);
}

void SearchPanel::metodoTemporaneoPerPagineDiVisualizzazione(){
    /*ROBA DA MODIFICARE, LA METTO QUI PER FARE LA PAGINA DI VISUALIZZAZIONE*/
    DetailPageVisitor* visitor = new DetailPageVisitor(); 

    

    Film* film = new Film(
                            "Il mio vicino Totoro (RE-RELEASE 2025)",
                            "La magica storia di due sorelle che si trasferiscono in campagna e incontrano le creature fantastiche del bosco",
                            year_month_day{2025y/June/1d},
                            year_month_day{2025y/June/30d},
                            86,
                            Formato::DCP,
                            Risoluzione::UHD_4K_2160p,
                            1,      
                            12.50,
                            "Studio Ghibli",
                            "Hayao Miyazaki",
                            ":/images/image9.png",
                            Classificazione::TUTTI
                        );
    film->aggiungiLingua(Lingua::Italiano);
    film->aggiungiLingua(Lingua::Inglese);
    film->aggiungiAttore("Noriko Hidaka");
    film->aggiungiAttore("Chika Sakamoto");
    film->aggiungiAttore("Shigesato Itoi");
    film->aggiungiAttore("Hitoshi Takagi");
    film->aggiungiAttore("Takashi Nagasako");

    film->aggiungiSottotitolo(Lingua::Italiano);
    film->IncrementaVisualizzazioni();
    film->setValutazione();
    // Primo trailer
    Trailer* trailer1 = new Trailer(
        "Trailer ufficiale - Il mio vicino Totoro (2025)",
        "Un assaggio del ritorno al cinema del capolavoro di Hayao Miyazaki.",
        year_month_day{2025y/April/15d},   // data inizio rilascio
        year_month_day{2025y/May/31d},     // data fine rilascio
        2,                                 // durata in minuti
        Formato::DCP,
        Risoluzione::UHD_4K_2160p,
        5,                                 // n° proiezioni giornaliere
        film,
        "Studio Ghibli",
        ":/images/image10.png"
    );
    trailer1->IncrementaVisualizzazioni();
    // Secondo trailer
    Trailer* trailer2 = new Trailer(
        "Trailer speciale anniversario - Il mio vicino Totoro (2025)",
        "Un trailer celebrativo con scene inedite per il ritorno del film in sala.",
        year_month_day{2025y/May/1d},      // data inizio rilascio
        year_month_day{2025y/June/15d},    // data fine rilascio
        3,                                 // durata in minuti
        Formato::DCP,
        Risoluzione::UHD_4K_2160p,
        3,                                 // n° proiezioni giornaliere
        film,
        "Hayao Miyazaki",
        ":/images/image10.png"
    );
    trailer2->IncrementaVisualizzazioni();

    mediaList.append(film);
    mediaList.append(trailer1);
    mediaList.append(trailer2);

    film->accept(visitor);
    QWidget * detailPage = visitor->getWidget();
    stackModifiche->addWidget(detailPage);
    stackModifiche->setCurrentIndex(2);

    connect(static_cast<FilmView*>(detailPage), &MediaView::returnButton, this, [this,detailPage](){
        updateModifierPanel(previousIndex);
        stackModifiche->removeWidget(detailPage);
        delete detailPage;
    });
    /* // 5 Film
    mediaList.push_back(new Film("2001: Odissea nello Spazio", "Avventura fantascientifica epica.",
                             year_month_day{2025y, June, 10d}, year_month_day{2025y, July, 5d},
                             140, Formato::DCP, Risoluzione::FullHD_1080p,
                             5, 9.1, "Cosmo Studios", "Stanley Nova"));
    mediaList.push_back(new Film("Il Segreto della Laguna", "Thriller ambientato in un villaggio italiano.",
                             year_month_day{2025y, August, 1d}, year_month_day{2025y, August, 20d},
                             110, Formato::IMAX_3D, Risoluzione::HD_720p,
                             3, 7.8, "Mediterranea Film", "Laura Rossi"));
    mediaList.push_back(new Film("Cuore di Acciaio", "Dramma su un robot che scopre l’umanità.",
                             year_month_day{2025y, September, 12d}, year_month_day{2025y, October, 2d},
                             125, Formato::DCP, Risoluzione::FullHD_1080p,
                             4, 8.6, "Future Pictures", "Kenji Yamato"));
    mediaList.push_back(new Film("Risveglio", "Un viaggio introspettivo tra sogno e realtà.",
                             year_month_day{2025y, March, 5d}, year_month_day{2025y, March, 25d},
                             98, Formato::DCP, Risoluzione::HD_720p,
                             2, 7.2, "Arthouse Films", "Marta Verdi"));
    mediaList.push_back(new Film("L’Ombra del Drago", "Fantasy epico con battaglie tra regni.",
                             year_month_day{2025y, November, 20d}, year_month_day{2025y, December, 20d},
                             160, Formato::IMAX_3D, Risoluzione::FullHD_1080p,
                             6, 8.9, "Dragon Studios", "Hao Zhang"));

    // 2 Inserzioni
    mediaList.push_back(new Inserzione("Promo Smartphone X15", "Campagna pubblicitaria nuovo modello X15.",
                                   year_month_day{2025y, May, 1d}, year_month_day{2025y, May, 30d},
                                   30, Formato::DCP, Risoluzione::HD_720p,
                                   20, Classificazione::TUTTI, 50.0, "TechCorp"));
    mediaList.push_back(new Inserzione("Bevanda Frizzante Zeta", "Spot per la nuova linea estiva.",
                                   year_month_day{2025y, June, 15d}, year_month_day{2025y, July, 15d},
                                   25, Formato::DCP, Risoluzione::FullHD_1080p,
                                   18, Classificazione::TUTTI, 35.0, "DrinkIt"));

    // 2 Podcast con 3 Puntate ciascuno
    Podcast* p1 = new Podcast("Storie dal Futuro", "Racconti di fantascienza e tecnologia.",
                              Formato::DCP, Risoluzione::FullHD_1080p);
    Puntata* p1_1 = new Puntata("Robot e Umanità", "Discussione su AI e coscienza.",
                                year_month_day{2025y, January, 10d}, year_month_day{2025y, January, 20d},
                                50, p1, 2);
    Puntata* p1_2 = new Puntata("Città del Domani", "Urbanistica futuristica.",
                                year_month_day{2025y, February, 5d}, year_month_day{2025y, February, 15d},
                                45, p1, 2);
    Puntata* p1_3 = new Puntata("Viaggi Interstellari", "Le sfide della colonizzazione spaziale.",
                                year_month_day{2025y, March, 1d}, year_month_day{2025y, March, 12d},
                                55, p1, 2);
    mediaList.push_back(p1);
    mediaList.push_back(p1_1);
    mediaList.push_back(p1_2);
    mediaList.push_back(p1_3);

    Podcast* p2 = new Podcast("Cronache Storiche", "Analisi di eventi e figure storiche.",
                              Formato::DCP, Risoluzione::HD_720p);
    Puntata* p2_1 = new Puntata("La Roma Antica", "La nascita dell’Impero.",
                                year_month_day{2025y, April, 1d}, year_month_day{2025y, April, 10d},
                                40, p2, 4);
    Puntata* p2_2 = new Puntata("Il Medioevo", "Un viaggio tra castelli e cavalieri.",
                                year_month_day{2025y, April, 20d}, year_month_day{2025y, April, 28d},
                                42, p2, 3);
    Puntata* p2_3 = new Puntata("La Rivoluzione Industriale", "Come è cambiato il mondo.",
                                year_month_day{2025y, May, 5d}, year_month_day{2025y, May, 15d},
                                48, p2, 1);
    mediaList.push_back(p2);
    mediaList.push_back(p2_1);
    mediaList.push_back(p2_2);
    mediaList.push_back(p2_3);
 */
   
}