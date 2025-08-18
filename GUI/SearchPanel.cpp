#include "SearchPanel.h"
#include "AddMedia.h"

void SearchPanel::addMenus(QVBoxLayout* mainLayout){
    QMenuBar* menuBar = new QMenuBar(this);
    menuBar->setContentsMargins(0, 0, 0, 0); 
    
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
}

void SearchPanel::updateModifierPanel(int index){
    previousIndex=stackModifiche->currentIndex();
    stackModifiche->setCurrentIndex(index);
}

void SearchPanel::addLatoSinistra(QWidget* widgetSinistra){
    //agginta ricerca latoSinistra
    QVBoxLayout* latoSinistra = new QVBoxLayout;
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
    
    //pannello latoSinistra completo
    latoSinistra->addSpacing(100);
    latoSinistra->addWidget(addMedia);
    latoSinistra->addSpacing(50);
    latoSinistra->addWidget(widegetMedia);
    latoSinistra->addWidget(cinema);
    widgetSinistra->setLayout(latoSinistra);
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
    barraCerca->setContentsMargins(50, 10, 100, 0);
    barraCerca->addWidget(invioCerca);
    
    
    //barra dei filtri
    QComboBox* attivita = new QComboBox;
    QComboBox* popolarita = new QComboBox;
    QComboBox* recenti = new QComboBox;
    QWidget* widgetDestra = new QWidget;
    
    attivita->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    popolarita->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    recenti->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    
    QPushButton* filtri = new QPushButton("icona Filtri");
    QPushButton* vista = new QPushButton("icona vista");
    
    filtri->setObjectName("filtri");
    vista->setObjectName("vista");
    
    filtri->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    vista->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    
    barraFiltri->addWidget(attivita,3);
    barraFiltri->addSpacing(10);
    barraFiltri->addWidget(popolarita,3);
    barraFiltri->addSpacing(10);
    barraFiltri->addWidget(recenti,3);
    barraFiltri->addSpacing(10);
    barraFiltri->addWidget(filtri,1);
    barraFiltri->setContentsMargins(50, 10, 50, 0);
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

    //pannello di aggiunta media
    AddMedia* nuovoMedia = new AddMedia(this);
    stackModifiche->addWidget(nuovoMedia);
    nuovoMedia->setObjectName("nuovoMedia");

    connect(addMedia, &QPushButton::clicked, this, [this](){updateModifierPanel(1);});
    connect(nuovoMedia, &AddMedia::tornaIndietro, this, [this](){
        updateModifierPanel(previousIndex);
    });
}

void SearchPanel::updateCerca(const QString& filtro){
    cerca->setPlaceholderText("Cerca in "+filtro+"...");
}

void SearchPanel::addRicerca(QVBoxLayout* mainLayout){
    QWidget* widgetSinistra = new QWidget;
    stackModifiche = new QStackedWidget;

    widgetSinistra->setObjectName("latoSinistraSP");
    stackModifiche->setObjectName("stackModifiche");
    
    QHBoxLayout* ricerca = new QHBoxLayout;
    ricerca->setContentsMargins(0, 0, 0, 0); 
    ricerca->setSpacing(0);

    addLatoSinistra(widgetSinistra); 
    addLatoDestra(stackModifiche); 
    
    ricerca->addWidget(widgetSinistra,2);
    ricerca->addWidget(stackModifiche,8);
    mainLayout->addLayout(ricerca);
} 

SearchPanel::SearchPanel(QWidget *parent): QWidget(parent){
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0); 
    mainLayout->setSpacing(0);

    addMenus(mainLayout);
    addRicerca(mainLayout);
    
    setLayout(mainLayout);
}