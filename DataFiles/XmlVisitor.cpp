#include "XmlVisitor.h"
#include "ConverterXml.h"

QDomElement XmlVisitor::getXmlElement() const { return xmlElement; }

void XmlVisitor::visit(Film* f){
    xmlElement = ConverterXml::toXmlElement(f, doc);
}

void XmlVisitor::visit(Trailer* t){
    xmlElement = ConverterXml::toXmlElement(t, doc);
}

void XmlVisitor::visit(Podcast* p){
    xmlElement = ConverterXml::toXmlElement(p, doc);
}

void XmlVisitor::visit(Puntata* pt){
    xmlElement = ConverterXml::toXmlElement(pt, doc);
}

void XmlVisitor::visit(Inserzione* i){
    xmlElement = ConverterXml::toXmlElement(i, doc);
}

    
