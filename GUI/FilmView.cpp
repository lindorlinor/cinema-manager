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
#include "GUI/PreviewCard.h"
#include "GUI/DetailsPageButtons.h"

#include <QDebug>

FilmView::FilmView(Film* fPtr, QWidget* parent):MediaView(fPtr,parent),filmPtr(fPtr){
    createMediaDetails();
    createScrollableSection();
    createButtons();
}


void FilmView::createMediaDetails(){
    leftSide->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leftSide->setObjectName("pupu");
    leftSide->setContentsMargins(0,0,0,0);
    leftLayout->setSpacing(0);
    leftLayout->setContentsMargins(0,0,0,0);
    
    createMediaCard();

    QScrollArea* scrollDetails = new QScrollArea(leftSide);
    QFrame * details = new QFrame(scrollDetails);
    QVBoxLayout * detailsLayout = new QVBoxLayout(details);
    detailsLayout->setContentsMargins(0, 0, 0, 0);
    // details->setFixedHeight(scaled.height()+210);
    details->setMaximumWidth(600);
    details->setContentsMargins(0,0,13,0);
    details->setObjectName("details");

    scrollDetails->setWidget(details);
    scrollDetails->setWidgetResizable(true);
    scrollDetails->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollDetails->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    leftLayout->addWidget(scrollDetails);
    detailsLayout->setSpacing(10);
    QWidget * sezioneProgrammazione = new QWidget(details);
    sezioneProgrammazione->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    QVBoxLayout * layoutProgrammazione = new QVBoxLayout(sezioneProgrammazione);
    
    QLabel * labelProgrammazione = new QLabel("Informazioni di programmazione");
    layoutProgrammazione->addWidget(labelProgrammazione);

    QWidget * dettagliProgrammazione = new QWidget(sezioneProgrammazione);
    QGridLayout * layoutDettagliProgrammazione = new QGridLayout(dettagliProgrammazione);
    dettagliProgrammazione->setContentsMargins(10,10,10,10);
    sezioneProgrammazione->setObjectName("sp");
    
    QLabel* inizioP = new QLabel(
        "<span style='color:white; font-weight:bold;'>Inizio proiezione: </span>"
        "<span style='color:black;'>" + QString::fromStdString(dateToString(filmPtr->getDataInizioRilascio())) + "</span>",dettagliProgrammazione);
    inizioP->setTextFormat(Qt::RichText);
    endDateLabel = new QLabel(
        "<span style='color:white; font-weight:bold;'>Fine proiezione: </span>"
        "<span style='color:black;'>" + QString::fromStdString(dateToString(filmPtr->getDataFineRilascio())) + "</span>",dettagliProgrammazione);
    endDateLabel->setTextFormat(Qt::RichText);
    inizioP->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    endDateLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    inizioP->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    QLabel* costoBiglietto = new QLabel(
        "<span style='color:white; font-weight:bold;'>Costo biglietto: </span>"
        "<span style='color:black;'>" + QString::number(filmPtr->getCostoBiglietto()) + " €</span>",dettagliProgrammazione);
    costoBiglietto->setTextFormat(Qt::RichText);
    costoBiglietto->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    
    layoutDettagliProgrammazione->addWidget(inizioP,0,0);
    layoutDettagliProgrammazione->addWidget(endDateLabel,0,1);
    layoutDettagliProgrammazione->addWidget(costoBiglietto,1,0);
    layoutProgrammazione->addWidget(dettagliProgrammazione);
    
    
    QWidget * sezionePerformance = new QWidget(details);
    QVBoxLayout * layoutPerformance = new QVBoxLayout(sezionePerformance);
    
    QLabel * labelPerformance = new QLabel("Performance e statistiche");
    layoutPerformance->addWidget(labelPerformance);
    
    QWidget * dettagliPerformance = new QWidget(sezionePerformance);
    QVBoxLayout * layoutDettagliPerformance = new QVBoxLayout(dettagliPerformance);
    dettagliPerformance->setContentsMargins(10,10,10,10);
    sezionePerformance->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    sezionePerformance->setObjectName("sp");
    
    // Visualizzazioni e incasso
    QLabel* incasso = new QLabel(
        "<span style='color:white; font-weight:bold;'>Incasso totale: </span>"
        "<span style='color:black;'>" + QString::number(filmPtr->calcolaIncasso()) + " €</span>",dettagliPerformance);
    incasso->setTextFormat(Qt::RichText);
    QLabel* visualizzazioni = new QLabel(
        "<span style='color:white; font-weight:bold;'>Visualizzazioni: </span>"
        "<span style='color:black;'>" + QString::number(filmPtr->getVisualizzazioni()) + "</span>",dettagliPerformance);
    visualizzazioni->setTextFormat(Qt::RichText);
    QLabel* valutazione = new QLabel(
        "<span style='color:white; font-weight:bold;'>Valutazione: </span>"
    "<span style='color:black;'>" + QString::number(filmPtr->getValutazione()) + "/5</span>",dettagliPerformance);
    valutazione->setTextFormat(Qt::RichText);

    layoutDettagliPerformance->addWidget(incasso);
    layoutDettagliPerformance->addWidget(visualizzazioni);
    layoutDettagliPerformance->addWidget(valutazione);
    layoutPerformance->addWidget(dettagliPerformance);
    
    QWidget * sezioneTecnica = new QWidget(details);
    QVBoxLayout * layoutTecnica = new QVBoxLayout(sezioneTecnica);
    sezioneTecnica->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    sezioneTecnica->setObjectName("sp");
    QLabel * labelTecnica = new QLabel("Caratteristiche tecniche");
    layoutTecnica->addWidget(labelTecnica);
    
    QWidget * dettagliTecnici = new QWidget(sezioneTecnica);
    QVBoxLayout * layoutDettagliTecnici = new QVBoxLayout(dettagliTecnici);
    dettagliTecnici->setContentsMargins(10,10,10,10);
    
    QLabel* risoluzione = new QLabel(
        "<span style='color:white; font-weight:bold;'>Risoluzione: </span>"
        "<span style='color:black;'>" + QString::fromUtf8(toString(filmPtr->getRisoluzione())) + "</span>",dettagliTecnici);
    risoluzione->setTextFormat(Qt::RichText);
    QLabel* formato = new QLabel(
        "<span style='color:white; font-weight:bold;'>Formato: </span>"
        "<span style='color:black;'>" + QString::fromUtf8(toString(filmPtr->getFormato())) + "</span>",dettagliTecnici);
    formato->setTextFormat(Qt::RichText);
    QLabel* postCredit = new QLabel(
        "<span style='color:white; font-weight:bold;'>Post credit: </span>"
        "<span style='color:black;'>" + QString::number(filmPtr->getNPostCredit()) + "</span>",dettagliTecnici);
    postCredit->setTextFormat(Qt::RichText);
    layoutDettagliTecnici->addWidget(risoluzione);
    layoutDettagliTecnici->addWidget(formato);
    layoutDettagliTecnici->addWidget(postCredit);
    layoutTecnica->addWidget(dettagliTecnici);
    
    QWidget *sezioneDettagli = new QWidget(details);
    sezioneDettagli->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    QVBoxLayout * layoutDettagli = new QVBoxLayout(sezioneDettagli);
    QLabel * labelDettagli = new QLabel("Dettagli sul film");
    layoutDettagli->addWidget(labelDettagli);
    labelDettagli->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    
    QWidget * dettagliDettagli = new QWidget(sezioneDettagli); //@to do ciao linor del futuro, cambia sto nome per favore
    QVBoxLayout * layoutDettagliDettagli = new QVBoxLayout(dettagliDettagli);
    dettagliDettagli->setContentsMargins(10,10,10,10);
    
    
    ExpandableLabel* descrizione = new ExpandableLabel(
         "<span style='color:white; font-weight:bold;'>Descrizione: </span><br>" + QString::fromStdString(filmPtr->getDescrizione()),dettagliDettagli);
   
    std::vector<std::string> attoriPrincipali = filmPtr->getAttoriPrincipali();
    QString attoriText;
    for (size_t i = 0; i < attoriPrincipali.size(); ++i) {
        attoriText += QString::fromStdString(attoriPrincipali[i]);
        if (i != attoriPrincipali.size() - 1) attoriText += ", ";
    }

    descrizione->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    ExpandableLabel* attoriLabel = new ExpandableLabel(
         "<span style='color:white; font-weight:bold;'>Attori principali: </span>" + attoriText,dettagliDettagli);
    attoriLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);


    std::vector<Genere> generi = filmPtr->getGeneri();
    QString generiText;
    for (size_t i = 0; i < generi.size(); ++i) {
        generiText += QString::fromUtf8(toString(generi[i]));
        if (i != generi.size() - 1) {
            generiText += ", ";
        }
    }

    QLabel* genere = new QLabel(
        "<span style='color:white; font-weight:bold;'>Genere: </span>"
        "<span style='color:black;'>" + generiText + "</span>",dettagliDettagli);
    genere->setTextFormat(Qt::RichText);

    QLabel* classificazione = new QLabel(
        "<span style='color:white; font-weight:bold;'>Classificazione: </span>"
        "<span style='color:black;'>" + QString::fromUtf8(toString(filmPtr->getTarget())) + "</span>");
    classificazione->setTextFormat(Qt::RichText);
    
    QLabel* casaProduzione = new QLabel(
        "<span style='color:white; font-weight:bold;'>Casa di produzione: </span>"
        "<span style='color:black;'>" + QString::fromStdString(filmPtr->getCasaDiProduzione()) + "</span>",dettagliDettagli);
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

