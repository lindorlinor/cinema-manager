#include "DetailPageVisitor.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QPixmap>
#include <QGridLayout>
#include <QScrollArea>
#include "../Film.h"
#include "GUI/ExpandableLabel.h"

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

    QWidget * splitter = new QWidget(page);
    QHBoxLayout * splitterLayout = new QHBoxLayout(splitter);

    layoutPage->addWidget(splitter,0,Qt::AlignHCenter);
    
    QWidget * partesx = new QWidget();
    partesx->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    partesx->setObjectName("pupu");
    QHBoxLayout * layoutsx = new QHBoxLayout(partesx);
    partesx->setContentsMargins(0,0,0,0);
    layoutsx->setSpacing(0);
    layoutsx->setContentsMargins(0,0,0,0);
    QWidget * card = new QWidget();
    QVBoxLayout * cardLayout = new QVBoxLayout(card);
    card->setContentsMargins(0,0,0,0);
    cardLayout->setContentsMargins(0,0,0,0);
    QPixmap image(QString::fromStdString(film->getImPath()));
    QLabel * copertina = new QLabel();
    // cardLayout->setAlignment(Qt::AlignBottom);//così almeno è attaccato alla box anche se non è scalato come si vorrebbe
    QPixmap scaled = image.scaled(300,445,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    copertina->setPixmap(scaled);
    cardLayout->addWidget(copertina);

    cardLayout->setSpacing(0);
    QWidget* box = new QWidget();
    box->setFixedSize(300, 210);
    box->setObjectName("caca");
    QVBoxLayout* layout = new QVBoxLayout(box);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(10);

    QLabel* regista = new QLabel(
        "<span style='color:white; font-weight:bold;'>Regista: </span>"
        "<span style='color:black;'>" + QString::fromStdString(film->getAutore()) + "</span>");
    regista->setTextFormat(Qt::RichText);

    QLabel* durata = new QLabel(
        "<span style='color:white; font-weight:bold;'>Durata: </span>"
        "<span style='color:black;'>" + QString::number(film->getDurataMinuti()) + " min</span>");
    durata->setTextFormat(Qt::RichText);

    //creazione label lingue
    std::vector<Lingua> lingueDisponibili = film->getLingue();
    QString lingueText;
    for (size_t i = 0; i < lingueDisponibili.size(); ++i) {
        lingueText += QString::fromUtf8(toString(lingueDisponibili[i]));
        if (i != lingueDisponibili.size() - 1) {
            lingueText += ", ";
        }
    }
    QLabel* lingue = new QLabel(
        "<span style='color:white; font-weight:bold;'>Lingue: </span>"
        "<span style='color:black;'>" + lingueText + "</span>");
    lingue->setTextFormat(Qt::RichText);

    //creazione label sottotitoli
    std::vector<Lingua> sottotitoliDisponibili = film->getSottotitoli();
    QString sottotitoliText;
    for (size_t i = 0; i < sottotitoliDisponibili.size(); ++i) {
        sottotitoliText += QString::fromUtf8(toString(sottotitoliDisponibili[i]));
        if (i != sottotitoliDisponibili.size() - 1) sottotitoliText += ", ";
    }
    QLabel* sottotitoli = new QLabel(
        "<span style='color:white; font-weight:bold;'>Sottotitoli: </span>"
        "<span style='color:black;'>" + sottotitoliText + "</span>");
    sottotitoli->setTextFormat(Qt::RichText);

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
    detailsLayout->setContentsMargins(0, 0, 0, 0);
    // details->setFixedHeight(scaled.height()+210);
    details->setMaximumWidth(570);
    details->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    details->setContentsMargins(0,0,0,0);
    details->setObjectName("details");
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidget(details);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    layoutsx->addWidget(scrollArea);
    detailsLayout->setSpacing(10);
    QWidget * sezioneProgrammazione = new QWidget();
    sezioneProgrammazione->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    QVBoxLayout * layoutProgrammazione = new QVBoxLayout(sezioneProgrammazione);
    
    QLabel * labelProgrammazione = new QLabel("Informazioni di programmazione");
    layoutProgrammazione->addWidget(labelProgrammazione);

    QWidget * dettagliProgrammazione = new QWidget();
    QGridLayout * layoutInternoProgrammazione = new QGridLayout(dettagliProgrammazione);
    dettagliProgrammazione->setContentsMargins(10,10,10,10);
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
    
    QLabel* inizioP = new QLabel(
        "<span style='color:white; font-weight:bold;'>Inizio proiezione: </span>"
        "<span style='color:black;'>" + QString::fromStdString(oss1.str()) + "</span>");
        inizioP->setTextFormat(Qt::RichText);
        QLabel* fineP = new QLabel(
            "<span style='color:white; font-weight:bold;'>Fine proiezione: </span>"
        "<span style='color:black;'>" + QString::fromStdString(oss2.str()) + "</span>");
        fineP->setTextFormat(Qt::RichText);
        inizioP->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        fineP->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        inizioP->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        QLabel* costoBiglietto = new QLabel(
            "<span style='color:white; font-weight:bold;'>Costo biglietto: </span>"
        "<span style='color:black;'>" + QString::number(film->getCostoBiglietto()) + " €</span>");
    costoBiglietto->setTextFormat(Qt::RichText);
    costoBiglietto->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    
    layoutInternoProgrammazione->addWidget(inizioP,0,0);
    layoutInternoProgrammazione->addWidget(fineP,0,1);
    layoutInternoProgrammazione->addWidget(costoBiglietto,1,0);
    layoutProgrammazione->addWidget(dettagliProgrammazione);
    
    
    QWidget * sezionePerformance = new QWidget();
    QVBoxLayout * layoutPerformance = new QVBoxLayout(sezionePerformance);
    
    QLabel * labelPerformance = new QLabel("Performance e statistiche");
    layoutPerformance->addWidget(labelPerformance);
    
    QWidget * dettagliPerformance = new QWidget();
    QVBoxLayout * layoutDettagliPerformance = new QVBoxLayout(dettagliPerformance);
    dettagliPerformance->setContentsMargins(10,10,10,10);
    sezionePerformance->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    sezionePerformance->setObjectName("sp");
    
    // Visualizzazioni e incasso
    QLabel* incasso = new QLabel(
        "<span style='color:white; font-weight:bold;'>Incasso totale: </span>"
        "<span style='color:black;'>" + QString::number(film->calcolaIncasso()) + " €</span>");
    incasso->setTextFormat(Qt::RichText);
    QLabel* visualizzazioni = new QLabel(
        "<span style='color:white; font-weight:bold;'>Visualizzazioni: </span>"
        "<span style='color:black;'>" + QString::number(film->getVisualizzazioni()) + "</span>");
    visualizzazioni->setTextFormat(Qt::RichText);
    QLabel* valutazione = new QLabel(
        "<span style='color:white; font-weight:bold;'>Valutazione: </span>"
    "<span style='color:black;'>" + QString::number(film->getValutazione()) + "/5</span>");
    valutazione->setTextFormat(Qt::RichText);

    layoutDettagliPerformance->addWidget(incasso);
    layoutDettagliPerformance->addWidget(visualizzazioni);
    layoutDettagliPerformance->addWidget(valutazione);
    layoutPerformance->addWidget(dettagliPerformance);
    
    QWidget * sezioneTecnica = new QWidget();
    QVBoxLayout * layoutTecnica = new QVBoxLayout(sezioneTecnica);
    sezioneTecnica->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    sezioneTecnica->setObjectName("sp");
    QLabel * labelTecnica = new QLabel("Caratteristiche tecniche");
    layoutTecnica->addWidget(labelTecnica);
    
    QWidget * dettagliTecnici = new QWidget();
    QVBoxLayout * layoutDettagliTecnici = new QVBoxLayout(dettagliTecnici);
    dettagliTecnici->setContentsMargins(10,10,10,10);
    
    QLabel* risoluzione = new QLabel(
        "<span style='color:white; font-weight:bold;'>Risoluzione: </span>"
        "<span style='color:black;'>" + QString::fromUtf8(toString(film->getRisoluzione())) + "</span>");
    risoluzione->setTextFormat(Qt::RichText);
    QLabel* formato = new QLabel(
        "<span style='color:white; font-weight:bold;'>Formato: </span>"
        "<span style='color:black;'>" + QString::fromUtf8(toString(film->getFormato())) + "</span>");
    formato->setTextFormat(Qt::RichText);
    QLabel* postCredit = new QLabel(
        "<span style='color:white; font-weight:bold;'>Post credit: </span>"
        "<span style='color:black;'>" + QString::number(film->getNPostCredit()) + "</span>");
    postCredit->setTextFormat(Qt::RichText);
    layoutDettagliTecnici->addWidget(risoluzione);
    layoutDettagliTecnici->addWidget(formato);
    layoutDettagliTecnici->addWidget(postCredit);
    layoutTecnica->addWidget(dettagliTecnici);
    
    QWidget *sezioneDettagli = new QWidget();
    sezioneDettagli->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    QVBoxLayout * layoutDettagli = new QVBoxLayout(sezioneDettagli);
    QLabel * labelDettagli = new QLabel("Dettagli sul film");
    layoutDettagli->addWidget(labelDettagli);
    labelDettagli->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    
    QWidget * dettagliDettagli = new QWidget(); //@to do ciao linor del futuro, cambia sto nome per favore
    QVBoxLayout * layoutDettagliDettagli = new QVBoxLayout(dettagliDettagli);
    dettagliDettagli->setContentsMargins(10,10,10,10);
    
    
    ExpandableLabel* descrizione = new ExpandableLabel(
         "<span style='color:white; font-weight:bold;'>Descrizione: </span><br>" + QString::fromStdString(film->getDescrizione())
        );
   
    // Creazione label attori principali
    std::vector<std::string> attoriPrincipali = film->getAttoriPrincipali();
    QString attoriText;
    for (size_t i = 0; i < attoriPrincipali.size(); ++i) {
        attoriText += QString::fromStdString(attoriPrincipali[i]);
        if (i != attoriPrincipali.size() - 1) attoriText += ", ";
    }

    descrizione->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ExpandableLabel* attoriLabel = new ExpandableLabel(
         "<span style='color:white; font-weight:bold;'>Attori principali: </span>" + attoriText
    );

    attoriLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QLabel* genere = new QLabel(
        "<span style='color:white; font-weight:bold;'>Genere: </span>"
        "<span style='color:black;'>" + QString::fromUtf8(toString(film->getGenere())) + "</span>");
    genere->setTextFormat(Qt::RichText);
    QLabel* classificazione = new QLabel(
        "<span style='color:white; font-weight:bold;'>Classificazione: </span>"
        "<span style='color:black;'>" + QString::fromUtf8(toString(film->getClassificazione())) + "</span>");
    classificazione->setTextFormat(Qt::RichText);
    
     QLabel* casaProduzione = new QLabel(
        "<span style='color:white; font-weight:bold;'>Casa di produzione: </span>"
        "<span style='color:black;'>" + QString::fromStdString(film->getCasaDiProduzione()) + "</span>");
    casaProduzione->setTextFormat(Qt::RichText);

    layoutDettagliDettagli->addWidget(descrizione);
    layoutDettagliDettagli->addWidget(attoriLabel);
    layoutDettagliDettagli->addWidget(genere);
    layoutDettagliDettagli->addWidget(classificazione);
    layoutDettagliDettagli->addWidget(casaProduzione);

    layoutDettagli->addWidget(dettagliDettagli);

    detailsLayout->addWidget(sezioneProgrammazione);
    detailsLayout->addWidget(sezionePerformance);
    detailsLayout->addWidget(sezioneTecnica);
    detailsLayout->addWidget(sezioneDettagli);

    
    QWidget* partedx = new QWidget();
    partedx->setObjectName("sp");
    QVBoxLayout * layoutdx = new QVBoxLayout(partedx);

    QWidget * sezioneTrailer = new QWidget();
    QVBoxLayout * layoutTrailer = new QVBoxLayout(sezioneTrailer);
    
    layoutdx->addWidget(sezioneTrailer);

    splitterLayout->addWidget(partesx);
    splitterLayout->addWidget(partedx);

  
    detailPage = page;
    page->setStyleSheet("QLabel { background-color: red} #sp { background-color: orange} #details { background-color: purple} #gugu { background-color: pink} #gaga {background-color: red} #pupu {background-color: yellow} #caca{background-color: blue}");

}
void DetailPageVisitor::visit(Trailer*) {}
void DetailPageVisitor::visit(Inserzione*) {}
void DetailPageVisitor::visit(Podcast*) {}
void DetailPageVisitor::visit(Puntata*) {}
