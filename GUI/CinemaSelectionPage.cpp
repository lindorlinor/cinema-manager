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

CinemaSelectionPage::CinemaSelectionPage(QWidget *parent) : QWidget(parent), layoutPulsanti(new QHBoxLayout()) {
    
    //crea il frame principale
    QFrame* framePrincipale = new QFrame();
    framePrincipale->setMinimumSize(630, 600);
    framePrincipale->setMaximumSize(1000, 750);

    //definisce il layout interno del frame
    QVBoxLayout *layoutFrame = new QVBoxLayout(framePrincipale);

    
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
    
    //aggiunge al frame il pulsante per aggiungere i cinema a destra
    QPushButton* addButton = new QPushButton("+ Aggiungi");
    addButton->setFixedSize(160, 40); 
    layoutFrame->addWidget(addButton, 0, Qt::AlignRight);

    //aggiunge i pulsanti del cinema al layoutPulsanti scansionando le risorse attuali
    refresh();

    //mette i pulsanti vicini tra loro, allineati a sinistra con uno spacing di 10
    layoutPulsanti->setAlignment(Qt::AlignLeft);
    layoutPulsanti->setSpacing(10);

    //setta la scrollArea per i pulsanti del cinema
    QScrollArea* scrollArea = new QScrollArea;
    QWidget* contenitorePulsanti = new QWidget;
    contenitorePulsanti->setLayout(layoutPulsanti);
    scrollArea->setWidget(contenitorePulsanti);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //cambia il comportamento di default della scrollArea che si espanderebbe
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    
    //aggiunge al frame la scrollArea del cinema
    layoutFrame->addWidget(scrollArea);

    // Pulsante esci
    QPushButton* escButton = new QPushButton("Esci");
    escButton->setFixedSize(160, 40); 
    connect(escButton, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(addButton, &QPushButton::clicked, this, &CinemaSelectionPage::insertCinema);
    
    
    layoutFrame->addWidget(escButton, 0, Qt::AlignCenter);

    QVBoxLayout * layoutPrincipale = new QVBoxLayout(this);
    layoutPrincipale->addWidget(framePrincipale);
    layoutPrincipale->setAlignment(Qt::AlignCenter);
    setLayout(layoutPrincipale);
    setStyleSheet("QScrollArea { border: none; }");

}

void CinemaSelectionPage::creaBottoneCinema(const QString& nomeC, const QString& imPath, const QString& xmlPath) {
    
    CinemaButton *btn = new CinemaButton(nomeC, QPixmap(imPath), xmlPath);
    layoutPulsanti->addWidget(btn);

    //TO DO
    connect(btn, &CinemaButton::selected, this, [this,xmlPath](){
        emit selectedCinema(xmlPath);
    });
}


void CinemaSelectionPage::refresh() {
    QLayoutItem* child;
    while ((child = layoutPulsanti->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    cinemaButtons.clear();

    CinemaXmlRepository repo(QDir(QCoreApplication::applicationDirPath()).filePath(".."));
    cinemas = repo.loadAllCinemas();
    for (const auto& c : cinemas) {
        creaBottoneCinema(c.nome, c.imagePath, c.xmlPath);
    }
}
