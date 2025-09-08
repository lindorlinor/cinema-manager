#include "XmlVisitor.h"
#include <QDomDocument>
#include <QDomElement>
#include <QDomText>
#include <iostream>
#include <QDebug>
#include <qmessagebox.h>
#include "../GUI/CustomMessageBox.h"

XmlVisitor::XmlVisitor(QDomDocument *d) : doc(d) {}
QDomElement XmlVisitor::getXmlElement() const
{
    return xmlElement;
}
QDomElement XmlVisitor::populateCommonFields(const Media *media)
{
    QDomElement mediaElem = doc->createElement("MediaFields");

    QDomElement elem = doc->createElement("Titolo");
    elem.appendChild(doc->createTextNode(QString::fromStdString(media->getTitolo())));
    mediaElem.appendChild(elem);

    elem = doc->createElement("Autore");
    elem.appendChild(doc->createTextNode(QString::fromStdString(media->getAutore())));
    mediaElem.appendChild(elem);

    elem = doc->createElement("Descrizione");
    elem.appendChild(doc->createTextNode(QString::fromStdString(media->getDescrizione())));
    mediaElem.appendChild(elem);

    elem = doc->createElement("DurataMinuti");
    elem.appendChild(doc->createTextNode(QString::number(media->getDurataMinuti())));
    mediaElem.appendChild(elem);

    elem = doc->createElement("Formato");
    elem.appendChild(doc->createTextNode(toString(media->getFormato())));
    mediaElem.appendChild(elem);

    elem = doc->createElement("Risoluzione");
    elem.appendChild(doc->createTextNode(toString(media->getRisoluzione())));
    mediaElem.appendChild(elem);

    elem = doc->createElement("Path");
    elem.appendChild(doc->createTextNode(QString::fromStdString(media->getImPath())));
    mediaElem.appendChild(elem);

    elem = doc->createElement("DataInizioRilascio");
    elem.appendChild(doc->createTextNode(QString::fromStdString(dateToString(media->getDataInizioRilascio()))));
    mediaElem.appendChild(elem);

    elem = doc->createElement("DataFineRilascio");
    elem.appendChild(doc->createTextNode(QString::fromStdString(dateToString(media->getDataFineRilascio()))));
    mediaElem.appendChild(elem);

    QDomElement lingueElem = doc->createElement("LingueDisponibili");
    for (const Lingua &l : media->getLingue())
    {

        QDomElement lElem = doc->createElement("Lingua");
        lElem.appendChild(doc->createTextNode(toString(l)));
        lingueElem.appendChild(lElem);
    }
    mediaElem.appendChild(lingueElem);

    QDomElement subElem = doc->createElement("SottotitoliDisponibili");
    for (const Lingua &l : media->getSottotitoli())
    {
        QDomElement lElem = doc->createElement("Lingua");
        lElem.appendChild(doc->createTextNode(toString(l)));
        subElem.appendChild(lElem);
    }
    mediaElem.appendChild(subElem);

    return mediaElem;
}

void XmlVisitor::visit(Film *film)
{

    QDomElement filmElem = doc->createElement("Film");

    QDomElement commonMediaFields = populateCommonFields(film);
    QDomNode child = commonMediaFields.firstChild();
    while (!child.isNull())
    {
        filmElem.appendChild(child.cloneNode()); // clone necessario perchè i nodi di commonMediaFields hanno già genitore
        child = child.nextSibling();
    }

    QDomElement genElem = doc->createElement("Generi");
    for (const Genere &g : film->getGeneri())
    {
        QDomElement gElem = doc->createElement("Genere");
        gElem.appendChild(doc->createTextNode(toString(g)));
        genElem.appendChild(gElem);
    }
    filmElem.appendChild(genElem);

    QDomElement attoriElem = doc->createElement("AttoriPrincipali");
    for (const string &attore : film->getAttoriPrincipali())
    {
        QDomElement aElem = doc->createElement("Attore");
        aElem.appendChild(doc->createTextNode(QString::fromStdString(attore)));
        attoriElem.appendChild(aElem);
    }
    filmElem.appendChild(attoriElem);

    QDomElement targetElem = doc->createElement("Target");
    targetElem.appendChild(doc->createTextNode(toString(film->getTarget())));
    filmElem.appendChild(targetElem);

    QDomElement costoElem = doc->createElement("CostoBiglietto");
    costoElem.appendChild(doc->createTextNode(QString::number(film->getCostoBiglietto())));
    filmElem.appendChild(costoElem);

    QDomElement casaElem = doc->createElement("CasaDiProduzione");
    casaElem.appendChild(doc->createTextNode(QString::fromStdString(film->getCasaDiProduzione())));
    filmElem.appendChild(casaElem);

    QDomElement postElem = doc->createElement("NPostCredit");
    postElem.appendChild(doc->createTextNode(QString::number(film->getNPostCredit())));
    filmElem.appendChild(postElem);

    xmlElement = filmElem;
}

