#include "EditMedia.h"

EditMedia::EditMedia(Media* media, QWidget *parent): MediaInterface(parent), em_media(media){

    initUI();

    titolo->setText("Modifica l'elemento "+QString::fromStdString(media->getTitolo()));

    //ottengo l0indice corretto per la staktipologia
    if (dynamic_cast<Film*>(media)) index = 0;
    if (dynamic_cast<Trailer*>(media)) index = 1;
    if (dynamic_cast<Podcast*>(media)) index = 2;
    if (dynamic_cast<Puntata*>(media)) index = 3;
    if (dynamic_cast<Inserzione*>(media)) index = 4;

    setLimitTabTipologia(index);

    connect(referencePuntate, &SelectMediaReference::mediaSelected, this, [this](){
        referencePuntate->setSelectedItem("","");
    });
    connect(referenceTrailer, &SelectMediaReference::mediaSelected, this, [this](){
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
    }
    else if(index == 1){
        Trailer* trailer = static_cast<Trailer*>(em_media);
        referenceTrailer->setSelectedItem(QString::fromStdString(trailer->getFilm()->getTitolo()),QString::fromStdString(trailer->getFilm()->getAutore()));
        if(referenceTrailer) referenceTrailer->reloadMedia(QString::fromStdString(im_cinemaSelezionato->getNomeCinema()));
        numeroProiezioniTrailer->setValue(trailer->getDurataMinuti());
    }
    else if(index == 2){
        Podcast* podcast = static_cast<Podcast*>(em_media);
        
        conduttorePodcast->setText(QString::fromStdString(podcast->getConduttore()));
    }
    else if(index == 3){
        Puntata* puntata = static_cast<Puntata*>(em_media);
        referencePuntate->setSelectedItem(QString::fromStdString(puntata->getPodcast()->getTitolo()),QString::fromStdString(puntata->getPodcast()->getAutore()));
        if(referencePuntate) referencePuntate->reloadMedia(QString::fromStdString(im_cinemaSelezionato->getNomeCinema()));
        QList<QString> risultato;
        for(const string& s : puntata->getOspiti()){ risultato.append(QString::fromStdString(s));}
        ospitiPuntata->setItems(risultato);
        numeroPubblicitaPuntata->setValue(puntata->getNumeroPubblicita());
    }
    else if(index == 4){
        Inserzione* inserzione = static_cast<Inserzione*>(em_media);
        aziendaInserzInserzione->setText(QString::fromStdString(inserzione->getAziendaInserzionistica()));
        numeroProiezioniGioInserzione->setValue(inserzione->getNProiezioniGiornaliere());
        costoBaseProiezInserzione->setValue(inserzione->getCostoFissoProiezione());
    
        QList<QString> fasce_orarie;
        for(FasciaOraria f :inserzione->getFasceOrarie()){ fasce_orarie.append(toString(f)); }
        setCheckListWidget(listFasceOrarie, fasce_orarie);
        comboTargetInserzioni->setCurrentText(toString(inserzione->getTarget()));
    }
    
    
}





//metodi funzionali per il corretto comportamento della pagina

//TO DO: quando funzionerà tutto, provo a spostare il comportamento comune nella base MediInterface
void EditMedia::setLimitTabTipologia(int i){
    
    stackTipologia->setCurrentIndex(i);
    comboTipologia->setCurrentIndex(i);
    comboTipologia->setEnabled(false);

    bool puntata = (i==3);
    comboFormato->setEnabled(!puntata);
    comboRisoluzione->setEnabled(!puntata);
    if(puntata){
        comboFormato->setCurrentIndex(0);
        comboRisoluzione->setCurrentIndex(0);
    }

    // Blocca la modifica dall'utente se è podcast
    bool podcast = (i == 2);

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

    em_media->setAutore(autoreMedia->text().toStdString());
    em_media->setTitolo(titoloMedia->text().toStdString());
    em_media->setDescrizione(descrizioneMedia->toPlainText().toStdString());
    em_media->setDataInizioRilascio(convertDate(dataInizio->date()));
    em_media->setDataFineRilascio(convertDate(dataFine->date()));
    em_media->setDurataMinuti(durataMinutiMedia->value());
    em_media->setFormato(toFormato(comboFormato->currentText().toStdString()));
    em_media->setRisoluzione(toRisoluzione(comboRisoluzione->currentText().toStdString()));
    em_media->setPath(imagePath==""?":/images/default.png":imagePath.toStdString());

    if(!(getSelectedList(listLingue)).empty()){
        for(const Lingua& l : em_media->getLingue())
            em_media->rimuoviLingua(l);
        addLingue(em_media);
    }

    if(!(getSelectedList(listSottotitoli)).empty()){
        for(const Lingua& s : em_media->getSottotitoli())
            em_media->rimuoviSottotitolo(s);
        addSottotitoli(em_media);
    }
    
    
    if(stackTipologia->currentIndex()==0){

        Film* film = static_cast<Film*>(em_media);

        film->setCasaDiProduzione(CasaProdFilm->text().trimmed().toStdString());
        film->setNPostCredit(totPostCreditFilm->value());
        film->setCostoBiglietto(costoBigliettoFilm->value());
        film->setTarget(toClassificazione(comboTargetFilm->currentText().toStdString()));

        if(!(getSelectedList(listGeneri)).empty()){
            for(const Genere& g : film->getGeneri())
                film->rimuoviGenere(g);
            addGeneri(film);
        }

        for(const string& a : film->getAttoriPrincipali())
            film->rimuoviAttore(a);
        addAttore(film);
    }

    //trailer
    else if(stackTipologia->currentIndex()==1){

        Media* filmAssociato = findMediaReference(titoloFilmRiferimento, autoreFilmRiferimento, "trailer");

        if(!filmAssociato){
            qDebug()<<"Errore!, nessun Film collegato al Trailer "<<titoloMedia->text();
            return;
        } 

        Trailer* trailer = static_cast<Trailer*>(em_media);
        trailer->setNProiezioniGiornaliere(numeroProiezioniTrailer->value());

        if( titoloFilmRiferimento != QString::fromStdString(trailer->getFilm()->getTitolo()) || 
            autoreFilmRiferimento != QString::fromStdString(trailer->getFilm()->getAutore())){
            trailer->associaFilm(static_cast<Film*>(filmAssociato));
        }
    }
    //podcast
    else if(stackTipologia->currentIndex()==2){
        Podcast* podcast = static_cast<Podcast*>(em_media);
        podcast->setConduttore(conduttorePodcast->text().toStdString());
    }   
    //puntata
    else if(stackTipologia->currentIndex()==3){
        
        Media* PodcastAssociato = findMediaReference(titoloPodcastRiferimento,autorePodcastRiferimento,"podcast");
        
        if(!PodcastAssociato){
            qDebug()<<"Errore!, nessun Podcast collegato al Trailer "<<titoloMedia->text();
            return;
        } 
        
        Puntata* puntata = static_cast<Puntata*>(em_media);
        
        puntata->setNumeroPubblicita(numeroPubblicitaPuntata->value());
        if( titoloPodcastRiferimento != QString::fromStdString(puntata->getPodcast()->getTitolo()) || 
            autorePodcastRiferimento != QString::fromStdString(puntata->getPodcast()->getAutore())){
            puntata->associaPodcast(static_cast<Podcast*>(PodcastAssociato));
        }
        
        for(const string& o : puntata->getOspiti())
        puntata->rimuoviOspite(o);
        addOspite(puntata);
        
    }   
    //inserzione
    else if(stackTipologia->currentIndex()==4){
        
        Inserzione* inserzione = static_cast<Inserzione*>(em_media);

        inserzione->setNProiezioniGiornaliere(numeroProiezioniGioInserzione->value());
        inserzione->setCostoFissoProiezione(costoBaseProiezInserzione->value());
        inserzione->setTarget(toClassificazione(comboTargetInserzioni->currentText().toStdString()));
        inserzione->setAziendaInserzionistica(aziendaInserzInserzione->text().toStdString());
    }   

    cinemaManager->updateMediaInJson(im_cinemaSelezionato);

}





void EditMedia::checkMediaNameAvailability(){
    QString titolo = titoloMedia->text().trimmed();
    QString autore = autoreMedia->text().trimmed();
    
    bool isAvailable = true;
    errorLabel->setVisible(false);

    if(titolo.isEmpty() || autore.isEmpty()) isAvailable = false;

    for (const Media* m: im_mediaList) {
        if (QString::fromStdString(m->getTitolo()).compare(titolo, Qt::CaseInsensitive) == 0 && QString::fromStdString(m->getAutore()).compare(autore, Qt::CaseInsensitive) == 0){
            isAvailable = false; 
        }
    }

    if(QString::fromStdString(em_media->getTitolo()).compare(titolo, Qt::CaseInsensitive) == 0 && QString::fromStdString(em_media->getAutore()).compare(autore, Qt::CaseInsensitive) == 0 && !isAvailable)
        isAvailable = true;

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

/* bool EditMedia::isModified(){

    bool modified = false;
    //valori comuni

    modified = (isLingueModified() || isSottotitoliModified() || convertDate(dataInizio->date()) != em_media->getDataInizioRilascio() || 
            convertDate(dataFine->date()) != em_media->getDataFineRilascio() || titoloMedia->text().trimmed().toStdString() != em_media->getTitolo() || 
            autoreMedia->text().trimmed().toStdString() != em_media->getAutore() || static_cast<unsigned int>(durataMinutiMedia->value()) != em_media->getDurataMinuti() ||
            descrizioneMedia->toPlainText().trimmed().toStdString() != em_media->getDescrizione() || framePath || comboFormato->currentText() != toString(em_media->getFormato()) ||
            comboRisoluzione->currentText() != toString(em_media->getRisoluzione()) || imagePath.toStdString() != em_media->getImPath());

    qDebug()<<"prima "<<modified;
            
    //valori per tipologia
    if(index == 0){
        Film* film = static_cast<Film*>(em_media);

        
        modified = (CasaProdFilm->text().trimmed().toStdString() != film->getCasaDiProduzione() || isGeneriModified(film) || isAttoreModified(film) ||
                static_cast<unsigned int>(totPostCreditFilm->value()) != film->getNPostCredit() || costoBigliettoFilm->value() != film->getCostoBiglietto() || 
                comboTargetFilm->currentText() != toString(film->getTarget()) || modified);
    }
    else if(index == 1){
        Trailer* trailer = static_cast<Trailer*>(em_media);

        modified= (titoloFilmRiferimento != QString::fromStdString(trailer->getFilm()->getTitolo()) || autoreFilmRiferimento != QString::fromStdString(trailer->getFilm()->getAutore()) ||
            static_cast<unsigned int>(numeroProiezioniTrailer->value()) != trailer->getNProiezioniGiornaliere()|| modified);
    }
    else if(index == 2){
        Podcast* podcast = static_cast<Podcast*>(em_media);

        modified = (conduttorePodcast->text().trimmed().toStdString() != podcast->getConduttore()|| modified);
    
    }
    else if(index == 3){
        Puntata* puntata = static_cast<Puntata*>(em_media);

        modified= (titoloPodcastRiferimento != QString::fromStdString(puntata->getPodcast()->getTitolo()) || autorePodcastRiferimento != QString::fromStdString(puntata->getPodcast()->getAutore()) ||
            isOspiteModified(puntata) || static_cast<unsigned int>(numeroPubblicitaPuntata->value()) != puntata->getNumeroPubblicita()|| modified);
    }
    else if(index == 4){
        Inserzione* inserzione = static_cast<Inserzione*>(em_media);

        modified = (aziendaInserzInserzione->text().trimmed().toStdString() != inserzione->getAziendaInserzionistica() || 
            static_cast<unsigned int>(numeroProiezioniGioInserzione->value()) != inserzione->getNProiezioniGiornaliere()||
            costoBaseProiezInserzione->value() != inserzione->getCostoFissoProiezione() || isFasceOrarieModified(inserzione)|| modified);
    }
    qDebug()<<modified;

    return modified;
}

bool EditMedia::isFasceOrarieModified(Inserzione* inserzione){
    QList<QString> attuali;
    QList<QString> originali;

    for (const std::string& f : getSelectedList(listFasceOrarie)) {
        attuali.append(QString::fromStdString(f));
    }
    for (const FasciaOraria& f : inserzione->getFasceOrarie()) {
        originali.append(toString(f));
    }

    QList<QString>attualiCopia = attuali = attuali;
    sort(attualiCopia.begin(), attualiCopia.end());
    sort(originali.begin(), originali.end());

    return attuali != originali;
}

bool EditMedia::isLingueModified(){
    QList<QString> attuali;
    QList<QString> originali;

    for (const std::string& l : getSelectedList(listLingue)) {
        attuali.append(QString::fromStdString(l));
    }
    for (const Lingua& l : em_media->getLingue()) {
        originali.append(toString(l));
    }

    QList<QString>attualiCopia = attuali;
    sort(attualiCopia.begin(), attualiCopia.end());
    sort(originali.begin(), originali.end());

    return attuali != originali;
}

bool EditMedia::isSottotitoliModified(){
    QList<QString> attuali;
    QList<QString> originali;

    for (const std::string& s : getSelectedList(listSottotitoli)) {
        attuali.append(QString::fromStdString(s));
    }
    for (const Lingua& s : em_media->getSottotitoli()){
        originali.append(toString(s));
    }

    QList<QString>attualiCopia = attuali;
    sort(attualiCopia.begin(), attualiCopia.end());
    sort(originali.begin(), originali.end());

    return attuali != originali;
}

bool EditMedia::isGeneriModified(Film* film){
    QList<QString> attuali;
    QList<QString> originali;

    for (const std::string& g : getSelectedList(listGeneri)) {
        attuali.append(QString::fromStdString(g));
    }
    for (const Genere& g : film->getGeneri()){
        originali.append(toString(g));
    }
    
    QList<QString>attualiCopia = attuali;
    sort(attualiCopia.begin(), attualiCopia.end());
    sort(originali.begin(), originali.end());

    return attuali != originali;
}

bool EditMedia::isAttoreModified(Film* film){
    QList<QString> attuali;
    QList<QString> originali;

    for (const QString& a : attoriFilm->getListaPersone()) {
        attuali.append(a);
    }
    for (const std::string& a : film->getAttoriPrincipali()){
        originali.append(QString::fromStdString(a));
    }
    
    QList<QString>attualiCopia = attuali;
    sort(attualiCopia.begin(), attualiCopia.end());
    sort(originali.begin(), originali.end());

    return attuali != originali;
}

bool EditMedia::isOspiteModified(Puntata* puntata){
    QList<QString> attuali;
    QList<QString> originali;

    for (const QString& o : ospitiPuntata->getListaPersone()) {
        attuali.append(o);
    }
    for (const std::string& o : puntata->getOspiti()){
        originali.append(QString::fromStdString(o));
    }
    
    QList<QString>attualiCopia = attuali;
    sort(attualiCopia.begin(), attualiCopia.end());
    sort(originali.begin(), originali.end());

    return attuali != originali;
}
 */