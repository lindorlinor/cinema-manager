#include "EditMedia.h"

EditMedia::EditMedia(Media* media, QWidget *parent): MediaInterface(parent), em_media(media){

    initUI();

    titolo->setText("Modifica l'elemento "+QString::fromStdString(media->getTitolo()));

    //ottengo l0indice corretto per la staktipologia
    if (dynamic_cast<Film*>(media)) index = 0;
    if (dynamic_cast<Trailer*>(media)) index = 1;
    if (dynamic_cast<Inserzione*>(media)) index = 2;
    if (dynamic_cast<Podcast*>(media)) index = 3;
    if (dynamic_cast<Puntata*>(media)) index = 4;

    setLimitTabTipologia(index);

    initValue();

    connect(referencePuntate, &SelectMediaReference::mediaSelected, this, [this](MediaFrame* f){
        referencePuntate->setSelectedItem("","");
    });
    connect(referenceTrailer, &SelectMediaReference::mediaSelected, this, [this](MediaFrame* f){
        referencePuntate->setSelectedItem("","");
    });

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
    
    //valori comuni
    QList<QString> lingue;
    for(Lingua l :em_media->getLingue()){
        lingue.append(toString(l));
    }

    QList<QString> sottotitoli;
    for(Lingua s :em_media->getSottotitoli()){
        sottotitoli.append(toString(s));
    }

    QDate dataInizioRilascio(static_cast<int>(em_media->getDataInizioRilascio().year()),
            static_cast<unsigned>(em_media->getDataInizioRilascio().month()),
            static_cast<unsigned>(em_media->getDataInizioRilascio().day()));

    QDate dataFineRilascio(static_cast<int>(em_media->getDataFineRilascio().year()),
            static_cast<unsigned>(em_media->getDataFineRilascio().month()),
            static_cast<unsigned>(em_media->getDataFineRilascio().day()));
            
    titoloMedia->setText(QString::fromStdString(em_media->getTitolo()));
    autoreMedia->setText(QString::fromStdString(em_media->getAutore()));
    durataMinutiMedia->setValue(em_media->getDurataMinuti());
    descrizioneMedia->setText(QString::fromStdString(em_media->getDescrizione()));
    framePath->insertImage(QFileInfo((QString::fromStdString(em_media->getImPath()))).fileName());
    comboFormato->setCurrentText(toString(em_media->getFormato()));
    comboRisoluzione->setCurrentText(toString(em_media->getRisoluzione()));
    imagePath = QString::fromStdString(em_media->getImPath());
    
    setCheckListWidget(listLingue, lingue);
    setCheckListWidget(listSottotitoli, sottotitoli);

    dataInizio->setDate(dataInizioRilascio);
    dataFine->setDate(dataFineRilascio);



    //valori per tipologia
    if(index == 0){
        Film* film = static_cast<Film*>(em_media);
        
        CasaProdFilm->setText(QString::fromStdString(film->getCasaDiProduzione()));
        
        QList<QString> risultato;
        QList<QString> generi; 
        for(const string& s : film->getAttoriPrincipali()){ risultato.append(QString::fromStdString(s));}
        for(Genere g :film->getGeneri()){ generi.append(toString(g)); }

        setCheckListWidget(listGeneri, generi);

        attoriFilm->setItems(risultato);
        totPostCreditFilm->setValue(film->getNPostCredit());
        costoBigliettoFilm->setValue(film->getCostoBiglietto());
        comboTargetFilm->setCurrentText(toString(film->getTarget()));
        comboTipologia->setCurrentIndex(0);
    }
    else if(index == 1){
        Trailer* trailer = static_cast<Trailer*>(em_media);
        referenceTrailer->setSelectedItem(QString::fromStdString(trailer->getTitolo()),QString::fromStdString(trailer->getAutore()));
        if(referenceTrailer) referenceTrailer->reloadMedia(QString::fromStdString(im_cinemaSelezionato->getNomeCinema()));
        numeroProiezioniTrailer->setValue(trailer->getDurataMinuti());
        comboTipologia->setCurrentIndex(1);
    }
    else if(index == 2){
        Inserzione* inserzione = static_cast<Inserzione*>(em_media);
        aziendaInserzInserzione->setText(QString::fromStdString(inserzione->getAziendaInserzionistica()));
        numeroProiezioniGioInserzione->setValue(inserzione->getNProiezioniGiornaliere());
        costoBaseProiezInserzione->setValue(inserzione->getCostoFissoProiezione());
        comboTipologia->setCurrentIndex(2);

        QList<QString> fasce_orarie;
        for(FasciaOraria f :inserzione->getFasceOrarie()){ fasce_orarie.append(toString(f)); }
        setCheckListWidget(listFasceOrarie, fasce_orarie);
        comboTargetInserzioni->setCurrentText(toString(inserzione->getTarget()));
    }
    else if(index == 3){
        Podcast* podcast = static_cast<Podcast*>(em_media);
        
        conduttorePodcast->setText(QString::fromStdString(podcast->getConduttore()));
        comboTipologia->setCurrentIndex(3);
    }
    else if(index == 4){
        Puntata* puntata = static_cast<Puntata*>(em_media);
        referencePuntate->setSelectedItem(QString::fromStdString(puntata->getTitolo()),QString::fromStdString(puntata->getAutore()));
        if(referencePuntate) referencePuntate->reloadMedia(QString::fromStdString(im_cinemaSelezionato->getNomeCinema()));
        QList<QString> risultato;
        for(const string& s : puntata->getOspiti()){ risultato.append(QString::fromStdString(s));}
        ospitiPuntata->setItems(risultato);
        numeroPubblicitaPuntata->setValue(puntata->getNumeroPubblicita());
        comboTipologia->setCurrentIndex(4);
    }

    
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




void EditMedia::setCheckListWidget(QListWidget* list, const QList<QString>& select) {
    for (int i = 0; i < list->count(); ++i) {
        QListWidgetItem* item = list->item(i);
        bool presente = select.contains(item->text());
        item->setCheckState(presente ? Qt::Checked : Qt::Unchecked);
    }
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





void EditMedia::checkMediaNameAvailability(){
    QString titolo = titoloMedia->text().trimmed();
    QString autore = autoreMedia->text().trimmed();
    
    bool isAvailable = true;
    errorLabel->setVisible(false);

    if(titolo.isEmpty() || autore.isEmpty()) isAvailable = false;

    for (const Media* m: im_mediaList) {
        if ((QString::fromStdString(m->getTitolo()).compare(titolo, Qt::CaseInsensitive) == 0 && QString::fromStdString(m->getAutore()).compare(autore, Qt::CaseInsensitive) == 0) &&
            (QString::fromStdString(em_media->getTitolo()).compare(titolo, Qt::CaseInsensitive) != 0 && QString::fromStdString(em_media->getAutore()).compare(autore, Qt::CaseInsensitive) != 0)) {
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
        saveButton->setEnabled(false);
    }
}