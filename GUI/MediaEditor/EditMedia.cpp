#include "EditMedia.h"

EditMedia::EditMedia(QList<Media *> &mediaList, Media *media, QWidget *parent) : MediaInterface(mediaList, parent), em_media(media)
{

    initUI();

    titolo->setText("Modifica l'elemento " + QString::fromStdString(media->getTitolo()));

    // ottengo l0indice corretto per la staktipologia
    if (dynamic_cast<Film *>(media))
        index = 0;
    if (dynamic_cast<Trailer *>(media))
        index = 1;
    if (dynamic_cast<Podcast *>(media))
        index = 2;
    if (dynamic_cast<Puntata *>(media))
        index = 3;
    if (dynamic_cast<Inserzione *>(media))
        index = 4;

    setLimitTabTipologia(index);

    connect(referencePuntate, &SelectMediaReference::mediaSelected, this, [this]()
            { referencePuntate->setSelectedItem("", ""); });
    connect(referenceTrailer, &SelectMediaReference::mediaSelected, this, [this]()
            { referencePuntate->setSelectedItem("", ""); });

    connect(indietro, &QPushButton::clicked, this, [this]()
            { emit tornaIndietro(); });

    connect(cancelButton, &QPushButton::clicked, this, [this]()
            { emit tornaIndietro(); });

    connect(saveButton, &QPushButton::clicked, this, [this]()
            {
        salvaMedia();
        emit tornaIndietro(); });
}