void XmlVisitor::visit(Trailer *trailer)
{

    QDomElement trailerElem = doc->createElement("Trailer");

    QDomElement commonMediaFields = populateCommonFields(trailer);

    QDomNode child = commonMediaFields.firstChild();
    while (!child.isNull())
    {
        trailerElem.appendChild(child.cloneNode());
        child = child.nextSibling();
    }

    QDomElement nProiezElem = doc->createElement("NProiezioniGiornaliere");
    nProiezElem.appendChild(doc->createTextNode(QString::number(trailer->getNProiezioniGiornaliere())));
    trailerElem.appendChild(nProiezElem);

    QDomElement tFilmAssElem = doc->createElement("TitoloFilmAssociato");
    tFilmAssElem.appendChild(doc->createTextNode(QString::fromStdString(trailer->getFilm()->getTitolo())));
    trailerElem.appendChild(tFilmAssElem);

    QDomElement aFilmAssElem = doc->createElement("AutoreFilmAssociato");
    aFilmAssElem.appendChild(doc->createTextNode(QString::fromStdString(trailer->getFilm()->getAutore())));
    trailerElem.appendChild(aFilmAssElem);

    xmlElement = trailerElem;
}
void XmlVisitor::visit(Inserzione *inserzione)
{

    QDomElement insElem = doc->createElement("Inserzione");

    QDomElement commonMediaFields = populateCommonFields(inserzione);
    QDomNode child = commonMediaFields.firstChild();
    while (!child.isNull())
    {
        insElem.appendChild(child.cloneNode());
        child = child.nextSibling();
    }

    QDomElement nProiezElem = doc->createElement("NProiezioniGiornaliere");
    nProiezElem.appendChild(doc->createTextNode(QString::number(inserzione->getNProiezioniGiornaliere())));
    insElem.appendChild(nProiezElem);

    QDomElement fasceOrarieElem = doc->createElement("FasceOrarie");
    for (const FasciaOraria &fo : inserzione->getFasceOrarie())
    {
        QDomElement fasciaElem = doc->createElement("Fascia");
        fasciaElem.appendChild(doc->createTextNode(toString(fo)));
        fasceOrarieElem.appendChild(fasciaElem);
    }
    insElem.appendChild(fasceOrarieElem);

    QDomElement targetElem = doc->createElement("Target");
    targetElem.appendChild(doc->createTextNode(QString::fromStdString(toString(inserzione->getTarget()))));
    insElem.appendChild(targetElem);

    QDomElement aziendaElem = doc->createElement("AziendaInserzionista");
    aziendaElem.appendChild(doc->createTextNode(QString::fromStdString(inserzione->getAziendaInserzionistica())));
    insElem.appendChild(aziendaElem);

    QDomElement costoElem = doc->createElement("CostoFissoProiezione");
    costoElem.appendChild(doc->createTextNode(QString::number(inserzione->getCostoFissoProiezione())));
    insElem.appendChild(costoElem);

    xmlElement = insElem;
}
void XmlVisitor::visit(Podcast *podcast)
{

    QDomElement podElem = doc->createElement("Podcast");

    QDomElement commonMediaFields = populateCommonFields(podcast);
    QDomNode child = commonMediaFields.firstChild();
    while (!child.isNull())
    {
        podElem.appendChild(child.cloneNode());
        child = child.nextSibling();
    }

    QDomElement conduttElem = doc->createElement("Conduttore");
    conduttElem.appendChild(doc->createTextNode(QString::fromStdString(podcast->getConduttore())));
    podElem.appendChild(conduttElem);

    xmlElement = podElem;
}

