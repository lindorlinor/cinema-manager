#include "SearchPanel.h"
#include "FilmView.h"
#include "TrailerView.h"
#include "DetailPageVisitor.h"
#include "LibraryObserver.h"
#include "InserzioneView.h"

SearchPanel::SearchPanel(CinemaRepositoryJson* s_jsonManager,MediaManagerXml* xmlManager,QWidget *parent):QWidget(parent), s_jsonManager(s_jsonManager),
                                                    s_xmlManager(xmlManager),stackModifiche(new QStackedWidget(this)){
    //carico tutti gli oggetti sal Json
    QVBoxLayout* mainLayout = new QVBoxLayout;

    addPagina(mainLayout);
    
    setLayout(mainLayout);
    
    //style
    mainLayout->setContentsMargins(0, 0, 0, 0); 
    mainLayout->setSpacing(0);
}

void SearchPanel::updateModifierPanel(int index){
    if(stackModifiche->currentIndex()!=index){
        if(previousIndex)
            previousIndex = stackModifiche->currentIndex();
        stackModifiche->setCurrentIndex(index);
    }
    if(index==2) emit setQMenuEnabled();
    else emit setQMenuDisabled();
}

void SearchPanel::showMediaView(MediaView& widget){
    if(auto inserzione = dynamic_cast<InserzioneView*>(&widget))
        inserzione->setMediaList(s_cinemaSelezionato->getListaMedia()); //per passargli il mediaList, dovevo scegliere tra un set oppure passarlo al visitor, mi semrbava meglio cosi

    stackModifiche->addWidget(&widget);
    stackModifiche->setCurrentWidget(&widget);

    connect(&widget, &MediaView::editMediaClicked, this, &SearchPanel::showEditPage);
    connect(&widget, &MediaView::returnButton, this, [this, &widget](){
        removeMediaView(&widget);
    });
    
    connect(&widget, &MediaView::extendMediaClicked, this, &SearchPanel::updateJson);
    connect(&widget, &MediaView::requestMediaView, this, &SearchPanel::showMediaView);
}

