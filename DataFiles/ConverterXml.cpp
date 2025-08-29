#include "ConverterXml.h"
#include <QDomDocument>
#include <QDomElement>
#include <QDomText>

//@TO DO controllo puntatori nulli ? che facc
QDomElement ConverterXml::toXmlElement(const Media* media, QDomDocument& doc) {
    MediaData data = mediaToData(media);

    QDomElement mediaElem = doc.createElement("MediaFields"); 

    QDomElement elem = doc.createElement("Titolo");
    elem.appendChild(doc.createTextNode(data.titolo));
    mediaElem.appendChild(elem);

    elem = doc.createElement("Autore");
    elem.appendChild(doc.createTextNode(data.autore));
    mediaElem.appendChild(elem);

    elem = doc.createElement("Descrizione");
    elem.appendChild(doc.createTextNode(data.descrizione));
    mediaElem.appendChild(elem);

    elem = doc.createElement("DurataMinuti");
    elem.appendChild(doc.createTextNode(QString::number(data.durataMinuti)));
    mediaElem.appendChild(elem);

    elem = doc.createElement("Formato");
    elem.appendChild(doc.createTextNode(toString(data.formato)));
    mediaElem.appendChild(elem);

    elem = doc.createElement("Risoluzione");
    elem.appendChild(doc.createTextNode(toString(data.risoluzione)));
    mediaElem.appendChild(elem);

    elem = doc.createElement("Path");
    elem.appendChild(doc.createTextNode(data.path));
    mediaElem.appendChild(elem);

    elem = doc.createElement("DataInizioRilascio");
    elem.appendChild(doc.createTextNode(data.dataInizioRilascio.toString("yyyy-MM-dd")));
    mediaElem.appendChild(elem);

    elem = doc.createElement("DataFineRilascio");
    elem.appendChild(doc.createTextNode(data.dataFineRilascio.toString("yyyy-MM-dd")));
    mediaElem.appendChild(elem);

    QDomElement lingueElem = doc.createElement("LingueDisponibili");
    for (const Lingua& l : data.lingueDisponibili) {
        QDomElement lElem = doc.createElement("Lingua");
        lElem.appendChild(doc.createTextNode(toString(l)));
        lingueElem.appendChild(lElem);
    }
    mediaElem.appendChild(lingueElem);

    QDomElement subElem = doc.createElement("SottotitoliDisponibili");
    for (const Lingua& l : data.sottotitoliDisponibili) {
        QDomElement lElem = doc.createElement("Lingua");
        lElem.appendChild(doc.createTextNode(toString(l)));
        subElem.appendChild(lElem);
    }
    mediaElem.appendChild(subElem);

    return mediaElem;
}


QDomElement ConverterXml::toXmlElement(const Film* film, QDomDocument& doc) {
    FilmData data = mediaToData(film);

    QDomElement filmElem = doc.createElement("Film");

    QDomElement commonMediaFields = toXmlElement(static_cast<const Media*>(film), doc); //static cast per richiamare il toXmlElement corretto -> altrimenti loop
    
    QDomNode child = commonMediaFields.firstChild();
    while(!child.isNull()) {
        filmElem.appendChild(child.cloneNode()); //clone necessario perchè i nodi di commonMediaFields hanno già genitore
        child = child.nextSibling();
    }

    QDomElement genElem = doc.createElement("Generi");
    for (const Genere& g : data.generi) {
        QDomElement gElem = doc.createElement("Genere");
        gElem.appendChild(doc.createTextNode(toString(g)));
        genElem.appendChild(gElem);
    }
    filmElem.appendChild(genElem);

    QDomElement attoriElem = doc.createElement("AttoriPrincipali");
    for (const QString& attore : data.attoriPrincipali) {
        QDomElement aElem = doc.createElement("Attore");
        aElem.appendChild(doc.createTextNode(attore));
        attoriElem.appendChild(aElem);
    }
    filmElem.appendChild(attoriElem);

    QDomElement targetElem = doc.createElement("Target");
    targetElem.appendChild(doc.createTextNode(toString(data.target)));
    filmElem.appendChild(targetElem);

    QDomElement costoElem = doc.createElement("CostoBiglietto");
    costoElem.appendChild(doc.createTextNode(QString::number(data.costoBiglietto)));
    filmElem.appendChild(costoElem);

    QDomElement casaElem = doc.createElement("CasaDiProduzione");
    casaElem.appendChild(doc.createTextNode(data.casaDiProduzione));
    filmElem.appendChild(casaElem);

    QDomElement postElem = doc.createElement("NPostCredit");
    postElem.appendChild(doc.createTextNode(QString::number(data.nPostCredit)));
    filmElem.appendChild(postElem);

    return filmElem;
}


