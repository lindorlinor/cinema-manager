#include "SearchPanel.h"

void SearchPanel::addMenus(QVBoxLayout* mainLayout){
    QMenuBar* menuBar = new QMenuBar(this);
    
    file = new QMenu("File", menuBar);
    modifica = new QMenu("Modifica", menuBar);
    visualizza = new QMenu("Visualizza", menuBar);
    altro = new QMenu("Altro", menuBar);
    
    menuBar->addMenu(file);
    menuBar->addMenu(modifica);
    menuBar->addMenu(visualizza);
    menuBar->addMenu(altro);
    
    //Menu "File"
    file->addAction(new QAction("Esci Senza Salvare", file));
    file->addAction(new QAction("Importa Media", file));
    file->addAction(new QAction("Aggiungi Media", file));
    file->addAction(new QAction("Esporta Sessione Media", file));
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
    
    connect(file->actions()[0], &QAction::triggered, qApp, &QApplication::quit);
    
    mainLayout->addWidget(menuBar);
}

void SearchPanel::addLatoSinistra(QHBoxLayout* ricerca){
    //agginta ricerca latoSinistra
    QVBoxLayout* latoSinistra = new QVBoxLayout;
    QHBoxLayout* selezioneCinema = new QHBoxLayout;
    QVBoxLayout* selezioneMedia = new QVBoxLayout;
    
    //selezione Cinema
    addCinema = new QPushButton("+");
    addCinema->setObjectName("addCinema");
    cinema = new QComboBox;
    cinema->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    selezioneCinema->addWidget(cinema,4);
    selezioneCinema->addWidget(addCinema,1);
    
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
    
    //aggiungi Media
    addMedia = new QPushButton("+ Aggiungi");
    addMedia->setObjectName("addMedia");
    
    //pannello latoSinistra completo
    latoSinistra->addWidget(addMedia);
    latoSinistra->addLayout(selezioneMedia);
    latoSinistra->addLayout(selezioneCinema);
    ricerca->addLayout(latoSinistra,2);
}

void SearchPanel::addLatoDestra(QHBoxLayout* ricerca){
    //aggiunta ricerca superiore
    QVBoxLayout* latoDestra = new QVBoxLayout;
    QHBoxLayout* barraCerca = new QHBoxLayout;
    QHBoxLayout* barraFiltri = new QHBoxLayout;
    
    //barra di ricerca
    cerca = new QLineEdit;
    cerca->setPlaceholderText("Cerca in Tutto...");
    invioCerca = new QPushButton("icona cerca");
    invioCerca->setObjectName("invioCerca");
    barraCerca->addWidget(cerca);
    barraCerca->addWidget(invioCerca);
    
    //barra dei filtri
    attivita = new QComboBox;
    popolarita = new QComboBox;
    recenti = new QComboBox;

    attivita->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    popolarita->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    recenti->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    
    filtri = new QPushButton("icona Filtri");
    vista = new QPushButton("icona vista");

    filtri->setObjectName("filtri");
    vista->setObjectName("vista");
    
    filtri->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    vista->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    barraFiltri->addWidget(attivita,3);
    barraFiltri->addWidget(popolarita,3);
    barraFiltri->addWidget(recenti,3);
    barraFiltri->addWidget(filtri,1);
    barraFiltri->addSpacing(100);
    barraFiltri->addWidget(vista,1);
    
    stack = new QStackedWidget;

    connect(tutto, &QPushButton::clicked, this, [this](){SearchPanel::updateCerca("Tutto");}); //uso una lambda per passare la stringa "Tutto" poiché non è possibile chiamare la funzione
    connect(film, &QPushButton::clicked, this, [this](){SearchPanel::updateCerca("Film");});
    connect(trailer, &QPushButton::clicked, this, [this](){SearchPanel::updateCerca("Trailer");});
    connect(inserzione, &QPushButton::clicked, this, [this](){SearchPanel::updateCerca("Inserzioni");});
    connect(podcast, &QPushButton::clicked, this, [this](){SearchPanel::updateCerca("Podcast");});
    
    latoDestra->addLayout(barraCerca,2);
    latoDestra->addLayout(barraFiltri,1);
    latoDestra->addWidget(stack,5);

    ricerca->addLayout(latoDestra,6);
}

void SearchPanel::updateCerca(const QString& filtro){
    cerca->setPlaceholderText("Cerca in "+filtro+"...");
}

void SearchPanel::addRicerca(QVBoxLayout* mainLayout){
    QHBoxLayout* ricerca = new QHBoxLayout;
    addLatoSinistra(ricerca); 
    addLatoDestra(ricerca); 
    mainLayout->addLayout(ricerca);
} 

SearchPanel::SearchPanel(QWidget *parent): QWidget(parent){
    QVBoxLayout* mainLayout = new QVBoxLayout;

    addMenus(mainLayout);
    addRicerca(mainLayout);
    
    setLayout(mainLayout);
}