void XmlVisitor::visit(Puntata *puntata)
{

    QDomElement puntElem = doc->createElement("Puntata");

    QDomElement commonMediaFields = populateCommonFields(puntata);
    QDomNode child = commonMediaFields.firstChild();
    while (!child.isNull())
    {
        puntElem.appendChild(child.cloneNode());
        child = child.nextSibling();
    }

    QDomElement tPodElem = doc->createElement("TitoloPodcastAssociato");
    tPodElem.appendChild(doc->createTextNode(QString::fromStdString((puntata->getPodcast())->getTitolo())));
    puntElem.appendChild(tPodElem);

    QDomElement aPodElem = doc->createElement("AutorePodcastAssociato");
    aPodElem.appendChild(doc->createTextNode(QString::fromStdString((puntata->getPodcast())->getAutore())));
    puntElem.appendChild(aPodElem);

    QDomElement nPubbElem = doc->createElement("NPubblicita");
    nPubbElem.appendChild(doc->createTextNode(QString::number(puntata->getNumeroPubblicita())));
    puntElem.appendChild(nPubbElem);

    xmlElement = puntElem;
}
void XmlVisitor::populateCommonFields(const QDomElement &elem, Media *media)
{

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

Film *XmlVisitor::fromXmlFilmElement(const QDomElement &elem)
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
    }catch (const std::exception &e){
        QString msg = QString("%1").arg(e.what());
        CustomMessageBox msgbox;
        msgbox.setTitleText("<span style='color: #E44043;'>Errore importazione di un media</span>");
        msgbox.setMainMessage("<span style='color: #E44043;'> Nel media dal titolo '"+ QString::fromStdString(titolo)+"' è stato trovo il seguente errore: <br/><br/></span>"+ QString("Errore importazione del media dal titolo %1: \n").arg(msg));
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
    for (QDomElement g = generiElem.firstChildElement("Genere"); !g.isNull(); g = g.nextSiblingElement("Genere"))
    {
        media->aggiungiGenere((toGenere(g.text().toStdString())));
    }

    QDomElement attoriElem = elem.firstChildElement("AttoriPrincipali");
    for (QDomElement a = attoriElem.firstChildElement("Attore"); !a.isNull(); a = a.nextSiblingElement("Attore"))
    {
        media->aggiungiAttore(a.text().toStdString());
    }
    return media;
}

Trailer *XmlVisitor::fromXmlTrailerElement(const QDomElement &elem, list<Media *> mediaList)
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
    }catch (const std::exception &e){
        QString msg = QString("%1").arg(e.what());
        CustomMessageBox msgbox;
        msgbox.setTitleText("<span style='color: #E44043;'>Errore importazione di un media</span>");
        msgbox.setMainMessage("<span style='color: #E44043;'> Nel media dal titolo '"+ QString::fromStdString(titolo)+"' è stato trovo il seguente errore: <br/><br/></span>"+ QString("Errore importazione del media dal titolo %1: \n").arg(msg));
        msgbox.hideCancelButton();
        msgbox.exec();
        return nullptr;
    }

    QDomElement nProiezioniElem = elem.firstChildElement("NProiezioniGiornaliere");
    int nProiezioniGiornaliere;
    if (!nProiezioniElem.isNull())
    {
        nProiezioniGiornaliere = nProiezioniElem.text().toInt();
    }

    QDomElement filmElem = elem.firstChildElement("TitoloFilmAssociato");
    QDomElement autoreElem = elem.firstChildElement("AutoreFilmAssociato");
    string titoloFilmA;
    string autoreFilmA;
    if (!autoreElem.isNull() && !filmElem.isNull())
    {
        titoloFilmA = filmElem.text().toStdString();
        autoreFilmA = autoreElem.text().toStdString();
    }
    Film *filmA = findFilmInList(mediaList, titoloFilmA, autoreFilmA);
    if (filmA)
    {
        Trailer *media = new Trailer(titolo, descrizione, dI, dF, durata, formato, ris, nProiezioniGiornaliere, filmA, autore, path);
        populateCommonFields(elem, media);
        return media;
    }
    
    CustomMessageBox msgbox;
    msgbox.setTitleText("<span style='color: #E44043;'>Errore importazione di un media</span>");
    msgbox.setMainMessage("<span style='color: #E44043;'> Il media dal titolo '"+ QString::fromStdString(titolo)+"' non è stato associato correttamente ad alcun film.</span>");
    msgbox.hideCancelButton();
    msgbox.exec();
    return nullptr;
}

