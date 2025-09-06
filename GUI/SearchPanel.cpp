#include "SearchPanel.h"
#include "FilmView.h"
#include "TrailerView.h"
#include "DetailPageVisitor.h"
#include "LibraryObserver.h"
#include "InserzioneView.h"

/* NOTE IMPORTANTI: s_MediaListOfCinema contiene gli oggetti caricati nel json ed è tramite lei che popolo il cinema selezionato con gli addMedia, ma così
ci sono i puntatori della liste di supporto e della liste media del cinema che puntano allo stesso media -> attenzione al dangling, quando si aggiunge un elemento non 
c'è bisogno di aggiornare la lista passata all'InsertMedia perché è passata per riferimento, e ogni volta che richiamo la libreria (tutto o generale) 
aggiorno la lista: cancella i suoi contenuti, quindi i puntatori agli oggetti, che non diventano garbage perché sono ancora associati alla lista del cinema, e la ripopolo
con gli elementi del cinema -> NON STO DISTRUGGENDO OGGETTI E RICREANDOLI, STO SOLO ASSEGNANDO E TOGLIENDO PUNTATORI AGLI OGGETTI. La popolazione degli oggetti nel cinema, 
ad eccezione del primo richiamo, è fatta all'interno di InsertMedia quando viene creato un oggetto. La lista rimane aggiornata anche in InserMedia perché è èassata per riferimento.
quando si esce dal cinema viene chiamato il reset che cancella tutti gli ogetti puntati nella lista media del cinema e cancella con clean() le lista, tutti gli oggetti sono stati 
eliminati, senza SF o dangling pointer. */

