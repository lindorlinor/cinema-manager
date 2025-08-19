#include "MediaFrame.h"

MediaFrame::MediaFrame(const QString& titolo, const QString& imagePath,const QString& autore, QWidget* parent):titoloMedia(titolo), autoreMedia(autore), QFrame(parent){
    imgLabel = new QLabel;
    pix.load(imagePath);
    imgLabel->setPixmap(pix.scaled(100, 150));
    imgLabel->setAlignment(Qt::AlignCenter);
    
    QLabel* titoloLabel = new QLabel(titolo);
    titoloLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(imgLabel);
    layout->addWidget(titoloLabel);

    setLayout(layout);
}

QString MediaFrame::getTitolo() const{
    return titoloMedia;
}

QString MediaFrame::getAutore() const{
    return autoreMedia;
}

void MediaFrame::mousePressEvent(QMouseEvent* event){
    emit selected(this);
    QFrame::mousePressEvent(event);
}

void MediaFrame::setSelected(bool selected){
    if (selected)   this->setStyleSheet("border: 2px solid black;");
    else            this->setStyleSheet("");
}