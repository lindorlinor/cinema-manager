#include "XmlVisitor.h"
#include <QDomDocument>
#include <QDomElement>
#include <QDomText>
#include <iostream>


XmlVisitor::XmlVisitor(QDomDocument *d) : doc(d) {}
QDomElement XmlVisitor::getXmlElement() const{
    return xmlElement;
}


void XmlVisitor::visit(Film *film){

    QDomElement filmElem = doc->createElement("Film");

    QDomElement commonMediaFields = populateCommonFields(film);
    QDomNode child = commonMediaFields.firstChild();
    while (!child.isNull()){
        filmElem.appendChild(child.cloneNode()); // clone necessario perchè i nodi di commonMediaFields hanno già genitore
        child = child.nextSibling();
    }

    QDomElement genElem = doc->createElement("Generi");
    for (const Genere &g : film->getGeneri()){
        QDomElement gElem = doc->createElement("Genere");
        gElem.appendChild(doc->createTextNode(toString(g)));
        genElem.appendChild(gElem);
    }
    filmElem.appendChild(genElem);

    QDomElement attoriElem = doc->createElement("AttoriPrincipali");
    for (const string &attore : film->getAttoriPrincipali()){
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

void XmlVisitor::visit(Trailer *trailer){

    QDomElement trailerElem = doc->createElement("Trailer");

    QDomElement commonMediaFields = populateCommonFields(trailer);

    QDomNode child = commonMediaFields.firstChild();
    while (!child.isNull()){
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
void XmlVisitor::visit(Inserzione *inserzione){

    QDomElement insElem = doc->createElement("Inserzione");

    QDomElement commonMediaFields = populateCommonFields(inserzione);
    QDomNode child = commonMediaFields.firstChild();
    while (!child.isNull()){
        insElem.appendChild(child.cloneNode());
        child = child.nextSibling();
    }

    QDomElement nProiezElem = doc->createElement("NProiezioniGiornaliere");
    nProiezElem.appendChild(doc->createTextNode(QString::number(inserzione->getNProiezioniGiornaliere())));
    insElem.appendChild(nProiezElem);

    QDomElement fasceOrarieElem = doc->createElement("FasceOrarie");
    for (const FasciaOraria &fo : inserzione->getFasceOrarie()){
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

void XmlVisitor::visit(Podcast *podcast){
    QDomElement podElem = doc->createElement("Podcast");

    QDomElement commonMediaFields = populateCommonFields(podcast);
    QDomNode child = commonMediaFields.firstChild();
    while (!child.isNull()){
        podElem.appendChild(child.cloneNode());
        child = child.nextSibling();
    }

    QDomElement conduttElem = doc->createElement("Conduttore");
    conduttElem.appendChild(doc->createTextNode(QString::fromStdString(podcast->getConduttore())));
    podElem.appendChild(conduttElem);

    xmlElement = podElem;
}

void XmlVisitor::visit(Puntata *puntata){
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


QDomElement XmlVisitor::populateCommonFields(const Media *media){
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
    for (const Lingua &l : media->getLingue()){

        QDomElement lElem = doc->createElement("Lingua");
        lElem.appendChild(doc->createTextNode(toString(l)));
        lingueElem.appendChild(lElem);
    }
    mediaElem.appendChild(lingueElem);

    QDomElement subElem = doc->createElement("SottotitoliDisponibili");
    for (const Lingua &l : media->getSottotitoli()){
        QDomElement lElem = doc->createElement("Lingua");
        lElem.appendChild(doc->createTextNode(toString(l)));
        subElem.appendChild(lElem);
    }
    mediaElem.appendChild(subElem);

    return mediaElem;
}