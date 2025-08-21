#include "MediaFrame.h"

MediaFrame::MediaFrame(const QString& titolo, const QString& imagePath,const QString& autore, QWidget* parent):titoloMedia(titolo), autoreMedia(autore), QFrame(parent){
    imgLabel = new QLabel;
    pix.load(imagePath);
    imgLabel->setPixmap(pix.scaled(100, 150));
    
    QLabel* titoloLabel = new QLabel(titolo);
    
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(imgLabel);
    layout->addWidget(titoloLabel);
    
    setLayout(layout);
    
    //style
    imgLabel->setAlignment(Qt::AlignCenter);
    titoloLabel->setAlignment(Qt::AlignCenter);
    setMaximumSize(250,200);
    titoloLabel->setMaximumHeight(60);
    imgLabel->setMaximumHeight(140);
    imgLabel->setStyleSheet("border:none");
    titoloLabel->setStyleSheet("color: #05313c; background-color: #4e7f8b; border:none; font-size: 12pt;");
    setStyleSheet("background-color: #4e7f8b;");
    layout->setAlignment(Qt::AlignCenter);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
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
    if (selected)   setStyleSheet("border: 3px solid #d9d9d9; padding: 0px;  background-color: #4e7f8b");
    else            setStyleSheet("");
}