QDomElement ConverterXml::toXmlElement(const Trailer* trailer, QDomDocument& doc){
    TrailerData data = mediaToData(trailer);
    QDomElement trailerElem = doc.createElement("Trailer");

    QDomElement commonMediaFields = toXmlElement(static_cast<const Media*>(trailer), doc); 
    QDomNode child = commonMediaFields.firstChild();
    while(!child.isNull()) {
        trailerElem.appendChild(child.cloneNode());
        child = child.nextSibling();
    }

    QDomElement nProiezElem = doc.createElement("NProiezioniGiornaliere");
    nProiezElem.appendChild(doc.createTextNode(QString::number(data.nProiezioniGiornaliere)));
    trailerElem.appendChild(nProiezElem);

    QDomElement tFilmAssElem = doc.createElement("TitoloFilmAssociato");
    tFilmAssElem.appendChild(doc.createTextNode(data.filmAssociato));
    trailerElem.appendChild(tFilmAssElem);

    QDomElement aFilmAssElem = doc.createElement("AutoreFilmAssociato");
    aFilmAssElem.appendChild(doc.createTextNode(data.autoreFilmAssociato));
    trailerElem.appendChild(aFilmAssElem);

    return trailerElem;
}
QDomElement ConverterXml::toXmlElement(const Inserzione* inserzione, QDomDocument& doc){
    InserzioneData data = mediaToData(inserzione);
    QDomElement insElem = doc.createElement("Inserzione");

    QDomElement commonMediaFields = toXmlElement(static_cast<const Media*>(inserzione), doc); 
    QDomNode child = commonMediaFields.firstChild();
    while(!child.isNull()) {
        insElem.appendChild(child.cloneNode());
        child = child.nextSibling();
    }

    QDomElement nProiezElem = doc.createElement("NProiezioniGiornaliere");
    nProiezElem.appendChild(doc.createTextNode(QString::number(data.nProiezioniGiornaliere)));
    insElem.appendChild(nProiezElem);
    
    QDomElement targetElem = doc.createElement("Target");
    targetElem.appendChild(doc.createTextNode(QString::fromStdString(toString(data.target))));
    insElem.appendChild(targetElem);

    QDomElement aziendaElem = doc.createElement("AziendaInserzionista");
    aziendaElem.appendChild(doc.createTextNode(data.aziendaInserzionista));
    insElem.appendChild(aziendaElem);

    QDomElement costoElem = doc.createElement("CostoFissoProiezione");
    costoElem.appendChild(doc.createTextNode(QString::number(data.costoFissoProiezione)));
    insElem.appendChild(costoElem);

    return insElem;

}
QDomElement ConverterXml::toXmlElement(const Podcast* podcast, QDomDocument& doc){
    PodcastData data = mediaToData(podcast);
    QDomElement podElem = doc.createElement("Podcast");

    QDomElement commonMediaFields = toXmlElement(static_cast<const Media*>(podcast), doc); 
    QDomNode child = commonMediaFields.firstChild();
    while(!child.isNull()) {
        podElem.appendChild(child.cloneNode());
        child = child.nextSibling();
    }

    QDomElement conduttElem = doc.createElement("Conduttore");
    conduttElem.appendChild(doc.createTextNode(data.conduttore));
    podElem.appendChild(conduttElem);

    return podElem;
}


QDomElement ConverterXml::toXmlElement(const Puntata* puntata, QDomDocument& doc){
    PuntataData data = mediaToData(puntata);

    QDomElement puntElem = doc.createElement("Puntata");

    QDomElement commonMediaFields = toXmlElement(static_cast<const Media*>(puntata), doc); 
    QDomNode child = commonMediaFields.firstChild();
    while(!child.isNull()) {
        puntElem.appendChild(child.cloneNode());
        child = child.nextSibling();
    }

    QDomElement tPodElem = doc.createElement("TitoloPodcastAssociato");
    tPodElem.appendChild(doc.createTextNode(data.podcastAssociato));
    puntElem.appendChild(tPodElem);

    QDomElement aPodElem = doc.createElement("AutorePodcastAssociato");
    aPodElem.appendChild(doc.createTextNode(data.autorePodcastAssociato));
    puntElem.appendChild(aPodElem);

    QDomElement nPubbElem = doc.createElement("NPubblicita");
    nPubbElem.appendChild(doc.createTextNode(QString::number(data.numeroPubblicita)));
    puntElem.appendChild(nPubbElem);

    return puntElem;
}

void ConverterXml::populateCommonFields(const QDomElement& elem, MediaData & data){
    data.titolo = elem.firstChildElement("Titolo").text();
    data.autore = elem.firstChildElement("Autore").text();
    data.descrizione = elem.firstChildElement("Descrizione").text();
    data.durataMinuti = elem.firstChildElement("DurataMinuti").text().toInt();
    data.formato = toFormato(elem.firstChildElement("Formato").text().toStdString());
    data.risoluzione = toRisoluzione(elem.firstChildElement("Risoluzione").text().toStdString());
    data.path = elem.firstChildElement("Path").text();
    data.dataInizioRilascio = QDate::fromString(elem.firstChildElement("DataInizioRilascio").text(), "yyyy-MM-dd");
    data.dataFineRilascio = QDate::fromString(elem.firstChildElement("DataFineRilascio").text(), "yyyy-MM-dd");

    QDomElement lingElem = elem.firstChildElement("LingueDisponibili");
    QDomElement l = lingElem.firstChildElement("Lingua");
    while(!l.isNull()) {
        data.lingueDisponibili.push_back(toLingua(l.text().toStdString()));
        l = l.nextSiblingElement("Lingua");
    }

    QDomElement subElem = elem.firstChildElement("SottotitoliDisponibili");
    l = subElem.firstChildElement("Lingua");
    while(!l.isNull()) {
        data.sottotitoliDisponibili.push_back(toLingua(l.text().toStdString()));
        l = l.nextSiblingElement("Lingua");
    }
}


