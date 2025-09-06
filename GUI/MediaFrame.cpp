#include "MediaFrame.h"

MediaFrame::MediaFrame( const Media& media, QWidget* parent):QFrame(parent),imgLabel(new QLabel(this)), pix(QString::fromStdString(media.getImPath())), mf_media(&media){

    imgLabel->setPixmap(pix.scaled(160, 160, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    
    titoloLabel = new QLabel(QString::fromStdString(mf_media->getTitolo()));
    
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
    return QString::fromStdString(mf_media->getTitolo());
}

QString MediaFrame::getAutore() const{
    return QString::fromStdString(mf_media->getAutore());
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