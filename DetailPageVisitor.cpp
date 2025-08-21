#include "DetailPageVisitor.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QPixmap>
#include <QGridLayout>
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
    detailsLayout->setContentsMargins(10, 10, 10, 10);
    details->setFixedHeight(655);
    details->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    details->setObjectName("details");
    layoutsx->addWidget(details);

    QWidget * sezioneProgrammazione = new QWidget();
    QVBoxLayout * layoutProgrammazione = new QVBoxLayout(sezioneProgrammazione);
    
    QLabel * labelProgrammazione = new QLabel("Informazioni di programmazione");
    layoutProgrammazione->addWidget(labelProgrammazione);

    QWidget * sezioneInternaProgrammazione = new QWidget();
    QGridLayout * layoutInternoProgrammazione = new QGridLayout(sezioneInternaProgrammazione);
    sezioneInternaProgrammazione->setContentsMargins(10,10,10,10);
    sezioneProgrammazione->setObjectName("sp");
    
    // Programmazione (date inizio/fine)
    auto inizio = film->getDataInizioRilascio();
    auto fine = film->getDataFineRilascio();
    std::ostringstream oss1;
    oss1 << static_cast<int>(unsigned(inizio.day())) << "/"
    << unsigned(inizio.month()) << "/"
    << int(inizio.year()) ;
    
    std::ostringstream oss2;
    oss2 << static_cast<int>(unsigned(fine.day())) << "/"
    << unsigned(fine.month()) << "/"
    << int(fine.year());
    
    QLabel* inizioP = new QLabel("Inizio proiezione: " + QString::fromStdString(oss1.str()));
    QLabel* fineP = new QLabel("Fine proiezione: " + QString::fromStdString(oss2.str()));
    inizioP->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    fineP->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    inizioP->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    QLabel* costoBiglietto = new QLabel("Costo biglietto: " + QString::number(film->getCostoBiglietto()) + " €");
    costoBiglietto->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    
    layoutInternoProgrammazione->addWidget(inizioP,0,0);
    layoutInternoProgrammazione->addWidget(fineP,0,1);
    layoutInternoProgrammazione->addWidget(costoBiglietto,1,0);
    layoutProgrammazione->addWidget(sezioneInternaProgrammazione);
    /* // Visualizzazioni e incasso
    QLabel* incasso = new QLabel("Incasso totale: " + QString::number(film->calcolaIncasso()) + " €");
    QLabel* visualizzazioni = new QLabel("Visualizzazioni: " + QString::number(film->getVisualizzazioni()));
    QLabel* valutazioni = new QLabel("Valutazione: " + QString::number(film->getValutazione())+ "/10");

    // Casa di produzione
    QLabel* casaProduzione = new QLabel("Casa di produzione: " + QString::fromStdString(film->getCasaDiProduzione()));
    QLabel* descrizione = new QLabel(QString::fromStdString(film->getDescrizione()));
    descrizione->setWordWrap(true);

    // --- aggiunta al layout ---
    detailsLayout->addWidget(inizioP);
    detailsLayout->addWidget(fineP);
    detailsLayout->addWidget(costoBiglietto);
    detailsLayout->addSpacing(10);
    detailsLayout->addWidget(incasso);
    detailsLayout->addWidget(visualizzazioni);
    detailsLayout->addWidget(valutazioni);
    detailsLayout->addSpacing(10);
    detailsLayout->addWidget(descrizione);
    detailsLayout->addStretch(); */

    detailsLayout->addWidget(sezioneProgrammazione);

    splitterLayout->addWidget(partesx);
    splitterLayout->setAlignment(Qt::AlignHCenter);
    detailPage = page;
    page->setStyleSheet("QLabel { background-color: red} #sp { background-color: orange} #details { background-color: purple} #gugu { background-color: pink} #gaga {background-color: red} #pupu {background-color: yellow} #caca{background-color: blue}");

}
void DetailPageVisitor::visit(Trailer*) {}
void DetailPageVisitor::visit(Inserzione*) {}
void DetailPageVisitor::visit(Podcast*) {}
void DetailPageVisitor::visit(Puntata*) {}
