#ifndef SELECTMEDIAREFERENCE_H
#define SELECTMEDIAREFERENCE_H

#include <QWidget>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QScrollArea>
#include <QJsonObject>
#include <QCoreApplication>
#include <QDir>

#include "MediaFrame.h"
#include "../DataFiles/MediaManagerJson.h"

class SelectMediaReference:public QWidget{
    Q_OBJECT
    
    private:
    QString titolo;
    QString casaProd;
    MediaFrame* currentSelected;

    public:
    explicit SelectMediaReference(const QString& tipo, QWidget *parent = nullptr);

    signals:
    void mediaSelected(MediaFrame* frame);
};

#endif //SELECTMEDIAREFERENCE_H