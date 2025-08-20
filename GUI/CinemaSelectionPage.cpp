#include "CinemaSelectionPage.h"
#include "CinemaButton.h"
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

CinemaSelectionPage::CinemaSelectionPage(QWidget *parent) : QWidget(parent), cinemaButtonsLayout(new QHBoxLayout), frameLayout(new QVBoxLayout) {
    //crea il frame centrale
    QFrame* framePrincipale = new QFrame(this);
    framePrincipale->setMinimumSize(630, 600);
    framePrincipale->setMaximumSize(1000, 750);
    framePrincipale->setLayout(frameLayout);

    createHeader();
    
    //aggiunge al frame il pulsante per aggiungere i cinema a destra
    QPushButton* addButton = new QPushButton("+ Aggiungi");
    addButton->setFixedSize(160, 40); 
    frameLayout->addWidget(addButton, 0, Qt::AlignRight);

    //aggiunge i pulsanti del cinema al cinemaButtonsLayout scansionando le risorse attuali
    refreshCinemaButtons();
    
    //mette i pulsanti vicini tra loro, allineati a sinistra con uno spacing di 10
    cinemaButtonsLayout->setAlignment(Qt::AlignLeft);
    cinemaButtonsLayout->setSpacing(10);
   
    // Pulsante esci
    QPushButton* escButton = new QPushButton("Esci");
    escButton->setFixedSize(160, 40); 
    connect(escButton, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(addButton, &QPushButton::clicked, this, &CinemaSelectionPage::insertCinema);
    frameLayout->addWidget(escButton, 0, Qt::AlignCenter);

    QVBoxLayout * layoutPrincipale = new QVBoxLayout(this);
    layoutPrincipale->addWidget(framePrincipale);
    layoutPrincipale->setAlignment(Qt::AlignCenter);
    setLayout(layoutPrincipale);
    setStyleSheet("QScrollArea { border: none; }");

}

void CinemaSelectionPage::createCinemaButton(const QString& nomeC, const QString& imPath, const QString& xmlPath) {
    
    CinemaButton *cinemaBtn = new CinemaButton(nomeC, QPixmap(imPath), xmlPath);
    cinemaButtonsLayout->addWidget(cinemaBtn);

    connect(cinemaBtn, &CinemaButton::selected, this, [this,xmlPath](){
        emit selectedCinema(xmlPath);
    });
}

/**
 * @brief toglie e ricrea i pulsanti del cinema. 
 * 
 * Utilizza @ref CinemaXmlRepository per scaricare in una lista di struct Cinema tutti i cinema, 
 * poi scorre la lista e crea per ciascuno il button.
 */
void CinemaSelectionPage::refreshCinemaButtons() {
    QLayoutItem* child;
    while ((child = cinemaButtonsLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    CinemaXmlRepository repo(QDir(QCoreApplication::applicationDirPath()).filePath(".."));
    cinemas = repo.loadAllCinemas();
    for (const auto& c : cinemas) {
        createCinemaButton(c.nome, c.imagePath, c.xmlPath);
    }
}

/**
 * @brief Crea l'intestazione della pagina
 * 
 * @note qui sono stati impostate delle grandezze per i font che poi dovranno essere messe nel qss così possiamo 
 * toglierle da qui
 */
void CinemaSelectionPage::createHeader(){
    QLabel *titolo = new QLabel("Tutti i cinema");
    QFont fontTitolo = titolo->font();
    fontTitolo.setPointSize(21);
    fontTitolo.setBold(true);
    titolo->setFont(fontTitolo);

    QLabel* descrizione = new QLabel("Seleziona un cinema della catena o creane uno nuovo");
    QFont fontDescrizione = descrizione->font();
    fontDescrizione.setPointSize(10);
    descrizione->setFont(fontDescrizione);

    titolo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    descrizione->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    //crea il contenitore per le due label titolo e descrizione e lo distanzia in verticale dal resto che verrà inserito nel frame
    QWidget* contenitoreTesto = new QWidget;
    QVBoxLayout* layoutTesto = new QVBoxLayout(contenitoreTesto);
    layoutTesto->addWidget(titolo);
    layoutTesto->addWidget(descrizione);
    layoutTesto->setAlignment(Qt::AlignLeft);
    layoutTesto->setContentsMargins(0,20,0,70);
    contenitoreTesto->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); //permette il margine, altrimenti non sarebbe esattamente 70
    //aggiunge il contenitore per le due label al frame e le allinea a sinistra
    frameLayout->addWidget(contenitoreTesto);
    frameLayout->setAlignment( Qt::AlignLeft);
}

/**
 * @brief Crea la scroll per la sezione dei pulsanti. 
 * 
 * La scroll è visibile solo quando i pulsanti non hanno abbastanza spazio per essere visualizzati.
 * 
 */
void CinemaSelectionPage::createCinemaScroll(){
     //setta la scrollArea per i pulsanti del cinema
    QScrollArea* scrollArea = new QScrollArea;
    QWidget* contenitorePulsanti = new QWidget;
    contenitorePulsanti->setLayout(cinemaButtonsLayout);
    scrollArea->setWidget(contenitorePulsanti);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //cambia il comportamento di default della scrollArea che si espanderebbe
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    
    //aggiunge al frame la scrollArea del cinema
    frameLayout->addWidget(scrollArea);
}