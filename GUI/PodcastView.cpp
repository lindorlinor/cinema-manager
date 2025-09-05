#include "PodcastView.h"
#include "Puntata.h"
#include "Podcast.h"
#include <QScrollArea>
#include "ExpandableLabel.h"
#include "PreviewCard.h"
#include "DetailsPageButtons.h"
#include <QMessageBox>
#include <QAbstractButton>
#include <QStyle>

PodcastView::PodcastView(Podcast* pPtr, QWidget* parent):MediaView(pPtr,parent),podPtr(pPtr){
    createMediaDetails();
    createScrollableSection();
    createButtons();
    layoutPage->addSpacing(30);
}   

void PodcastView::createMediaDetails(){
    createRowDetails();
    leftSide->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leftSide->setContentsMargins(0,0,0,0);
    leftLayout->setSpacing(0);
    leftLayout->setContentsMargins(0,0,0,0);
    
    createMediaCard();

    QScrollArea* scrollDetails = new QScrollArea(leftSide);
    details->setParent(scrollDetails);
    detailsLayout->setContentsMargins(0, 0, 0, 0);
    details->setMaximumWidth(600);
    

    scrollDetails->setWidget(details);
    scrollDetails->setWidgetResizable(true);
    scrollDetails->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollDetails->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    leftLayout->addWidget(scrollDetails);
    detailsLayout->setSpacing(10);
    QWidget * sezioneProgrammazione = new QWidget(details);
    sezioneProgrammazione->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    QVBoxLayout * layoutProgrammazione = new QVBoxLayout(sezioneProgrammazione);
    
    QLabel * labelProgrammazione = new QLabel("Informazioni di distribuzione");
    layoutProgrammazione->addWidget(labelProgrammazione);

    QWidget * dettagliProgrammazione = new QWidget(sezioneProgrammazione);
    QHBoxLayout * layoutDettagliProgrammazione = new QHBoxLayout(dettagliProgrammazione);
    layoutDettagliProgrammazione->setSpacing(35);
    layoutDettagliProgrammazione->setAlignment(Qt::AlignLeft);
    dettagliProgrammazione->setContentsMargins(10,10,10,10);
    
    
    QLabel* inizioP = new QLabel(
        "<span style='color: #bdced3; font-weight:bold;'>Inizio proiezione: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromStdString(dateToString(podPtr->getDataInizioRilascio())) + "</span>",dettagliProgrammazione);
    inizioP->setTextFormat(Qt::RichText);
    endDateLabel = new QLabel(
        "<span style='color: #bdced3; font-weight:bold;'>Fine proiezione: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromStdString(dateToString(podPtr->getDataFineRilascio())) + "</span>",dettagliProgrammazione);
    endDateLabel->setTextFormat(Qt::RichText);
    inizioP->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    endDateLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    inizioP->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
   
    layoutDettagliProgrammazione->addWidget(inizioP);
    layoutDettagliProgrammazione->addWidget(endDateLabel);

    layoutProgrammazione->addWidget(dettagliProgrammazione);
    
    
    QWidget * sezionePerformance = new QWidget(details);
    QVBoxLayout * layoutPerformance = new QVBoxLayout(sezionePerformance);
    
    QLabel * labelPerformance = new QLabel("Performance e statistiche");
    layoutPerformance->addWidget(labelPerformance);
    
    QWidget * dettagliPerformance = new QWidget(sezionePerformance);
    QVBoxLayout * layoutDettagliPerformance = new QVBoxLayout(dettagliPerformance);
    dettagliPerformance->setContentsMargins(10,10,10,10);
    sezionePerformance->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    
    // Visualizzazioni e incasso
    QLabel* incasso = new QLabel(
        "<span style='color: #bdced3; font-weight:bold;'>Incasso totale: </span>"
        "<span style='color: #4e7f8b;'>" + QString::number(podPtr->calcolaIncasso()) + " €</span>",dettagliPerformance);
    incasso->setTextFormat(Qt::RichText);
    QLabel* visualizzazioni = new QLabel(
        "<span style='color: #bdced3; font-weight:bold;'>Visualizzazioni: </span>"
        "<span style='color: #4e7f8b;'>" + QString::number(podPtr->getVisualizzazioni()) + "</span>",dettagliPerformance);
    visualizzazioni->setTextFormat(Qt::RichText);

    layoutDettagliPerformance->addWidget(incasso);
    layoutDettagliPerformance->addWidget(visualizzazioni);
    layoutPerformance->addWidget(dettagliPerformance);
    
    QWidget * sezioneTecnica = new QWidget(details);
    QVBoxLayout * layoutTecnica = new QVBoxLayout(sezioneTecnica);
    sezioneTecnica->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);

    QLabel * labelTecnica = new QLabel("Caratteristiche tecniche");
    layoutTecnica->addWidget(labelTecnica);
    
    QWidget * dettagliTecnici = new QWidget(sezioneTecnica);
    QVBoxLayout * layoutDettagliTecnici = new QVBoxLayout(dettagliTecnici);
    dettagliTecnici->setContentsMargins(10,10,10,10);
    
    QLabel* risoluzione = new QLabel(
        "<span style='color: #bdced3; font-weight:bold;'>Risoluzione: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromUtf8(toString(podPtr->getRisoluzione())) + "</span>",dettagliTecnici);
    risoluzione->setTextFormat(Qt::RichText);
    QLabel* formato = new QLabel(
        "<span style='color: #bdced3; font-weight:bold;'>Formato: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromUtf8(toString(podPtr->getFormato())) + "</span>",dettagliTecnici);
    formato->setTextFormat(Qt::RichText);

    layoutDettagliTecnici->addWidget(risoluzione);
    layoutDettagliTecnici->addWidget(formato);
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
         "<span style='color: #bdced3; font-weight:bold;'>Descrizione: </span><br>" + QString::fromStdString(podPtr->getDescrizione()),dettagliDettagli);
        
    QLabel* conduttore = new QLabel(
        "<span style='color: #bdced3; font-weight:bold;'>Conduttore: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromStdString(podPtr->getConduttore()) + "</span>",dettagliTecnici);
    conduttore->setTextFormat(Qt::RichText);
    conduttore->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);   

     QLabel* nPuntate = new QLabel(
        "<span style='color: #bdced3; font-weight:bold;'>Numero di puntate: </span>"
        "<span style='color: #4e7f8b;'>" + QString::number(podPtr->getElencoPuntate().size()) + "</span>",dettagliTecnici);
    nPuntate->setTextFormat(Qt::RichText);
     nPuntate->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);  

    layoutDettagliDettagli->addWidget(descrizione);
    layoutDettagliDettagli->addWidget(conduttore);
    layoutDettagliDettagli->addWidget(nPuntate);



    layoutDettagli->addWidget(dettagliDettagli);

    detailsLayout->addWidget(sezioneProgrammazione);
    detailsLayout->addWidget(sezionePerformance);
    detailsLayout->addWidget(sezioneTecnica);
    detailsLayout->addWidget(sezioneDettagli);
    detailsLayout->addStretch();

    leftSide->setFixedHeight(700);
    splitterLayout->addWidget(leftSide);

    //stile
    labelProgrammazione->setObjectName("programmazione");
    labelPerformance->setObjectName("labelPerformance");
    labelTecnica->setObjectName("labelTecnica");
    labelDettagli->setObjectName("labelDettagli");
    scrollDetails->setObjectName("scrollDetails");
    
}
void PodcastView::createScrollableSection(){
    rightSide->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    
    QLabel *labelPuntate = new QLabel("Puntate",rightSide);
    labelPuntate->setObjectName("labelCorrelati");
    QFont fontPuntate = labelPuntate->font();
    fontPuntate.setPointSize(17);
    fontPuntate.setBold(true);
    labelPuntate->setFont(fontPuntate);
    
    rightLayout->addWidget(labelPuntate);

    QScrollArea* scrollPuntate = new QScrollArea(rightSide); //configurata dopo
    scrollPuntate->setObjectName("scrollDetails");
    QWidget * sezionePuntate = new QWidget(scrollPuntate);
    sezionePuntate->setObjectName("sezioneScroll");
    QVBoxLayout * layoutPuntate = new QVBoxLayout(sezionePuntate);
    layoutPuntate->setAlignment(Qt::AlignTop);

    for (Puntata* p : podPtr->getElencoPuntate()) {
        PreviewCard* card = new PreviewCard(p);
        layoutPuntate->addWidget(card);
        connect(card, &PreviewCard::viewMedia, this, [this,p](){
            DetailPageVisitor detailVisitor;
            p->accept(&detailVisitor);
            emit requestMediaView(*detailVisitor.getWidget());
        });
    }
    layoutPuntate->setSpacing(20);  
    sezionePuntate->setContentsMargins(20,20,20,33);

    scrollPuntate->setWidget(sezionePuntate);
    scrollPuntate->setWidgetResizable(true);
    scrollPuntate->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollPuntate->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollPuntate->setMinimumHeight(600);
    rightLayout->addWidget(scrollPuntate,0,Qt::AlignTop);

    splitterLayout->addWidget(rightSide);
}

void PodcastView::createButtons(){
    DetailsPageButtons * buttons = new DetailsPageButtons(podPtr,leftSide);
    buttons->setDeleteButtonText("Elimina podcast");
    connect(buttons,&DetailsPageButtons::extendMedia,this,
        [this](){
            QMessageBox msgBox(this);
            auto fine = podPtr->getDataFineRilascio();
            auto nuovaFine = sys_days(fine) + days{1};

            if(fine!=nuovaFine){
                msgBox.setWindowTitle("Conferma estensione data");
                msgBox.setText(QString::fromStdString(
                "La data di fine proiezione cambierà in\n" + dateToString(fine) + " → " + dateToString(nuovaFine) + "."));
                msgBox.setInformativeText(QString::fromStdString("La data di fine rilascio delle puntate associate verrà posticipata di un giorno ciascuna \n\nPremi conferma per continuare, annulla per non modificare."));
                msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
                msgBox.button(QMessageBox::Ok)->setText("Conferma");
                msgBox.button(QMessageBox::Cancel)->setText("Annulla");

                int ret = msgBox.exec();
                if (ret == QMessageBox::Ok) {
                    podPtr->estendiDataFineRilascio();
                    emit extendMediaClicked();
                    endDateLabel->setText("<span style='color:white; font-weight:bold;'>Fine proiezione: </span>"
                    "<span style='color:black;'>" + QString::fromStdString(dateToString(podPtr->getDataFineRilascio())) + "</span>");
                }
            }else{
                msgBox.setWindowTitle("Impossibile estendere la data");
                msgBox.setText("La data di fine rilascio del trailer non può superare quella del film");
                msgBox.setInformativeText("Estendere la proiezione del film in sala per poter estendere il rilascio dei suoi trailer");
            }

            
        });
           
    
    connect(buttons,&DetailsPageButtons::deleteMedia,this,[this](){
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Conferma eliminazione");
        msgBox.setText("Sei sicuro di voler eliminare il trailer? "
                    "Premi conferma per continuare, annulla per non modificare.");

        QPushButton* annullaBtn = msgBox.addButton("Annulla", QMessageBox::RejectRole);
        QPushButton* confermaBtn = msgBox.addButton("Conferma", QMessageBox::AcceptRole);

        msgBox.exec();


        if (msgBox.clickedButton() == confermaBtn) {
                emit deleteMediaClicked(podPtr);
        }
        else if(msgBox.clickedButton() == annullaBtn){
            qDebug()<<"Eliminazione del media annullata";
            }

        });

    cardLayout->addSpacing(40);
    cardLayout->addWidget(buttons,0,Qt::AlignCenter);
}