#include "MediaView.h"
#include <QPushButton>
MediaView::MediaView(Media* mPtr, QWidget* parent)
    : QWidget(parent), mediaPtr(mPtr),layoutPage( new QVBoxLayout(this)),splitter(new QWidget(this)),splitterLayout(new QHBoxLayout(splitter)),leftSide(new QWidget(splitter)),
    rightSide(new QWidget(splitter)),leftLayout(new QHBoxLayout(leftSide)),endDateLabel(nullptr),rightLayout(new QVBoxLayout(rightSide)),card(new QWidget(leftSide)),cardLayout(new QVBoxLayout(card)){
    this->setObjectName("gugu");
    
    createHeader();
    
    splitterLayout->setSpacing(55); //aggiunge un po di spazio tra parte sinistra e destra della pagina
    layoutPage->addWidget(splitter,0,Qt::AlignHCenter);
}


void MediaView::createHeader(){
    QWidget * contenitoreHeader = new QWidget(this);
    contenitoreHeader->setObjectName("gaga");
    contenitoreHeader->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    QVBoxLayout * layoutHeader = new QVBoxLayout(contenitoreHeader);

    QPushButton* returnButton = new QPushButton("← indietro",contenitoreHeader);
    layoutHeader->addWidget(returnButton);

    returnButton->setCursor(Qt::PointingHandCursor);
    returnButton->setFixedSize(96,26);

    connect(returnButton, &QPushButton::clicked, this, &MediaView::returnButton);

    QLabel *titolo = new QLabel(QString::fromStdString(mediaPtr->getTitolo()));
    QFont fontTitolo = titolo->font();
    fontTitolo.setPointSize(21);
    fontTitolo.setBold(true);
    titolo->setFont(fontTitolo);

    layoutHeader->addWidget(titolo);
    layoutHeader->setAlignment(Qt::AlignLeft);

    layoutPage->addWidget(contenitoreHeader);
}



void MediaView::createMediaCard(){
    card->setContentsMargins(0,0,0,0);
    cardLayout->setContentsMargins(0,0,0,0);
    QPixmap image(QString::fromStdString(mediaPtr->getImPath()));
    QLabel * copertina = new QLabel(card);
    copertina->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    QPixmap scaled = image.scaled(330,489,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    copertina->setPixmap(scaled);
    cardLayout->addWidget(copertina,0,Qt::AlignTop);

    cardLayout->setSpacing(0);
    QWidget* box = new QWidget(card);
    box->setFixedSize(330, 231);
    box->setObjectName("caca");
    QVBoxLayout* layoutBox = new QVBoxLayout(box);
    layoutBox->setContentsMargins(35, 35, 35, 35);
    layoutBox->setSpacing(10);
    QLabel* regista = new QLabel(
        "<span style='color:white; font-weight:bold;'>Autore: </span>"
        "<span style='color:black;'>" + QString::fromStdString(mediaPtr->getAutore()) + "</span>",box);
    regista->setTextFormat(Qt::RichText);

    QLabel* durata = new QLabel(
        "<span style='color:white; font-weight:bold;'>Durata: </span>"
        "<span style='color:black;'>" + QString::number(mediaPtr->getDurataMinuti()) + " min</span>",box);
    durata->setTextFormat(Qt::RichText);

    //creazione label lingue
    std::vector<Lingua> lingueDisponibili = mediaPtr->getLingue();
    QString lingueText;
    for (size_t i = 0; i < lingueDisponibili.size(); ++i) {
        lingueText += QString::fromUtf8(toString(lingueDisponibili[i]));
        if (i != lingueDisponibili.size() - 1) {
            lingueText += ", ";
        }
    }
    QLabel* lingue = new QLabel(
        "<span style='color:white; font-weight:bold;'>Lingue: </span>"
        "<span style='color:black;'>" + lingueText + "</span>",box);
    lingue->setTextFormat(Qt::RichText);

    //creazione label sottotitoli
    std::vector<Lingua> sottotitoliDisponibili = mediaPtr->getSottotitoli();
    QString sottotitoliText;
    for (size_t i = 0; i < sottotitoliDisponibili.size(); ++i) {
        sottotitoliText += QString::fromUtf8(toString(sottotitoliDisponibili[i]));
        if (i != sottotitoliDisponibili.size() - 1) sottotitoliText += ", ";
    }
    QLabel* sottotitoli = new QLabel(
        "<span style='color:white; font-weight:bold;'>Sottotitoli: </span>"
        "<span style='color:black;'>" + sottotitoliText + "</span>",box);
    sottotitoli->setTextFormat(Qt::RichText);

    layoutBox->addWidget(regista);
    layoutBox->addWidget(durata);
    layoutBox->addWidget(lingue);
    layoutBox->addWidget(sottotitoli);
    layoutBox->setAlignment(Qt::AlignLeft);
    box->setFixedHeight(165);
    cardLayout->addWidget(box,0,Qt::AlignTop);
    card->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    leftLayout->addWidget(card,0,Qt::AlignTop);
}
