#include "InsertCinemaPage.h"
#include "../DataFiles/CinemaXmlRepository.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QDomDocument>
#include <QCoreApplication>

InsertCinemaPage::InsertCinemaPage(QWidget * parent):QWidget(parent),isAvailable(false),textInput(new QLineEdit(this)),imageArea(new InsertImageFrame(this)),imageLabel(new QLabel),imagePath(":/../images/image4.png"){
    
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
    // layoutLabels->setContentsMargins(0,20,0,70);
    contenitoreLabels->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); //permette il margine, altrimenti non sarebbe esattamente 70
    //aggiunge il contenitore per le due label al frame e le allinea a sinistra
    layoutFrame->addWidget(contenitoreLabels);
    layoutFrame->addStretch();
    layoutFrame->setAlignment( Qt::AlignLeft);

    contenitoreLabels->setObjectName("caca");

    QHBoxLayout * splitter = new QHBoxLayout;
    splitter->setSpacing(30);
    QWidget* contenitoredx = new QWidget;
    QVBoxLayout * layoutdx = new QVBoxLayout(contenitoredx);
    QWidget * contenitoreInput = new QWidget;
    QVBoxLayout * layoutInput = new QVBoxLayout(contenitoreInput);

    layoutdx->addWidget(contenitoreInput);

    QVBoxLayout *layoutNome = new QVBoxLayout;
    QLabel *nameLabel = new QLabel("Nome cinema:");
    nameLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    layoutNome->addWidget(nameLabel);
    layoutNome->addWidget(textInput);

    
    errorLabel = new QLabel;
    errorLabel->setStyleSheet("color: red; font-size: 11px;");
    errorLabel->setText("");
    errorLabel->setVisible(false);
    errorLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    layoutInput->addLayout(layoutNome);
    layoutInput->addWidget(errorLabel);
    layoutInput->addStretch();
    imageArea->setMinimumSize(365,240);
    imageArea->setMaximumSize(7435,240);


    layoutInput->addWidget(imageArea);
    layoutInput->setAlignment(Qt::AlignCenter);
    connect(textInput, &QLineEdit::textChanged, this, &InsertCinemaPage::checkCinemaNameAvailability);
    connect(imageArea,&InsertImageFrame::clicked,this,&InsertCinemaPage::chooseImage);
    connect(imageArea,&InsertImageFrame::removeImage,this,&InsertCinemaPage::removeImage);

    contenitoredx->setMinimumHeight(400); //ricordati di cambiare valore se cambi risoluzione e dimensioni dell'immagine
    contenitoreInput->setObjectName("pupu");
    contenitoredx->setObjectName("gaga");
    imageLabel->setMaximumSize(330,400);
    QPixmap pixmap(":/images/coverCinema.png");
    imageLabel->setPixmap(pixmap);
    imageLabel->setAlignment(Qt::AlignCenter);
    pixmap = pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
   
    splitter->insertWidget(0, imageLabel);
    splitter->addWidget(contenitoredx);

    layoutFrame->addLayout(splitter);
    QWidget * contenitorePulsanti = new QWidget;
    QHBoxLayout * layoutPulsanti = new QHBoxLayout(contenitorePulsanti);
    escButton = new QPushButton("Annulla");
    saveButton = new QPushButton("Salva");
    escButton->setFixedSize(160, 40); 
    saveButton->setFixedSize(160, 40); 
    connect(escButton,&QPushButton::clicked,this,&InsertCinemaPage::returnCinemaSelectionPage);
    connect(saveButton,&QPushButton::clicked,this,[this](){
        if(!hasCustomImage)
        QMessageBox::information(this, tr("Immagine non selezionata"), tr("Verrà impostata un'immagine di default"));
        emit saveCinemaInXml();
    });
    
    layoutPulsanti->addWidget(escButton);
    layoutPulsanti->addStretch();
    layoutPulsanti->addWidget(saveButton);
    
    layoutdx->addWidget(contenitorePulsanti);
    contenitorePulsanti->setObjectName("gugu");

    layoutPulsanti->setContentsMargins(0,0,0,0); //attacca a filo i pulsanti al contenitorePulsanti
    layoutInput->setContentsMargins(20,20,20,20);
    layoutdx->setContentsMargins(0,0,0,0); //attacca a filo il contenitorePulsanti al layoutdx
    QVBoxLayout * layoutPrincipale = new QVBoxLayout(this);
    layoutPrincipale->addWidget(framePrincipale);
    layoutPrincipale->setAlignment(Qt::AlignCenter);
    setLayout(layoutPrincipale);
    // setStyleSheet("QScrollArea { border: none; } QFrame { background-color: pink} QLabel { background-color: yellow} #caca{background-color: red} #pupu{background-color:blue} #gugu{background-color:purple} #gaga{background-color: green}");
}

void InsertCinemaPage::checkCinemaNameAvailability(const QString& text) {
    if (text.isEmpty()) {
        errorLabel->setVisible(false);
        saveButton->setEnabled(false);
        return;
    }
    QString nome = text.trimmed();

    // Carico la lista dei cinema esistenti
    CinemaXmlRepository repo(QDir(QCoreApplication::applicationDirPath()).filePath(".."));
    QList<Cinema> cinemaList = repo.loadAllCinemas();
    isAvailable=true;
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
        hasCustomImage = true;
        imageArea->insertImage(QFileInfo(fileName).fileName());
    }
}

void InsertCinemaPage::removeImage(){
    imagePath=":/../images/image4.png";  //qui bisogna mettere l'immagine di default che vogliamo mettere 
    hasCustomImage = false;
}

//crea il file xml del cinema e appare un messaggio che conferma il successo dell'operazione
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

//per togliere ciò che è stato precedentemente inserito quando la pagina viene richiamata (l'utente ritorna sulla pagina)
void InsertCinemaPage::reset() {
    textInput->clear();
    imagePath=":/../images/image4.png";
    imageArea->reset();
    errorLabel->setVisible(false);
    saveButton->setEnabled(false);
}

//appare l'immagine solo quando la finestra ha dimensione minima di 800x600
void InsertCinemaPage::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);

    if (width() >= 800 && height() >= 600) {
        imageLabel->show();
    } else {
        imageLabel->hide();
    }
}
