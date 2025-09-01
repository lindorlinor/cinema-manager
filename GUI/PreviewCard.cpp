#include "PreviewCard.h"
#include <QPixmap>
#include <QFont>
#include <QPalette>
#include <QMouseEvent>

PreviewCard::PreviewCard(const Media* mPtr, QWidget* parent)
    : QFrame(parent),mediaPtr(mPtr)
{
    setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed); //gasp per fortuna me ne sono accorta, si espandeva solo in alcuni casi
    cardLayout = new QVBoxLayout(this);
    cardLayout->setContentsMargins(0,0,0,0);
    setContentsMargins(0,0,0,0);
    this->setObjectName("card");

    imageLabel = new QLabel(this);
    QPixmap pix(QString::fromStdString(mediaPtr->getImPath()));
    qDebug() << QString::fromStdString(mediaPtr->getImPath());
    imageLabel->setPixmap(pix.scaled(222, 320, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageLabel->setAlignment(Qt::AlignCenter);
    
    titleLabel = new QLabel(QString::fromStdString(mediaPtr->getTitolo()), this);
    titleLabel->setAlignment(Qt::AlignLeft);
    titleLabel->setWordWrap(true);
    titleLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    
    statusLabel = new QLabel(this);
    if (mediaPtr->FuoriProduzione()) {
        statusLabel->setText("Fuori produzione");
    } else {
        statusLabel->setText("Oggi in sala");
    }
    statusLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    statusLabel->setAlignment(Qt::AlignRight);

    // Layout
    cardLayout->addWidget(imageLabel);
    cardLayout->addWidget(titleLabel);
    cardLayout->addSpacing(20);
    // cardLayout->addStretch();
    cardLayout->addWidget(statusLabel);
    setLayout(cardLayout);

    setFixedWidth(224);

    setCursor(Qt::PointingHandCursor);
    setStyleSheet(
        "#card { background-color: #f8f9fa; border: 1px solid #ddd; border-radius: 5px; }"
        "#card:hover { background-color: #e9ecef; }"
    );
}

void PreviewCard::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        emit viewMedia();
    }
}