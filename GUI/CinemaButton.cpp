#include "CinemaButton.h"

CinemaButton::CinemaButton(const QString& cinemaName="Untitled", const QPixmap& cinemaImage, QWidget *parent)
    : QFrame(parent)
{
    setFixedSize(150, 180);  // larghezza x altezza
    setObjectName("CinemaButton");
    imageLabel = new QLabel(this);
    imageLabel->setPixmap(cinemaImage.scaled(120, 120));
    imageLabel->setAlignment(Qt::AlignCenter);
    
    nameLabel = new QLabel(cinemaName,this);
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setWordWrap(true);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(imageLabel);
    layout->addWidget(nameLabel);
    setLayout(layout);

    setCursor(Qt::PointingHandCursor);

    nameLabel->setObjectName("nomeCinema");
}

void CinemaButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit selected();
    }
}

