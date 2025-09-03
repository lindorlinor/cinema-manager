#include "EditMediaVisitor.h"

EditMediaVisitor::EditMediaVisitor() {}

EditMediaVisitor::~EditMediaVisitor() {}

int EditMediaVisitor::getIndex() const{
    return index;
}

void EditMediaVisitor::visit(Film* film){
    index = 0;
}

void EditMediaVisitor::visit(Trailer* trailer){
    index = 1;
}

void EditMediaVisitor::visit(Inserzione* inserzione){
    index = 2;
}

void EditMediaVisitor::visit(Podcast* podcast){
    index = 3;
}

void EditMediaVisitor::visit(Puntata* puntata){
    index = 4;
}
