#include "InsertCinemaPage.h"
#include "../DataFiles/CinemaXmlRepository.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QDomDocument>
#include <QCoreApplication>

InsertCinemaPage::InsertCinemaPage(QWidget * parent):QWidget(parent),
                                            frameLayout(new QVBoxLayout),
                                            isAvailable(false),
                                            hasCustomImage(false),
                                            textInput(new QLineEdit(this)),
                                            imageArea(new InsertImageFrame( "<span style='color:white; font-size:16px;'>+ <u>Aggiungi copertina</u></span>"
                                                                            "<span style='color: #708084; font-size:16px;'> oppure rilasciala</span>",
                                                                            "#frame { border: 2px dashed #4E7F8B; border-radius: 12px; } "
                                                                            "QToolButton { border: none; color: #BDCED3; font-weight: bold; } "
                                                                            "QToolButton:hover { color: #ffffffff; }", this)),
                                            imageLabel(new QLabel(this)),imagePath(":/../images/default.png"),
                                            escButton(new QPushButton("Annulla",this)),
                                            saveButton(new QPushButton("Salva",this))
{
    
    QFrame* frameCentrale = new QFrame(this);
    frameCentrale->setMinimumSize(630, 600);
    frameCentrale->setMaximumSize(1000, 750);
    frameCentrale->setLayout(frameLayout);
    
    createHeader();

    createSplitView();
    
    QVBoxLayout * layoutPrincipale = new QVBoxLayout(this);
    layoutPrincipale->addWidget(frameCentrale);
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

    CinemaXmlRepository repo(QDir(QCoreApplication::applicationDirPath()).filePath("../Json_XML"));
    isAvailable = repo.isNameAvailable(text);

    if (!isAvailable) {
        errorLabel->setText("Nome non disponibile. Scegliere un altro nome per il cinema");
        errorLabel->setVisible(true);
        saveButton->setEnabled(false);
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
    imagePath=":/images/default.png";  //qui bisogna mettere l'immagine di default che vogliamo mettere 
    hasCustomImage = false;
}

//crea il file xml del cinema e appare un messaggio che conferma il successo dell'operazione
void InsertCinemaPage::saveCinemaInXml() {
    Cinema cinema;
    cinema.nome = textInput->text().trimmed();
    cinema.imagePath = imagePath;

    CinemaXmlRepository repo(QDir(QCoreApplication::applicationDirPath()).filePath("../Json_XML"));
    if (!repo.saveCinema(cinema)) {
        QMessageBox::critical(this, tr("Errore"), tr("Impossibile salvare il file XML."));
        return;
    }

    QMessageBox::information(this, tr("Salvato"), tr("Cinema salvato correttamente."));
    emit returnCinemaSelectionPage();
}

/**
 * @brief per togliere quello che era stato precedentemente inserito nei campi di input e nella imageArea. 
 * 
 * In particolare per farlo: cancella l'input text, setta l'immagine di default, richima @ref InsertImageFrame::reset, setta la label
 * di errore invisibile, setta il pulsante di salvataggio disabilitato (perchè la input text è vuota)
 *  
 * @note reset() viene richiamato sempre dallo slot @ref MainWindow::showInsertCinemaPage che mostra la pagina di inserimento cinema.
 * Generalmente @ref MainWindow::showInsertCinemaPage è collegato a tutti i pulsanti/oggetti che mandano un segnale per andare alla pagina 
 * di inserimento di un cinema.
 * 
 * @see MainWindow::MainWindow @see CinemaSelectionPage::insertCinema
 * 
 */

//@to do e se mettessi che se textInput è clear allora saveButton è disabilitato, con un trigger connect?
void InsertCinemaPage::reset() {
    textInput->clear();
    imagePath=":/images/default.png";
    imageArea->reset();
    errorLabel->setVisible(false);
    saveButton->setEnabled(false);
}

/**
 * @brief imposta l'immagine visibile solo quando la finestra ha dimensione minima 800x600, altrimenti rimane nascosta
 * 
 */
void InsertCinemaPage::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);

    if (width() >= 800 && height() >= 600) {
        imageLabel->show();
    } else {
        imageLabel->hide();
    }
}


