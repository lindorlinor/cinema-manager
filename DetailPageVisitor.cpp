#include "DetailPageVisitor.h"
#include "GUI/TrailerView.h"
#include "GUI/InserzioneView.h"
#include "GUI/FilmView.h"
#include "../Film.h"
#include "../Trailer.h"
#include "../Inserzione.h"
#include "../Podcast.h"
#include "../Puntata.h"

DetailPageVisitor::DetailPageVisitor()
    : detailPage(nullptr)
{}

QWidget* DetailPageVisitor::getWidget() const {
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
void DetailPageVisitor::visit(Podcast*) {}
void DetailPageVisitor::visit(Puntata*) {}
