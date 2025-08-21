#include "DetailPageVisitor.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QPixmap>
#include "../Film.h"

DetailPageVisitor::DetailPageVisitor()
    : detailPage(nullptr)
{}

QWidget* DetailPageVisitor::getWidget() const {
    return detailPage;
}


void DetailPageVisitor::visit(Film* film) {
    QWidget* page = new QWidget;
    page->setObjectName("gugu");
    QVBoxLayout* layoutPage = new QVBoxLayout(page);
    
    QWidget * contenitoreHeader = new QWidget;
    contenitoreHeader->setObjectName("gaga");
    contenitoreHeader->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QVBoxLayout * layoutHeader = new QVBoxLayout(contenitoreHeader);

    QPushButton* returnButton = new QPushButton("← indietro",contenitoreHeader);
    layoutHeader->addWidget(returnButton);

    returnButton->setCursor(Qt::PointingHandCursor);
    returnButton->setFixedSize(96,26);
    /* @TODO
    connect(returnButton, &QPushButton::clicked, this, [this](){
        this->resetAllInput();
        this->tornaIndietro();
    });  */

    QLabel *titolo = new QLabel(QString::fromStdString(film->getTitolo()));
    QFont fontTitolo = titolo->font();
    fontTitolo.setPointSize(21);
    fontTitolo.setBold(true);
    titolo->setFont(fontTitolo);
    titolo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    layoutHeader->addWidget(titolo);
    layoutHeader->setAlignment(Qt::AlignLeft);

    layoutPage->addWidget(contenitoreHeader);
    layoutPage->addStretch();

    QWidget * splitter = new QWidget(page);
    QHBoxLayout * splitterLayout = new QHBoxLayout(splitter);

    layoutPage->addWidget(splitter);
    
    QWidget * partesx = new QWidget();
    partesx->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    partesx->setObjectName("pupu");
    QHBoxLayout * layoutsx = new QHBoxLayout(partesx);
    partesx->setContentsMargins(0,0,0,0);
    layoutsx->setContentsMargins(0,0,0,0);
    QWidget * card = new QWidget();
    QVBoxLayout * cardLayout = new QVBoxLayout(card);
    card->setContentsMargins(0,0,0,0);
    cardLayout->setContentsMargins(0,0,0,0);
    QPixmap image(QString::fromStdString(film->getImPath()));
    QLabel * copertina = new QLabel();
    // cardLayout->setAlignment(Qt::AlignBottom);//così almeno è attaccato alla box anche se non è scalato come si vorrebbe
    copertina->setPixmap(image.scaled(300,445,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    cardLayout->addWidget(copertina);

    cardLayout->setSpacing(0);
    QWidget* box = new QWidget();
    box->setFixedSize(300, 210);
    box->setObjectName("caca");
    QVBoxLayout* layout = new QVBoxLayout(box);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(10);

    QLabel* regista = new QLabel("Regista: "+QString::fromStdString(film->getAutore()));
    QLabel* durata = new QLabel("Durata: "+QString::number(film->getDurataMinuti()));

    //creazione label lingue
    std::vector<Lingua> lingueDisponibili = film->getLingue();
    QString lingueText = "Lingue: ";
    for (size_t i = 0; i < lingueDisponibili.size(); ++i) {
        lingueText += QString::fromUtf8(toString(lingueDisponibili[i]));
        if (i != lingueDisponibili.size() - 1) {
            lingueText += ", ";
        }
    }
    QLabel* lingue = new QLabel(lingueText);

    //creazione label sottotitoli
    std::vector<Lingua> sottotitoliDisponibili = film->getSottotitoli();
    QString sottotitoliText = "Sottotitoli: ";
    for (size_t i = 0; i < sottotitoliDisponibili.size(); ++i) {
        sottotitoliText += QString::fromUtf8(toString(sottotitoliDisponibili[i]));
        if (i != sottotitoliDisponibili.size() - 1) {
            sottotitoliText += ", ";
        }
    }
    QLabel* sottotitoli = new QLabel(sottotitoliText);

    layout->addWidget(regista);
    layout->addWidget(durata);
    layout->addWidget(lingue);
    layout->addWidget(sottotitoli);
    layout->setAlignment(Qt::AlignLeft);

    cardLayout->addWidget(box);
    cardLayout->setAlignment(Qt::AlignLeft);
    layoutsx->addWidget(card);

    QFrame * details = new QFrame();
    QVBoxLayout * detailsLayout = new QVBoxLayout(details);
    details->setFixedHeight(655);
    details->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    details->setObjectName("gagagaag");
    layoutsx->addWidget(details);

    splitterLayout->addWidget(partesx);
    splitterLayout->setAlignment(Qt::AlignHCenter);
    detailPage = page;
    page->setStyleSheet("#gagagaag { background-color: purple} #gugu { background-color: pink} #gaga {background-color: red} #pupu {background-color: yellow} #caca{background-color: blue}");

}
void DetailPageVisitor::visit(Trailer*) {}
void DetailPageVisitor::visit(Inserzione*) {}
void DetailPageVisitor::visit(Podcast*) {}
void DetailPageVisitor::visit(Puntata*) {}
