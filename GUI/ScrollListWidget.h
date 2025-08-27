#ifndef SCROLLLISTWIDGET_H
#define SCROLLLISTWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QList>

#include "../Media.h"

class ScrollListWidget: public QWidget{

    private:
    const QList<const Media*>& listMedia;
    QString tipoFiltro;
    
    public:
    explicit ScrollListWidget(const QList<const Media*>& media, const QString& filtro, QWidget* parent = nullptr);

};

#endif //SCROLLLISTWIDGET_H