#include "InsertCinemaPage.h"
#include "Custom/CustomMessageBox.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QDomDocument>
#include <QCoreApplication>
#include <QApplication>

InsertCinemaPage::InsertCinemaPage(QList<Cinema *> &w_cinema, QWidget *parent) : QWidget(parent), ic_cinema(w_cinema),
                                                                                 frameLayout(new QVBoxLayout),
                                                                                 textInput(new QLineEdit(this)),
                                                                                 imageArea(new InsertImageFrame("<span style='color:white; font-size:16px;'>+ <u>Aggiungi copertina</u></span>",
                                                                                                                "#frame { border: 2px dashed #4E7F8B; border-radius: 12px; } "
                                                                                                                "QToolButton { border: none; color: #BDCED3; font-weight: bold; } "
                                                                                                                "QToolButton:hover { color: #ffffffff; }",
                                                                                                                this)),
                                                                                 imagePath(":/images/coverCinema.png"), imageLabel(new QLabel(this)),
                                                                                 escButton(new QPushButton("Annulla", this)),
                                                                                 saveButton(new QPushButton("Salva", this)),
                                                                                 hasCustomImage(false),
                                                                                 isAvailable(false)
{
    QFrame *frameCentrale = new QFrame(this);
    frameCentrale->setMinimumSize(630, 500);
    frameCentrale->setMaximumSize(800, 500);
    frameCentrale->setLayout(frameLayout);

    createHeader();

    createSplitView();

    QVBoxLayout *layoutPrincipale = new QVBoxLayout(this);
    layoutPrincipale->addWidget(frameCentrale);
    layoutPrincipale->setAlignment(Qt::AlignCenter);
    setLayout(layoutPrincipale);

    escButton->setObjectName("escButInsertCinema");
    saveButton->setObjectName("saveButInsertCinema");
    escButton->setCursor(Qt::PointingHandCursor);
    saveButton->setCursor(Qt::PointingHandCursor);
}

void InsertCinemaPage::checkCinemaNameAvailability(const QString &text)
{
    if (text.isEmpty())
    {
        errorLabel->setVisible(false);
        saveButton->setEnabled(false);
        return;
    }
    QString nome = text.trimmed();

    isAvailable = true;

    for (const Cinema *c : ic_cinema)
    {
        if (QString::fromStdString(c->getNomeCinema()).compare(text, Qt::CaseInsensitive) == 0)
        {
            isAvailable = false;
        }
    }

    if (!isAvailable)
    {
        errorLabel->setText("Nome non disponibile. Scegliere un altro nome per il cinema");
        errorLabel->setVisible(true);
        saveButton->setEnabled(false);
    }
    else
    {
        errorLabel->setVisible(false);
        saveButton->setEnabled(true);
    }
}

void InsertCinemaPage::chooseImage()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Seleziona un'immagine"),
        QString(),
        tr("Immagini (*.png *.jpg *.jpeg *.bmp *.gif)"));

    if (!fileName.isEmpty())
    {
        imagePath = fileName; /* ":/images/" + QFileInfo(fileName).fileName(); */
        hasCustomImage = true;
        imageArea->insertImage(QFileInfo(fileName).fileName());
    }
}

void InsertCinemaPage::removeImage()
{
    imagePath = ":/images/coverCinema.png";
    hasCustomImage = false;
}

// crea il file xml del cinema e appare un messaggio che conferma il successo dell'operazione
void InsertCinemaPage::saveCinemaInJson()
{

    Cinema *cinema = new Cinema(textInput->text().trimmed().toStdString(), imagePath.toStdString());
    ic_cinema.append(cinema);

    CinemaRepositoryJson cinemaManager;
    cinemaManager.saveCinemaInJson(cinema);

    CustomMessageBox msgbox(this);
    msgbox.move(QApplication::primaryScreen()->geometry().center() - msgbox.rect().center());
    msgbox.setTitleText("Salvato");
    msgbox.setMainMessage("Cinema salvato correttamente.");
    msgbox.hideCancelButton();
    msgbox.setInfoMessage("Premi ok per continuare.");
    msgbox.exec();
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
void InsertCinemaPage::reset()
{
    textInput->clear();
    imagePath = ":/images/coverCinema.png";
    imageArea->reset();
    errorLabel->setVisible(false);
    saveButton->setEnabled(false);
}

/**
 * @brief imposta l'immagine visibile solo quando la finestra ha dimensione minima 800x600, altrimenti rimane nascosta
 *
 */
void InsertCinemaPage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (width() >= 800 && height() >= 600)
    {
        imageLabel->show();
    }
    else
    {
        imageLabel->hide();
    }
}

