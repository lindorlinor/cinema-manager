#include "MediaFrame.h"

MediaFrame::MediaFrame( const QString& titolo, const QString& imagePath,const QString& autore, QWidget* parent):QFrame(parent), titoloMedia(titolo), 
                        autoreMedia(autore), imgLabel(new QLabel(this)), pix(imagePath){

    imgLabel->setPixmap(pix.scaled(160, 160, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    
    titoloLabel = new QLabel(titolo);
    
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(imgLabel);
    layout->addWidget(titoloLabel);
    
    setLayout(layout);
    
    //style
    imgLabel->setContentsMargins(0,0,0,0);
    imgLabel->setAlignment(Qt::AlignCenter);
    titoloLabel->setAlignment(Qt::AlignCenter);
    titoloLabel->setWordWrap(true);
    titoloLabel->setMaximumHeight(60);
    imgLabel->setStyleSheet("border:none");
    titoloLabel->setStyleSheet("color: #05313c; background-color: #4e7f8b; border:none; font-size: 12pt; font-weight: bold; ");
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
    else            setStyleSheet("background-color: #4e7f8b;");
             
}
void MediaFrame::editImageScale(int w, int h){
    imgLabel->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setStyleSheet("background-color: #05313c;");
    titoloLabel->setStyleSheet("color: #bdced3; background-color: #05313c; border:none; font-size: 12pt;");
}
