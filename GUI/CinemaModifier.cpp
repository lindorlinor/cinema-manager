#include "CinemaModifier.h"

CinemaModifier::CinemaModifier(Cinema* cinema, QWidget *parent): QDialog(parent), editCinema(cinema){
   setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    /* setAttribute(Qt::WA_TranslucentBackground); */
    imagePath = QString::fromStdString(editCinema->getCopertinaCinema());

    QHBoxLayout* popUpH1 = new QHBoxLayout;
    QHBoxLayout* popUpH2 = new QHBoxLayout;
    QVBoxLayout* popUpV1 = new QVBoxLayout; 
    QVBoxLayout* popUpV2 = new QVBoxLayout;
    QWidget* widgetPopUp1 = new QWidget(this);
    QWidget* widgetPopUp2 = new QWidget(this);
    QWidget* widgetPopUp3 = new QWidget(this);
    
    QLabel* label = new QLabel("Scegli un nuovo nome per il cinema", this);
    img = new QLabel(this);
    QPixmap pix(QString::fromStdString(editCinema->getCopertinaCinema())); 
    img->setPixmap(pix);
    img->setScaledContents(true);
    imgFrame = new InsertImageFrame(" <span style='color:#05313c; font-size:16px;'><b> +<u>Cambia la copertina</u></b></span><br>",
                                                        "#frame { border: 3px dashed #05313c; border-radius: 12px; } "
                                                        "QLabel { qproperty-alignment: AlignCenter; }" 
                                                        "QToolButton { border: none; color: #073c47; font-weight: bold; } "
                                                        "QToolButton:hover { color: #ffffffff; }", this);  
    saveButton = new QPushButton("salva", this);
    saveButton->setEnabled(false);
    QPushButton* cancelButton = new QPushButton("annulla", this);
    errorLabel = new QLabel(this);
    lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText("Nuovo nome del cinema...");
    lineEdit->setText(QString::fromStdString(editCinema->getNomeCinema()));

    popUpH1->addWidget(cancelButton);
    popUpH1->addWidget(saveButton);
    widgetPopUp1->setLayout(popUpH1);

    popUpV1->addWidget(img);
    popUpV1->addWidget(imgFrame);
    widgetPopUp2->setLayout(popUpV1);

    popUpV2->addWidget(label);
    popUpV2->addWidget(lineEdit);
    popUpV2->addWidget(errorLabel);
    popUpV2->addWidget(widgetPopUp1);
    widgetPopUp3->setLayout(popUpV2);

    popUpH2->addWidget(widgetPopUp2);
    popUpH2->addWidget(widgetPopUp3);
    
    setLayout(popUpH2);

    //connect
    connect(saveButton, &QPushButton::clicked, this, [this](){saveEdit(); accept();});
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(lineEdit, &QLineEdit::textChanged, this, &CinemaModifier::checkCinemaNameAvailability);
    connect(imgFrame,&InsertImageFrame::clicked,this,&CinemaModifier::chooseImage);
    connect(imgFrame, &InsertImageFrame::removeImage, this, &CinemaModifier::removeImage);

    //style
    widgetPopUp2->setMaximumWidth(250);
    imgFrame->setCursor(Qt::PointingHandCursor);
    errorLabel->setStyleSheet("color: red; font-size: 12pt;");
    errorLabel->setText("");
    errorLabel->setVisible(false);
    errorLabel->setAlignment(Qt::AlignCenter);
}

void CinemaModifier::checkCinemaNameAvailability(){
    QString text = lineEdit->text().trimmed();
    if (text.isEmpty()) {
        errorLabel->setVisible(false);
        saveButton->setEnabled(false);
        return;
    }

    isAvailable = true;

    QList<Cinema*> cinemaList;
    CinemaRepositoryJson manager;
    manager.loadCinema(cinemaList);

    for (const Cinema* c: cinemaList) {
        if (QString::fromStdString(c->getNomeCinema()).compare(text, Qt::CaseInsensitive) == 0) {
            isAvailable = false;
        }
    }

    if (!isAvailable) {
        errorLabel->setText("Nome non disponibile. Scegliere un altro nome per il cinema");
        errorLabel->setVisible(true);
        saveButton->setEnabled(false);
    } else {
        errorLabel->setVisible(false);
        saveButton->setEnabled(true);
    }
}

//slot
void CinemaModifier::chooseImage(){
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Seleziona un'immagine"),
        QString(),
        tr("Immagini (*.png *.jpg *.jpeg *.bmp *.gif)")
    );

    if (!fileName.isEmpty()) {
        imagePath = ":/images/" + QFileInfo(fileName).fileName();
        QPixmap pixmap(imagePath);
        img->setAlignment(Qt::AlignCenter);
        img->setPixmap(pixmap.scaled(200,200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        imgFrame->insertImage(QFileInfo(fileName).fileName());
    }
}

void CinemaModifier::removeImage(){
    QPixmap pixmap(":/images/default.png"); 
    img->setPixmap(pixmap.scaled(200,200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imagePath = QString::fromStdString(editCinema->getCopertinaCinema());
}

void CinemaModifier::saveEdit(){
    editCinema->setNomeCinema((lineEdit->text().trimmed()).toStdString());
    editCinema->setCopertinaCinema(imagePath.toStdString());
}