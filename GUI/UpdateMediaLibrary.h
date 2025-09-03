#ifndef UPDATEMEDIALIBRARY_H
#define UPDATEMEDIALIBRARY_H

#include <QWidget>
#include <QObject>
#include <QString>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QLayout>

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
    QHBoxLayout* HorizontalLayoutContainer; //true
    FlowLayout* FlowLayoutContainer; //false
    int numeroWidget;
    bool chooseLayout;
    void setPreferredLayout(QLayout* layout);
        
    public:
    UpdateMediaLibrary(QWidget* parent = nullptr);
    virtual void update(int comboAttivita, int comboOrdinamento, const QString& filtro, const QString& ricerca, QList<Media*>& mediaList);
    int getNumeroWidgetLayout() const;
    
    signals:
    void requestMediaView(MediaView& widget);
};
#endif //UPDATEMEDIALIBRARY_H