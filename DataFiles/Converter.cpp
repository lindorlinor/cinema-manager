#include "Converter.h"
void Converter::populateCommonFields(const Media* media, MediaData& data) {
    if(!media) return;
    data.titolo = QString::fromStdString(media->getTitolo());
    data.autore = QString::fromStdString(media->getAutore());
    data.descrizione = QString::fromStdString(media->getDescrizione());
    data.durataMinuti = media->getDurataMinuti();
    data.formato = media->getFormato();
    data.risoluzione = media->getRisoluzione();
    data.path = QString::fromStdString(media->getPath());
    auto ymd = media->getDataInizioRilascio();
    data.dataInizioRilascio = QDate(
        int(ymd.year()),
        unsigned(ymd.month()),
        unsigned(ymd.day())
    );
    ymd = media->getDataFineRilascio();
    data.dataFineRilascio = QDate(
        int(ymd.year()),
        unsigned(ymd.month()),
        unsigned(ymd.day())
    );

    data.lingueDisponibili.clear();
    data.lingueDisponibili = media->getLingue();
    data.sottotitoliDisponibili.clear();
    data.sottotitoliDisponibili = media->getSottotitoli();
}


void Converter::populateFilmFields(const Film* film, FilmData& data) {
    if(!film) return;
    data.tipologia="film";
    data.genere.clear();
    data.genere = film->getGenere();
    data.casaDiProduzione= QString::fromStdString(film->getCasaDiProduzione());
    data.nPostCredit=film->getNPostCredit();
    data.costoBiglietto = film->getCostoBiglietto();
    data.target = film->getClassificazione();
    data.attoriPrincipali.clear();
    for (const std::string& s : film->getAttoriPrincipali()) {
       data.attoriPrincipali.push_back(QString::fromStdString(s));
    }
}

/* void Converter::populatePubblicitaFields(const Pubblicita* pubb, PubblicitaData& data) {
    if(!pubb) return;
} */

void Converter::populateTrailerFields(const Trailer* trailer, TrailerData& data) {
    if(!trailer) return;
    data.tipologia = "trailer";
    data.nProiezioniGiornaliere = trailer->getNProiezioniGiornaliere();
    data.filmAssociato = QString::fromStdString(trailer->getFilm()->getTitolo());
    data.autoreFilmAssociato = QString::fromStdString(trailer->getFilm()->getAutore());
}

void Converter::populateInserzioneFields(const Inserzione* ins, InserzioneData& data) {
    if(!ins) return;

    data.tipologia = "inserzione";
    data.target = ins->getTarget();
    data.aziendaInserzionista = QString::fromStdString(ins->getAziendaInserzionistica());
    data.costoFissoProiezione = ins->getCostoFissoProiezione();
}

void Converter::populatePodcastFields(const Podcast* pod, PodcastData& data) {
    if(!pod) return;
    data.tipologia = "podcast";
    data.conduttore = QString::fromStdString(pod->getConduttore());
}

void Converter::populatePuntataFields(const Puntata* punt, PuntataData& data) {
    if(!punt) return;
    data.tipologia = "puntata";
    data.numeroPubblicita = punt->getNumeroPubblicita();
    data.podcastAssociato = QString::fromStdString(punt->getPodcast()->getTitolo());
    data.autorePodcastAssociato = QString::fromStdString(punt->getPodcast()->getAutore());
    data.ospiti.clear();
    for (const std::string& s : punt->getOspiti()) {
       data.ospiti.push_back(QString::fromStdString(s));
    }
}


MediaData Converter::mediaToData(const Media* media) {
    MediaData data;
    if(!media) return data;

    populateCommonFields(media, data);

    return data;
}


FilmData Converter::mediaToData(const Film* film) {
    FilmData data;
    if(!film) return data;

    populateCommonFields(film,data);
    populateFilmFields(film,data);

    return data;
}

TrailerData Converter::mediaToData(const Trailer* trailer) {
    TrailerData data;
    if(!trailer) return data;

    populateCommonFields(trailer,data);
    populateTrailerFields(trailer,data);

    return data;
}

PodcastData Converter::mediaToData(const Podcast* podcast) {
    PodcastData data;
    if(!podcast) return data;

    populateCommonFields(podcast,data);
    populatePodcastFields(podcast,data);

    return data;
}

PuntataData Converter::mediaToData(const Puntata* puntata) {
    PuntataData data;
    if(!puntata) return data;

    populateCommonFields(puntata,data);
    populatePuntataFields(puntata,data);

    return data;
}

InserzioneData Converter::mediaToData(const Inserzione* inserzione) {
    InserzioneData data;
    if(!inserzione) return data;

    populateCommonFields(inserzione,data);
    populateInserzioneFields(inserzione,data);

    return data;
}