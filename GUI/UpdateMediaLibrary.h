#ifndef UPDATEMEDIALIBRARY_H
#define UPDATEMEDIALIBRARY_H

#include <QWidget>
#include <QObject>
#include <QString>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QDebug>

#include "FrameVisitor.h"
#include "FlowLayout.h"
#include "MediaView.h"
#include "MediaFrame.h"
#include "../Media.h"
#include "../DetailPageVisitor.h"

class UpdateMediaLibrary: public QWidget{
    Q_OBJECT

    protected:
    QWidget* container;
    FlowLayout* layoutContainer;
    int numeroWidget;
        
    public:
    UpdateMediaLibrary(QWidget* parent = nullptr);
    virtual void update(int comboAttivita, int comboOrdinamento, const QString& filtro, const QString& ricerca, QList<Media*>& mediaList);
    int getNumeroWidgetLayout() const;

    signals:
    void requestMediaView(MediaView& widget);
};
#endif //UPDATEMEDIALIBRARY_H