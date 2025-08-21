#include "SearchPanel.h"
#include "InsertMedia.h"

void SearchPanel::addMenus(QVBoxLayout* mainLayout){
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
    file->addAction(new QAction("Esci Senza Salvare", file));
    
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
    connect(file->actions()[5],&QAction::triggered, this, [this](){emit escSearchPanel();});
    connect(file->actions()[6], &QAction::triggered, qApp, &QApplication::quit);
    
    mainLayout->addWidget(menuBar);
    
    //style
    menuBar->setContentsMargins(0, 0, 0, 0); 
}

void SearchPanel::updateModifierPanel(int index){
    if(stackModifiche->currentIndex()!=index){
        previousIndex = stackModifiche->currentIndex();
        stackModifiche->setCurrentIndex(index);
    } 
}

void SearchPanel::addLatoFiltri(QWidget* widgetSinistra){
    //agginta ricerca LatoFiltri
    QVBoxLayout* latoFiltri = new QVBoxLayout;
    QVBoxLayout* selezioneMedia = new QVBoxLayout;
    QWidget* widegetMedia = new QWidget;

    widegetMedia->setObjectName("widegetMedia");
    
    //selezione Cinema
    QPushButton* cinema = new QPushButton("Cinema nome");
    cinema->setObjectName("cinema");
    
    //selezione Media
    tutto = new QPushButton("Tutto");
    film = new QPushButton("Film");
    trailer = new QPushButton("Trailer");
    inserzione = new QPushButton("Inserzione");
    podcast = new QPushButton("Podcast");
    selezioneMedia->addWidget(tutto);
    selezioneMedia->addWidget(film);
    selezioneMedia->addWidget(trailer);
    selezioneMedia->addWidget(inserzione);
    selezioneMedia->addWidget(podcast);
    widegetMedia->setLayout(selezioneMedia);
    
    //aggiungi Media
    addMedia = new QPushButton("+ Aggiungi");
    addMedia->setObjectName("addMedia");
    
    //pannello latoFiltri completo
    latoFiltri->addSpacing(100);
    latoFiltri->addWidget(addMedia);
    latoFiltri->addSpacing(50);
    latoFiltri->addWidget(widegetMedia);
    latoFiltri->addWidget(cinema);
    widgetSinistra->setLayout(latoFiltri);

    //style
    cinema->setCursor(Qt::PointingHandCursor);
    addMedia->setCursor(Qt::PointingHandCursor);
    tutto->setCursor(Qt::PointingHandCursor);
    film->setCursor(Qt::PointingHandCursor);
    trailer->setCursor(Qt::PointingHandCursor);
    inserzione->setCursor(Qt::PointingHandCursor);
    podcast->setCursor(Qt::PointingHandCursor);
}

