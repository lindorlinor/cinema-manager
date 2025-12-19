#include "CinemaSelectionPage.h"
#include <QVBoxLayout>
#include <QDir>
#include <QFile>
#include <QXmlStreamReader>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QString>
#include <QFont>
#include <QScrollArea>
#include <QGridLayout>

CinemaSelectionPage::CinemaSelectionPage(QList<Cinema *> &w_cinema, QWidget *parent) : QWidget(parent), sp_cinema(w_cinema), cinemaButtonsLayout(new QHBoxLayout), framePrincipale(new QFrame(this)), frameLayout(new QVBoxLayout(framePrincipale))
{

    refreshCinemaButtons();

    // crea il frame centrale
    framePrincipale->setMinimumSize(630, 500);
    framePrincipale->setMaximumSize(800, 500);

    createHeader();

    // aggiunge al frame il pulsante per aggiungere i cinema a destra
    QPushButton *addButton = new QPushButton("+ Aggiungi", framePrincipale);
    addButton->setFixedSize(160, 40);
    frameLayout->addWidget(addButton, 0, Qt::AlignRight);
    frameLayout->addSpacing(15);

    // aggiunge i pulsanti del cinema al cinemaButtonsLayout scansionando le risorse attuali
    refreshCinemaButtons();
    createCinemaScroll();

    // Pulsante esci
    QPushButton *escButton = new QPushButton("Esci", framePrincipale);
    escButton->setFixedSize(160, 40);
    connect(escButton, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(addButton, &QPushButton::clicked, this, &CinemaSelectionPage::insertCinema);
    frameLayout->addWidget(escButton, 0, Qt::AlignCenter);

    QVBoxLayout *layoutPrincipale = new QVBoxLayout(this);
    layoutPrincipale->addWidget(framePrincipale);
    layoutPrincipale->setAlignment(Qt::AlignCenter);
    setLayout(layoutPrincipale);
    setStyleSheet("QScrollArea { border: none; }");
    escButton->setObjectName("escButtonSelectCinema");
    addButton->setObjectName("addCinema");
    escButton->setContentsMargins(0, 15, 0, 0);
    escButton->setCursor(Qt::PointingHandCursor);
    addButton->setCursor(Qt::PointingHandCursor);
}

void CinemaSelectionPage::createCinemaButton(Cinema *c)
{

    CinemaButton *cinemaBtn = new CinemaButton(QString::fromStdString(c->getNomeCinema()), QString::fromStdString(c->getCopertinaCinema()), this);
    cinemaButtonsLayout->addWidget(cinemaBtn);

    connect(cinemaBtn, &CinemaButton::selected, this, [this, c]()
            { emit selectedCinema(c); });
}

void CinemaSelectionPage::refreshCinemaButtons()
{
    sp_cinema.clear();
    CinemaRepositoryJson cinemaManager;
    cinemaManager.loadCinema(sp_cinema);

    QLayoutItem *child;
    while ((child = cinemaButtonsLayout->takeAt(0)) != nullptr)
    {
        delete child->widget();
        delete child;
    }

    for (Cinema *c : sp_cinema)
    {
        createCinemaButton(c);
    }
}

void CinemaSelectionPage::createHeader()
{
    QLabel *titolo = new QLabel("Tutti i cinema", this);
    QFont fontTitolo = titolo->font();
    fontTitolo.setPointSize(25);
    fontTitolo.setBold(true);
    titolo->setFont(fontTitolo);

    QLabel *descrizione = new QLabel("Seleziona un cinema della catena o creane uno nuovo", this);
    QFont fontDescrizione = descrizione->font();
    fontDescrizione.setPointSize(14);
    descrizione->setFont(fontDescrizione);

    titolo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    descrizione->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    // crea il contenitore per le due label titolo e descrizione e lo distanzia in verticale dal resto che verrà inserito nel frame
    QWidget *contenitoreTesto = new QWidget(this);
    QVBoxLayout *layoutTesto = new QVBoxLayout(contenitoreTesto);
    layoutTesto->addWidget(titolo);
    layoutTesto->addWidget(descrizione);
    layoutTesto->setAlignment(Qt::AlignLeft);
    layoutTesto->setContentsMargins(0, 20, 0, 70);
    contenitoreTesto->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); // permette il margine, altrimenti non sarebbe esattamente 70
    // aggiunge il contenitore per le due label al frame e le allinea a sinistra
    frameLayout->addWidget(contenitoreTesto);
    frameLayout->setAlignment(Qt::AlignLeft);
    titolo->setObjectName("titoloSelectCinema");
    descrizione->setObjectName("descrizioneSelectCinema");
}

void CinemaSelectionPage::createCinemaScroll()
{
    // setta la scrollArea per i pulsanti del cinema
    QScrollArea *scrollArea = new QScrollArea(framePrincipale);
    QWidget *contenitorePulsanti = new QWidget(scrollArea);
    contenitorePulsanti->setLayout(cinemaButtonsLayout);
    cinemaButtonsLayout->setContentsMargins(0, 0, 0, 0);
    contenitorePulsanti->setContentsMargins(0, 0, 0, 0);

    scrollArea->setWidget(contenitorePulsanti);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setMinimumHeight(200);

    // cambia il comportamento di default della scrollArea che si espanderebbe
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // mette i pulsanti vicini tra loro, allineati a sinistra con uno spacing di 10
    cinemaButtonsLayout->setAlignment(Qt::AlignCenter);
    cinemaButtonsLayout->setSpacing(10);

    // aggiunge al frame la scrollArea del cinema
    frameLayout->addWidget(scrollArea);

    contenitorePulsanti->setObjectName("contenitoreCinema");

    scrollArea->setStyleSheet(
        "QScrollArea QWidget{"
        "border-radius: 10px;"
        "border: none}"
        "QScrollArea{"
        "background: transparent;}"
        "QScrollBar:horizontal {"
        "background: #4e7f8a;"
        "height: 12px;"
        "margin: 0px;"
        "border-radius: 5px;"
        "border: 1px solid #4e7f8a;}"
        "QScrollBar::handle:horizontal {"
        "background: #d9d9d9;"
        "min-height: 20px;"
        "border-radius: 5px;}"
        "QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {"
        "width: 0px;"
        "height: 0px;"
        "subcontrol-origin: margin;"
        "subcontrol-position: none;}"
        "QScrollBar::add-line:horizontal:hover, QScrollBar::sub-line:horizontal:hover {"
        "background: #4e7f8a;}");
}
