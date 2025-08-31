#ifndef MEDIALIBRARYGENERALE_H
#define MEDIALIBRARYGENERALE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../Media.h"
#include "MediaFrame.h"
#include "../Media.h"
#include "FlowLayout.h"
#include "FlowVisitor.h"
#include "LibraryObserver.h"
#include "MediaView.h"
#include "../DetailPageVisitor.h"

class MediaLibraryGenerale: public QWidget, public LibraryObserver{
    Q_OBJECT
    private:

    QList<Media*>& ml_mediaList;
    QLabel* titolo;
    FlowLayout* flow;
    QWidget* widgetSupporto;
    
    public:
    explicit MediaLibraryGenerale(QList<Media*>& media, const QString& filtro, QWidget* parent = nullptr);
    virtual void update(int comboAttivita, int comboOrdinamento, const QString& filtroBottone, const QString& ricerca, const QString& nomeCinema);

    signals: 
    void requestMediaView(MediaView& widget);

};

#endif //MEDIALIBRARYGENERALE_H