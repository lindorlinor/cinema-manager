#include "MediaView.h"
#include <QPushButton>
#include <QToolButton>
MediaView::MediaView(Media* mPtr, QWidget* parent)
    : QWidget(parent), mediaPtr(mPtr),layoutPage( new QVBoxLayout(this)),splitter(new QWidget(this)),splitterLayout(new QHBoxLayout(splitter)),leftSide(new QWidget(splitter)),leftLayout(new QHBoxLayout(leftSide)),
    details(new QFrame(leftSide)),detailsLayout(new QVBoxLayout(details)),endDateLabel(nullptr),rightSide(new QWidget(splitter)),rightLayout(new QVBoxLayout(rightSide)),card(new QWidget(leftSide)),cardLayout(new QVBoxLayout(card)){
    
    createHeader();
    
    splitterLayout->setSpacing(80); //aggiunge un po di spazio tra parte sinistra e destra della pagina
    layoutPage->addWidget(splitter,0,Qt::AlignHCenter);
    rightSide->setMinimumWidth(300);
    leftSide->setMinimumWidth(1000);
    details->setContentsMargins(15,15,15,0);

    details->setObjectName("details");
}


void MediaView::createHeader(){
    QWidget * contenitoreHeader = new QWidget(this);
    contenitoreHeader->setContentsMargins(62,20,0,0);
    contenitoreHeader->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
   
    QVBoxLayout * layoutHeader = new QVBoxLayout(contenitoreHeader);

    QPushButton* returnButton = new QPushButton("← indietro",contenitoreHeader);
    layoutHeader->addWidget(returnButton);
    layoutHeader->setAlignment(Qt::AlignTop);
    layoutHeader->setSpacing(20);

    returnButton->setCursor(Qt::PointingHandCursor);
    returnButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(returnButton, &QPushButton::clicked, this, &MediaView::returnButton);

    QLabel *titolo = new QLabel(QString::fromStdString(mediaPtr->getTitolo()));
    titolo->setContentsMargins(15,0,0,0);
    QFont fontTitolo = titolo->font();
    fontTitolo.setPointSize(21);
    fontTitolo.setBold(true);
    titolo->setFont(fontTitolo);

    layoutHeader->addWidget(titolo);
    layoutHeader->setAlignment(Qt::AlignLeft);
    contenitoreHeader->setLayout(layoutHeader);
    layoutPage->addWidget(contenitoreHeader);
    layoutPage->addSpacing(10);

    titolo->setStyleSheet("color: #fed36a;");
    returnButton->setObjectName("indietro");


}



