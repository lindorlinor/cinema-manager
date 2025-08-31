#include "JsonVisitor.h"

JsonVisitor::JsonVisitor(Media* media): v_media(media){}

JsonVisitor::~JsonVisitor() {}

QJsonObject JsonVisitor::getObj(){
    return v_obj;
}

void JsonVisitor::visit(Film* film){
    JsonConverter converter;
    v_obj = (converter.serialize(film));
}

void JsonVisitor::visit(Trailer* trailer){
    JsonConverter converter;
    v_obj = (converter.serialize(trailer));
}

void JsonVisitor::visit(Inserzione* inserzione){
    JsonConverter converter;
    v_obj = (converter.serialize(inserzione));
}

void JsonVisitor::visit(Podcast* podcast){
    JsonConverter converter;
    v_obj = (converter.serialize(podcast));
}

void JsonVisitor::visit(Puntata* puntata){
    JsonConverter converter;
    v_obj = (converter.serialize(puntata));
}