#include "InserzioneView.h"
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

InserzioneView::InserzioneView(Inserzione* iPtr, QWidget* parent):MediaView(iPtr,parent),insPtr(iPtr){
    createMediaDetails();
    createScrollableSection();
    createButtons();
}


void InserzioneView::createMediaDetails(){
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
    scrollDetails->setMinimumHeight(550);
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
        "<span style='color:black;'>" + QString::fromStdString(dateToString(insPtr->getDataInizioRilascio())) + "</span>",dettagliProgrammazione);
    inizioP->setTextFormat(Qt::RichText);
    endDateLabel = new QLabel(
        "<span style='color:white; font-weight:bold;'>Fine proiezione: </span>"
        "<span style='color:black;'>" + QString::fromStdString(dateToString(insPtr->getDataFineRilascio())) + "</span>",dettagliProgrammazione);
    endDateLabel->setTextFormat(Qt::RichText);
    inizioP->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    endDateLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    inizioP->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    QLabel* nProiezioniGiornaliere = new QLabel(
        "<span style='color:white; font-weight:bold;'>Numero proiezioni giornaliere: </span>"
        "<span style='color:black;'>" + QString::number(insPtr->getNProiezioniGiornaliere()) + "</span>",dettagliProgrammazione);
    nProiezioniGiornaliere->setTextFormat(Qt::RichText);
    nProiezioniGiornaliere->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    std::vector<FasciaOraria> fasceOrarie = insPtr->getFasceOrarie();
    QString fasceTxt;
    for (size_t i = 0; i < fasceOrarie.size(); ++i) {
        fasceTxt += QString::fromUtf8(toString(fasceOrarie[i]));
        if (i != fasceOrarie.size() - 1) {
            fasceTxt += ", ";
        }
    }
    QLabel* fasce = new QLabel(
        "<span style='color:white; font-weight:bold;'>Fasce orarie: </span>"
        "<span style='color:black;'>" + fasceTxt + "</span>",dettagliProgrammazione);
    fasce->setTextFormat(Qt::RichText);
    fasce->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        
    QLabel* targetPubb = new QLabel(
        "<span style='color:white; font-weight:bold;'>Target pubblico: </span>"
        "<span style='color:black;'>" + QString::fromStdString(toString(insPtr->getTarget())) + "</span>",dettagliProgrammazione);
    
    targetPubb->setTextFormat(Qt::RichText);
    targetPubb->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    layoutDettagliProgrammazione->addWidget(inizioP,0,0);
    layoutDettagliProgrammazione->addWidget(endDateLabel,0,1);
    layoutDettagliProgrammazione->addWidget(nProiezioniGiornaliere,1,0);
    layoutDettagliProgrammazione->addWidget(fasce,2,0);
    layoutDettagliProgrammazione->addWidget(targetPubb,3,0);
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
    
    
    QLabel* costoFissoProiezioni = new QLabel(
        "<span style='color:white; font-weight:bold;'>Costo fisso proiezioni: </span>"
        "<span style='color:black;'>" + QString::number(insPtr->getCostoFissoProiezione()) + " €</span>",dettagliPerformance);
    costoFissoProiezioni->setTextFormat(Qt::RichText);

    QLabel* incasso = new QLabel(
        "<span style='color:white; font-weight:bold;'>Stima incasso totale: </span>"
        "<span style='color:black;'>" + QString::number(insPtr->calcolaIncasso()) + " €</span>",dettagliPerformance);
    incasso->setTextFormat(Qt::RichText);
    QLabel* visualizzazioni = new QLabel(
        "<span style='color:white; font-weight:bold;'>Visualizzazioni: </span>"
        "<span style='color:black;'>" + QString::number(insPtr->getVisualizzazioni()) + "</span>",dettagliPerformance);
    visualizzazioni->setTextFormat(Qt::RichText);

    layoutDettagliPerformance->addWidget(costoFissoProiezioni);
    layoutDettagliPerformance->addWidget(incasso);
    layoutDettagliPerformance->addWidget(visualizzazioni);

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
        "<span style='color:black;'>" + QString::fromUtf8(toString(insPtr->getRisoluzione())) + "</span>",dettagliTecnici);
    risoluzione->setTextFormat(Qt::RichText);
    QLabel* formato = new QLabel(
        "<span style='color:white; font-weight:bold;'>Formato: </span>"
        "<span style='color:black;'>" + QString::fromUtf8(toString(insPtr->getFormato())) + "</span>",dettagliTecnici);
    formato->setTextFormat(Qt::RichText);

    layoutDettagliTecnici->addWidget(risoluzione);
    layoutDettagliTecnici->addWidget(formato);
    layoutTecnica->addWidget(dettagliTecnici);
    
    QWidget *sezioneDettagli = new QWidget(details);
    sezioneDettagli->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    QVBoxLayout * layoutDettagli = new QVBoxLayout(sezioneDettagli);
    QLabel * labelDettagli = new QLabel("Dettagli sul trailer");
    layoutDettagli->addWidget(labelDettagli);
    labelDettagli->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    
    QWidget * dettagliDettagli = new QWidget(sezioneDettagli); //@to do ciao linor del futuro, cambia sto nome per favore
    QVBoxLayout * layoutDettagliDettagli = new QVBoxLayout(dettagliDettagli);
    dettagliDettagli->setContentsMargins(10,10,10,10);
    
    
    ExpandableLabel* descrizione = new ExpandableLabel(
         "<span style='color:white; font-weight:bold;'>Descrizione: </span><br>" + QString::fromStdString(insPtr->getDescrizione()),dettagliDettagli);
   
    descrizione->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    layoutDettagliDettagli->addWidget(descrizione,0,Qt::AlignTop);
   
    layoutDettagli->addWidget(dettagliDettagli);

    detailsLayout->addWidget(sezioneProgrammazione);
    detailsLayout->addWidget(sezionePerformance);
    detailsLayout->addWidget(sezioneTecnica);
    detailsLayout->addWidget(sezioneDettagli);

    splitterLayout->addWidget(leftSide);

}


