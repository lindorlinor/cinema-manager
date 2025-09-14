#include "InsertImageFrame.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QToolButton>

InsertImageFrame::InsertImageFrame(const QString& testo, const QString& style, QWidget *parent)
    : QFrame(parent), defaultText(testo),
      label(new QLabel(defaultText, this)),
      closeButton(new QToolButton(this))
{   
    setObjectName("frame");
    label->setTextFormat(Qt::RichText);
    label->setAlignment(Qt::AlignCenter);

    setStyleSheet(style);
    closeButton->setText("x");
    closeButton->setVisible(false);
    closeButton->setFixedSize(16,16);
    label->setContentsMargins(20,0,20,0);
    label->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
  

    QVBoxLayout *layoutPrincipale = new QVBoxLayout(this);
    QWidget * contenitoreDettagli = new QWidget(this);
    QVBoxLayout * layoutDettagli = new QVBoxLayout(contenitoreDettagli);
    layoutDettagli->addWidget(closeButton, 0, Qt::AlignRight);
    layoutDettagli->addWidget(label,0,Qt::AlignCenter);
    contenitoreDettagli->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    layoutDettagli->setSpacing(0);

    layoutPrincipale->addWidget(contenitoreDettagli,0, Qt::AlignCenter);
    
    connect(closeButton, &QToolButton::clicked, this, [this](){
                                    emit removeImage();
                                    reset();
    });

}

void InsertImageFrame::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit clicked();
    }
    QFrame::mousePressEvent(event);
}

void InsertImageFrame::setText(const QString &text) {
    label->setText(text);
    if (text != defaultText) {
        label->setStyleSheet("color: #BDCED3; font-size:16px;");
    }
}

void InsertImageFrame::reset() {
    setText(defaultText);
    closeButton->setVisible(false); 
}


void InsertImageFrame::insertImage(const QString &text){
    setText(text);            
    closeButton->setVisible(true); 
}
