#include "InsertCinemaPage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
InsertCinemaPage::InsertCinemaPage(QWidget * parent):QWidget(parent),textInput(new QLineEdit(this)),imageArea(new InsertImageFrame(this)){
    QVBoxLayout * layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Inserisci un nuovo cinema", this);
    QFont font = label->font();
    font.setPointSize(21);
    font.setBold(true);
    label->setFont(font);
    layout->addWidget(label, 0, Qt::AlignCenter);

    QWidget * input = new QWidget(this);
    QVBoxLayout * layoutInput = new QVBoxLayout(input);

    QHBoxLayout *nameLayout = new QHBoxLayout;
    QLabel *nameLabel = new QLabel("Nome cinema:", this);
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(textInput);

    layoutInput->addLayout(nameLayout);
    layoutInput->addWidget(imageArea);
    connect(imageArea,&InsertImageFrame::clicked,this,&InsertCinemaPage::chooseImage);
    input->setFixedSize(500,400);
    layoutInput->setSpacing(30);
    layout->addWidget(input,0, Qt::AlignCenter);

    QWidget * contenitorePulsanti = new QWidget;
    QHBoxLayout * layoutPulsanti = new QHBoxLayout(contenitorePulsanti);
    QPushButton * escButton = new QPushButton("Annulla");
    QPushButton * saveButton = new QPushButton("Salva");
    connect(escButton,&QPushButton::clicked,this,[=](){emit returnCinemaSelectionPage();});
    layoutPulsanti->setSpacing(150);
    layoutPulsanti->addWidget(escButton,0, Qt::AlignCenter);
    layoutPulsanti->addWidget(saveButton,0, Qt::AlignCenter);
    layout->addWidget(contenitorePulsanti, 0, Qt::AlignHCenter);
    
}

void InsertCinemaPage::chooseImage(){
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Seleziona un'immagine"),
        QString(),
        tr("Immagini (*.png *.jpg *.jpeg *.bmp *.gif)")
    );

    if (!fileName.isEmpty()) {
        imagePath = fileName;
        // Mostra solo il nome file
        imageArea->setText(QFileInfo(fileName).fileName());
    }
}

