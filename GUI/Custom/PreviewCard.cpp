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
    if (pix.isNull()) {
        pix = QPixmap(":/images/default.png"); 
    }
    imageLabel->setPixmap(pix.scaled(222, 320, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageLabel->setAlignment(Qt::AlignCenter);
    
    titleLabel = new QLabel(QString::fromStdString(mediaPtr->getTitolo()), this);
    titleLabel->setAlignment(Qt::AlignLeft);
    titleLabel->setWordWrap(true);
    titleLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    
    QWidget* containerLabel = new QWidget(this);
    QHBoxLayout* containerLayout = new QHBoxLayout(containerLabel);
    containerLayout->setContentsMargins(0,0,0,0);

    statusLabel = new QLabel(containerLabel);
    textLabel = new QLabel(containerLabel);
    
    containerLayout->addWidget(statusLabel);
    containerLayout->addWidget(textLabel);

    if (mediaPtr->FuoriProduzione()) {
        statusLabel->setPixmap(QPixmap(":/icons/non_in_sala_dark.png").scaled(10, 10, Qt::KeepAspectRatio));
        textLabel->setText("Fuori produzione");
    } else {
        statusLabel->setPixmap(QPixmap(":/icons/in_sala_dark.png").scaled(10, 10, Qt::KeepAspectRatio));
        textLabel->setText("Attualmente in distribuzione");
    }
    statusLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    textLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    containerLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    statusLabel->setAlignment(Qt::AlignRight);
    textLabel->setAlignment(Qt::AlignRight);

    cardLayout->addWidget(imageLabel);
    cardLayout->addWidget(titleLabel);
    cardLayout->addSpacing(20);

    cardLayout->addWidget(containerLabel);
    setLayout(cardLayout);

    setFixedWidth(224);

    setCursor(Qt::PointingHandCursor);
    setStyleSheet(
        "#card { color: #243F46; background-color: #BDCED3; border: 1px solid #BDCED3; border-radius: 5px; }"
        "#card:hover { background-color: rgba(189, 206, 211, 0.5); }"
    );
}

void PreviewCard::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        emit viewMedia();
    }
}