#include "DetailPageVisitor.h"
#include "GUI/FilmView.h"
#include "GUI/TrailerView.h"
#include "GUI/InserzioneView.h"
#include "GUI/PodcastView.h"
#include "GUI/PuntataView.h"
#include "../Film.h"
#include "../Trailer.h"
#include "../Inserzione.h"
#include "../Podcast.h"
#include "../Puntata.h"

DetailPageVisitor::DetailPageVisitor()
    : detailPage(nullptr)
{}

MediaView* DetailPageVisitor::getWidget() const {
    return detailPage;
}

void DetailPageVisitor::visit(Film* film) {
    detailPage = new FilmView(film);
}
void DetailPageVisitor::visit(Trailer* trailer) {
    detailPage = new TrailerView(trailer);
}
void DetailPageVisitor::visit(Inserzione* inserzione) {
    detailPage = new InserzioneView(inserzione);
}
void DetailPageVisitor::visit(Podcast* podcast) {
    detailPage = new PodcastView(podcast);
}
void DetailPageVisitor::visit(Puntata* puntata) {
    detailPage = new PuntataView(puntata);
}
