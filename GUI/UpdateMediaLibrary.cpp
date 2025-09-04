#include "UpdateMediaLibrary.h"

UpdateMediaLibrary::UpdateMediaLibrary(QWidget* parent):QWidget(parent),chooseLayout(false){}

void UpdateMediaLibrary::update(int comboAttivita, int comboOrdinamento, const QString& filtro, const QString& ricerca, QList<Media*>& mediaList) {
    //oridnamento
    if(comboOrdinamento == 0){
        std::sort(mediaList.begin(), mediaList.end(), [](Media* a, Media* b){
            return a->getVisualizzazioni() > b->getVisualizzazioni();
        });
    }else if(comboOrdinamento == 1){
        std::sort(mediaList.begin(), mediaList.end(), [](Media* a, Media* b){
            return a->getVisualizzazioni() < b->getVisualizzazioni();
        });
    }else if(comboOrdinamento == 2){
        std::sort(mediaList.begin(), mediaList.end(), [](Media* a, Media* b){
            return a->getDataInizioRilascio() > b->getDataInizioRilascio();
        });
    }else{
        std::sort(mediaList.begin(), mediaList.end(), [](Media* a, Media* b){
            return a->getDataInizioRilascio() < b->getDataInizioRilascio();
        });
    }

    // Rimuovo tutti i widget dal FlowLayout
    QLayoutItem* item;
    if(chooseLayout){
        while ((item = HorizontalLayoutContainer->takeAt(0)) != nullptr) {
            if (item->widget()) {
                item->widget()->deleteLater();  
            }
            delete item;
        }
    }
    else{
        while ((item = FlowLayoutContainer->takeAt(0)) != nullptr) {
            if (item->widget()) {
                item->widget()->deleteLater();  
            }
            delete item;
        }
    }

    // Ricreo i widget secondo il nuovo filtro
    for (Media* m : mediaList) {
        if( //controllo che sia attivo o meno
            ((comboAttivita == 0 && !m->FuoriProduzione()) || (comboAttivita == 1 && m->FuoriProduzione()) || comboAttivita == 2) &&
            //trovo i media che soddisfano la ricerca
            (((QString::fromStdString(m->getTitolo()).contains(ricerca, Qt::CaseInsensitive)) || (QString::fromStdString(m->getAutore()).contains(ricerca, Qt::CaseInsensitive))))
        ){
            FrameVisitor* libraryVisitor = new FrameVisitor(container, filtro);
            m->accept(libraryVisitor);
            MediaFrame* media(libraryVisitor->getWidget());
            if(media != nullptr){

                if(chooseLayout) HorizontalLayoutContainer->addWidget(media);
                else FlowLayoutContainer->addWidget(media);

                media->setCursor(Qt::PointingHandCursor);
                media->editImageScale(430,250);
                media->setMinimumSize(240,300);
                media->setMaximumSize(430,300);
                
                //visitor per visualizzare la pagina con i dettagli del media

                connect(media, &MediaFrame::selected, this, [this, m](){
                    DetailPageVisitor detailVisitor;
                    m->accept(&detailVisitor);
                    emit requestMediaView(*detailVisitor.getWidget());
                });
            }
        }
    }

    numeroWidget = chooseLayout? HorizontalLayoutContainer->count() : FlowLayoutContainer->count();
}

int UpdateMediaLibrary::getNumeroWidgetLayout() const{
    return numeroWidget;
}

void UpdateMediaLibrary::setPreferredLayout(QLayout* layout){
    if(!layout) return;

    if(dynamic_cast<QHBoxLayout*>(layout)) chooseLayout = true;
    if(dynamic_cast<FlowLayout*>(layout)) chooseLayout = false;
}