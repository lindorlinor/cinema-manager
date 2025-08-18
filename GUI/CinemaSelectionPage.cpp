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
    
    // Crea il frame principale
    QFrame* framePrincipale = new QFrame();
    framePrincipale->setMinimumSize(630, 600);
    framePrincipale->setMaximumSize(1000, 750);

    // Layout interno del frame
    QVBoxLayout *layoutFrame = new QVBoxLayout(framePrincipale);

    // Titolo e descrizione
    QLabel *titolo = new QLabel("Tutti i cinema");
    QFont font = titolo->font();
    font.setPointSize(21);
    font.setBold(true);
    titolo->setFont(font);

    QLabel* descrizione = new QLabel("Seleziona un cinema della catena o creane uno nuovo");

    QFont fontDescrizione = descrizione->font();
    fontDescrizione.setPointSize(10);
    descrizione->setFont(fontDescrizione);

    titolo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    descrizione->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    QWidget* contenitoreLabel = new QWidget;
    QVBoxLayout* layoutLabel = new QVBoxLayout(contenitoreLabel);
    layoutLabel->addWidget(titolo);
    layoutLabel->addWidget(descrizione);
    layoutLabel->setAlignment(Qt::AlignLeft);
    layoutLabel->setContentsMargins(0,0,0,100);

    contenitoreLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    layoutFrame->addWidget(contenitoreLabel);
    layoutFrame->setAlignment( Qt::AlignLeft);
    // Pulsante aggiungi
    QPushButton* addButton = new QPushButton("+ Aggiungi");
    addButton->setFixedSize(160, 40); 
    layoutFrame->addWidget(addButton, 0, Qt::AlignRight);

    // Caricamento dei cinema
    refresh();
    layoutPulsanti->setAlignment(Qt::AlignLeft);
    layoutPulsanti->setSpacing(10);
    // Scroll area
    QScrollArea* scrollArea = new QScrollArea;
    QWidget* contenitorePulsanti = new QWidget;
    contenitorePulsanti->setLayout(layoutPulsanti);
    scrollArea->setWidget(contenitorePulsanti);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    
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
