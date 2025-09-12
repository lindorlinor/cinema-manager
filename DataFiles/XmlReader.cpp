#include "XmlReader.h"
#include "../GUI/Custom/CustomMessageBox.h"
void XmlReader::populateCommonFields(const QDomElement &elem, Media *media){

    QDomElement lingElem = elem.firstChildElement("LingueDisponibili");
    QDomElement l = lingElem.firstChildElement("Lingua");
    while (!l.isNull())
    {
        media->aggiungiLingua(toLingua(l.text().toStdString()));
        l = l.nextSiblingElement("Lingua");
    }

    QDomElement subElem = elem.firstChildElement("SottotitoliDisponibili");
    l = subElem.firstChildElement("Lingua");
    while (!l.isNull())
    {
        media->aggiungiSottotitolo(toLingua(l.text().toStdString()));
        l = l.nextSiblingElement("Lingua");
    }
}

Film *XmlReader::fromXmlFilmElement(const QDomElement &elem){
    std::string titolo = elem.firstChildElement("Titolo").text().toStdString();
    std::string autore = elem.firstChildElement("Autore").text().toStdString();
    std::string descrizione = elem.firstChildElement("Descrizione").text().toStdString();
    int durata = elem.firstChildElement("DurataMinuti").text().toInt();
    Formato formato = toFormato(elem.firstChildElement("Formato").text().toStdString());
    Risoluzione ris = toRisoluzione(elem.firstChildElement("Risoluzione").text().toStdString());
    std::string path = elem.firstChildElement("Path").text().toStdString();

    year_month_day dI;
    year_month_day dF;
    try{
        dI = stringToDate(elem.firstChildElement("DataInizioRilascio").text().toStdString());
        dF = stringToDate(elem.firstChildElement("DataFineRilascio").text().toStdString());
    }catch (const std::exception &e){
        QString msg = QString("%1").arg(e.what());
        CustomMessageBox msgbox;
        msgbox.setTitleText("<span style='color: #E44043;'>Errore importazione di un media</span>");
        msgbox.setMainMessage("<span style='color: #E44043;'> Nel media dal titolo '" + QString::fromStdString(titolo) + "' è stato trovo il seguente errore: <br/><br/></span>" + QString("Errore importazione del media dal titolo %1: \n").arg(msg));
        msgbox.hideCancelButton();
        msgbox.exec();
        return nullptr;
    }

    Classificazione target = toClassificazione(elem.firstChildElement("Target").text().toStdString());
    double costoBiglietto = elem.firstChildElement("CostoBiglietto").text().toDouble();

    std::string casaDiProduzione = elem.firstChildElement("CasaDiProduzione").text().toStdString();
    int nPostCredit = elem.firstChildElement("NPostCredit").text().toInt();

    Film *media = new Film(titolo, descrizione, dI, dF, durata, formato, ris, nPostCredit, costoBiglietto, casaDiProduzione, autore, path, target);

    populateCommonFields(elem, media);

    QDomElement generiElem = elem.firstChildElement("Generi");
    for (QDomElement g = generiElem.firstChildElement("Genere"); !g.isNull(); g = g.nextSiblingElement("Genere")){
        media->aggiungiGenere((toGenere(g.text().toStdString())));
    }

    QDomElement attoriElem = elem.firstChildElement("AttoriPrincipali");
    for (QDomElement a = attoriElem.firstChildElement("Attore"); !a.isNull(); a = a.nextSiblingElement("Attore")){
        media->aggiungiAttore(a.text().toStdString());
    }
    return media;
}

