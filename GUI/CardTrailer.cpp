#include "CardTrailer.h"
#include <QPixmap>
#include <QFont>
#include <QPalette>
#include <QMouseEvent>

CardTrailer::CardTrailer(const Trailer* trailer, QWidget* parent)
    : QFrame(parent),trailerPtr(trailer)
{
    setFixedSize(270,200);
    cardLayout = new QVBoxLayout(this);
    cardLayout->setContentsMargins(0,0,0,0);
    setContentsMargins(0,0,0,0);
    this->setObjectName("card");

    imageLabel = new QLabel(this);
    QPixmap pix(QString::fromStdString(trailer->getImPath()));
    imageLabel->setPixmap(pix.scaled(240,135, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageLabel->setAlignment(Qt::AlignCenter);

    titleLabel = new QLabel(QString::fromStdString(trailer->getTitolo()), this);
    titleLabel->setAlignment(Qt::AlignLeft);
    titleLabel->setWordWrap(true);
    
    statusLabel = new QLabel(this);
    if (trailer->FuoriProduzione()) {
        statusLabel->setText("Fuori produzione");
    } else {
        statusLabel->setText("Oggi in sala");
    }
    statusLabel->setAlignment(Qt::AlignRight);

    // Layout
    cardLayout->addWidget(imageLabel);
    cardLayout->addWidget(titleLabel);
    cardLayout->addStretch();
    cardLayout->addWidget(statusLabel);
    setLayout(cardLayout);

    setFixedWidth(224);

    setCursor(Qt::PointingHandCursor);
    setStyleSheet(
        "#card { background-color: #f8f9fa; border: 1px solid #ddd; border-radius: 5px; }"
        "#card:hover { background-color: #e9ecef; }"
    );
}

void CardTrailer::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        emit viewTrailer(trailerPtr);
    }
}