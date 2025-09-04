#include "ScrollListWidget.h"

ScrollListWidget::ScrollListWidget(QWidget* parent):UpdateMediaLibrary(parent){

    container = new QWidget(this);
    HorizontalLayoutContainer = new QHBoxLayout(container);
    container->setLayout(HorizontalLayoutContainer);
    
    setPreferredLayout(HorizontalLayoutContainer);

    // Scroll area
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(container);
    
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);

    //style
    HorizontalLayoutContainer->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(0,0,0,0);
    scrollArea->setStyleSheet(
                                "QScrollArea QWidget{"
                                    "border-radius: 10px;"
                                    "background-color: #073c47;"
                                    "border: none}"
                                    "QScrollArea{"
                                    "background: transparent;}"
                                "QScrollBar:horizontal {"
                                    "background: #4e7f8b;"
                                    "height: 12px;"
                                    "margin: 0px;"
                                    "border-radius: 5px;"
                                    "border: 1px solid #05313c;}"
                                "QScrollBar::handle:horizontal {"
                                    "background: #05313c;"
                                    "min-height: 20px;"
                                    "border-radius: 5px;}"
                                "QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {"
                                    "width: 0px;"  
                                    "height: 0px;"
                                    "subcontrol-origin: margin;"
                                    "subcontrol-position: none;}"
                                "QScrollBar::add-line:horizontal:hover, QScrollBar::sub-line:horizontal:hover {"
                                    "background: #4e7f8b;}"
                            );
    mainLayout->setAlignment(Qt::AlignLeft);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}