FilmData ConverterXml::fromXmlFilmElement(const QDomElement& elem) {
    FilmData data;
    populateCommonFields(elem,data);

    data.tipologia="film";

    QDomElement generiElem = elem.firstChildElement("Generi");
    for(QDomElement g = generiElem.firstChildElement("Genere"); !g.isNull(); g = g.nextSiblingElement("Genere")) {
        data.generi.push_back(toGenere(g.text().toStdString()));
    }

    QDomElement attoriElem = elem.firstChildElement("AttoriPrincipali");
    for(QDomElement a = attoriElem.firstChildElement("Attore"); !a.isNull(); a = a.nextSiblingElement("Attore")) {
        data.attoriPrincipali.push_back(a.text());
    }

    data.target = toClassificazione(elem.firstChildElement("Target").text().toStdString());
    data.costoBiglietto = elem.firstChildElement("CostoBiglietto").text().toDouble();
    data.casaDiProduzione = elem.firstChildElement("CasaDiProduzione").text();
    data.nPostCredit = elem.firstChildElement("NPostCredit").text().toInt();
   
    return data;
}

TrailerData ConverterXml::fromXmlTrailerElement(const QDomElement& elem){
    TrailerData data;
    populateCommonFields(elem,data);
    data.tipologia = "trailer";

    QDomElement nProiezioniElem = elem.firstChildElement("NProiezioniGiornaliere");
    if(!nProiezioniElem.isNull()) {
        data.nProiezioniGiornaliere = nProiezioniElem.text().toInt();
    }

    QDomElement filmElem = elem.firstChildElement("FilmAssociato");
    if(!filmElem.isNull()) {
        data.filmAssociato = filmElem.text();
    }

    QDomElement autoreElem = elem.firstChildElement("AutoreFilmAssociato");
    if(!autoreElem.isNull()) {
        data.autoreFilmAssociato = autoreElem.text();
    }

    return data;
}
InserzioneData ConverterXml::fromXmlInserzioneElement(const QDomElement& elem) {
    InserzioneData data;
    populateCommonFields(elem, data);

    data.tipologia = "inserzione";

    QDomElement nProiezioniElem = elem.firstChildElement("NProiezioniGiornaliere");
    if(!nProiezioniElem.isNull()) {
        data.nProiezioniGiornaliere = nProiezioniElem.text().toInt();
    }

    QDomElement targetElem = elem.firstChildElement("Target");
    if(!targetElem.isNull()) {
        data.target = toClassificazione(targetElem.text().toStdString());
    }

    QDomElement aziendaElem = elem.firstChildElement("AziendaInserzionistica");
    if(!aziendaElem.isNull()) {
        data.aziendaInserzionista = aziendaElem.text();
    }

    QDomElement costoElem = elem.firstChildElement("CostoFissoProiezione");
    if(!costoElem.isNull()) {
        data.costoFissoProiezione = costoElem.text().toDouble();
    }

    return data;
}


PodcastData ConverterXml::fromXmlPodcastElement(const QDomElement& elem) {
    PodcastData data;
    populateCommonFields(elem, data);

    data.tipologia = "podcast";

    QDomElement conduttoreElem = elem.firstChildElement("Conduttore");
    if(!conduttoreElem.isNull()) {
        data.conduttore = conduttoreElem.text();
    }

    return data;
}


PuntataData ConverterXml::fromXmlPuntataElement(const QDomElement& elem) {
    PuntataData data;
    populateCommonFields(elem, data);

    data.tipologia = "puntata";

    QDomElement numPubElem = elem.firstChildElement("NumeroPubblicita");
    if(!numPubElem.isNull()) {
        data.numeroPubblicita = numPubElem.text().toInt();
    }

    QDomElement podcastElem = elem.firstChildElement("PodcastAssociato");
    if(!podcastElem.isNull()) {
        data.podcastAssociato = podcastElem.text();
    }
    QDomElement autoreElem = elem.firstChildElement("AutorePodcastAssociato");
    if(!autoreElem.isNull()) {
        data.autorePodcastAssociato = autoreElem.text();
    }
    data.ospiti.clear();
    QDomElement ospitiElem = elem.firstChildElement("Ospiti");
    for(QDomElement o = ospitiElem.firstChildElement("Ospite"); !o.isNull(); o = o.nextSiblingElement("Ospite")) {
        data.ospiti.push_back(o.text());
    }

    return data;
}

