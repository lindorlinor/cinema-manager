#include "SelectMediaReference.h"
#include "MediaFrame.h"

SelectMediaReference::SelectMediaReference(const QString& tipo, QWidget *parent)
    : QWidget(parent), tipoMedia(tipo), currentSelected(nullptr), sm_titolo(""), sm_autore("")
{
    // Container interno per gli item
    container = new QWidget(this);
    layoutContainer = new QVBoxLayout(container);
    container->setLayout(layoutContainer);
    
    // Scroll area
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(container);
    
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);

    //style
    layoutContainer->addSpacerItem(new QSpacerItem(20, 400, QSizePolicy::Minimum, QSizePolicy::Expanding));
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
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainLayout->setAlignment(Qt::AlignRight);
}

void SelectMediaReference::reloadMedia(const Cinema& cinema) {

    // Pulisce i widget esistenti
    QLayoutItem* child;
    while ((child = layoutContainer->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        } else if (child->layout()) {
            delete child->layout(); 
        }
        delete child;
    }

    for(Media* m : cinema.getListaMedia()){
        
        MediaFrame* mediaframe = new MediaFrame(*m, container);
        mediaframe->setFixedSize(200,250);
        layoutContainer->addWidget(mediaframe);
        mediaframe->setCursor(Qt::PointingHandCursor);

        titolo = QString::fromStdString(m->getTitolo());
        autore = QString::fromStdString(m->getAutore());

        if(titolo == sm_titolo && autore == sm_autore){
            qDebug()<<"trovato";
            currentSelected = mediaframe;
            currentSelected->setSelected(true);
            emit mediaSelected(mediaframe);
        }

        connect(mediaframe, &MediaFrame::selected, this, [this](MediaFrame* f){
            if (currentSelected) currentSelected->setSelected(false);
    
            currentSelected = f;
            currentSelected->setSelected(true);
            emit mediaSelected(f);
        });
    }

    //style
    layoutContainer->setAlignment(Qt::AlignCenter);
}

void SelectMediaReference::setSelectFalse() {
    if (currentSelected) {
        currentSelected->setSelected(false);
        currentSelected = nullptr;
    }
}

void SelectMediaReference::setSelectedItem(const QString& titolo, const QString& autore) {
    qDebug()<<"impostati";
    sm_titolo = titolo;
    sm_autore = autore;
}