void InserzioneView::createButtons(){
    DetailsPageButtons * buttons = new DetailsPageButtons(insPtr,leftSide);
    buttons->setDeleteButtonText("Elimina Inserzione");

    connect(buttons,&DetailsPageButtons::extendMedia,this,
        [this](){
            QMessageBox msgBox(this);
            auto fine = insPtr->getDataFineRilascio();
            auto nuovaFine = insPtr->getDataFineRilascio() + months{1};

            if(fine!=nuovaFine){
                msgBox.setWindowTitle("Conferma estensione data");
                msgBox.setText(QString::fromStdString(
                "La data di fine proiezione cambierà in\n" + dateToString(fine) + " → " + dateToString(nuovaFine)));

                msgBox.setInformativeText("Premi conferma per continuare, annulla per non modificare.");
                msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
                msgBox.button(QMessageBox::Ok)->setText("Conferma");
                msgBox.button(QMessageBox::Cancel)->setText("Annulla");

                int ret = msgBox.exec();
                if (ret == QMessageBox::Ok) {
                    qDebug() << "Confermato";
                    endDateLabel->setText("<span style='color:white; font-weight:bold;'>Fine proiezione: </span>"
                    "<span style='color:black;'>" + QString::fromStdString(dateToString(nuovaFine)) + "</span>");
                    emit extendMediaClicked();
                }
            }
        });
           
    
    connect(buttons,&DetailsPageButtons::deleteMedia,this,[this](){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Conferma eliminazione");
        msgBox.setText("Sei sicuro di voler eliminare l'inserzione?");
        msgBox.setInformativeText("Premi conferma per continuare, annulla per non modificare.");
        msgBox.addButton("Annulla", QMessageBox::RejectRole);
        msgBox.addButton("Conferma", QMessageBox::AcceptRole);
        int ret = msgBox.exec();
        if (ret == QMessageBox::Ok) {
            qDebug() << "Confermato";
            emit deleteMediaClicked();
        }
        });
    cardLayout->addSpacing(40);
    cardLayout->addWidget(buttons);
}

//@to do non so come farla al momento, devo passare la lista di media WOPSIEE COME FACCIO AAGHHH
void InserzioneView::createScrollableSection(){
    /* rightSide->setObjectName("gaga");
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

    for (const Trailer* t : insPtr->get()) {
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

    splitterLayout->addWidget(rightSide); */
}







