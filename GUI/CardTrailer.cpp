#include "CardTrailer.h"
#include <QPixmap>
#include <QFont>
#include <QPalette>

CardTrailer::CardTrailer(const Trailer* trailer, QWidget* parent)
    : QFrame(parent)
{
    setFixedSize(240,200);
    cardLayout = new QVBoxLayout(this);
    cardLayout->setContentsMargins(0,0,0,0);
    setContentsMargins(0,0,0,0);
    this->setObjectName("card");
    imageLabel = new QLabel(this);
    QPixmap pix(QString::fromStdString(trailer->getImPath()));   // path dell’immagine
    imageLabel->setPixmap(pix.scaled(240,135, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageLabel->setAlignment(Qt::AlignCenter);

    titleLabel = new QLabel(QString::fromStdString(trailer->getTitolo()), this);
    titleLabel->setAlignment(Qt::AlignLeft);
    titleLabel->setWordWrap(true);
    // --- Stato (in sala / fuori produzione) ---
    statusLabel = new QLabel(this);
    if (trailer->FuoriProduzione()) {
        statusLabel->setText("Fuori produzione");
    } else {
        statusLabel->setText("Oggi in sala");
    }
    statusLabel->setAlignment(Qt::AlignRight);
    // --- Layout principale ---
    
    cardLayout->addWidget(imageLabel);
    cardLayout->addWidget(titleLabel);
    cardLayout->addStretch();
    cardLayout->addWidget(statusLabel);

    setLayout(cardLayout);
    setFixedWidth(220);
    setStyleSheet("#card { background-color: #f8f9fa;}");
}