void SearchPanel::addLatoDestra(QStackedWidget* stackModifiche){
    //aggiunta ricerca superiore
    QVBoxLayout* latoDestra = new QVBoxLayout;
    QHBoxLayout* barraCerca = new QHBoxLayout;
    QHBoxLayout* barraFiltri = new QHBoxLayout;
    
    //barra di ricerca
    cerca = new QLineEdit;
    cerca->setPlaceholderText("Cerca in Tutto...");
    QPushButton* invioCerca = new QPushButton("icona cerca");
    invioCerca->setObjectName("invioCerca");
    barraCerca->addWidget(cerca);
    barraCerca->addWidget(invioCerca);
    
    //barra dei filtri
    QComboBox* attivita = new QComboBox;
    QComboBox* popolarita = new QComboBox;
    QComboBox* recenti = new QComboBox;
    QWidget* widgetDestra = new QWidget;
    
    QPushButton* filtri = new QPushButton("icona Filtri");
    QPushButton* vista = new QPushButton("icona vista");
    
    filtri->setObjectName("filtri");
    vista->setObjectName("vista");
    
    barraFiltri->addWidget(attivita,3);
    barraFiltri->addSpacing(10);
    barraFiltri->addWidget(popolarita,3);
    barraFiltri->addSpacing(10);
    barraFiltri->addWidget(recenti,3);
    barraFiltri->addSpacing(10);
    barraFiltri->addWidget(filtri,1);
    barraFiltri->addWidget(vista,1,Qt::AlignRight);
    
    stackLibreria = new QStackedWidget;
    
    connect(tutto, &QPushButton::clicked, this, [this](){SearchPanel::updateCerca("Tutto");}); //uso una lambda per passare la stringa "Tutto" poiché non è possibile chiamare la funzione
    connect(film, &QPushButton::clicked, this, [this](){SearchPanel::updateCerca("Film");});
    connect(trailer, &QPushButton::clicked, this, [this](){SearchPanel::updateCerca("Trailer");});
    connect(inserzione, &QPushButton::clicked, this, [this](){SearchPanel::updateCerca("Inserzioni");});
    connect(podcast, &QPushButton::clicked, this, [this](){SearchPanel::updateCerca("Podcast");});
    
    latoDestra->addLayout(barraCerca,2);
    latoDestra->addLayout(barraFiltri,1);
    latoDestra->addWidget(stackLibreria,5);
    widgetDestra->setLayout(latoDestra);
    
    stackModifiche->addWidget(widgetDestra);
    
    //pannello per la libreria
    stackModifiche->setCurrentIndex(0);
    previousIndex=0;
    
    //pannello di aggiunta media
    InsertMedia* nuovoMedia = new InsertMedia(this);
    stackModifiche->addWidget(nuovoMedia);
    nuovoMedia->setObjectName("nuovoMedia");
    
    connect(addMedia, &QPushButton::clicked, this, [this](){updateModifierPanel(1);});
    connect(nuovoMedia, &InsertMedia::tornaIndietro, this, [this](){
        updateModifierPanel(previousIndex);
    });
    connect(nuovoMedia, &InsertMedia::tornaAllaLibreria, this, [this](){
        updateModifierPanel(0);
    });
    
    //style
    attivita->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    popolarita->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    recenti->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    filtri->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    vista->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    barraCerca->setContentsMargins(50, 10, 100, 0);
    barraFiltri->setContentsMargins(50, 10, 50, 0);
    invioCerca->setCursor(Qt::PointingHandCursor);
    filtri->setCursor(Qt::PointingHandCursor);
    vista->setCursor(Qt::PointingHandCursor);
}


void SearchPanel::updateCerca(const QString& filtro){
    cerca->setPlaceholderText("Cerca in "+filtro+"...");
}

void SearchPanel::addPagina(QVBoxLayout* mainLayout){
    QWidget* widgetFiltri = new QWidget;
    stackModifiche = new QStackedWidget;

    
    QHBoxLayout* ricerca = new QHBoxLayout;
    
    addLatoFiltri(widgetFiltri); 
    addLatoDestra(stackModifiche); 
    
    ricerca->addWidget(widgetFiltri,2);
    ricerca->addWidget(stackModifiche,8);
    mainLayout->addLayout(ricerca);
    
    //style
    widgetFiltri->setObjectName("latoSinistraSP");
    stackModifiche->setObjectName("stackModifiche");
    ricerca->setSpacing(0);
    ricerca->setContentsMargins(0, 0, 0, 0); 
    widgetFiltri->setMinimumWidth(200);
    widgetFiltri->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    stackModifiche->setMinimumWidth(800);
    stackModifiche->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

} 

SearchPanel::SearchPanel(QWidget *parent): QWidget(parent){
    QVBoxLayout* mainLayout = new QVBoxLayout;
    
    addMenus(mainLayout);
    addPagina(mainLayout);
    
    setLayout(mainLayout);
    
    //style
    mainLayout->setContentsMargins(0, 0, 0, 0); 
    mainLayout->setSpacing(0);
}