#ifndef CONVERTERXML_H
#define CONVERTERXML_H

#include <QDomDocument>
#include <QDomElement>
#include "Converter.h"
#include "Populate.h"
#include "../Podcast.h"
#include "../Puntata.h"
#include "../Inserzione.h"
#include "../Film.h"
#include "../Trailer.h"
#include <vector>

class ConverterXml : public Converter{
public:
    ConverterXml() = default;
    ~ConverterXml() = default;

    static QDomElement toXmlElement(const Media* media, QDomDocument& doc);
    static QDomElement toXmlElement(const Film* film, QDomDocument& doc);
    static QDomElement toXmlElement(const Trailer* trailer, QDomDocument& doc);
    static QDomElement toXmlElement(const Inserzione* inserzione, QDomDocument& doc);
    static QDomElement toXmlElement(const Podcast* podcast, QDomDocument& doc);
    static QDomElement toXmlElement(const Puntata* puntata, QDomDocument& doc);

};

#endif // CONVERTERXML_H
