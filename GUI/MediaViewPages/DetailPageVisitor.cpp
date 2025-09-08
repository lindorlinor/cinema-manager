#include "DetailPageVisitor.h"
#include "FilmView.h"
#include "TrailerView.h"
#include "InserzioneView.h"
#include "PodcastView.h"
#include "PuntataView.h"
#include "../../Film.h"
#include "../../Trailer.h"
#include "../../Inserzione.h"
#include "../../Podcast.h"
#include "../../Puntata.h"

DetailPageVisitor::DetailPageVisitor()
    : detailPage(nullptr)
{
}

MediaView *DetailPageVisitor::getWidget() const
{
    return detailPage;
}

void DetailPageVisitor::visit(Film *film)
{
    detailPage = new FilmView(film);
}
void DetailPageVisitor::visit(Trailer *trailer)
{
    detailPage = new TrailerView(trailer);
}
void DetailPageVisitor::visit(Inserzione *inserzione)
{
    detailPage = new InserzioneView(inserzione);
}
void DetailPageVisitor::visit(Podcast *podcast)
{
    detailPage = new PodcastView(podcast);
}
void DetailPageVisitor::visit(Puntata *puntata)
{
    detailPage = new PuntataView(puntata);
}