void SearchPanel::removeMediaView(QWidget* widget){
    int widgetIndex = stackModifiche->indexOf(widget);

    if(widgetIndex > 2)
        stackModifiche->setCurrentIndex(widgetIndex-1);
    else
        stackModifiche->setCurrentIndex(0);

    stackModifiche->removeWidget(widget);
    delete widget;
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
    

    connect(cinema, &QToolButton::clicked, this, [this](){
        deleteViewPages();
        emit escSearchPanel();
        s_xmlManager->setCurrentCinema(nullptr);
    });

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

void SearchPanel::addLatoDestra(){
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
    
    stackModifiche->addWidget(widgetDestra); // 0
    previousIndex=0;
    
    //pannello di aggiunta media
    InsertMedia* nuovoMedia = new InsertMedia(this);
    stackModifiche->addWidget(nuovoMedia); // 1
    
    

    //pannello per la libreria dei media
    libreriaMediaTutto = new MediaLibraryTutto(this);
    libreriaMediaGenerale = new MediaLibraryGenerale( "Film" ,this);

    this->addObserver(libreriaMediaGenerale);

    stackLibreria->addWidget(libreriaMediaTutto); //0
    stackLibreria->addWidget(libreriaMediaGenerale); //1
    stackLibreria->setCurrentIndex(0);
    
    //GESTIONE PULSANTI
    connect(cerca, &QLineEdit::textChanged, this, [this](const QString &testo){ ricerca = testo; 
                                                                                for(auto o : s_libraryObservers) 
                                                                                    o->update(comboAttivita, comboOrdinamento, filtroBottone, ricerca, s_MediaListOfCinema);});
    connect(addMedia, &QPushButton::clicked, this, [this](){
        deleteViewPages();
        updateModifierPanel(1);
    });
    connect(tutto, &QToolButton::clicked, this, &SearchPanel::updateFiltroTutto);
    connect(film, &QToolButton::clicked, this, [this](){updateFiltroMedia("Film");});
    connect(trailer, &QToolButton::clicked, this, [this](){updateFiltroMedia("Trailer");});
    connect(inserzione, &QToolButton::clicked, this, [this](){updateFiltroMedia("Inserzioni");});
    connect(podcast, &QToolButton::clicked, this, [this](){updateFiltroMedia("Podcast");});
    connect(puntata, &QToolButton::clicked, this, [this](){updateFiltroMedia("Puntate");});


    connect(this, &SearchPanel::giveCinemaInfoToIP, nuovoMedia, &InsertMedia::getCinemaInfo);
    connect(this, &SearchPanel::resetPages, nuovoMedia, &InsertMedia::resetAllInput);
    connect(nuovoMedia, &InsertMedia::tornaIndietro, this, [this](){
        updateModifierPanel(previousIndex);
    });
    connect(nuovoMedia, &InsertMedia::tornaAllaLibreria, this, [this](){
        updateModifierPanel(0);
        updateMediaList(); //to do
        updateFiltroTutto();
    });

    connect(libreriaMediaGenerale, &MediaLibraryGenerale::requestMediaView, this, &SearchPanel::showMediaView);
    connect(libreriaMediaTutto, &MediaLibraryTutto::requestMediaView, this, &SearchPanel::showMediaView);
    
    
    //style
    latoDestra->setContentsMargins(60,0,0,0);
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
    cerca->setContentsMargins(0, 10, 100, 0);
    barraFiltri->setContentsMargins(0, 10, 50, 0);
    filtri->setCursor(Qt::PointingHandCursor);
    vista->setCursor(Qt::PointingHandCursor);
    widgetSelezioneFiltri->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

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
    inserzione->setChecked(filtro == "Inserzione");
    podcast->setChecked(filtro == "Podcast");
    puntata->setChecked(filtro == "Puntata");
}

void SearchPanel::addPagina(QVBoxLayout* mainLayout){
    QWidget* widgetFiltri = new QWidget(this);

    
    QHBoxLayout* ricerca = new QHBoxLayout;
    
    addLatoFiltri(widgetFiltri); 
    addLatoDestra(); 
    
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
    widgetFiltri->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    stackModifiche->setMinimumWidth(800);
    stackModifiche->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

} 


void SearchPanel::addObserver(LibraryObserver* obs){
    s_libraryObservers.push_back(obs);
}

void SearchPanel::update(int comboAttivita, int comboOrdinamento, const QString& filtroBottone, const QString& ricerca){
    for(auto obs : s_libraryObservers){
        obs->update(comboAttivita, comboOrdinamento, filtroBottone, ricerca, s_MediaListOfCinema);
    }
}

void SearchPanel::updateFiltroMedia(const QString& filtro){
    updateCerca(filtro);
    stackLibreria->setCurrentIndex(1);
    filtroBottone = filtro;
    preUpdate();
}

void SearchPanel::updateFiltroTutto(){
    updateCerca("Tutto"); 
    stackLibreria->setCurrentIndex(0); 
    libreriaMediaTutto->update(comboAttivita, comboOrdinamento, ricerca, s_MediaListOfCinema);
}

void SearchPanel::preUpdate(){
    libreriaMediaTutto->update(comboAttivita, comboOrdinamento, ricerca, s_MediaListOfCinema);
    for(auto o : s_libraryObservers)
        o->update(comboAttivita, comboOrdinamento, filtroBottone, ricerca, s_MediaListOfCinema);
}

void SearchPanel::updateMediaList(){
    s_MediaListOfCinema.clear();
    
    if(s_cinemaSelezionato){
        s_jsonManager->loadMedia(s_MediaListOfCinema, QString::fromStdString(s_cinemaSelezionato->getNomeCinema()));
        for(Media* m : s_MediaListOfCinema){
            s_cinemaSelezionato->addMedia(m);
        }
    }
}

//slot

void SearchPanel::updateInfoCinema(Cinema* cinemaSel){
    //selezione Cinema
    s_cinemaSelezionato = cinemaSel;
    cinema->setText("Cinema " + QString::fromStdString(s_cinemaSelezionato->getNomeCinema()));

    updateMediaList();
    updateFiltroTutto();
    emit giveCinemaInfoToIP(s_cinemaSelezionato, s_MediaListOfCinema);
    
    s_xmlManager->setCurrentCinema(s_cinemaSelezionato);
}


void SearchPanel::resetSearchPanel(){
    updateCerca("Tutto");
    comboAttivita = 0; 
    comboOrdinamento = 0; 
    filtroBottone = "Film"; 
    ricerca.clear();

    attivita->setCurrentIndex(0);
    ordinamento->setCurrentIndex(0);

    if(stackModifiche->currentIndex()==1) emit resetPages();
    stackModifiche->setCurrentIndex(0);

    updateMediaList();

    for(Media* m : s_MediaListOfCinema){
        s_cinemaSelezionato->removeMedia(m);
    }

    preUpdate();
    updateFiltroTutto();
}



void SearchPanel::acceptEditCinema(){
    QString nomeCinema = QString::fromStdString(s_cinemaSelezionato->getNomeCinema());
    CinemaModifier dialog(s_cinemaSelezionato, this);

    dialog.setFixedSize(850, 500);
    int result = dialog.exec();
    if (result == QDialog::Accepted) {
        s_jsonManager->updateCinemaInJson(nomeCinema, s_cinemaSelezionato);
        updateInfoCinema(s_cinemaSelezionato);
    }
}

void SearchPanel::acceptDeleteCinema(){
    QMessageBox msgBox;
    msgBox.setWindowTitle("Conferma eliminazione");
    msgBox.setText("Sei sicuro di voler eliminare il cinema? "
                    "Avrà l'effetto di eliminare tutti i media ad esso associati");
    QPushButton* annulla = msgBox.addButton("Annulla", QMessageBox::RejectRole);
    QPushButton* conferma = msgBox.addButton("Conferma", QMessageBox::AcceptRole);
    msgBox.exec();
    if (msgBox.clickedButton() == conferma) {
        qDebug() << "Eliminazione cinema "<<QString::fromStdString(s_cinemaSelezionato->getNomeCinema())<<" confermata";
        emit deleteCinemaInSearchPanel(s_cinemaSelezionato);
        s_cinemaSelezionato = nullptr;
        emit escSearchPanel();
    }
    else if (msgBox.clickedButton() == annulla){
        qDebug() << "Eliminazione cinema "<<QString::fromStdString(s_cinemaSelezionato->getNomeCinema())<<" annullata";
    }
}


void SearchPanel::showEditPage(Media* media){
    EditMedia* editMedia = new EditMedia(media, this); 
    int backIndex = stackModifiche->currentIndex();
    
    editMedia->getCinemaInfo(s_cinemaSelezionato, s_MediaListOfCinema);
    editMedia->initValue();
    
    stackModifiche->addWidget(editMedia);
    stackModifiche->setCurrentWidget(editMedia);
    connect(editMedia, &EditMedia::tornaIndietro, this, [this, editMedia, backIndex](){
        stackModifiche->setCurrentIndex(backIndex);       
        stackModifiche->removeWidget(editMedia); 
        delete editMedia;});
}



void SearchPanel::updateJson(){
    s_jsonManager->updateMediaInJson(s_cinemaSelezionato);
}



void SearchPanel::deleteViewPages(){
    if(stackModifiche->currentIndex()>2){
            for (int i=stackModifiche->count()-1; i>=2; --i) {
                QWidget* w = stackModifiche->widget(i);
                stackModifiche->removeWidget(w);
                delete w;
            }
    }
}