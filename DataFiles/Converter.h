#ifndef CONVERTER_H
#define CONVERTER_H

#include <QDomDocument>
#include <QDomElement>
#include "Populate.h"
#include "../Podcast.h"
#include "../Puntata.h"
#include "../Inserzione.h"
#include "../Film.h"
#include "../Trailer.h"
#include <vector>

class Converter {
public:
    Converter() = default;
    ~Converter() = default;

protected:
    static void populateCommonFields(const Media* media, MediaData& data);
    static void populateFilmFields(const Film* film, FilmData & data);
    static void populateTrailerFields(const Trailer* trailer, TrailerData & data);
    static void populateInserzioneFields(const Inserzione* ins, InserzioneData & data);
    static void populatePodcastFields(const Podcast* pod, PodcastData & data);
    static void populatePuntataFields(const Puntata* punt, PuntataData & data);

    static MediaData mediaToData(const Media* media);
    static FilmData mediaToData(const Film* film);
    static TrailerData mediaToData(const Trailer* trailer);
    static PodcastData mediaToData(const Podcast* podcast);
    static PuntataData mediaToData(const Puntata* puntata);
    static InserzioneData mediaToData(const Inserzione* inserzione);
};

#endif // CONVERTER_H
