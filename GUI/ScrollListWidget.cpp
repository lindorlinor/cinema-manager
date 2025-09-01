#include "ScrollListWidget.h"

ScrollListWidget::ScrollListWidget(QWidget* parent): QWidget(parent){

    container = new QWidget(this);
    layoutContainer = new QHBoxLayout(container);
    container->setLayout(layoutContainer);
    
    // Scroll area
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(container);
    
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);

    //style
    layoutContainer->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(0,0,0,0);
    container->setMinimumHeight(300);
    scrollArea->setStyleSheet(
                                "QScrollArea QWidget{"
                                    "border-radius: 10px;"
                                    "background-color: #073c47;"
                                    "border: none}"
                                    "QScrollArea{"
                                    "background: transparent;}"
                                "QScrollBar:vertical {"
                                    "background: #4e7f8b;"
                                    "width: 12px;"
                                    "margin: 0px;"
                                    "border: 1px solid #4e7f8b;}"
                                "QScrollBar::handle:vertical {"
                                    "background: #d9d9d9;"
                                    "min-height: 20px;"
                                    "border-radius: 3px;}"
                                "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
                                    "background: #4e7f8b;"
                                    "border: 1px solid #4e7f8b;"
                                    "height: 12px;"
                                    "border-radius: 5px;"
                                    "subcontrol-position: top;"
                                    "subcontrol-origin: margin;}"
                                "QScrollBar::add-line:vertical:hover, QScrollBar::sub-line:vertical:hover {"
                                    "background: #4e7f8b;}"
                            );
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    mainLayout->setAlignment(Qt::AlignLeft);
}

void ScrollListWidget::update(int comboAttivita, int comboOrdinamento, const QString& filtro, const QString& ricerca, QList<Media*>& mediaList) {

    // Pulisce i widget esistenti
    QLayoutItem* child;
    while ((child = layoutContainer->takeAt(0)) != nullptr) {
        if (child->widget()) child->widget()->deleteLater();
        delete child;
    }

    for (Media* m : mediaList) {

        FrameVisitor* visitor = new FrameVisitor(m, container, filtro);
        m->accept(visitor);
        MediaFrame* frame(visitor->getFrame());
        /* qDebug()<<"richiamato"; */
        
        if(frame != nullptr){
            /* qDebug()<<"eh è sbagliato cogliona"; */
            frame->setMinimumSize(140,200);
            frame->setCursor(Qt::PointingHandCursor);
            layoutContainer->addWidget(frame);
            //visitor per visualizzare la pagina con i dettagli del media
            connect(frame, &MediaFrame::selected, this, [this, m](){
                DetailPageVisitor detailVisitor;
                m->accept(&detailVisitor);
                emit requestMediaViewfromScoll(*detailVisitor.getWidget());
            });
        }
    }

    //style
    layoutContainer->setAlignment(Qt::AlignLeft);
}

/* void ScrollListWidget::update(int comboAttivita, int comboOrdinamento, const QString& filtro, const QString& ricerca, QList<Media*>& mediaList) {
    titolo->setText(filtro+" in Sala");

    //oridnamentos
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
            return a->getDataInizioRilascio() < b->getDataInizioRilascio();
        });
    }else{
        std::sort(mediaList.begin(), mediaList.end(), [](Media* a, Media* b){
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
    for (Media* m : mediaList) {
        if( //controllo che sia attivo o meno
            ((comboAttivita == 0 && !m->FuoriProduzione()) || (comboAttivita == 1 && m->FuoriProduzione()) || comboAttivita == 2) &&
            //trovo i media che soddisfano la ricerca
            (((QString::fromStdString(m->getTitolo()).contains(ricerca, Qt::CaseInsensitive)) || (QString::fromStdString(m->getAutore()).contains(ricerca, Qt::CaseInsensitive))))
        ){
            FlowVisitor* libraryVisitor = new FlowVisitor(container, filtro);
            m->accept(libraryVisitor);
            MediaFrame* media(libraryVisitor->getWidget());
            if(media != nullptr){
                flow->addWidget(media);
                //visitor per visualizzare la pagina con i dettagli del media
                media->setCursor(Qt::PointingHandCursor);

                connect(media, &MediaFrame::selected, this, [this, m](){
                    DetailPageVisitor detailVisitor;
                    m->accept(&detailVisitor);
                    emit requestMediaViewfromScoll(*detailVisitor.getWidget());
                });
                }
        }
    }
}
 */
