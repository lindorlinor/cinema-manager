#include "MediaLibraryGenerale.h"

MediaLibraryGenerale::MediaLibraryGenerale(QList<Media*>& media, const QString& filtroBottone, QWidget* parent): QWidget(parent),listMedia(media){

    titolo = new QLabel(filtroBottone+" in Sala",this);
    QVBoxLayout* mainLayout = new QVBoxLayout;
    widgetSupporto = new QWidget(this);

    flow = new FlowLayout(this);
    widgetSupporto->setLayout(flow);

    update(0, 0, filtroBottone, "");

    mainLayout->addWidget(titolo);
    mainLayout->addWidget(widgetSupporto);
    setLayout(mainLayout);
}

void MediaLibraryGenerale::update(int comboAttivita, int comboOrdinamento, const QString& filtro, const QString& ricerca) {
    
    titolo->setText(filtro+" in Sala");

    //oridnamento
    if(comboOrdinamento == 0){
        std::sort(listMedia.begin(), listMedia.end(), [](Media* a, Media* b){
            return a->getVisualizzazioni() > b->getVisualizzazioni();
        });
    }else if(comboOrdinamento == 1){
        std::sort(listMedia.begin(), listMedia.end(), [](Media* a, Media* b){
            return a->getVisualizzazioni() < b->getVisualizzazioni();
        });
    }else if(comboOrdinamento == 2){
        std::sort(listMedia.begin(), listMedia.end(), [](Media* a, Media* b){
            return a->getDataInizioRilascio() < b->getDataInizioRilascio();
        });
    }else{
        std::sort(listMedia.begin(), listMedia.end(), [](Media* a, Media* b){
            return a->getDataInizioRilascio() > b->getDataInizioRilascio();
        });
    }

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
        if( //controllo che sia attivo o meno
            ((comboAttivita == 0 && !m->FuoriProduzione()) || (comboAttivita == 1 && m->FuoriProduzione()) || comboAttivita == 2) &&
            //trovo i media che soddisfano la ricerca
            (QString::fromStdString(m->getTitolo()).contains(ricerca, Qt::CaseInsensitive) || (QString::fromStdString(m->getAutore()).contains(ricerca, Qt::CaseInsensitive)))
        ){
            FlowVisitor* visitor = new FlowVisitor(widgetSupporto, filtro);
            const_cast<Media*>(m)->accept(visitor);
            if(visitor->getWidget() != nullptr)
                flow->addWidget(visitor->getWidget());
        }
    }
}
