#include "EditMedia.h"

EditMedia::EditMedia(Media* media, QWidget *parent): MediaInterface(parent){

    initUI();

    //decidere se usare i dynamic_cast o il visitor che ho già creato
    EditMediaVisitor* visitor;
    media->accept(visitor);
    index = visitor->getIndex();
    setLimitTabTipologia(index);

    initValue();

    connect(indietro, &QPushButton::clicked, this, [this](){
        emit tornaIndietro();
    }); 

    connect(cancelButton, &QPushButton::clicked, this, [this](){
        emit tornaIndietro(); 
    });

    connect(saveButton, &QPushButton::clicked, this, [this]() {
        salvaMedia();
        emit tornaIndietro();
    });

}




void EditMedia::initValue(){
    //inizializza i valori di tutti i combobox, editline ecc
}





//metodi funzionali per il corretto comportamento della pagina

//TO DO: quando funzionerà tutto, provo a spostare il comportamento comune nella base MediInterface
void EditMedia::setLimitTabTipologia(int index){
    
    stackTipologia->setCurrentIndex(index);
    stackTipologia->setEnabled(false);

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










//salvare le modifiche agli oggetti

void EditMedia::salvaMedia(){

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





