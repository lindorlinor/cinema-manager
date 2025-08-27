#include "MediaUpdateVisitor.h"
#include "MediaManagerJson.h"

MediaUpdateVisitor::MediaUpdateVisitor(MediaData* newD, MediaData* currD, MediaManagerJson* m)
        : newData(newD), currentData(currD), manager(m) {}

MediaUpdateVisitor::~MediaUpdateVisitor() {}

void MediaUpdateVisitor::visit(Film* film){
    *static_cast<FilmData*>(currentData) = *static_cast<FilmData*>(newData);
    manager->updateFilm(*film, static_cast<FilmData*>(currentData));
}

void MediaUpdateVisitor::visit(Trailer* trailer){
    *static_cast<TrailerData*>(currentData) = *static_cast<TrailerData*>(newData);
    manager->updateTrailer(*trailer, static_cast<TrailerData*>(currentData));
}

void MediaUpdateVisitor::visit(Inserzione* inserzione){
    *static_cast<InserzioniData*>(currentData) = *static_cast<InserzioniData*>(newData);
    manager->updateInserzione(*inserzione, static_cast<InserzioniData*>(currentData));
}

void MediaUpdateVisitor::visit(Podcast* podcast){
    *static_cast<PodcastData*>(currentData) = *static_cast<PodcastData*>(newData);
    manager->updatePodcast(*podcast, static_cast<PodcastData*>(currentData));
}

void MediaUpdateVisitor::visit(Puntata* puntata){
    *static_cast<PuntataData*>(currentData) = *static_cast<PuntataData*>(newData);
    manager->updatePuntata(*puntata, static_cast<PuntataData*>(currentData));
}

