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

class MediaLibraryGenerale: public QWidget{

    private:

    const QList<const Media*>& listMedia;
    QString tipoFiltro;
    QLabel* titolo;
    FlowLayout* flow;
    QWidget* widgetSupporto;
    
    public:
    explicit MediaLibraryGenerale(const QList<const Media*>& media, const QString& filtro, QWidget* parent = nullptr);
    void getFiltro(const QString& filtro);
    void refresh();

};

#endif //MEDIALIBRARYGENERALE_H