Inserzione *XmlVisitor::fromXmlInserzioneElement(const QDomElement &elem)
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
    }catch (const std::exception &e){
        QString msg = QString("%1").arg(e.what());
        CustomMessageBox msgbox;
        msgbox.setTitleText("<span style='color: #E44043;'>Errore importazione di un media</span>");
        msgbox.setMainMessage("<span style='color: #E44043;'> Nel media dal titolo '"+ QString::fromStdString(titolo)+"' è stato trovo il seguente errore: <br/><br/></span>"+ QString("Errore importazione del media dal titolo %1: \n").arg(msg));
        msgbox.hideCancelButton();
        msgbox.exec();
        return nullptr;
    }

    QDomElement nProiezioniElem = elem.firstChildElement("NProiezioniGiornaliere");
    int nProiezioniGiornaliere;
    if (!nProiezioniElem.isNull())
    {
        nProiezioniGiornaliere = nProiezioniElem.text().toInt();
    }

    Classificazione target = toClassificazione(elem.firstChildElement("Target").text().toStdString());

    QDomElement costoElem = elem.firstChildElement("CostoFissoProiezione");
    double costoFissoProiezione;
    if (!costoElem.isNull())
    {
        costoFissoProiezione = costoElem.text().toDouble();
    }

    QDomElement aziendaElem = elem.firstChildElement("AziendaInserzionistica");
    string aziendaI;
    if (!aziendaElem.isNull())
    {
        aziendaI = aziendaElem.text().toStdString();
    }

    Inserzione *media = new Inserzione(titolo, descrizione, dI, dF, durata, formato, ris, nProiezioniGiornaliere, target, costoFissoProiezione, aziendaI, autore, path);
    populateCommonFields(elem, media);

    QDomElement fasceOrarieEleme = elem.firstChildElement("FasceOrarie");
    QDomElement f = fasceOrarieEleme.firstChildElement("Fascia");
    while (!f.isNull())
    {
        media->aggiungiFasciaOraria(toFasciaOraria(f.text().toStdString()));
        f = f.nextSiblingElement("Fascia");
    }

    QDomElement targetElem = elem.firstChildElement("Target");
    if (!targetElem.isNull())
    {
        media->setTarget(toClassificazione(targetElem.text().toStdString()));
    }

    return media;
}

Podcast *XmlVisitor::fromXmlPodcastElement(const QDomElement &elem)
{

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

Puntata *XmlVisitor::fromXmlPuntataElement(const QDomElement &elem, list<Media *> mediaList)
{
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
        msgbox.setMainMessage("<span style='color: #E44043;'> Nel media dal titolo '"+ QString::fromStdString(titolo)+"' è stato trovo il seguente errore: <br/><br/></span>"+ QString("Errore importazione del media dal titolo %1: \n").arg(msg));
        msgbox.hideCancelButton();
        msgbox.exec();
        return nullptr;
    }

    QDomElement podcastElem = elem.firstChildElement("TitoloPodcastAssociato");
    QDomElement autoreElem = elem.firstChildElement("AutorePodcastAssociato");
    string titoloPodA;
    string autorePodA;
    if (!podcastElem.isNull() && !autoreElem.isNull())
    {
        titoloPodA = podcastElem.text().toStdString();
        autorePodA = autoreElem.text().toStdString();
    }

    QDomElement numPubElem = elem.firstChildElement("NPubblicita");
    int nPubblicita = 0;
    if (!numPubElem.isNull())
    {
        nPubblicita = numPubElem.text().trimmed().toInt();
    }

    Podcast *podA = findPodcastInList(mediaList, titoloPodA, autorePodA);
    if (podA){
        Puntata * media = new Puntata(titolo, descrizione, dI, dF, durata, podA , nPubblicita, autore, path);
        populateCommonFields(elem, media);
        QDomElement ospitiElem = elem.firstChildElement("Ospiti");
        for (QDomElement o = ospitiElem.firstChildElement("Ospite"); !o.isNull(); o = o.nextSiblingElement("Ospite")){
            media->aggiungiOspite(o.text().toStdString());
        }

        return media;
    }

    CustomMessageBox msgbox;
    msgbox.setTitleText("<span style='color: #E44043;'>Errore importazione di un media</span>");
    msgbox.setMainMessage("<span style='color: #E44043;'> Il media dal titolo '"+ QString::fromStdString(titolo)+"' non è stato associato correttamente ad alcun podcast.</span>");
    msgbox.hideCancelButton();
    msgbox.exec();
    return nullptr;
}

Film *XmlVisitor::findFilmInList(const list<Media *> &mediaList, const string &titolo, const string &autore)
{
    for (Media *m : mediaList)
    {
        Film *f = dynamic_cast<Film *>(m);
        if (f && f->getTitolo() == titolo && f->getAutore() == autore)
        {
            return f;
        }
    }
    return nullptr; //non trovato
}

Podcast *XmlVisitor::findPodcastInList(const list<Media *> &mediaList, const string &titolo, const string &autore)
{
    for (Media *m : mediaList)
    {
        Podcast *p = dynamic_cast<Podcast *>(m);
        if (p && p->getTitolo() == titolo && p->getAutore() == autore)
        {
            return p;
        }
    }
    return nullptr; //non trovato
}
