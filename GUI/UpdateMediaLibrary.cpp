#include "UpdateMediaLibrary.h"

UpdateMediaLibrary::UpdateMediaLibrary(QWidget* parent):QWidget(parent),chooseLayout(false){}

void UpdateMediaLibrary::update(const bool& view, int comboAttivita, int comboOrdinamento, const QString& filtro, const QString& ricerca, QList<Media*>& mediaList) {

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
        /* Film* film = dynamic_cast<Film*>(m);
        Puntata* puntata = dynamic_cast<Puntata*>(m); */
        if( //controllo che sia attivo o meno
            ((comboAttivita == 0 && !m->FuoriProduzione()) || (comboAttivita == 1 && m->FuoriProduzione()) || comboAttivita == 2) &&
            //trovo i media che soddisfano la ricerca

            //controllo se hanno un titolo o un autore corrispondente
            ((QString::fromStdString(m->getTitolo()).contains(ricerca, Qt::CaseInsensitive)) || (QString::fromStdString(m->getAutore()).contains(ricerca, Qt::CaseInsensitive)) /* ||
            
            //controllo se hanno un genere o un attore corrispondente 
            (film && (std::any_of(film->getGeneri().begin(), film->getGeneri().end(), [&](const Genere& g)
            { return QString::fromStdString(toString(g)).contains(ricerca, Qt::CaseInsensitive);}) || std::any_of(film->getAttoriPrincipali().begin(), 
            film->getAttoriPrincipali().end(), [&](const std::string& a){return QString::fromStdString(a).contains(ricerca, Qt::CaseInsensitive);}))) ||

            //controllo se hanno ospiti corrispondenti
            (puntata && std::any_of(puntata->getOspiti().begin(), puntata->getOspiti().end(), [&](const std::string& a)
            {return QString::fromStdString(a).contains(ricerca, Qt::CaseInsensitive);})) */)){
                
            CardVisitor* libraryVisitor = new CardVisitor(container, filtro, view);
            m->accept(libraryVisitor);

            if(!view){
                HorizontalCard* card(libraryVisitor->getWidgetCard());
    
                if(card != nullptr){
                    if(chooseLayout) HorizontalLayoutContainer->addWidget(card);
                    else FlowLayoutContainer->addWidget(card);
    
                    card->setCursor(Qt::PointingHandCursor);
                    card->setFixedHeight(300);
                    card->setMaximumWidth(710);
                    //visitor per visualizzare la pagina con i dettagli del media
    
                    connect(card, &HorizontalCard::selected, this, [this, m](){
                        DetailPageVisitor detailVisitor;
                        m->accept(&detailVisitor);
                        emit requestMediaView(*detailVisitor.getWidget());
                    });
                }
            }
            else{
                MediaFrame* media(libraryVisitor->getWidgetFrame());
    
                if(media != nullptr){
                    if(chooseLayout) HorizontalLayoutContainer->addWidget(media);
                    else FlowLayoutContainer->addWidget(media);
    
                    media->setCursor(Qt::PointingHandCursor);
                    media->editImageScale(430,250);
                    media->setFixedHeight(300);
                    media->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
                    
                    //visitor per visualizzare la pagina con i dettagli del media
    
                    connect(media, &MediaFrame::selected, this, [this, m](){
                        DetailPageVisitor detailVisitor;
                        m->accept(&detailVisitor);
                        emit requestMediaView(*detailVisitor.getWidget());
                    });
    
                }
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


