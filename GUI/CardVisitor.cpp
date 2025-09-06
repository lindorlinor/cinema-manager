#include "CardVisitor.h"

CardVisitor::CardVisitor(QWidget* l, const QString& filter, const bool& view)
        : library(l), filtro(filter), frame(nullptr), card(nullptr), vista(view) {}

CardVisitor::~CardVisitor() {}

HorizontalCard* CardVisitor::getWidgetCard() const{
    return card;
}

MediaFrame* CardVisitor::getWidgetFrame() const{
    return frame;
}

void CardVisitor::visit(Film* film){
    if(filtro == "Film"){
        if(vista){
            frame = new MediaFrame(*film, library);
        }
        else    card = new HorizontalCard(*film, library);
    }
}

void CardVisitor::visit(Trailer* trailer){
    if(filtro == "Trailer"){
        if(vista){
        frame = new MediaFrame(*trailer, library);
        }
        else    card = new HorizontalCard(*trailer, library);
    }
}

void CardVisitor::visit(Inserzione* inserzione){
    if(filtro == "Inserzioni"){
        if(vista){
        frame = new MediaFrame(*inserzione, library);
        }
        else    card = new HorizontalCard(*inserzione, library);
    }
}

void CardVisitor::visit(Podcast* podcast){
    if(filtro == "Podcast"){
        if(vista){
        frame = new MediaFrame(*podcast, library);
        }
        else    card = new HorizontalCard(*podcast, library);
    }
}

void CardVisitor::visit(Puntata* puntata){
    if(filtro == "Puntate"){
        if(vista){
        frame = new MediaFrame(*puntata, library);
        }
        else    card = new HorizontalCard(*puntata, library);
    }
}