void MediaView::createMediaCard(){
    card->setContentsMargins(0,0,0,0);
    cardLayout->setContentsMargins(0,0,0,0);
    QPixmap image(QString::fromStdString(mediaPtr->getImPath()));
    QLabel * copertina = new QLabel(card);
    copertina->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    QPixmap scaled = image.scaled(390,577,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    copertina->setPixmap(scaled);
    cardLayout->addWidget(copertina,0,Qt::AlignTop);
    cardLayout->setSpacing(0);
    QWidget* box = new QWidget(card);
    box->setFixedSize(390, 218);
    box->setObjectName("box");
    QVBoxLayout* layoutBox = new QVBoxLayout(box);
    layoutBox->setContentsMargins(35, 35, 35, 35);
    layoutBox->setSpacing(10);
    QLabel* regista = new QLabel(
        "<span style='color: #bdced3; font-size: 13pt; font-weight:bold;'>Autore: </span>"
        "<span style='color: #bdced3; font-size: 11pt;'>" + QString::fromStdString(mediaPtr->getAutore()) + "</span>",box);
    regista->setTextFormat(Qt::RichText);

    QLabel* durata = new QLabel(
        "<span style='color: #bdced3; font-size: 13pt; font-weight:bold;'>Durata: </span>"
        "<span style='color: #bdced3; font-size: 11pt;'>" + QString::number(mediaPtr->getDurataMinuti()) + " min</span>",box);
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
        "<span style='color: #bdced3; font-size: 13pt; font-weight:bold;'>Lingue: </span>"
        "<span style='color: #bdced3; font-size: 11pt;'>" + lingueText + "</span>",box);
    lingue->setTextFormat(Qt::RichText);

    //creazione label sottotitoli
    std::vector<Lingua> sottotitoliDisponibili = mediaPtr->getSottotitoli();
    QString sottotitoliText;
    for (size_t i = 0; i < sottotitoliDisponibili.size(); ++i) {
        sottotitoliText += QString::fromUtf8(toString(sottotitoliDisponibili[i]));
        if (i != sottotitoliDisponibili.size() - 1) sottotitoliText += ", ";
    }
    QLabel* sottotitoli = new QLabel(
        "<span style='color: #bdced3;font-size: 13pt; font-weight:bold;'>Sottotitoli: </span>"
        "<span style='color: #bdced3; font-size: 11pt; '>" + sottotitoliText + "</span>",box);
    sottotitoli->setTextFormat(Qt::RichText);

    layoutBox->addWidget(regista);
    layoutBox->addWidget(durata);
    layoutBox->addWidget(lingue);
    layoutBox->addWidget(sottotitoli);
    layoutBox->setAlignment(Qt::AlignLeft);
    // box->setFixedHeight(165);
    cardLayout->addWidget(box,0,Qt::AlignTop);
    card->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    leftLayout->addWidget(card,0,Qt::AlignTop);

}


void MediaView::createRowDetails(){
    QWidget * row = new QWidget(details);
    row->setFixedHeight(50);
    row->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    QHBoxLayout * rowLayout = new QHBoxLayout(row);

    QWidget* containerLabel = new QWidget;
    QHBoxLayout* containerLayout = new QHBoxLayout(containerLabel);
    containerLayout->setContentsMargins(0,0,0,0);

    QLabel* iconLabel = new QLabel(containerLabel);
    QLabel* textLabel = new QLabel(containerLabel);
    if (!mediaPtr->FuoriProduzione()){
        iconLabel->setPixmap(QPixmap(":/icons/in_sala.png").scaled(16,16, Qt::KeepAspectRatio));
        textLabel->setText("Attualmente in distribuzione");
        textLabel->setStyleSheet("font-size: 11pt; color: #FED36A;");
    }else{
        iconLabel->setPixmap(QPixmap(":/icons/non_in_sala.png").scaled(16,16, Qt::KeepAspectRatio));
        textLabel->setText("Fuori produzione");
        textLabel->setStyleSheet("color: #BDCED3;");
    }

    containerLayout->addWidget(iconLabel);
    containerLayout->addWidget(textLabel);

    
    QToolButton* editTool = new QToolButton(containerLabel);
    editTool->setFixedSize(135, 30);
    editTool->setCursor(Qt::PointingHandCursor);
    editTool->setEnabled(true);
    editTool->setAutoRaise(true);
    editTool->setText("Modifica media");
    editTool->setStyleSheet(R"(
        QToolButton {
            font-size: 11pt;
            color: #FED36A;
            background-color: #05313c;
            border-radius: 5px;
        }
        QToolButton:pressed  {
            color: #FFE28C;
            background-color: #4e7f8a;
        }   
    )");

    editTool->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    editTool->setIcon(QIcon(":/icons/edit.png"));

    connect(editTool, &QToolButton::clicked, this, [this](){
        qDebug() << "hai cliccato edit del media " << QString::fromStdString(mediaPtr->getTitolo());
        emit editMediaClicked(mediaPtr);
    });

    rowLayout->addWidget(containerLabel);
    rowLayout->addStretch();
    rowLayout->addWidget(editTool,0,Qt::AlignRight);
    detailsLayout->addWidget(row);
}
