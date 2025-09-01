#include "FrameVisitor.h"

FrameVisitor::FrameVisitor(QWidget* l, const QString& filter)
        : library(l), filtro(filter), frame(nullptr) {}

FrameVisitor::~FrameVisitor() {}

MediaFrame* FrameVisitor::getWidget() const{
    return frame;
}

void FrameVisitor::visit(Film* film){
    if(filtro == "Film"){
        frame = new MediaFrame(
            QString::fromStdString(film->getTitolo()),
            QString::fromStdString(film->getImPath()),
            QString::fromStdString(film->getAutore()),
            library);
    }
}

void FrameVisitor::visit(Trailer* trailer){
    if(filtro == "Trailer"){
        frame = new MediaFrame(
            QString::fromStdString(trailer->getTitolo()),
            QString::fromStdString(trailer->getImPath()),
            QString::fromStdString(trailer->getAutore()),
            library);
    }
}

void FrameVisitor::visit(Inserzione* inserzione){
    if(filtro == "Inserzioni"){
        frame = new MediaFrame(
            QString::fromStdString(inserzione->getTitolo()),
            QString::fromStdString(inserzione->getImPath()),
            QString::fromStdString(inserzione->getAutore()),
            library);
    }
}

void FrameVisitor::visit(Podcast* podcast){
    if(filtro == "Podcast"){
        frame = new MediaFrame(
            QString::fromStdString(podcast->getTitolo()),
            QString::fromStdString(podcast->getImPath()),
            QString::fromStdString(podcast->getAutore()),
            library);
    }
}

void FrameVisitor::visit(Puntata* puntata){
    if(filtro == "Puntate"){
        frame = new MediaFrame(
            QString::fromStdString(puntata->getTitolo()),
            QString::fromStdString(puntata->getImPath()),
            QString::fromStdString(puntata->getAutore()),
            library);
    }
}
