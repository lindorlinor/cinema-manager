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

    connect(modifica, &QPushButton::clicked, this, [this](){
        QString filePath = QFileDialog::getOpenFileName(this, "Seleziona una copertina", "", "Immagini (*.png *.jpg *.jpeg *.bmp)");

        //l'utente non seleziona nulla
        if (filePath.isEmpty())
                return;

        QString fileName = QFileInfo(filePath).fileName();
        QString targetPath = QDir("images").filePath(fileName);
        QDir().mkpath("images");
        QFile::copy(filePath, targetPath);
        pathImage=targetPath;

        QPixmap pix(targetPath);
        if (!pix.isNull()) {
            imageLabel->setPixmap(pix.scaled(129, 180));
        }
    });
    
    connect(elimina, &QPushButton::clicked, this, [this, mediaImage](){
        imageLabel->setPixmap(mediaImage.scaled(129,180));
    });
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

QString PathButton::getPath(){
    return pathImage;
}