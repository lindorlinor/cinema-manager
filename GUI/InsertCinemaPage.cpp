#include "InsertCinemaPage.h"
#include "../DataFiles/CinemaXmlRepository.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QDomDocument>
#include <QCoreApplication>

InsertCinemaPage::InsertCinemaPage(QWidget * parent):QWidget(parent),textInput(new QLineEdit(this)),imageArea(new InsertImageFrame(this)),imageLabel(new QLabel){
    
    QFrame* framePrincipale = new QFrame();
    framePrincipale->setMinimumSize(630, 600);
    framePrincipale->setMaximumSize(1000, 750);

    QVBoxLayout *layoutFrame = new QVBoxLayout(framePrincipale);
    
    QLabel *titolo = new QLabel("Inserisci nuovo cinema");
    QFont fontTitolo = titolo->font();
    fontTitolo.setPointSize(21);
    fontTitolo.setBold(true);
    titolo->setFont(fontTitolo);

    QLabel* descrizione = new QLabel("Scegli un nome e un'immagine per un nuovo cinema");
    QFont fontDescrizione = descrizione->font();
    fontDescrizione.setPointSize(10);
    descrizione->setFont(fontDescrizione);

    titolo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    descrizione->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    //crea il contenitore per le due label titolo e descrizione e lo distanzia in verticale dal resto che verrà inserito nel frame
    QWidget* contenitoreLabels = new QWidget;
    QVBoxLayout* layoutLabels = new QVBoxLayout(contenitoreLabels);
    layoutLabels->addWidget(titolo);
    layoutLabels->addWidget(descrizione);
    layoutLabels->setAlignment(Qt::AlignLeft);
    layoutLabels->setContentsMargins(0,20,0,70);
    contenitoreLabels->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); //permette il margine, altrimenti non sarebbe esattamente 70
    //aggiunge il contenitore per le due label al frame e le allinea a sinistra
    layoutFrame->addWidget(contenitoreLabels);
    layoutFrame->setAlignment( Qt::AlignLeft);

    contenitoreLabels->setObjectName("caca");

    QHBoxLayout * splitter = new QHBoxLayout;
    splitter->setSpacing(30);
    QWidget * contenitoreInput = new QWidget;
    QVBoxLayout * layoutInput = new QVBoxLayout(contenitoreInput);

    QHBoxLayout *layoutNome = new QHBoxLayout;
    QLabel *nameLabel = new QLabel("Nome cinema:");
    layoutNome->addWidget(nameLabel);
    layoutNome->addWidget(textInput);

    //Messaggio di errore
    errorLabel = new QLabel;
    errorLabel->setStyleSheet("color: red; font-size: 11px;");
    errorLabel->setText("");
    errorLabel->setVisible(false);
    errorLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    layoutInput->addLayout(layoutNome);
    layoutInput->addWidget(errorLabel);
    layoutInput->addWidget(imageArea);
    connect(textInput, &QLineEdit::textChanged, this, &InsertCinemaPage::checkCinemaNameAvailability);
    connect(imageArea,&InsertImageFrame::clicked,this,&InsertCinemaPage::chooseImage);
    contenitoreInput->setMinimumSize(330,360);
    // contenitoreInput->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    contenitoreInput->setObjectName("pupu");

    // imageLabel->setMinimumSize(200,400);
    imageLabel->setMaximumSize(330,400);
    QPixmap pixmap(":/images/coverCinema.png");
    imageLabel->setPixmap(pixmap);
    imageLabel->setAlignment(Qt::AlignCenter);
    pixmap = pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation); // ridimensiona se vuoi
    // Aggiungi l'immagine a sinistra nel layout splitter
    splitter->insertWidget(0, imageLabel); // 0 = prima posizione
    splitter->addWidget(contenitoreInput);

    layoutFrame->addLayout(splitter);

    QWidget * contenitorePulsanti = new QWidget;
    QHBoxLayout * layoutPulsanti = new QHBoxLayout(contenitorePulsanti);
    escButton = new QPushButton("Annulla");
    saveButton = new QPushButton("Salva");
    escButton->setFixedSize(160, 40); 
    saveButton->setFixedSize(160, 40); 
    connect(escButton,&QPushButton::clicked,this,&InsertCinemaPage::returnCinemaSelectionPage);
    connect(saveButton,&QPushButton::clicked,this,&InsertCinemaPage::saveCinemaInXml);
    layoutPulsanti->setSpacing(150);
    layoutPulsanti->addWidget(escButton,0, Qt::AlignCenter);
    layoutPulsanti->addWidget(saveButton,0, Qt::AlignCenter);
    layoutInput->addWidget(contenitorePulsanti, 0, Qt::AlignHCenter);
    
    QVBoxLayout * layoutPrincipale = new QVBoxLayout(this);
    layoutPrincipale->addWidget(framePrincipale);
    layoutPrincipale->setAlignment(Qt::AlignCenter);
    setLayout(layoutPrincipale);
    setStyleSheet("QScrollArea { border: none; } QFrame { background-color: pink} QLabel { background-color: yellow} #caca{background-color: red} #pupu{background-color:blue}");
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

void InsertCinemaPage::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);

    if (width() >= 800 && height() >= 600) {
        imageLabel->show();
    } else {
        imageLabel->hide();
    }
}
