#include "JsonVisitor.h"

JsonVisitor::JsonVisitor(QString cName):cinemaName(cName){}

JsonVisitor::~JsonVisitor() {}

QJsonObject JsonVisitor::getObj(){
    return v_obj;
}

void JsonVisitor::visit(Film* film){
    JsonConverter converter(cinemaName);
    v_obj = (converter.serialize(film));
}

void JsonVisitor::visit(Trailer* trailer){
    JsonConverter converter(cinemaName);
    v_obj = (converter.serialize(trailer));
}

void JsonVisitor::visit(Inserzione* inserzione){
    JsonConverter converter(cinemaName);
    v_obj = (converter.serialize(inserzione));
}

void JsonVisitor::visit(Podcast* podcast){
    JsonConverter converter(cinemaName);
    v_obj = (converter.serialize(podcast));
}

void JsonVisitor::visit(Puntata* puntata){
    JsonConverter converter(cinemaName);
    v_obj = (converter.serialize(puntata));
}