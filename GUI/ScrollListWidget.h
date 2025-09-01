#ifndef SCROLLLISTWIDGET_H
#define SCROLLLISTWIDGET_H

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

#include "FrameVisitor.h"
#include "FlowLayout.h"
#include "MediaView.h"
#include "../Media.h"
#include "../DetailPageVisitor.h"

class ScrollListWidget: public QWidget{
    Q_OBJECT
    private:
    QWidget* container;
    FlowLayout* layoutContainer;
        
    public:
    explicit ScrollListWidget(QWidget* parent = nullptr);
    void update(int comboAttivita, int comboOrdinamento, const QString& filtro, const QString& ricerca, QList<Media*>& mediaList);

    signals:
     void requestMediaViewfromScoll(MediaView& widget);
};

#endif //SCROLLLISTWIDGET_H