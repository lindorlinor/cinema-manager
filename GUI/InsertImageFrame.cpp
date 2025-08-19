#include "InsertImageFrame.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QToolButton>

InsertImageFrame::InsertImageFrame(QWidget *parent)
    : QFrame(parent), 
      defaultText("<span style='color:white; font-size:16px;'>+ <u>Aggiungi copertina</u></span>"
                  "<span style='color:gray; font-size:16px;'> oppure rilasciala</span>"), 
      label(new QLabel(defaultText.text(), this)),
      closeButton(new QToolButton(this))
{   
    setObjectName("frame");
    defaultText.setTextFormat(Qt::RichText);
    setStyleSheet(
        "#frame { border: 2px dashed #4E7F8B; border-radius: 12px; } "
        "QLabel { qproperty-alignment: AlignCenter; } "
        "QToolButton { border: none; color: #708084; font-weight: bold; } "
        "QToolButton:hover { color: #4E7F8B; }"
    );

    closeButton->setText("x");
    closeButton->setVisible(false);
    closeButton->setFixedSize(16,16);
    label->setContentsMargins(20,0,20,0);
    label->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
  

    QVBoxLayout *layoutPrincipale = new QVBoxLayout(this);
    QWidget * contenitoreDettagli = new QWidget;
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
}

void InsertImageFrame::reset() {
    label->setText(defaultText.text());
    closeButton->setVisible(false); 
}

void InsertImageFrame::insertImage(const QString &text){
    setText(text);            
    closeButton->setVisible(true); 
}
