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
    detailPage->setStyleSheet("QLabel { background-color: red} #sp { background-color: orange} #details { background-color: purple} #gugu { background-color: pink} #gaga {background-color: red} #pupu {background-color: yellow} #caca{background-color: blue}");
}
void DetailPageVisitor::visit(Trailer* trailer) {
    detailPage = new TrailerView(trailer);
    detailPage->setStyleSheet("QLabel { background-color: red} #sp { background-color: orange} #details { background-color: purple} #gugu { background-color: pink} #gaga {background-color: red} #pupu {background-color: yellow} #caca{background-color: blue}");

}
void DetailPageVisitor::visit(Inserzione* inserzione) {
    detailPage = new InserzioneView(inserzione);
    detailPage->setStyleSheet("QLabel { background-color: red} #sp { background-color: orange} #details { background-color: purple} #gugu { background-color: pink} #gaga {background-color: red} #pupu {background-color: yellow} #caca{background-color: blue}");
}
void DetailPageVisitor::visit(Podcast* podcast) {
    detailPage = new PodcastView(podcast);
    detailPage->setStyleSheet("QLabel { background-color: red} #sp { background-color: orange} #details { background-color: purple} #gugu { background-color: pink} #gaga {background-color: red} #pupu {background-color: yellow} #caca{background-color: blue}");
}
void DetailPageVisitor::visit(Puntata* puntata) {
    detailPage = new PuntataView(puntata);
    detailPage->setStyleSheet("QLabel { background-color: red} #sp { background-color: orange} #details { background-color: purple} #gugu { background-color: pink} #gaga {background-color: red} #pupu {background-color: yellow} #caca{background-color: blue}");
}