Trailer *XmlReader::fromXmlTrailerElement(const QDomElement &elem, list<Media *> mediaList){
    std::string titolo = elem.firstChildElement("Titolo").text().toStdString();
    std::string autore = elem.firstChildElement("Autore").text().toStdString();
    std::string descrizione = elem.firstChildElement("Descrizione").text().toStdString();
    int durata = elem.firstChildElement("DurataMinuti").text().toInt();
    Formato formato = toFormato(elem.firstChildElement("Formato").text().toStdString());
    Risoluzione ris = toRisoluzione(elem.firstChildElement("Risoluzione").text().toStdString());
    std::string path = elem.firstChildElement("Path").text().toStdString();

    year_month_day dI;
    year_month_day dF;
    try{
        dI = stringToDate(elem.firstChildElement("DataInizioRilascio").text().toStdString());
        dF = stringToDate(elem.firstChildElement("DataFineRilascio").text().toStdString());
    }catch (const std::exception &e){
        QString msg = QString("%1").arg(e.what());
        CustomMessageBox msgbox;
        msgbox.setTitleText("<span style='color: #E44043;'>Errore importazione di un media</span>");
        msgbox.setMainMessage("<span style='color: #E44043;'> Nel media dal titolo '" + QString::fromStdString(titolo) + "' è stato trovo il seguente errore: <br/><br/></span>" + QString("Errore importazione del media dal titolo %1: \n").arg(msg));
        msgbox.hideCancelButton();
        msgbox.exec();
        return nullptr;
    }

    QDomElement nProiezioniElem = elem.firstChildElement("NProiezioniGiornaliere");
    int nProiezioniGiornaliere;
    if (!nProiezioniElem.isNull()){
        nProiezioniGiornaliere = nProiezioniElem.text().toInt();
    }

    QDomElement filmElem = elem.firstChildElement("TitoloFilmAssociato");
    QDomElement autoreElem = elem.firstChildElement("AutoreFilmAssociato");
    string titoloFilmA;
    string autoreFilmA;
    if (!autoreElem.isNull() && !filmElem.isNull()){
        titoloFilmA = filmElem.text().toStdString();
        autoreFilmA = autoreElem.text().toStdString();
    }
    Film *filmA = findFilmInList(mediaList, titoloFilmA, autoreFilmA);
    if (filmA){
        Trailer *media = new Trailer(titolo, descrizione, dI, dF, durata, formato, ris, nProiezioniGiornaliere, filmA, autore, path);
        populateCommonFields(elem, media);
        return media;
    }

    CustomMessageBox msgbox;
    msgbox.setTitleText("<span style='color: #E44043;'>Errore importazione di un media</span>");
    msgbox.setMainMessage("<span style='color: #E44043;'> Il media dal titolo '" + QString::fromStdString(titolo) + "' non è stato associato correttamente ad alcun film.</span>");
    msgbox.hideCancelButton();
    msgbox.exec();
    return nullptr;
}

Inserzione *XmlReader::fromXmlInserzioneElement(const QDomElement &elem)
{

    std::string titolo = elem.firstChildElement("Titolo").text().toStdString();
    std::string autore = elem.firstChildElement("Autore").text().toStdString();
    std::string descrizione = elem.firstChildElement("Descrizione").text().toStdString();
    int durata = elem.firstChildElement("DurataMinuti").text().toInt();
    Formato formato = toFormato(elem.firstChildElement("Formato").text().toStdString());
    Risoluzione ris = toRisoluzione(elem.firstChildElement("Risoluzione").text().toStdString());
    std::string path = elem.firstChildElement("Path").text().toStdString();

    year_month_day dI;
    year_month_day dF;
    try{
        dI = stringToDate(elem.firstChildElement("DataInizioRilascio").text().toStdString());
        dF = stringToDate(elem.firstChildElement("DataFineRilascio").text().toStdString());
    }
    catch (const std::exception &e){
        QString msg = QString("%1").arg(e.what());
        CustomMessageBox msgbox;
        msgbox.setTitleText("<span style='color: #E44043;'>Errore importazione di un media</span>");
        msgbox.setMainMessage("<span style='color: #E44043;'> Nel media dal titolo '" + QString::fromStdString(titolo) + "' è stato trovo il seguente errore: <br/><br/></span>" + QString("Errore importazione del media dal titolo %1: \n").arg(msg));
        msgbox.hideCancelButton();
        msgbox.exec();
        return nullptr;
    }

    QDomElement nProiezioniElem = elem.firstChildElement("NProiezioniGiornaliere");
    int nProiezioniGiornaliere;
    if (!nProiezioniElem.isNull())
        nProiezioniGiornaliere = nProiezioniElem.text().toInt();
    

    Classificazione target = toClassificazione(elem.firstChildElement("Target").text().toStdString());

    QDomElement costoElem = elem.firstChildElement("CostoFissoProiezione");
    double costoFissoProiezione;
    if (!costoElem.isNull())
        costoFissoProiezione = costoElem.text().toDouble();
    

    QDomElement aziendaElem = elem.firstChildElement("AziendaInserzionistica");
    string aziendaI;
    if (!aziendaElem.isNull())
        aziendaI = aziendaElem.text().toStdString();
    

    Inserzione *media = new Inserzione(titolo, descrizione, dI, dF, durata, formato, ris, nProiezioniGiornaliere, target, costoFissoProiezione, aziendaI, autore, path);
    populateCommonFields(elem, media);

    QDomElement fasceOrarieEleme = elem.firstChildElement("FasceOrarie");
    QDomElement f = fasceOrarieEleme.firstChildElement("Fascia");
    while (!f.isNull()){
        media->aggiungiFasciaOraria(toFasciaOraria(f.text().toStdString()));
        f = f.nextSiblingElement("Fascia");
    }
    

    QDomElement targetElem = elem.firstChildElement("Target");
    if (!targetElem.isNull())
        media->setTarget(toClassificazione(targetElem.text().toStdString()));
    

    return media;
}

