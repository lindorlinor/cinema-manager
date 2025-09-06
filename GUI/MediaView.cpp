#include "MediaView.h"
#include <QPushButton>
#include <QToolButton>
MediaView::MediaView(Media* mPtr, QWidget* parent)
    : QWidget(parent), mediaPtr(mPtr),layoutPage( new QVBoxLayout(this)),splitter(new QWidget(this)),splitterLayout(new QHBoxLayout(splitter)),leftSide(new QWidget(splitter)),leftLayout(new QHBoxLayout(leftSide)),
    details(new QFrame(leftSide)),detailsLayout(new QVBoxLayout(details)),endDateLabel(nullptr),rightSide(new QWidget(splitter)),rightLayout(new QVBoxLayout(rightSide)),card(new QWidget(leftSide)),cardLayout(new QVBoxLayout(card)), box(new QWidget(card)),copertina(new QLabel(card)){
    
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

    titolo = new QLabel(contenitoreHeader);
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

    updateHeader(); //aggiorna con il valore corrente
}

void MediaView::updateHeader(){
    titolo->setText(QString::fromStdString(mediaPtr->getTitolo()));
}

void MediaView::createMediaCard() {
    card->setContentsMargins(0,0,0,0);
    cardLayout->setContentsMargins(0,0,0,0);

   
    copertina->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    cardLayout->addWidget(copertina, 0, Qt::AlignTop);

    
    box->setFixedSize(390, 218);
    QVBoxLayout* layoutBox = new QVBoxLayout(box);
    layoutBox->setContentsMargins(35, 35, 35, 35);
    layoutBox->setSpacing(10);

    regista = new QLabel(box);
    durata = new QLabel(box);
    lingue = new QLabel(box);
    sottotitoli = new QLabel(box);

    layoutBox->addWidget(regista);
    layoutBox->addWidget(durata);
    layoutBox->addWidget(lingue);
    layoutBox->addWidget(sottotitoli);
    layoutBox->setAlignment(Qt::AlignLeft);

    cardLayout->addWidget(box, 0, Qt::AlignTop);
    card->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    leftLayout->addWidget(card, 0, Qt::AlignTop);

    updateMediaCard(); //aggiorna con il valore corrente

    box->setObjectName("box");
}

void MediaView::updateMediaCard() {
    if (!mediaPtr) return;


    QPixmap image(QString::fromStdString(mediaPtr->getImPath()));
    QPixmap scaled = image.scaled(390,577,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    copertina->setPixmap(scaled);


    regista->setText(
        "<span style='color: #bdced3; font-size: 13pt; font-weight:bold;'>Autore: </span>"
        "<span style='color: #bdced3; font-size: 11pt;'>" + QString::fromStdString(mediaPtr->getAutore()) + "</span>");
    durata->setText(
        "<span style='color: #bdced3; font-size: 13pt; font-weight:bold;'>Durata: </span>"
        "<span style='color: #bdced3; font-size: 11pt;'>" + QString::number(mediaPtr->getDurataMinuti()) + " min</span>");

    
    QString lingueText;
    for (size_t i = 0; i < mediaPtr->getLingue().size(); ++i) {
        lingueText += QString::fromUtf8(toString(mediaPtr->getLingue()[i]));
        if (i != mediaPtr->getLingue().size() - 1) lingueText += ", ";
    }
    lingue->setText(
        "<span style='color: #bdced3; font-size: 13pt; font-weight:bold;'>Lingue: </span>"
        "<span style='color: #bdced3; font-size: 11pt;'>" + lingueText + "</span>");

    QString sottotitoliText;
    for (size_t i = 0; i < mediaPtr->getSottotitoli().size(); ++i) {
        sottotitoliText += QString::fromUtf8(toString(mediaPtr->getSottotitoli()[i]));
        if (i != mediaPtr->getSottotitoli().size() - 1) sottotitoliText += ", ";
    }
    sottotitoli->setText(
        "<span style='color: #bdced3; font-size: 13pt; font-weight:bold;'>Sottotitoli: </span>"
        "<span style='color: #bdced3; font-size: 11pt;'>" + sottotitoliText + "</span>");
}



void MediaView::createRowDetails(){
    QWidget * row = new QWidget(details);
    row->setFixedHeight(50);
    row->setFixedWidth(580);
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
        textLabel->setStyleSheet("color: #bdced3;");
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


void MediaView::update(){
    updateHeader();
    updateMediaCard();
}


void MediaView::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event); // chiama il comportamento di default

    if (width() < 1350) {
        rightSide->hide();   // nasconde rightSide se la larghezza è minore di 1027
    } else {
        rightSide->show();   // mostra rightSide se la larghezza è maggiore o uguale a 1027
    }
}
