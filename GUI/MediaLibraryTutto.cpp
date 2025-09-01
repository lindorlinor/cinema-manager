#include "MediaLibraryTutto.h"

MediaLibraryTutto::MediaLibraryTutto(QWidget* parent):QWidget(parent){

    container = new QWidget();  
    QVBoxLayout* mainLayout = new QVBoxLayout;
    layoutContainer = new QVBoxLayout(container); 
    container->setLayout(layoutContainer);
    QLabel* titoloPagina = new QLabel("Tutto", this);

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(container); 

    mainLayout->addWidget(titoloPagina);
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);

    //style
    mainLayout->setAlignment(Qt::AlignTop);
    titoloPagina->setStyleSheet("color: #fed36a; font-size: 20pt; font-weight: bold;");
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
                                    "border-radius: 5px;"
                                    "border: 1px solid #4e7f8b;}"
                                "QScrollBar::handle:vertical {"
                                    "background: #d9d9d9;"
                                    "min-height: 20px;"
                                    "border-radius: 5px;}"
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
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MediaLibraryTutto::update(int comboAttivita, int comboOrdinamento, const QString& ricerca, QList<Media*>& mediaList){

    QList<QString> allFiltri = QList<QString>({"Film", "Trailer", "Inserzioni", "Podcast", "Puntate"});

    QLayoutItem* item;
    while ((item = layoutContainer->takeAt(0)) != nullptr) {
        if (item->widget()) {
            item->widget()->deleteLater();  
        }
        delete item;
    }

    for(QString f : allFiltri){
        QWidget* salaWidget = new QWidget(container);
        QVBoxLayout* salaV = new QVBoxLayout(salaWidget);
        QLabel* titolo = new QLabel(f + " in Sala", salaWidget);
        ScrollListWidget* scroll = new ScrollListWidget(salaWidget); 
        scroll->update(comboAttivita, comboOrdinamento, f, ricerca, mediaList);
        scroll->setFixedHeight(330);
        if (scroll->getNumeroWidgetLayout()){
            salaV->addWidget(titolo);
            salaV->addWidget(scroll);
            salaWidget->setLayout(salaV);
    
            layoutContainer->addWidget(salaWidget,0,Qt::AlignTop);
    
            connect(scroll, &ScrollListWidget::requestMediaView, this, &MediaLibraryTutto::reciveRequestMediaView);
        }

        titolo->setStyleSheet("color: #fed36a; font-size: 18pt; font-weight: bold;");

    }

}

void MediaLibraryTutto::reciveRequestMediaView(MediaView& widget){
    emit requestMediaView(widget);
}
