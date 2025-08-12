#include "PathButton.h"

PathButton::PathButton(const QPixmap& mediaImage,QFrame *parent):QFrame(parent)
{
    setMouseTracking(true);

    setFixedSize(139,190);
    setObjectName("PathButton");
    imageLabel = new QLabel;
    imageLabel->setPixmap(mediaImage.scaled(129,180));
    imageLabel->setAlignment(Qt::AlignCenter);
    
    QPushButton* elimina = new QPushButton("elimina");
    QPushButton* modifica = new QPushButton("modifica");

    QHBoxLayout* layoutH = new QHBoxLayout;
    bottoni = new QWidget;
    layoutH->addWidget(elimina);
    layoutH->addWidget(modifica);
    bottoni->setLayout(layoutH);

    stackPath = new QStackedLayout(this);
    stackPath->addWidget(imageLabel);
    stackPath->addWidget(bottoni);
    stackPath->setCurrentIndex(0);
    setLayout(stackPath);

    
}

void PathButton::enterEvent(QEnterEvent* event) {

    stackPath->setCurrentIndex(1);
    bottoni->setStyleSheet("background-color: rgba(128, 128, 128, 150);");
    QFrame::enterEvent(event);
}

void PathButton::leaveEvent(QEvent* event) {
    stackPath->setCurrentIndex(0);
    QFrame::leaveEvent(event);
}