#include "ScrollListWidget.h"

ScrollListWidget::ScrollListWidget(const QList<Media*> media, const QString& filtro, QWidget* parent): listMedia(media), QWidget(parent), tipoFiltro(filtro){
    
}
