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
#include "../Cinema.h"

class SelectMediaReference:public QWidget{
    Q_OBJECT
    
    private:
    QString titolo;
    QString autore;
    QString tipoMedia;
    MediaFrame* currentSelected;
    QWidget* container;
    QVBoxLayout* layoutContainer; 
    QString sm_titolo;
    QString sm_autore;

    public:
    explicit SelectMediaReference(const QString& tipo, QWidget *parent = nullptr);
    void setSelectFalse();
    void reloadMedia(const Cinema& cinema);
    void setSelectedItem(const QString& titolo, const QString& autore);

    signals:
    void mediaSelected(MediaFrame* frame);
};

#endif //SELECTMEDIAREFERENCE_H