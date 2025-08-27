#include "MediaLibraryGenerale.h"

MediaLibraryGenerale::MediaLibraryGenerale(const QList<const Media*>& media, const QString& filtro, QWidget* parent): QWidget(parent),listMedia(media), tipoFiltro(filtro){

    titolo = new QLabel(tipoFiltro+" in Sala",this);
    QVBoxLayout* mainLayout = new QVBoxLayout;
    widgetSupporto = new QWidget(this);

    flow = new FlowLayout(this);
    for(const Media* m : listMedia){
        FlowVisitor visitor(widgetSupporto, flow, tipoFiltro);
        const_cast<Media*>(m)->accept(&visitor);
    }

    widgetSupporto->setLayout(flow);

    mainLayout->addWidget(titolo);
    mainLayout->addWidget(widgetSupporto);
    setLayout(mainLayout);
}

void MediaLibraryGenerale::getFiltro(const QString& filtro){
    tipoFiltro = filtro;
    titolo->setText(tipoFiltro+" in Sala");

    refresh();
}

void MediaLibraryGenerale::refresh() {

    // Rimuovo tutti i widget dal FlowLayout
    QLayoutItem* item;
    while ((item = flow->takeAt(0)) != nullptr) {
        if (item->widget()) {
            item->widget()->deleteLater();  
        }
        delete item;
    }

    // Ricreo i widget secondo il nuovo filtro
    for (const Media* m : listMedia) {
        FlowVisitor visitor(widgetSupporto, flow, tipoFiltro);
        const_cast<Media*>(m)->accept(&visitor);
    }
}
