#ifndef MEDIALIBRARYTUTTO_H
#define MEDIALIBRARYTUTTO_H

#include <QWidget>
#include <QList>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>

#include "ScrollListWidget.h"

class MediaLibraryTutto: public QWidget{
    Q_OBJECT
    private:
    QVBoxLayout* layoutContainer;
    QWidget* container;
    QScrollArea* scrollArea;
    
    public:
    explicit MediaLibraryTutto(QWidget* parent = nullptr);
    void update(int comboAttivita, int comboOrdinamento, const QString& ricerca, QList<Media*>& mediaList);

    signals: 
    void requestMediaView(MediaView& widget);

    public slots:
    void reciveRequestMediaView(MediaView& widget);

};

#endif //MEDIALIBRARYTUTTO_H