void InsertCinemaPage::createHeader(){
    QLabel *titolo = new QLabel("Inserisci nuovo cinema",this);
    QFont fontTitolo = titolo->font();
    fontTitolo.setPointSize(21);
    fontTitolo.setBold(true);
    titolo->setFont(fontTitolo);
    
    QLabel* descrizione = new QLabel("Scegli un nome e un'immagine per un nuovo cinema",this);
    QFont fontDescrizione = descrizione->font();
    fontDescrizione.setPointSize(10);
    descrizione->setFont(fontDescrizione);

    titolo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    descrizione->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    //crea il contenitore per le due label titolo e descrizione e lo distanzia in verticale dal resto che verrà inserito nel frame
    QWidget* contenitoreLabels = new QWidget(this);
    QVBoxLayout* layoutLabels = new QVBoxLayout(contenitoreLabels);
    layoutLabels->addWidget(titolo);
    layoutLabels->addWidget(descrizione);
    layoutLabels->setAlignment(Qt::AlignLeft);
    contenitoreLabels->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); //permette il margine, altrimenti non sarebbe esattamente 70
    //aggiunge il contenitore per le due label al frame e le allinea a sinistra
    frameLayout->addWidget(contenitoreLabels);
    frameLayout->addStretch();
    frameLayout->setAlignment( Qt::AlignLeft);

    // contenitoreLabels->setObjectName("caca");
}

void InsertCinemaPage::createSplitView(){
    QHBoxLayout * splitter = new QHBoxLayout;
    splitter->setSpacing(30);

    QWidget* contenitoredx = new QWidget(this);
    QVBoxLayout * layoutdx = new QVBoxLayout(contenitoredx);


    createLayoutInput(layoutdx);

    contenitoredx->setMinimumHeight(400);  //alto quanto l'immagine, così quando appare l'immagine la transizione è giusto un po più fluida

 
    // contenitoredx->setObjectName("gaga");
    imageLabel->setMaximumSize(330,400);
    QPixmap pixmap(":/images/coverCinema.png");
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setPixmap(pixmap);

    splitter->insertWidget(0, imageLabel);
    splitter->addWidget(contenitoredx);

    frameLayout->addLayout(splitter);

    createButtonLayout(layoutdx);

    layoutdx->setContentsMargins(0,0,0,0);
}

void InsertCinemaPage::createLayoutInput(QVBoxLayout* layoutdx) {
    QWidget * contenitoreInput = new QWidget(this);
    QVBoxLayout * layoutInput = new QVBoxLayout(contenitoreInput);

    
    QVBoxLayout *layoutNome = new QVBoxLayout;
    QLabel *nameLabel = new QLabel("Nome cinema:",this);
    nameLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    layoutNome->addWidget(nameLabel);
    layoutNome->addWidget(textInput);
    
    errorLabel = new QLabel(this);
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
    
    layoutInput->setContentsMargins(20,20,20,20);
    layoutdx->addWidget(contenitoreInput);
    // contenitoreInput->setObjectName("pupu");
}

void InsertCinemaPage::createButtonLayout(QVBoxLayout* layoutdx) {
    QWidget * contenitorePulsanti = new QWidget(this);
    QHBoxLayout * layoutPulsanti = new QHBoxLayout(contenitorePulsanti);

   
    escButton->setFixedSize(160, 40); 
    saveButton->setFixedSize(160, 40); 

    connect(escButton,&QPushButton::clicked,this,&InsertCinemaPage::returnCinemaSelectionPage);
    connect(saveButton,&QPushButton::clicked,this,[this](){
        if(!hasCustomImage)
            QMessageBox::information(this, tr("Immagine non selezionata"), tr("Verrà impostata un'immagine di default"));
        saveCinemaInXml();
    });

    layoutPulsanti->addWidget(escButton);
    layoutPulsanti->addStretch();
    layoutPulsanti->addWidget(saveButton);

    layoutdx->addWidget(contenitorePulsanti);
    // contenitorePulsanti->setObjectName("gugu");

    layoutPulsanti->setContentsMargins(0,0,0,0);
}
