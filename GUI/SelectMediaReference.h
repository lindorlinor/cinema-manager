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
    QString autore;
    QString tipoMedia;
    const QString* cinemaNomeRiferimento;
    MediaFrame* currentSelected;
    QWidget* container;
    QVBoxLayout* layoutContainer; 

    public:
    explicit SelectMediaReference(const QString& tipo, const QString* cinema, QWidget *parent = nullptr);
    void setSelectFalse();
    void reloadMedia();

    signals:
    void mediaSelected(MediaFrame* frame);

    public slots:
};

#endif //SELECTMEDIAREFERENCE_H