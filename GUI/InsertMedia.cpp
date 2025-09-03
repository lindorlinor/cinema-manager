#include "InsertMedia.h"

InsertMedia::InsertMedia(QWidget *parent): MediaInterface(parent){

    initUI();

    connect(indietro, &QPushButton::clicked, this, [this](){
        resetAllInput();
        emit tornaIndietro();
    }); 

    connect(cancelButton, &QPushButton::clicked, this, [this](){
        resetAllInput();
        emit tornaAllaLibreria(); 
    });

    connect(saveButton, &QPushButton::clicked, this, [this]() {
        salvaMedia();
        resetAllInput();
        emit tornaAllaLibreria();
    });

    connect(comboTipologia, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index){
        setLimitTabTipologia(index);
    });
}










//metodi funzionali per il corretto comportamento della pagina
void InsertMedia::setLimitTabTipologia(int index){
    
    //per resettare tutto ad eccezione dei campi comuni
    resetInputFilm();
    resetInputTrailer();
    resetInputInserzione();
    resetInputPodcast();
    resetInputPuntata();

    stackTipologia->setCurrentIndex(index);

    bool puntata = (index==3);
    comboFormato->setEnabled(!puntata);
    comboRisoluzione->setEnabled(!puntata);
    if(puntata){
        comboFormato->setCurrentIndex(0);
        comboRisoluzione->setCurrentIndex(0);
    }

    // Blocca la modifica dall'utente se è podcast
    bool podcast = (index == 2);

    dataInizio->setEnabled(!podcast);
    dataFine->setEnabled(!podcast);
    listLingue->setEnabled(!podcast);
    listSottotitoli->setEnabled(!podcast);
    durataMinutiMedia->setEnabled(!podcast);

    if(podcast){
        dataInizio->setDate(QDate::currentDate());
        dataFine->setDate(QDate::currentDate());
        durataMinutiMedia->setValue(0);

        for (int i = 0; i < listLingue->count(); ++i) {
        listLingue->item(i)->setCheckState(Qt::Unchecked);   
        }

        for (int i = 0; i < listSottotitoli->count(); ++i) {
        listSottotitoli->item(i)->setCheckState(Qt::Unchecked);   
        }

    }

    checkMediaNameAvailability();
}










//creazione oggetti e salvataggio su json

