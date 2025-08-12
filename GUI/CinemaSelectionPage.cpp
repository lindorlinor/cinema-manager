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

CinemaSelectionPage::CinemaSelectionPage(QWidget *parent = nullptr):QWidget(parent){
    QVBoxLayout * layout = new QVBoxLayout(this);
    layout->setSpacing(10);  
    layout->setContentsMargins(20, 20, 20, 20);

    QLabel *label = new QLabel("Seleziona cinema", this);
    QFont font = label->font();
    font.setPointSize(21);
    font.setBold(true);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label, 0, Qt::AlignCenter);

    //Layout orizzontale con i bottoni dei cinema
    QWidget* contenitorePulsanti = new QWidget;
    QHBoxLayout* layoutPulsanti = new QHBoxLayout(contenitorePulsanti);

    //Caricamento e creazione dei Button cinema
    QDir baseDir(QCoreApplication::applicationDirPath());
    baseDir.cdUp();  // Vai dalla /release alla root
    caricaCinemaDaXML(baseDir.absolutePath(), layoutPulsanti);


    //ScrollArea che mostra i bottoni
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidget(contenitorePulsanti);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setFixedSize(500,210); 

    //Bottone "Nuovo+" fuori dalla scroll area
    QPushButton* addButton = new QPushButton("Nuovo+");
    addButton->setFixedSize(150, 180); 

    //Layout orizzontale che contiene scrollArea + addButton
    QHBoxLayout* layoutRigaCinema = new QHBoxLayout;
    layoutRigaCinema->addWidget(scrollArea);
    layoutRigaCinema->addWidget(addButton);
    layoutRigaCinema->setAlignment(Qt::AlignCenter);
    layoutRigaCinema->setSpacing(20);

    //Container per il layout orizzontale
    QWidget* containerRigaCinema = new QWidget;
    containerRigaCinema->setLayout(layoutRigaCinema);

    //Aggiunta al layout principale (centrato)
    layout->addWidget(containerRigaCinema, 0, Qt::AlignCenter);
    
    QPushButton* escButton = new QPushButton("Esci");
    connect(escButton,&QPushButton::clicked,qApp,&QApplication::quit);
    connect(addButton,&QPushButton::clicked,this,&CinemaSelectionPage::insertCinema);
    layout->addWidget(escButton,0, Qt::AlignCenter);

    setStyleSheet("QScrollArea { border: none; }");
}

void CinemaSelectionPage::caricaCinemaDaXML(const QString& path, QHBoxLayout * layout) {
    QList<QStringList> lista;
    QDir cinemaDir(path);
    QStringList xmlFiles = cinemaDir.entryList(QStringList() << "*.xml", QDir::Files);
    for (const QString &fileName : xmlFiles) {
        QFile file(cinemaDir.filePath(fileName));
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Impossibile aprire file:" << fileName;
            continue;
        }

        QXmlStreamReader xml(&file);
        QString nomeCinema, pathImmagine;
        while (!xml.atEnd() && !xml.hasError()) {
            xml.readNext();
            if (xml.isStartElement()) {
                if (xml.name().toString() == "nome") {
                    nomeCinema = xml.readElementText();
                } else if (xml.name().toString() == "immagine") {
                    pathImmagine = xml.readElementText();
                    break;
                }
            }
        }

        QString resourcePath = pathImmagine;
        if (!pathImmagine.startsWith(":/")) {
            resourcePath = ":/images/" + pathImmagine;
        }
        if (!nomeCinema.isEmpty()) {
            qDebug() << "Carico immagine da:" << resourcePath;
            creaBottoneCinema(nomeCinema,pathImmagine,cinemaDir.filePath(fileName), layout);
        } else {
            qWarning() << "Nessun nome trovato in" << fileName;
        }

        file.close();
    }
}


void CinemaSelectionPage::creaBottoneCinema(const QString& nomeC, const QString& imPath, const QString& xmlPath, QHBoxLayout* layout) {
    
    CinemaButton *btn = new CinemaButton(nomeC, QPixmap(imPath), xmlPath);
    layout->addWidget(btn);
    cinemaButtons.append(btn);

    //TO DO
    connect(btn, &CinemaButton::selected, this, [=](){
        emit selectedCinema(xmlPath);
    });
}