SearchPanel::SearchPanel(CinemaRepositoryJson* s_jsonManager,MediaManagerXml* xmlManager,QWidget *parent):QWidget(parent), s_jsonManager(s_jsonManager),
                                                    s_xmlManager(xmlManager), comboAttivita(0), comboOrdinamento(0), filtroBottone("Film"),
                                                    ricerca(""), changeView(1),stackModifiche(new QStackedWidget(this)){
    //carico tutti gli oggetti sal Json
    QVBoxLayout* mainLayout = new QVBoxLayout;

    addPagina(mainLayout);
    
    setLayout(mainLayout);
    
    //style
    mainLayout->setContentsMargins(0, 0, 0, 0); 
    mainLayout->setSpacing(0);
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
        emit setQMenuDisabled();
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
    InsertMedia* nuovoMedia = new InsertMedia(s_MediaListOfCinema, this);
    stackModifiche->addWidget(nuovoMedia); // 1
    
    

    //pannello per la libreria dei media
    libreriaMediaTutto = new MediaLibraryTutto(this);
    libreriaMediaGenerale = new MediaLibraryGenerale("Film" ,this);

    this->addObserver(libreriaMediaGenerale);

    stackLibreria->addWidget(libreriaMediaTutto); //0
    stackLibreria->addWidget(libreriaMediaGenerale); //1
    stackLibreria->setCurrentIndex(0);
    
    //GESTIONE PULSANTI
    connect(cerca, &QLineEdit::textChanged, this, [this](const QString &testo){ ricerca = testo; 
                                                                                updateFiltroTutto();
                                                                                for(auto o : s_libraryObservers) 
                                                                                    o->update(changeView, comboAttivita, comboOrdinamento, filtroBottone, ricerca, s_MediaListOfCinema);});
    connect(addMedia, &QPushButton::clicked, this, [this](){
        deleteViewPages();
        updateModifierPanel(1);
    });
    connect(tutto, &QToolButton::clicked, this, [this](){
        deleteViewPages();
        updateModifierPanel(0);
        updateFiltroTutto();
    });
    connect(film, &QToolButton::clicked, this, [this](){
        deleteViewPages();
        updateModifierPanel(0);
        updateFiltroMedia("Film");});
    connect(trailer, &QToolButton::clicked, this, [this](){
        deleteViewPages();
        updateModifierPanel(0);
        updateFiltroMedia("Trailer");});
    connect(inserzione, &QToolButton::clicked, this, [this](){
        deleteViewPages();
        updateModifierPanel(0);
        updateFiltroMedia("Inserzione");});
    connect(podcast, &QToolButton::clicked, this, [this](){
        deleteViewPages();
        updateModifierPanel(0);
        updateFiltroMedia("Podcast");});
    connect(puntata, &QToolButton::clicked, this, [this](){
        deleteViewPages();
        updateModifierPanel(0);
        updateFiltroMedia("Puntate");});


    connect(vista, &QPushButton::clicked, this, &SearchPanel::acceptChangeView);
    connect(this, &SearchPanel::giveCinemaInfoToIP, nuovoMedia, &InsertMedia::getCinemaInfo);
    connect(this, &SearchPanel::resetPages, nuovoMedia, &InsertMedia::resetAllInput);
    connect(nuovoMedia, &InsertMedia::tornaIndietro, this, [this](){
        updateModifierPanel(previousIndex);
    });
    connect(nuovoMedia, &InsertMedia::tornaAllaLibreria, this, [this](){
        updateModifierPanel(0);
        updateMediaList();
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

    vista->setObjectName("vista");
    cerca->setObjectName("cerca");
    attivita->setObjectName("attivita");
    ordinamento->setObjectName("ordinamento");
    attivita->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    ordinamento->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    vista->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    cerca->setContentsMargins(0, 10, 100, 0);
    barraFiltri->setContentsMargins(0, 10, 50, 0);
    vista->setCursor(Qt::PointingHandCursor);
    widgetSelezioneFiltri->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    //icone
    QIcon iconaVista(":/icons/vista.png");
    vista->setIcon(iconaVista);
    vista->setIconSize(QSize(40,40));
}

void SearchPanel::acceptViewFilm(){
    updateFiltroMedia("Film"); 
    deleteViewPages(); 
    updateModifierPanel(0);}

void SearchPanel::acceptViewTrailer(){
    updateFiltroMedia("Trailer");
    deleteViewPages(); 
    updateModifierPanel(0);}

void SearchPanel::acceptViewInserzione(){
    updateFiltroMedia("Inserzione");
    deleteViewPages(); 
    updateModifierPanel(0);}

void SearchPanel::acceptViewPodcast(){
    updateFiltroMedia("Podcast");
    deleteViewPages(); 
    updateModifierPanel(0);}

void SearchPanel::acceptViewPuntata(){
    updateFiltroMedia("Puntate");
    deleteViewPages(); 
    updateModifierPanel(0);}

void SearchPanel::acceptAddMedia(){
    deleteViewPages();
    updateModifierPanel(1);}


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
        obs->update(changeView, comboAttivita, comboOrdinamento, filtroBottone, ricerca, s_MediaListOfCinema);
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
    libreriaMediaTutto->update(changeView, comboAttivita, comboOrdinamento, ricerca, s_MediaListOfCinema);
}

void SearchPanel::preUpdate(){
    libreriaMediaTutto->update(changeView, comboAttivita, comboOrdinamento, ricerca, s_MediaListOfCinema);
    for(auto o : s_libraryObservers)
        o->update(changeView, comboAttivita, comboOrdinamento, filtroBottone, ricerca, s_MediaListOfCinema);
}

void SearchPanel::updateMediaList(){

    s_MediaListOfCinema.clear();
    
    if(s_cinemaSelezionato){
        for(Media* m : s_cinemaSelezionato->getListaMedia()){
            s_MediaListOfCinema.append(m);
        }
    }
}

//slot

void SearchPanel::acceptChangeView(){
    changeView = !changeView;
    if(stackLibreria->currentIndex() == 0){
        updateFiltroTutto();
    } else preUpdate();
}

void SearchPanel::updateInfoCinema(Cinema* cinemaSel){
    //selezione Cinema
    s_cinemaSelezionato = cinemaSel;
    cinema->setText("Cinema " + QString::fromStdString(s_cinemaSelezionato->getNomeCinema()));

    //carico tutto quello che c'è nel Json nella lista media del cinema    
    if(s_cinemaSelezionato){
        s_jsonManager->loadMedia(s_MediaListOfCinema, QString::fromStdString(s_cinemaSelezionato->getNomeCinema()));
        for(Media* m : s_MediaListOfCinema){
            s_cinemaSelezionato->addMedia(m);
        }
    }

    updateFiltroTutto();
    emit giveCinemaInfoToIP(s_cinemaSelezionato);
    
    s_xmlManager->setCurrentCinema(s_cinemaSelezionato);
}


void SearchPanel::resetSearchPanel(){
    updateCerca("Tutto");
    comboAttivita = 0; 
    comboOrdinamento = 0; 
    filtroBottone = "Film"; 
    changeView = 1;
    ricerca.clear();

    attivita->setCurrentIndex(0);
    ordinamento->setCurrentIndex(0);

    if(stackModifiche->currentIndex()==1) emit resetPages();
    stackModifiche->setCurrentIndex(0);

    for(Media* m : s_cinemaSelezionato->getListaMedia()){
        s_cinemaSelezionato->removeMedia(m);
    }
    s_jsonManager->deleteMediaPointer(s_MediaListOfCinema);

    updateFiltroTutto();
}

void SearchPanel::resetSearchPanelAfterDeleteCinema(){
    updateCerca("Tutto");
    comboAttivita = 0; 
    comboOrdinamento = 0; 
    filtroBottone = "Film"; 
    changeView = 1;
    ricerca.clear();

    attivita->setCurrentIndex(0);
    ordinamento->setCurrentIndex(0);

    if(stackModifiche->currentIndex()==1) emit resetPages();
    stackModifiche->setCurrentIndex(0);

    //non elimino gli oggetti e non li tolgo dalla lista media del cinema perché
    //quest'operazione è già stata fatta quando + stato eliminato il cinema 
    s_MediaListOfCinema.clear();

    updateFiltroTutto();
}



void SearchPanel::acceptEditCinema(){
    QString nomeCinema = QString::fromStdString(s_cinemaSelezionato->getNomeCinema());
    CinemaModifier dialog(s_cinemaSelezionato, this);

    dialog.setFixedSize(850, 500);
    int result = dialog.exec();
    if (result == QDialog::Accepted) {
        s_jsonManager->updateCinemaInJson(nomeCinema, s_cinemaSelezionato);

        cinema->setText("Cinema " + QString::fromStdString(s_cinemaSelezionato->getNomeCinema()));
        updateFiltroTutto();
    }
}

void SearchPanel::acceptDeleteCinema(){
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Conferma eliminazione");
    msgBox.setText("Sei sicuro di voler eliminare il cinema? "
                    "Avrà l'effetto di eliminare tutti i media ad esso associati");
    QPushButton* annulla = msgBox.addButton("Annulla", QMessageBox::RejectRole);
    QPushButton* conferma = msgBox.addButton("Conferma", QMessageBox::AcceptRole);
    msgBox.exec();
    if (msgBox.clickedButton() == conferma) {
        // qDebug() << "Eliminazione cinema "<<QString::fromStdString(s_cinemaSelezionato->getNomeCinema())<<" confermata";
        s_xmlManager->setCurrentCinema(nullptr);
        emit deleteCinemaInSearchPanel(s_cinemaSelezionato);
        resetSearchPanelAfterDeleteCinema();
        emit escSearchPanelAfterDeleteCinema();
        emit setQMenuDisabled();
    }
    else if (msgBox.clickedButton() == annulla){
        // qDebug() << "Eliminazione cinema "<<QString::fromStdString(s_cinemaSelezionato->getNomeCinema())<<" annullata";
    }
}


void SearchPanel::showEditPage(Media* media){
    EditMedia* editMedia = new EditMedia(s_MediaListOfCinema, media, this); 
    int backIndex = stackModifiche->currentIndex();
    
    editMedia->getCinemaInfo(s_cinemaSelezionato);
    editMedia->initValue();
    
    stackModifiche->addWidget(editMedia);
    stackModifiche->setCurrentWidget(editMedia);
    connect(editMedia, &EditMedia::tornaIndietro, this, [this, editMedia, backIndex](){
        updateMediaList(); 
        updateFiltroTutto();
        stackModifiche->setCurrentIndex(backIndex);       
        stackModifiche->removeWidget(editMedia);
        if(dynamic_cast<MediaView*>(stackModifiche->currentWidget())) //anche se a editmedia ci si arriva solo tramite MediaView faccio controllo
            (static_cast<MediaView*>((stackModifiche->currentWidget())))->update(); //sfrutta il polimorfismo, viene chiamato update della MediaView corrente
        delete editMedia;});
    connect(editMedia, &EditMedia::savedMedia, this,[this](){updateMediaList();});

}



void SearchPanel::updateJson(){
    s_jsonManager->updateMediaInJson(s_cinemaSelezionato);
}



void SearchPanel::deleteViewPages(){
    if(stackModifiche->currentIndex()>=2){
        for (int i=stackModifiche->count()-1; i>=2; --i) {
            QWidget* w = stackModifiche->widget(i);
            stackModifiche->removeWidget(w);
            delete w;
        }
    }
}

void SearchPanel::updateModifierPanel(int index){
    if(stackModifiche->currentIndex()!=index){
        if(previousIndex)
            previousIndex = stackModifiche->currentIndex();
        stackModifiche->setCurrentIndex(index);
    }
    if(index==0) emit setQMenuEnabled();
    else emit setQMenuDisabled();
}

void SearchPanel::showMediaView(MediaView& widget){
    if(auto inserzione = dynamic_cast<InserzioneView*>(&widget))
        inserzione->setMediaList(&s_MediaListOfCinema); //per passargli il mediaList, dovevo scegliere tra un set oppure passarlo al visitor, mi semrbava meglio cosi

    stackModifiche->addWidget(&widget);
    stackModifiche->setCurrentWidget(&widget);

    connect(&widget, &MediaView::editMediaClicked, this, &SearchPanel::showEditPage);
    connect(&widget, &MediaView::returnButton, this, [this, &widget](){
        removeMediaView(&widget);
    });
    
    connect(&widget, &MediaView::extendMediaClicked, this, &SearchPanel::updateJson);
    connect(&widget, &MediaView::requestMediaView, this, &SearchPanel::showMediaView);
    connect(&widget, &MediaView::deleteMediaClicked, this, [this, &widget](Media* m){acceptDeleteMedia(m);});
}

/*@to do metto MediaView invece che widget? no tanto stackModifiche 
ritorna sempre un QWidget non mi ritorna un mediaView...
posso fare static_cast invece che dynamic_cast? tanto so per 
certo che è sempre un mediaView.......giusto??? l
inor del futuro pensaci meglio grazie*/
void SearchPanel::removeMediaView(QWidget* widget){
    int widgetIndex = stackModifiche->indexOf(widget);

    if(widgetIndex > 2){
        stackModifiche->setCurrentIndex(widgetIndex-1);
        /* if(auto insPtr = dynamic_cast<InserzioneView*>(stackModifiche->currentWidget())){
            updateMediaList();
            insPtr->setMediaList(s_MediaListOfCinema);
        } */
            
        (static_cast<MediaView*>((stackModifiche->currentWidget())))->update(); //fa l'update nel caso in cui vi è stata una modifica del media
    }
    else
        stackModifiche->setCurrentIndex(0);

    stackModifiche->removeWidget(widget);
    delete widget;
}

void SearchPanel::acceptDeleteMedia(Media* media){

    if(Film* film = dynamic_cast<Film*>(media)){
        for(Trailer* t : film->getTrailers()){
            film->disaccoppiaTrailer(t);
            s_MediaListOfCinema.removeOne(t);
            s_cinemaSelezionato->removeMedia(t);
            
            delete t;
        }
    }
    
    if(Podcast* podcast = dynamic_cast<Podcast*>(media)){
        for(Puntata* p : podcast->getElencoPuntate()){
            podcast->disaccoppiaPuntata(p);
            s_MediaListOfCinema.removeOne(p);
            s_cinemaSelezionato->removeMedia(p);
            delete p;
        }
    }

    s_MediaListOfCinema.removeOne(media);
    s_cinemaSelezionato->removeMedia(media);
    delete media;
    updateJson();
    updateMediaList();

    deleteViewPages();
    stackModifiche->setCurrentIndex(0);
    updateFiltroTutto();
}
