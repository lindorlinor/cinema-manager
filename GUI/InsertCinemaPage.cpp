#include "InsertCinemaPage.h"
#include "../DataFiles/CinemaXmlRepository.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QDomDocument>
#include <QCoreApplication>

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

    //Messaggio di errore
    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color: red; font-size: 11px;");
    errorLabel->setText("");
    errorLabel->setVisible(false);

    layoutInput->addLayout(nameLayout);
    layoutInput->addWidget(errorLabel);
    layoutInput->addWidget(imageArea);

    connect(textInput, &QLineEdit::textChanged, this, &InsertCinemaPage::checkCinemaNameAvailability);
    connect(imageArea,&InsertImageFrame::clicked,this,&InsertCinemaPage::chooseImage);
    input->setFixedSize(500,400);
    layoutInput->setSpacing(30);
    layout->addWidget(input,0, Qt::AlignCenter);

    QWidget * contenitorePulsanti = new QWidget;
    QHBoxLayout * layoutPulsanti = new QHBoxLayout(contenitorePulsanti);
    escButton = new QPushButton("Annulla");
    saveButton = new QPushButton("Salva");
    connect(escButton,&QPushButton::clicked,this,[=](){emit returnCinemaSelectionPage();});
    connect(saveButton,&QPushButton::clicked,this,&InsertCinemaPage::saveCinemaInXml);
    layoutPulsanti->setSpacing(150);
    layoutPulsanti->addWidget(escButton,0, Qt::AlignCenter);
    layoutPulsanti->addWidget(saveButton,0, Qt::AlignCenter);
    layout->addWidget(contenitorePulsanti, 0, Qt::AlignHCenter);
    
}

void InsertCinemaPage::checkCinemaNameAvailability(const QString& text) {
    QString nome = text.trimmed();

    // Carico la lista dei cinema esistenti
    CinemaXmlRepository repo(QDir(QCoreApplication::applicationDirPath()).filePath(".."));
    QList<Cinema> cinemaList = repo.loadAllCinemas();
    
    bool isAvailable = true;
    for (const Cinema& c: cinemaList) {
        if (c.nome.compare(nome, Qt::CaseInsensitive) == 0) {
            isAvailable = false;
            break;
        }
    }

    if (!isAvailable) {
        errorLabel->setText("Nome non disponibile. Scegliere un altro nome per il cinema");
        errorLabel->setVisible(true);
        saveButton->setEnabled(false); // disabilita bottone
    } else {
        errorLabel->setVisible(false);
        saveButton->setEnabled(true);
    }
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
        imageArea->setText(QFileInfo(fileName).fileName());
    }
}

void InsertCinemaPage::saveCinemaInXml() {
    Cinema cinema;
    cinema.nome = textInput->text().trimmed();
    cinema.imagePath = imagePath;

    CinemaXmlRepository repo(QDir(QCoreApplication::applicationDirPath()).filePath(".."));
    if (!repo.saveCinema(cinema)) {
        QMessageBox::critical(this, tr("Errore"), tr("Impossibile salvare il file XML."));
        return;
    }

    QMessageBox::information(this, tr("Salvato"), tr("Cinema salvato correttamente."));
    emit returnCinemaSelectionPage();
}


void InsertCinemaPage::reset() {
    textInput->clear();
    imagePath.clear();
    imageArea->reset();
    errorLabel->setVisible(false);
    saveButton->setEnabled(true);
}