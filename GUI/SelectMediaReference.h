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
#include <QVBoxLayout>
#include <QDebug>

#include "MediaFrame.h"

class SelectMediaReference:public QWidget{
    Q_OBJECT
    
    private:
    QString titolo;
    QString autore;
    QString tipoMedia;
    MediaFrame* currentSelected;
    QWidget* container;
    QVBoxLayout* layoutContainer; 

    public:
    explicit SelectMediaReference(const QString& tipo, QWidget *parent = nullptr);
    void setSelectFalse();
    void reloadMedia(const QString& nomeCinema);

    signals:
    void mediaSelected(MediaFrame* frame);

    public slots:
};

#endif //SELECTMEDIAREFERENCE_H