void InsertCinemaPage::createHeader()
{
    QLabel *titolo = new QLabel("Inserisci nuovo cinema", this);
    QFont fontTitolo = titolo->font();
    fontTitolo.setPointSize(25);
    fontTitolo.setBold(true);
    titolo->setFont(fontTitolo);

    QLabel *descrizione = new QLabel("Scegli un nome e un'immagine per un nuovo cinema", this);
    QFont fontDescrizione = descrizione->font();
    fontDescrizione.setPointSize(14);
    descrizione->setFont(fontDescrizione);

    titolo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    descrizione->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    // crea il contenitore per le due label titolo e descrizione e lo distanzia in verticale dal resto che verrà inserito nel frame
    QWidget *contenitoreLabels = new QWidget(this);
    QVBoxLayout *layoutLabels = new QVBoxLayout(contenitoreLabels);
    layoutLabels->addWidget(titolo);
    layoutLabels->addWidget(descrizione);
    layoutLabels->setAlignment(Qt::AlignLeft);
    contenitoreLabels->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    frameLayout->addWidget(contenitoreLabels);
    frameLayout->addStretch();
    frameLayout->setAlignment(Qt::AlignLeft);

    titolo->setObjectName("titoloInsertCinema");
    descrizione->setObjectName("descrizioneInsertCinema");
}

void InsertCinemaPage::createSplitView()
{
    QHBoxLayout *splitter = new QHBoxLayout;
    splitter->setSpacing(30);

    QWidget *contenitoredx = new QWidget(this);
    QVBoxLayout *layoutdx = new QVBoxLayout(contenitoredx);

    createLayoutInput(layoutdx);

    contenitoredx->setMinimumHeight(400);

    imageLabel->setMaximumSize(330, 400);
    QPixmap pixmap(":/images/coverCinema.png");
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setPixmap(pixmap);

    splitter->insertWidget(0, imageLabel);
    splitter->addWidget(contenitoredx);

    frameLayout->addLayout(splitter);

    createButtonLayout(layoutdx);

    layoutdx->setContentsMargins(0, 0, 0, 0);
}

void InsertCinemaPage::createLayoutInput(QVBoxLayout *layoutdx)
{
    QWidget *contenitoreInput = new QWidget(this);
    QVBoxLayout *layoutInput = new QVBoxLayout(contenitoreInput);

    QVBoxLayout *layoutNome = new QVBoxLayout;
    QLabel *nameLabel = new QLabel("Nome del cinema:", this);
    nameLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    layoutNome->addWidget(nameLabel);
    layoutNome->addWidget(textInput);

    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color: red; font-size: 11px;");
    errorLabel->setText("");
    errorLabel->setVisible(false);
    errorLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    layoutInput->addLayout(layoutNome);
    layoutInput->addWidget(errorLabel);
    layoutInput->addStretch();

    imageArea->setMinimumSize(365, 170);
    imageArea->setMaximumSize(460, 170);
    contenitoreInput->setMaximumHeight(310);
    layoutInput->addWidget(imageArea);
    layoutInput->setAlignment(Qt::AlignCenter);

    connect(textInput, &QLineEdit::textChanged, this, &InsertCinemaPage::checkCinemaNameAvailability);
    connect(imageArea, &InsertImageFrame::clicked, this, &InsertCinemaPage::chooseImage);
    connect(imageArea, &InsertImageFrame::removeImage, this, &InsertCinemaPage::removeImage);

    layoutInput->setContentsMargins(20, 20, 20, 20);
    layoutdx->addWidget(contenitoreInput);
    contenitoreInput->setStyleSheet("background-color: #0e4551;");

    nameLabel->setObjectName("labelInsertCinema");
    textInput->setObjectName("inputInsertCinema");
    textInput->setStyleSheet("background-color: #4e7f8b;");
    textInput->setPlaceholderText("Nome cinema...");
    layoutdx->setContentsMargins(20, 0, 0, 0);
}

void InsertCinemaPage::createButtonLayout(QVBoxLayout *layoutdx)
{
    QWidget *contenitorePulsanti = new QWidget(this);
    QHBoxLayout *layoutPulsanti = new QHBoxLayout(contenitorePulsanti);

    escButton->setFixedSize(160, 40);
    saveButton->setFixedSize(160, 40);

    connect(escButton, &QPushButton::clicked, this, &InsertCinemaPage::returnCinemaSelectionPage);
    connect(saveButton, &QPushButton::clicked, this, [this]()
            {
        if(!hasCustomImage){
            CustomMessageBox msgbox(this);
            msgbox.move(QApplication::primaryScreen()->geometry().center() - msgbox.rect().center());
            msgbox.setTitleText("Immagine non selezionata");
            msgbox.setMainMessage("Verrà impostata un'immagine di default");
            msgbox.hideCancelButton();
            msgbox.exec();
            msgbox.setInfoMessage("Premi ok per continuare");
        } 
        saveCinemaInJson(); });

    layoutPulsanti->addWidget(escButton);
    layoutPulsanti->addStretch();
    layoutPulsanti->addWidget(saveButton);

    layoutdx->addWidget(contenitorePulsanti);

    layoutPulsanti->setContentsMargins(0, 0, 0, 0);
}
