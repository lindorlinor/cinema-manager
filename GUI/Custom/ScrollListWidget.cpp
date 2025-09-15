#include "ScrollListWidget.h"

ScrollListWidget::ScrollListWidget(QWidget *parent) : UpdateMediaLibrary(parent)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    titolo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    container = new QWidget(this);
    HorizontalLayoutContainer = new QHBoxLayout(container);
    container->setLayout(HorizontalLayoutContainer);

    setPreferredLayout(HorizontalLayoutContainer);

    // Scroll area
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(container);
    scrollArea->setMaximumHeight(340);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(titolo);
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);

    // style
    HorizontalLayoutContainer->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setAlignment(Qt::AlignLeft);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    titolo->setStyleSheet("color: #fed36a; font-size: 18pt; font-weight: bold;");
    scrollArea->setStyleSheet(
        "QScrollArea QWidget{"
        "border-radius: 10px;"
        "border: none}"
        "QScrollArea{"
        "background: transparent;}"
        "QScrollBar:horizontal {"
        "background: #4e7f8a;"
        "height: 12px;"
        "margin: 0px;"
        "border-radius: 5px;"
        "border: 1px solid #4e7f8a;}"
        "QScrollBar::handle:horizontal {"
        "background: #d9d9d9;"
        "min-height: 20px;"
        "border-radius: 5px;}"
        "QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {"
        "width: 0px;"
        "height: 0px;"
        "subcontrol-origin: margin;"
        "subcontrol-position: none;}"
        "QScrollBar::add-line:horizontal:hover, QScrollBar::sub-line:horizontal:hover {"
        "background: #4e7f8a;}");
}