void FilmView::createScrollableSection(){
    rightSide->setObjectName("gaga");
    rightSide->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    
    QLabel *labelTrailer = new QLabel("Trailer",rightSide);
    QFont fontTrailer = labelTrailer->font();
    fontTrailer.setPointSize(17);
    fontTrailer.setBold(true);
    labelTrailer->setFont(fontTrailer);
    
    rightLayout->addWidget(labelTrailer);

    QScrollArea* scrollTrailer = new QScrollArea(rightSide); //configurata dopo
    QWidget * sezioneTrailer = new QWidget(scrollTrailer);
    QVBoxLayout * layoutTrailer = new QVBoxLayout(sezioneTrailer);
    sezioneTrailer->setObjectName("sp");

    for (const Trailer* t : filmPtr->getTrailers()) {
        PreviewCard* card = new PreviewCard(t);
        layoutTrailer->addWidget(card);
        connect(card, &PreviewCard::viewMedia, this, [this,t](){
            qDebug() << "view Media: " << QString::fromStdString(t->getTitolo());
            emit trailerSelected(t);
        });
    }
    layoutTrailer->setSpacing(20);  
    sezioneTrailer->setContentsMargins(20,20,20,33);

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

            auto fine = filmPtr->getDataFineRilascio();
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

        msgBox.addButton("Annulla", QMessageBox::RejectRole);
        msgBox.addButton("Conferma", QMessageBox::AcceptRole);
        int ret = msgBox.exec();
        if (ret == QMessageBox::Ok) {
            qDebug() << "Confermato";
            emit deleteMediaClicked();
        }
        });
    rightLayout->addSpacing(60);
    rightLayout->addWidget(buttons);
}