void EditMedia::initValue()
{

    // valori comuni
    QList<QString> lingue;
    for (Lingua l : em_media->getLingue())
    {
        lingue.append(toString(l));
    }

    QList<QString> sottotitoli;
    for (Lingua s : em_media->getSottotitoli())
    {
        sottotitoli.append(toString(s));
    }

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

    dataInizio->setDate(convertToQDate(em_media->getDataInizioRilascio()));
    dataFine->setDate(convertToQDate(em_media->getDataFineRilascio()));

    QPixmap pixmap(imagePath);
    copertina->setPixmap(pixmap.scaled(280, 330, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // valori per tipologia
    if (index == 0)
    {
        Film *film = static_cast<Film *>(em_media);

        CasaProdFilm->setText(QString::fromStdString(film->getCasaDiProduzione()));

        QList<QString> risultato;
        QList<QString> generi;
        for (const string &s : film->getAttoriPrincipali())
        {
            risultato.append(QString::fromStdString(s));
        }
        for (Genere g : film->getGeneri())
        {
            generi.append(toString(g));
        }

        setCheckListWidget(listGeneri, generi);

        attoriFilm->setItems(risultato);
        totPostCreditFilm->setValue(film->getNPostCredit());
        costoBigliettoFilm->setValue(film->getCostoBiglietto());
        comboTargetFilm->setCurrentText(toString(film->getTarget()));
    }
    else if (index == 1)
    {
        Trailer *trailer = static_cast<Trailer *>(em_media);
        referenceTrailer->setSelectedItem(QString::fromStdString(trailer->getFilm()->getTitolo()), QString::fromStdString(trailer->getFilm()->getAutore()));
        titoloFilmRiferimento = QString::fromStdString(trailer->getFilm()->getTitolo());
        autoreFilmRiferimento = QString::fromStdString(trailer->getFilm()->getAutore());
        if (referenceTrailer)
            referenceTrailer->reloadMedia(*im_cinemaSelezionato);
        numeroProiezioniTrailer->setValue(trailer->getDurataMinuti());
    }
    else if (index == 2)
    {
        Podcast *podcast = static_cast<Podcast *>(em_media);

        conduttorePodcast->setText(QString::fromStdString(podcast->getConduttore()));
    }
    else if (index == 3)
    {
        Puntata *puntata = static_cast<Puntata *>(em_media);
        referencePuntate->setSelectedItem(QString::fromStdString(puntata->getPodcast()->getTitolo()), QString::fromStdString(puntata->getPodcast()->getAutore()));
        titoloPodcastRiferimento = QString::fromStdString(puntata->getPodcast()->getAutore());
        autorePodcastRiferimento = QString::fromStdString(puntata->getPodcast()->getTitolo());
        if (referencePuntate)
            referencePuntate->reloadMedia(*im_cinemaSelezionato);
        QList<QString> risultato;
        for (const string &s : puntata->getOspiti())
        {
            risultato.append(QString::fromStdString(s));
        }
        ospitiPuntata->setItems(risultato);
        numeroPubblicitaPuntata->setValue(puntata->getNumeroPubblicita());
    }
    else if (index == 4)
    {
        Inserzione *inserzione = static_cast<Inserzione *>(em_media);
        aziendaInserzInserzione->setText(QString::fromStdString(inserzione->getAziendaInserzionistica()));
        numeroProiezioniGioInserzione->setValue(inserzione->getNProiezioniGiornaliere());
        costoBaseProiezInserzione->setValue(inserzione->getCostoFissoProiezione());

        QList<QString> fasce_orarie;
        for (FasciaOraria f : inserzione->getFasceOrarie())
        {
            fasce_orarie.append(toString(f));
        }
        setCheckListWidget(listFasceOrarie, fasce_orarie);
        comboTargetInserzioni->setCurrentText(toString(inserzione->getTarget()));
    }
}

// metodi funzionali per il corretto comportamento della pagina

// TO DO: quando funzionerà tutto, provo a spostare il comportamento comune nella base MediInterface
void EditMedia::setLimitTabTipologia(int i)
{

    stackTipologia->setCurrentIndex(i);
    comboTipologia->setCurrentIndex(i);
    comboTipologia->setEnabled(false);

    bool puntata = (i == 3);
    comboFormato->setEnabled(!puntata);
    comboRisoluzione->setEnabled(!puntata);
    if (puntata)
    {
        comboFormato->setCurrentIndex(0);
        comboRisoluzione->setCurrentIndex(0);
    }

    MediaInterface::setLimitTabTipologia(i);

    checkMediaNameAvailability();
}

void EditMedia::setCheckListWidget(QListWidget *list, const QList<QString> &select)
{
    for (int i = 0; i < list->count(); ++i)
    {
        QListWidgetItem *item = list->item(i);
        bool presente = select.contains(item->text());
        item->setCheckState(presente ? Qt::Checked : Qt::Unchecked);
    }
}

// salvare le modifiche agli oggetti

void EditMedia::salvaMedia()
{

    QString default_image;
    if (stackTipologia->currentIndex() == 0)
        default_image = ":/images/default_film.png";
    else if (stackTipologia->currentIndex() == 1)
        default_image = ":/images/default_trailer.png";
    else if (stackTipologia->currentIndex() == 2)
        default_image = ":/images/default_podcast_puntate.png";
    else if (stackTipologia->currentIndex() == 3)
        default_image = ":/images/default_puntata.png";
    else if (stackTipologia->currentIndex() == 4)
        default_image = ":/images/default_inserzioni.png";

    em_media->setAutore(autoreMedia->text().toStdString());
    em_media->setTitolo(titoloMedia->text().toStdString());
    em_media->setDescrizione(descrizioneMedia->toPlainText().toStdString());
    em_media->setDataInizioRilascio(convertDate(dataInizio->date()));
    em_media->setDataFineRilascio(convertDate(dataFine->date()));
    em_media->setDurataMinuti(durataMinutiMedia->value());
    em_media->setFormato(toFormato(comboFormato->currentText().toStdString()));
    em_media->setRisoluzione(toRisoluzione(comboRisoluzione->currentText().toStdString()));
    em_media->setPath(imagePath == "" ? default_image.toStdString() : imagePath.toStdString());

    for (const Lingua &l : em_media->getLingue())
        em_media->rimuoviLingua(l);

    if (!(getSelectedList(listLingue)).empty())
        addLingue(em_media);

    for (const Lingua &s : em_media->getSottotitoli())
        em_media->rimuoviSottotitolo(s);

    if (!(getSelectedList(listSottotitoli)).empty())
        addSottotitoli(em_media);

    if (stackTipologia->currentIndex() == 0)
    {

        Film *film = static_cast<Film *>(em_media);

        film->setCasaDiProduzione(CasaProdFilm->text().trimmed().toStdString());
        film->setNPostCredit(totPostCreditFilm->value());
        film->setCostoBiglietto(costoBigliettoFilm->value());
        film->setTarget(toClassificazione(comboTargetFilm->currentText().toStdString()));

        if (!(getSelectedList(listGeneri)).empty())
        {
            for (const Genere &g : film->getGeneri())
                film->rimuoviGenere(g);
            addGeneri(film);
        }

        while (!film->getAttoriPrincipali().empty())
        {
            film->rimuoviAttore(film->getAttoriPrincipali().front());
        }
        addAttore(film);
    }

    // trailer
    else if (stackTipologia->currentIndex() == 1)
    {

        Media *filmAssociato = findMediaReference(titoloFilmRiferimento, autoreFilmRiferimento, "trailer");

        if (!filmAssociato)
        {
            qDebug() << "Errore!, nessun Film collegato al Trailer " << titoloMedia->text();
            return;
        }

        Trailer *trailer = static_cast<Trailer *>(em_media);
        trailer->setNProiezioniGiornaliere(numeroProiezioniTrailer->value());

        if (titoloFilmRiferimento != QString::fromStdString(trailer->getFilm()->getTitolo()) ||
            autoreFilmRiferimento != QString::fromStdString(trailer->getFilm()->getAutore()))
        {
            trailer->associaFilm(static_cast<Film *>(filmAssociato));
        }
    }
    // podcast
    else if (stackTipologia->currentIndex() == 2)
    {
        Podcast *podcast = static_cast<Podcast *>(em_media);
        podcast->setConduttore(conduttorePodcast->text().toStdString());
    }
    // puntata
    else if (stackTipologia->currentIndex() == 3)
    {

        Media *PodcastAssociato = findMediaReference(titoloPodcastRiferimento, autorePodcastRiferimento, "puntata");

        if (!PodcastAssociato)
        {
            qDebug() << "Errore!, nessun Podcast collegato al Trailer " << titoloMedia->text();
            return;
        }

        Puntata *puntata = static_cast<Puntata *>(em_media);

        puntata->setNumeroPubblicita(numeroPubblicitaPuntata->value());
        if (titoloPodcastRiferimento != QString::fromStdString(puntata->getPodcast()->getTitolo()) ||
            autorePodcastRiferimento != QString::fromStdString(puntata->getPodcast()->getAutore()))
        {
            puntata->associaPodcast(static_cast<Podcast *>(PodcastAssociato));
        }

        while (!puntata->getOspiti().empty())
        {
            puntata->rimuoviOspite(puntata->getOspiti().front());
        }
        addOspite(puntata);
    }
    // inserzione
    else if (stackTipologia->currentIndex() == 4)
    {

        Inserzione *inserzione = static_cast<Inserzione *>(em_media);

        inserzione->setNProiezioniGiornaliere(numeroProiezioniGioInserzione->value());
        inserzione->setCostoFissoProiezione(costoBaseProiezInserzione->value());
        inserzione->setTarget(toClassificazione(comboTargetInserzioni->currentText().toStdString()));
        inserzione->setAziendaInserzionistica(aziendaInserzInserzione->text().toStdString());
    }

    cinemaManager->updateMediaInJson(im_cinemaSelezionato);
    emit savedMedia();
}

void EditMedia::checkMediaNameAvailability()
{
    QString titolo = titoloMedia->text().trimmed();
    QString autore = autoreMedia->text().trimmed();

    bool isAvailable = true;
    errorLabel->setVisible(false);

    setLimitTrailer();

    if (titolo.isEmpty() || autore.isEmpty())
        isAvailable = false;

    for (const Media *m : im_mediaList)
    {
        if (QString::fromStdString(m->getTitolo()).compare(titolo, Qt::CaseInsensitive) == 0 && QString::fromStdString(m->getAutore()).compare(autore, Qt::CaseInsensitive) == 0)
        {
            isAvailable = false;
        }
    }

    if (QString::fromStdString(em_media->getTitolo()).compare(titolo, Qt::CaseInsensitive) == 0 && QString::fromStdString(em_media->getAutore()).compare(autore, Qt::CaseInsensitive) == 0 && !isAvailable)
        isAvailable = true;

    if (!isAvailable)
    {
        if (!titolo.isEmpty() && !autore.isEmpty())
        {
            errorLabel->setText("Titolo già presente per questo autore");
            errorLabel->setVisible(true);
        }
        saveButton->setEnabled(false); // disabilita bottone
    }
    else if ((comboTipologia->currentIndex() == 1 && autoreFilmRiferimento != "" && titoloFilmRiferimento != "") ||
             (comboTipologia->currentIndex() == 3 && autorePodcastRiferimento != "" && titoloPodcastRiferimento != "") ||
             (comboTipologia->currentIndex() != 3 && comboTipologia->currentIndex() != 1))
    {
        errorLabel->setVisible(false);
        saveButton->setEnabled(true);
    }
    else
    {
        errorLabel->setVisible(false);
        saveButton->setEnabled(true);
    }
}
