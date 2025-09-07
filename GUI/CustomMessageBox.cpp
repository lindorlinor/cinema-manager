#include "CustomMessageBox.h"
#include <QFrame>
#include <QMouseEvent>

CustomMessageBox::CustomMessageBox(QWidget *parent):QDialog(parent){
    
    setContentsMargins(20,20,20,20);
    setFixedSize(485, 285);
    setObjectName("customMessageBox");
    //rimuove cornice e button. mette la finestra always on top
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setModal(true);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    titleLabel = new QLabel(this);
    titleLabel->setObjectName("titleLabel");

    QFrame *line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setObjectName("separatorLine");

    mainMessageLabel = new QLabel(this);
    mainMessageLabel->setWordWrap(true);
    mainMessageLabel->setObjectName("mainMessageLabel");

    infoMessageLabel = new QLabel(this);
    infoMessageLabel->setWordWrap(true);
    infoMessageLabel->setObjectName("infoMessageLabel");

    cancelButton = new QPushButton("Annulla", this);
    cancelButton->setObjectName("cancelButton");
    confirmButton = new QPushButton("Conferma", this);
    confirmButton->setObjectName("confirmButton");


    QWidget* contenitoreButton = new QWidget(this); 
    QHBoxLayout *layoutbutton = new QHBoxLayout(contenitoreButton);

    cancelButton->setMinimumWidth(100);
    confirmButton->setMinimumWidth(100);

    // contenitoreButton->setStyleSheet("background-color: red");
    layoutbutton->addWidget(cancelButton);
    layoutbutton->addStretch();
    layoutbutton->addWidget(confirmButton);

    // Layout principale
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(line);
    mainLayout->addSpacing(30);
    mainLayout->addWidget(mainMessageLabel);
    mainLayout->addWidget(infoMessageLabel);
    mainLayout->addStretch();
    mainLayout->addWidget(contenitoreButton);

    connect(cancelButton, &QPushButton::clicked, this, &CustomMessageBox::reject); //reject e accept ereditati da QDialog
    connect(confirmButton, &QPushButton::clicked, this, &CustomMessageBox::accept);
}

void CustomMessageBox::setTitleText(const QString &text)
{
    titleLabel->setText(text);
}

void CustomMessageBox::setMainMessage(const QString &text)
{
    mainMessageLabel->setText(text);
}

void CustomMessageBox::setInfoMessage(const QString &text)
{
    infoMessageLabel->setText(text);
}


//per permettere lo postamento della finestra
void CustomMessageBox::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void CustomMessageBox::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
}

