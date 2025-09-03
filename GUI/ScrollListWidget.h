#ifndef SCROLLLISTWIDGET_H
#define SCROLLLISTWIDGET_H

#include <QWidget>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QDebug>

#include "UpdateMediaLibrary.h"

class ScrollListWidget: public UpdateMediaLibrary{
    Q_OBJECT
    private:
    QScrollArea* scrollArea;
        
    public:
    explicit ScrollListWidget(QWidget* parent);
};

#endif //SCROLLLISTWIDGET_H