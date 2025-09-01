#include "FrameVisitor.h"

FrameVisitor::FrameVisitor(Media* media, QWidget* container, const QString& filtro): v_media(media), v_container(container), v_filtro(filtro), v_frame(nullptr){}

FrameVisitor::~FrameVisitor() {}

MediaFrame* FrameVisitor::getFrame(){
    return v_frame;
}

void FrameVisitor::visit(Film* film){
    if(v_filtro == "Film")
        v_frame = new MediaFrame(QString::fromStdString(film->getTitolo()), QString::fromStdString(film->getImPath()), QString::fromStdString(film->getAutore()), v_container);
}

void FrameVisitor::visit(Trailer* trailer){
    if(v_filtro == "Trailer")
        v_frame = new MediaFrame(QString::fromStdString(trailer->getTitolo()), QString::fromStdString(trailer->getImPath()), QString::fromStdString(trailer->getAutore()), v_container);
}

void FrameVisitor::visit(Inserzione* inserzione){
    if(v_filtro == "Inserzioni")
        v_frame = new MediaFrame(QString::fromStdString(inserzione->getTitolo()), QString::fromStdString(inserzione->getImPath()), QString::fromStdString(inserzione->getAutore()), v_container);
}

void FrameVisitor::visit(Podcast* podcast){
    if(v_filtro == "Podcast")
        v_frame = new MediaFrame(QString::fromStdString(podcast->getTitolo()), QString::fromStdString(podcast->getImPath()), QString::fromStdString(podcast->getAutore()), v_container);
}

void FrameVisitor::visit(Puntata* puntata){
    if(v_filtro == "Puntate")
        v_frame = new MediaFrame(QString::fromStdString(puntata->getTitolo()), QString::fromStdString(puntata->getImPath()), QString::fromStdString(puntata->getAutore()), v_container);
}