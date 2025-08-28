#include "ScrollListWidget.h"

ScrollListWidget::ScrollListWidget(const QList<const Media*>& media, const QString& filtro, QWidget* parent): listMedia(media), QWidget(parent), tipoFiltro(filtro){
    QWidget* finestra = new QWidget(this);
    for(const Media* m : listMedia){
        
    }
}
