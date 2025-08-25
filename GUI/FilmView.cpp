#include "FilmView.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QString>
#include <QPixmap>
#include <QGridLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QHBoxLayout>
#include "GUI/ExpandableLabel.h"
#include "GUI/CardTrailer.h"
#include "GUI/DetailsPageButtons.h"

#include <QDebug>

FilmView::FilmView(Film* filmPtr, QWidget* parent)
    : QWidget(parent), film(filmPtr),layoutPage( new QVBoxLayout(this)),splitter(new QWidget(this)),splitterLayout(new QHBoxLayout(splitter)),leftSide(new QWidget(splitter)),
     rightSide(new QWidget(splitter)),leftLayout(new QHBoxLayout(leftSide)),endDateLabel(nullptr),rightLayout(new QVBoxLayout(rightSide))
{
    this->setObjectName("gugu");
    
    createHeader();
    
    splitterLayout->setSpacing(55);
    layoutPage->addWidget(splitter,0,Qt::AlignHCenter);

    createFilmDetails();
    createTrailersSection();
    createButtons();

    setLayout(layoutPage); 
}


void FilmView::createHeader(){
    QWidget * contenitoreHeader = new QWidget(this);
    contenitoreHeader->setObjectName("gaga");
    contenitoreHeader->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    QVBoxLayout * layoutHeader = new QVBoxLayout(contenitoreHeader);

    QPushButton* returnButton = new QPushButton("← indietro",contenitoreHeader);
    layoutHeader->addWidget(returnButton);

    returnButton->setCursor(Qt::PointingHandCursor);
    returnButton->setFixedSize(96,26);

    connect(returnButton, &QPushButton::clicked, this, &FilmView::returnButton);

    QLabel *titolo = new QLabel(QString::fromStdString(film->getTitolo()));
    QFont fontTitolo = titolo->font();
    fontTitolo.setPointSize(21);
    fontTitolo.setBold(true);
    titolo->setFont(fontTitolo);

    layoutHeader->addWidget(titolo);
    layoutHeader->setAlignment(Qt::AlignLeft);

    layoutPage->addWidget(contenitoreHeader);
}


void FilmView::createFilmDetails(){
    leftSide->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leftSide->setObjectName("pupu");
    leftSide->setContentsMargins(0,0,0,0);
    leftLayout->setSpacing(0);
    leftLayout->setContentsMargins(0,0,0,0);
    
    createFilmCard();

    QFrame * details = new QFrame();
    QVBoxLayout * detailsLayout = new QVBoxLayout(details);
    detailsLayout->setContentsMargins(0, 0, 0, 0);
    // details->setFixedHeight(scaled.height()+210);
    details->setMaximumWidth(600);
    details->setContentsMargins(0,0,13,0);
    details->setObjectName("details");
    QScrollArea* scrollDetails = new QScrollArea;
    scrollDetails->setWidget(details);
    scrollDetails->setWidgetResizable(true);
    scrollDetails->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollDetails->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    leftLayout->addWidget(scrollDetails);
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
    
    QLabel* inizioP = new QLabel(
        "<span style='color:white; font-weight:bold;'>Inizio proiezione: </span>"
        "<span style='color:black;'>" + QString::fromStdString(dateToString(film->getDataInizioRilascio())) + "</span>");
    inizioP->setTextFormat(Qt::RichText);
    endDateLabel = new QLabel(
        "<span style='color:white; font-weight:bold;'>Fine proiezione: </span>"
        "<span style='color:black;'>" + QString::fromStdString(dateToString(film->getDataFineRilascio())) + "</span>");
    endDateLabel->setTextFormat(Qt::RichText);
    inizioP->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    endDateLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    inizioP->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    QLabel* costoBiglietto = new QLabel(
        "<span style='color:white; font-weight:bold;'>Costo biglietto: </span>"
        "<span style='color:black;'>" + QString::number(film->getCostoBiglietto()) + " €</span>");
    costoBiglietto->setTextFormat(Qt::RichText);
    costoBiglietto->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    
    layoutInternoProgrammazione->addWidget(inizioP,0,0);
    layoutInternoProgrammazione->addWidget(endDateLabel,0,1);
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
         "<span style='color:white; font-weight:bold;'>Descrizione: </span><br>" + QString::fromStdString(film->getDescrizione()));
   
    std::vector<std::string> attoriPrincipali = film->getAttoriPrincipali();
    QString attoriText;
    for (size_t i = 0; i < attoriPrincipali.size(); ++i) {
        attoriText += QString::fromStdString(attoriPrincipali[i]);
        if (i != attoriPrincipali.size() - 1) attoriText += ", ";
    }

    descrizione->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    ExpandableLabel* attoriLabel = new ExpandableLabel(
         "<span style='color:white; font-weight:bold;'>Attori principali: </span>" + attoriText
    );
    attoriLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

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
    genere->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    layoutDettagliDettagli->addWidget(genere);
    classificazione->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    layoutDettagliDettagli->addWidget(classificazione);
    casaProduzione->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    layoutDettagliDettagli->addWidget(casaProduzione);

    layoutDettagli->addWidget(dettagliDettagli);

    detailsLayout->addWidget(sezioneProgrammazione);
    detailsLayout->addWidget(sezionePerformance);
    detailsLayout->addWidget(sezioneTecnica);
    detailsLayout->addWidget(sezioneDettagli);

    splitterLayout->addWidget(leftSide);

}