Podcast *XmlReader::fromXmlPodcastElement(const QDomElement &elem){

    std::string titolo = elem.firstChildElement("Titolo").text().toStdString();
    std::string autore = elem.firstChildElement("Autore").text().toStdString();
    std::string descrizione = elem.firstChildElement("Descrizione").text().toStdString();
    Formato formato = toFormato(elem.firstChildElement("Formato").text().toStdString());
    Risoluzione ris = toRisoluzione(elem.firstChildElement("Risoluzione").text().toStdString());
    std::string path = elem.firstChildElement("Path").text().toStdString();

    QDomElement conduttoreElem = elem.firstChildElement("Conduttore");
    string conduttore;
    if (!conduttoreElem.isNull())
    {
        conduttore = conduttoreElem.text().toStdString();
    }
    Podcast *media = new Podcast(titolo, descrizione, formato, ris, autore, path, conduttore);
    return media;
}

Puntata *XmlReader::fromXmlPuntataElement(const QDomElement &elem, list<Media *> mediaList){
    std::string titolo = elem.firstChildElement("Titolo").text().toStdString();
    std::string autore = elem.firstChildElement("Autore").text().toStdString();
    std::string descrizione = elem.firstChildElement("Descrizione").text().toStdString();
    int durata = elem.firstChildElement("DurataMinuti").text().toInt();
    std::string path = elem.firstChildElement("Path").text().toStdString();

    year_month_day dI;
    year_month_day dF;
    try{
        dI = stringToDate(elem.firstChildElement("DataInizioRilascio").text().toStdString());
        dF = stringToDate(elem.firstChildElement("DataFineRilascio").text().toStdString());
    }catch (const std::exception &e){
        QString msg = QString("%1").arg(e.what());
        CustomMessageBox msgbox;
        msgbox.setTitleText("<span style='color: #E44043;'>Errore importazione di un media</span>");
        msgbox.setMainMessage("<span style='color: #E44043;'> Nel media dal titolo '" + QString::fromStdString(titolo) + "' è stato trovo il seguente errore: <br/><br/></span>" + QString("Errore importazione del media dal titolo %1: \n").arg(msg));
        msgbox.hideCancelButton();
        msgbox.exec();
        return nullptr;
    }

    QDomElement podcastElem = elem.firstChildElement("TitoloPodcastAssociato");
    QDomElement autoreElem = elem.firstChildElement("AutorePodcastAssociato");
    string titoloPodA;
    string autorePodA;
    if (!podcastElem.isNull() && !autoreElem.isNull()){
        titoloPodA = podcastElem.text().toStdString();
        autorePodA = autoreElem.text().toStdString();
    }

    QDomElement numPubElem = elem.firstChildElement("NPubblicita");
    int nPubblicita = 0;
    if (!numPubElem.isNull()){
        nPubblicita = numPubElem.text().trimmed().toInt();
    }

    Podcast *podA = findPodcastInList(mediaList, titoloPodA, autorePodA);
    if (podA){
        Puntata *media = new Puntata(titolo, descrizione, dI, dF, durata, podA, nPubblicita, autore, path);
        populateCommonFields(elem, media);
        QDomElement ospitiElem = elem.firstChildElement("Ospiti");
        for (QDomElement o = ospitiElem.firstChildElement("Ospite"); !o.isNull(); o = o.nextSiblingElement("Ospite")){
            media->aggiungiOspite(o.text().toStdString());
        }
        return media;
    }

    CustomMessageBox msgbox;
    msgbox.setTitleText("<span style='color: #E44043;'>Errore importazione di un media</span>");
    msgbox.setMainMessage("<span style='color: #E44043;'> Il media dal titolo '" + QString::fromStdString(titolo) + "' non è stato associato correttamente ad alcun podcast.</span>");
    msgbox.hideCancelButton();
    msgbox.exec();
    return nullptr;
}

Film *XmlReader::findFilmInList(const list<Media *> &mediaList, const string &titolo, const string &autore){
    for (Media *m : mediaList){
        Film *f = dynamic_cast<Film *>(m);
        if (f && f->getTitolo() == titolo && f->getAutore() == autore)
            return f;
        
    }
    return nullptr; // non trovato
}

Podcast *XmlReader::findPodcastInList(const list<Media *> &mediaList, const string &titolo, const string &autore){
    for (Media *m : mediaList){
        Podcast *p = dynamic_cast<Podcast *>(m);
        if (p && p->getTitolo() == titolo && p->getAutore() == autore)
            return p;
    }
    return nullptr; // non trovato
}