void InsertMedia::salvaMedia(){//funzione per salvare gli input in un json

    //film
    if(stackTipologia->currentIndex()==0){

        Film* film = new Film(  
                                titoloMedia->text().toStdString(),
                                descrizioneMedia->toPlainText().toStdString(),
                                convertDate(dataInizio->date()),
                                convertDate(dataFine->date()),
                                durataMinutiMedia->value(),
                                toFormato(comboFormato->currentText().toStdString()),
                                toRisoluzione(comboRisoluzione->currentText().toStdString()),
                                totPostCreditFilm->value(),
                                costoBigliettoFilm->value(),
                                CasaProdFilm->text().toStdString(),
                                autoreMedia->text().toStdString(),
                                imagePath==""?":/images/default.png":imagePath.toStdString(),
                                toClassificazione(comboTargetFilm->currentText().toStdString()));

        addLingue(film);
        addSottotitoli(film);
        addGeneri(film);
        addAttore(film);

        im_cinemaSelezionato->addMedia(film);
        
        cinemaManager->saveMediaInJson(film, QString::fromStdString(im_cinemaSelezionato->getNomeCinema()));
    }

    //trailer
    else if(stackTipologia->currentIndex()==1){

        Media* filmAssociato = findMediaReference(titoloFilmRiferimento, autoreFilmRiferimento, "trailer");

        if(!filmAssociato){
            qDebug()<<"Errore!, nessun Film collegato al Trailer "<<titoloMedia->text();
            return;
        } 

        Trailer* trailer = new Trailer(
                                titoloMedia->text().toStdString(),
                                descrizioneMedia->toPlainText().toStdString(),
                                convertDate(dataInizio->date()),
                                convertDate(dataFine->date()),
                                durataMinutiMedia->value(),
                                toFormato(comboFormato->currentText().toStdString()),
                                toRisoluzione(comboRisoluzione->currentText().toStdString()),
                                numeroProiezioniTrailer->value(),
                                static_cast<Film*>(filmAssociato),
                                autoreMedia->text().toStdString(),
                                imagePath==""?":/images/default.png":imagePath.toStdString());
        
        addLingue(trailer);
        addSottotitoli(trailer);
    
        im_cinemaSelezionato->addMedia(trailer);
        
        cinemaManager->saveMediaInJson(trailer, QString::fromStdString(im_cinemaSelezionato->getNomeCinema()));
    }
    //podcast
    else if(stackTipologia->currentIndex()==2){
        
        Podcast* podcast = new Podcast(
                                titoloMedia->text().toStdString(),
                                descrizioneMedia->toPlainText().toStdString(),
                                toFormato(comboFormato->currentText().toStdString()),
                                toRisoluzione(comboRisoluzione->currentText().toStdString()),
                                autoreMedia->text().toStdString(),
                                imagePath==""?":/images/default.png":imagePath.toStdString(),
                                conduttorePodcast->text().toStdString());
    
        im_cinemaSelezionato->addMedia(podcast);
        
        cinemaManager->saveMediaInJson(podcast, QString::fromStdString(im_cinemaSelezionato->getNomeCinema()));
    }   
    //puntata
    else if(stackTipologia->currentIndex()==3){

        Media* PodcastAssociato = findMediaReference(titoloPodcastRiferimento,autorePodcastRiferimento,"podcast");

        if(!PodcastAssociato){
            qDebug()<<"Errore!, nessun Podcast collegato al Trailer "<<titoloMedia->text();
            return;
        } 

        Puntata* puntata = new Puntata(
                                titoloMedia->text().toStdString(),
                                descrizioneMedia->toPlainText().toStdString(),
                                convertDate(dataInizio->date()),
                                convertDate(dataFine->date()),
                                durataMinutiMedia->value(),
                                static_cast<Podcast*>(PodcastAssociato),
                                numeroPubblicitaPuntata->value(),
                                autoreMedia->text().toStdString(),
                                imagePath==""?":/images/default.png":imagePath.toStdString());
        
        addLingue(puntata);
        addSottotitoli(puntata);
        addOspite(puntata);
    
        im_cinemaSelezionato->addMedia(puntata);
        
        cinemaManager->saveMediaInJson(puntata, QString::fromStdString(im_cinemaSelezionato->getNomeCinema()));

    }   
    //inserzione
    else if(stackTipologia->currentIndex()==4){

        Inserzione* inserzione = new Inserzione(  
                                titoloMedia->text().toStdString(),
                                descrizioneMedia->toPlainText().toStdString(),
                                convertDate(dataInizio->date()),
                                convertDate(dataFine->date()),
                                durataMinutiMedia->value(),
                                toFormato(comboFormato->currentText().toStdString()),
                                toRisoluzione(comboRisoluzione->currentText().toStdString()),
                                numeroProiezioniGioInserzione->value(),
                                toClassificazione(comboTargetInserzioni->currentText().toStdString()),
                                costoBaseProiezInserzione->value(),
                                aziendaInserzInserzione->text().toStdString(),
                                autoreMedia->text().toStdString(),
                                imagePath==""?":/images/default.png":imagePath.toStdString());

        addLingue(inserzione);
        addSottotitoli(inserzione);

        im_cinemaSelezionato->addMedia(inserzione);
        
        cinemaManager->saveMediaInJson(inserzione, QString::fromStdString(im_cinemaSelezionato->getNomeCinema()));
    }   

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

    if(comboTargetFilm) comboTargetFilm->setCurrentIndex(0);
    
}

void InsertMedia::resetInputTrailer(){
    if(numeroProiezioniTrailer) numeroProiezioniTrailer->setValue(0);
    if(titoloFilmRiferimento!="") titoloFilmRiferimento = "";
    if(autoreFilmRiferimento!="") autoreFilmRiferimento = "";
    if(referenceTrailer) referenceTrailer->setSelectFalse();
}
void InsertMedia::resetInputPodcast(){
    if(conduttorePodcast) conduttorePodcast->clear();
}
void InsertMedia::resetInputPuntata(){
    if(numeroPubblicitaPuntata) numeroPubblicitaPuntata->setValue(0);
    if(titoloPodcastRiferimento!="") titoloPodcastRiferimento = "";
    if(autorePodcastRiferimento!="") autorePodcastRiferimento = "";
    if(ospitiPuntata) ospitiPuntata->resetWidget();
    if(referencePuntate)referencePuntate->setSelectFalse();
}
void InsertMedia::resetInputInserzione(){
    if(aziendaInserzInserzione) aziendaInserzInserzione->clear();
    if(costoBaseProiezInserzione) costoBaseProiezInserzione->setValue(30.0);
    if(numeroProiezioniGioInserzione) numeroProiezioniGioInserzione->setValue(0);
    if(comboTargetInserzioni) comboTargetInserzioni->setCurrentIndex(0);

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

    if(referencePuntate)referencePuntate->reloadMedia(QString::fromStdString(im_cinemaSelezionato->getNomeCinema()));
    if(referenceTrailer)referenceTrailer->reloadMedia(QString::fromStdString(im_cinemaSelezionato->getNomeCinema()));
    
    QPixmap pixmap(":/images/default.png"); 
    copertina->setPixmap(pixmap.scaled(280,330, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    if(stackTipologia)stackTipologia->setCurrentIndex(0);
    if(tab) tab->setCurrentIndex(0);
    if(comboTipologia)comboTipologia->setCurrentIndex(0);
    
    // QString
    imagePath.clear();
    
    checkMediaNameAvailability();
}
