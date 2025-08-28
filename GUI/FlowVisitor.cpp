#include "FlowVisitor.h"

FlowVisitor::FlowVisitor(QWidget* l, FlowLayout* f, const QString& filter)
        : library(l), flow(f), filtro(filter) {}

FlowVisitor::~FlowVisitor() {}

void FlowVisitor::visit(Film* film){
    if(filtro == "Film"){
        MediaFrame* frame = new MediaFrame(
            QString::fromStdString(film->getTitolo()),
            QString::fromStdString(film->getImPath()),
            QString::fromStdString(film->getAutore()),
            library);
        flow->addWidget(frame);
    }
}

void FlowVisitor::visit(Trailer* trailer){
    if(filtro == "Trailer"){
        MediaFrame* frame = new MediaFrame(
            QString::fromStdString(trailer->getTitolo()),
            QString::fromStdString(trailer->getImPath()),
            QString::fromStdString(trailer->getAutore()),
            library);
        flow->addWidget(frame);
    }
}

void FlowVisitor::visit(Inserzione* inserzione){
    if(filtro == "Inserzione"){
        MediaFrame* frame = new MediaFrame(
            QString::fromStdString(inserzione->getTitolo()),
            QString::fromStdString(inserzione->getImPath()),
            QString::fromStdString(inserzione->getAutore()),
            library);
        flow->addWidget(frame);
    }
}

void FlowVisitor::visit(Podcast* podcast){
    if(filtro == "Podcast"){
        MediaFrame* frame = new MediaFrame(
            QString::fromStdString(podcast->getTitolo()),
            QString::fromStdString(podcast->getImPath()),
            QString::fromStdString(podcast->getAutore()),
            library);
        flow->addWidget(frame);
    }
}

void FlowVisitor::visit(Puntata* puntata){
    if(filtro == "Puntata"){
        MediaFrame* frame = new MediaFrame(
            QString::fromStdString(puntata->getTitolo()),
            QString::fromStdString(puntata->getImPath()),
            QString::fromStdString(puntata->getAutore()),
            library);
        flow->addWidget(frame);
    }
}
