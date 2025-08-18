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

CinemaSelectionPage::CinemaSelectionPage(QWidget *parent = nullptr):QWidget(parent),layoutPulsanti(new QHBoxLayout()){
    
    QFrame* framePrincipale = new QFrame(this);
    framePrincipale->setFixedSize(900 , 600);
    QGridLayout* grid = new QGridLayout(this);
    grid->addWidget(framePrincipale, 0, 0, Qt::AlignCenter);

    QVBoxLayout * layout = new QVBoxLayout(framePrincipale);
    layout->setSpacing(10);  
    layout->setContentsMargins(20, 20, 20, 20);


    QLabel *titolo = new QLabel("Tutti i cinema");
    QFont font = titolo->font();
    font.setPointSize(21);
    font.setBold(true);
    titolo->setFont(font);

    QLabel* descrizione = new QLabel("Seleziona un cinema della catena o creane uno nuovo", this);


    QWidget* contenitoreLabel = new QWidget;
    layout->addWidget(contenitoreLabel, 0, Qt::AlignLeft);
    QVBoxLayout* layoutLabel = new QVBoxLayout(contenitoreLabel);
    layoutLabel->addWidget(titolo);
    layoutLabel->addWidget(descrizione);
    layoutLabel->setContentsMargins(0,0,0,0);
    titolo->setAlignment(Qt::AlignLeft);
    descrizione->setAlignment(Qt::AlignLeft);

    //Layout orizzontale con i bottoni dei cinema
    QWidget* contenitorePulsanti = new QWidget;
    contenitorePulsanti->setLayout(layoutPulsanti);

    QPushButton* addButton = new QPushButton("+ Aggiungi");
    addButton->setFixedSize(160, 40); 
    layout->addWidget(addButton,0, Qt::AlignRight);

    //Caricamento e creazione dei Button cinema
    refresh();

    //ScrollArea che mostra i bottoni
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidget(contenitorePulsanti);
    scrollArea->setWidgetResizable(true);
    scrollArea->setMaximumSize(900,240);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    //Aggiunta al layout principale (centrato)
    layout->addWidget(scrollArea);

    
    QPushButton* escButton = new QPushButton("Esci");
    escButton->setFixedSize(160, 40); 
    connect(escButton,&QPushButton::clicked,qApp,&QApplication::quit);
    connect(addButton,&QPushButton::clicked,this,&CinemaSelectionPage::insertCinema);
    layout->addWidget(escButton,0, Qt::AlignCenter);

    setStyleSheet("QScrollArea { border: none; }");
}

void CinemaSelectionPage::creaBottoneCinema(const QString& nomeC, const QString& imPath, const QString& xmlPath) {
    
    CinemaButton *btn = new CinemaButton(nomeC, QPixmap(imPath), xmlPath);
    layoutPulsanti->addWidget(btn);

    //TO DO
    connect(btn, &CinemaButton::selected, this, [=](){
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