void FilmView::createFilmCard(){
    QWidget * card = new QWidget(leftSide);
    QVBoxLayout * cardLayout = new QVBoxLayout(card);
    card->setContentsMargins(0,0,0,0);
    cardLayout->setContentsMargins(0,0,0,0);
    QPixmap image(QString::fromStdString(film->getImPath()));
    QLabel * copertina = new QLabel();
    QPixmap scaled = image.scaled(330,489,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    copertina->setPixmap(scaled);
    cardLayout->addWidget(copertina);

    cardLayout->setSpacing(0);
    QWidget* box = new QWidget();
    box->setFixedSize(330, 231);
    box->setObjectName("caca");
    QVBoxLayout* layoutBox = new QVBoxLayout(box);
    layoutBox->setContentsMargins(35, 35, 35, 35);
    layoutBox->setSpacing(10);

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

    layoutBox->addWidget(regista);
    layoutBox->addWidget(durata);
    layoutBox->addWidget(lingue);
    layoutBox->addWidget(sottotitoli);
    layoutBox->setAlignment(Qt::AlignLeft);

    cardLayout->addWidget(box);
    leftLayout->addWidget(card);
}

void FilmView::createTrailersSection(){
    rightSide->setObjectName("gaga");
    rightSide->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    
    QLabel *labelTrailer = new QLabel("Trailer");
    QFont fontTrailer = labelTrailer->font();
    fontTrailer.setPointSize(17);
    fontTrailer.setBold(true);
    labelTrailer->setFont(fontTrailer);
    
    rightLayout->addWidget(labelTrailer);

    QWidget * sezioneTrailer = new QWidget();
    QVBoxLayout * layoutTrailer = new QVBoxLayout(sezioneTrailer);
    sezioneTrailer->setObjectName("sp");

    for (const Trailer* t : film->getTrailers()) {
        CardTrailer* card = new CardTrailer(t);
        layoutTrailer->addWidget(card);
        connect(card, &CardTrailer::viewTrailer, this, [this](const Trailer* trailer){
            qDebug() << "view Trailer: " << QString::fromStdString(trailer->getTitolo());
            emit trailerSelected(trailer);
        });
    }
    layoutTrailer->setSpacing(20);  
    sezioneTrailer->setContentsMargins(20,20,20,33);

    QScrollArea* scrollTrailer = new QScrollArea;
    scrollTrailer->setWidget(sezioneTrailer);
    scrollTrailer->setWidgetResizable(true);
    scrollTrailer->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollTrailer->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollTrailer->setMinimumHeight(400);
    rightLayout->addWidget(scrollTrailer,0,Qt::AlignTop);

    splitterLayout->addWidget(rightSide);
}
void FilmView::createButtons(){
    DetailsPageButtons * buttons = new DetailsPageButtons(rightSide);
    buttons->setDeleteButtonText("Elimina film");
    connect(buttons,&DetailsPageButtons::extendMedia,this,[this](){
        
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Conferma estensione data");

            auto fine = film->getDataFineRilascio();
            auto nuovaFine = sys_days(fine) + days{7}; 

            msgBox.setText(QString::fromStdString(
                "La data di fine proiezione cambierà in\n" + dateToString(fine) + " → " + dateToString(year_month_day{nuovaFine})));

            msgBox.setInformativeText(QString::fromStdString("I trailer associati in sala termineranno la proiezione il " + dateToString(year_month_day{nuovaFine}) +
                                      "\n\nPremi conferma per continuare, annulla per non modificare."));
            msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
            msgBox.button(QMessageBox::Ok)->setText("Conferma");
            msgBox.button(QMessageBox::Cancel)->setText("Annulla");

            int ret = msgBox.exec();
            if (ret == QMessageBox::Ok) {
                qDebug() << "Confermato";
                //logica observer???? o solo un set????
                endDateLabel->setText("<span style='color:white; font-weight:bold;'>Fine proiezione: </span>"
                "<span style='color:black;'>" + QString::fromStdString(dateToString(year_month_day(nuovaFine))) + "</span>");

                emit extendMediaClicked();
            }
        });
    
    connect(buttons,&DetailsPageButtons::deleteMedia,this,[this](){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Conferma eliminazione");
        msgBox.setText("Sei sicuro di voler eliminare il film? "
                    "Avrà l'effetto di eliminare tutti i trailer ad esso associati");


        QPushButton *btnAnnulla = msgBox.addButton("Annulla", QMessageBox::RejectRole);
        QPushButton *btnConferma = msgBox.addButton("Conferma", QMessageBox::AcceptRole);
        int ret = msgBox.exec();
        if (ret == QMessageBox::Ok) {
            qDebug() << "Confermato";
            emit deleteMediaClicked();
        }
        });
    rightLayout->addSpacing(60);
    rightLayout->addWidget(buttons);
}