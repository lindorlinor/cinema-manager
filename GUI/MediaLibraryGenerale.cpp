#include "MediaLibraryGenerale.h"

MediaLibraryGenerale::MediaLibraryGenerale(QList<Media*>& media, const QString& filtroBottone, QWidget* parent): QWidget(parent),ml_mediaList(media){

    titolo = new QLabel(filtroBottone+" in Sala",this);
    QVBoxLayout* mainLayout = new QVBoxLayout;
    widgetSupporto = new QWidget(this);

    flow = new FlowLayout(this);
    widgetSupporto->setLayout(flow);

    update(0, 0, filtroBottone, "", "");

    mainLayout->addWidget(titolo);
    mainLayout->addWidget(widgetSupporto);
    setLayout(mainLayout);
}

void MediaLibraryGenerale::update(int comboAttivita, int comboOrdinamento, const QString& filtro, const QString& ricerca, const QString& nomeCinema) {
    
    titolo->setText(filtro+" in Sala");

    //oridnamento
    if(comboOrdinamento == 0){
        std::sort(ml_mediaList.begin(), ml_mediaList.end(), [](Media* a, Media* b){
            return a->getVisualizzazioni() > b->getVisualizzazioni();
        });
    }else if(comboOrdinamento == 1){
        std::sort(ml_mediaList.begin(), ml_mediaList.end(), [](Media* a, Media* b){
            return a->getVisualizzazioni() < b->getVisualizzazioni();
        });
    }else if(comboOrdinamento == 2){
        std::sort(ml_mediaList.begin(), ml_mediaList.end(), [](Media* a, Media* b){
            return a->getDataInizioRilascio() < b->getDataInizioRilascio();
        });
    }else{
        std::sort(ml_mediaList.begin(), ml_mediaList.end(), [](Media* a, Media* b){
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
    for (Media* m : ml_mediaList) {
        if( //controllo che sia attivo o meno
            ((comboAttivita == 0 && !m->FuoriProduzione()) || (comboAttivita == 1 && m->FuoriProduzione()) || comboAttivita == 2) &&
            //trovo i media che soddisfano la ricerca
            (QString::fromStdString(m->getTitolo()).contains(ricerca, Qt::CaseInsensitive) || (QString::fromStdString(m->getAutore()).contains(ricerca, Qt::CaseInsensitive)) &&
            QString::fromStdString(m->getNomeCinema()).compare(nomeCinema, Qt::CaseInsensitive) == 0)
        ){
            FlowVisitor* libraryVisitor = new FlowVisitor(widgetSupporto, filtro);
            m->accept(libraryVisitor);
            MediaFrame* media(libraryVisitor->getWidget());
            if(media != nullptr){
                flow->addWidget(media);
                //visitor per visualizzare la pagina con i dettagli del media
                media->setCursor(Qt::PointingHandCursor);

                connect(media, &MediaFrame::selected, this, [this, m](){
                    DetailPageVisitor detailVisitor;
                    m->accept(&detailVisitor);
                    emit requestMediaView(*detailVisitor.getWidget());
                });
                }
        }
    }
}
