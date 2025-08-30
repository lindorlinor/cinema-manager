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

class MediaLibraryGenerale: public QWidget, public LibraryObserver{

    private:

    QList<Media*>& listMedia;
    QLabel* titolo;
    FlowLayout* flow;
    QWidget* widgetSupporto;
    
    public:
    explicit MediaLibraryGenerale(QList<Media*>& media, const QString& filtro, QWidget* parent = nullptr);
    virtual void update(int comboAttivita, int comboOrdinamento, const QString& filtroBottone, const QString& ricerca);

};

#endif //MEDIALIBRARYGENERALE_H