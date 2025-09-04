#include "PuntataView.h"
#include "Podcast.h"
#include <QScrollArea>
#include "ExpandableLabel.h"
#include "DetailsPageButtons.h"
#include "PreviewCard.h"
#include <QMessageBox>
#include <QAbstractButton>
PuntataView::PuntataView(Puntata* pPtr,QWidget* parent):MediaView(pPtr,parent),puntPtr(pPtr){
    createMediaDetails();
    createScrollableSection();
    createButtons();
    layoutPage->addSpacing(30);
}

void PuntataView::createMediaDetails(){
    createRowDetails();
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
    sezioneProgrammazione->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    QVBoxLayout * layoutProgrammazione = new QVBoxLayout(sezioneProgrammazione);
    
    QLabel * labelProgrammazione = new QLabel("Informazioni di distribuzione");
    layoutProgrammazione->addWidget(labelProgrammazione);

    QWidget * dettagliProgrammazione = new QWidget(sezioneProgrammazione);
    QGridLayout * layoutDettagliProgrammazione = new QGridLayout(dettagliProgrammazione);
    layoutDettagliProgrammazione->setAlignment(Qt::AlignLeft);
    dettagliProgrammazione->setContentsMargins(10,10,10,10);
    sezioneProgrammazione->setObjectName("sp");
    
    QLabel* inizioP = new QLabel(
        "<span style='color:white; font-weight:bold;'>Inizio proiezione: </span>"
        "<span style='color:black;'>" + QString::fromStdString(dateToString(puntPtr->getDataInizioRilascio())) + "</span>",dettagliProgrammazione);
    inizioP->setTextFormat(Qt::RichText);
    endDateLabel = new QLabel(
        "<span style='color:white; font-weight:bold;'>Fine proiezione: </span>"
        "<span style='color:black;'>" + QString::fromStdString(dateToString(puntPtr->getDataFineRilascio())) + "</span>",dettagliProgrammazione);
    endDateLabel->setTextFormat(Qt::RichText);
    inizioP->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    endDateLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    inizioP->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        
    QLabel* nPubblicita = new QLabel(
        "<span style='color:white; font-weight:bold;'>Numero di pubblicita': </span>"
        "<span style='color:black;'>" + QString::number(puntPtr->getNumeroPubblicita()) + "</span>",dettagliProgrammazione);
    nPubblicita->setTextFormat(Qt::RichText);

    layoutDettagliProgrammazione->addWidget(inizioP,1,0);
    layoutDettagliProgrammazione->addWidget(endDateLabel,1,1);
    layoutDettagliProgrammazione->addWidget(nPubblicita,2,0);

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
        "<span style='color:black;'>" + QString::number(puntPtr->calcolaIncasso()) + " €</span>",dettagliPerformance);
    incasso->setTextFormat(Qt::RichText);
    QLabel* visualizzazioni = new QLabel(
        "<span style='color:white; font-weight:bold;'>Visualizzazioni: </span>"
        "<span style='color:black;'>" + QString::number(puntPtr->getVisualizzazioni()) + "</span>",dettagliPerformance);
    visualizzazioni->setTextFormat(Qt::RichText);

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
        "<span style='color:black;'>" + QString::fromUtf8(toString(puntPtr->getRisoluzione())) + "</span>",dettagliTecnici);
    risoluzione->setTextFormat(Qt::RichText);
    QLabel* formato = new QLabel(
        "<span style='color:white; font-weight:bold;'>Formato: </span>"
        "<span style='color:black;'>" + QString::fromUtf8(toString(puntPtr->getFormato())) + "</span>",dettagliTecnici);
    formato->setTextFormat(Qt::RichText);

    layoutDettagliTecnici->addWidget(risoluzione);
    layoutDettagliTecnici->addWidget(formato);
    layoutTecnica->addWidget(dettagliTecnici);
    
    QWidget *sezioneDettagli = new QWidget(details);
    sezioneDettagli->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    QVBoxLayout * layoutDettagli = new QVBoxLayout(sezioneDettagli);
    QLabel * labelDettagli = new QLabel("Dettagli della puntata");
    layoutDettagli->addWidget(labelDettagli);
    labelDettagli->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    
    QWidget * dettagliDettagli = new QWidget(sezioneDettagli); //@to do ciao linor del futuro, cambia sto nome per favore
    QVBoxLayout * layoutDettagliDettagli = new QVBoxLayout(dettagliDettagli);
    dettagliDettagli->setContentsMargins(10,10,10,10);
    
    
    ExpandableLabel* descrizione = new ExpandableLabel(
        "<span style='color:white; font-weight:bold;'>Descrizione: </span><br>" + QString::fromStdString(puntPtr->getDescrizione()),dettagliDettagli);
        
    QLabel* conduttore = new QLabel(
        "<span style='color:white; font-weight:bold;'>Conduttore: </span>"
        "<span style='color:black;'>" + QString::fromStdString((puntPtr->getPodcast())->getConduttore()) + "</span>",dettagliTecnici);
    conduttore->setTextFormat(Qt::RichText);
    conduttore->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
            
    layoutDettagliDettagli->addWidget(descrizione);
    layoutDettagliDettagli->addWidget(conduttore);


    layoutDettagli->addWidget(dettagliDettagli);

    detailsLayout->addWidget(sezioneProgrammazione);
    detailsLayout->addWidget(sezionePerformance);
    detailsLayout->addWidget(sezioneTecnica);
    detailsLayout->addWidget(sezioneDettagli);
    detailsLayout->addStretch();

    leftSide->setFixedHeight(700);
    splitterLayout->addWidget(leftSide);
}
void PuntataView::createScrollableSection(){
    rightSide->setFixedHeight(650);
    rightSide->setObjectName("gaga");
    rightSide->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    
    QLabel *labelPodA = new QLabel("Podcast associato",rightSide);
    QFont fontPodA = labelPodA->font();
    fontPodA.setPointSize(17);
    fontPodA.setBold(true);
    labelPodA->setFont(fontPodA);
    

    QWidget * sezionePodA = new QWidget(rightSide);
    QVBoxLayout* layoutPodA = new QVBoxLayout(sezionePodA);
    sezionePodA->setObjectName("sp"); 

    Podcast* podA = puntPtr->getPodcast();
    PreviewCard* cardPodA = new PreviewCard(podA);
    // cardPodA->setFixedSize(210, 320);   
    layoutPodA->addWidget(cardPodA,0,Qt::AlignCenter);
    connect(cardPodA, &PreviewCard::viewMedia, this, [this,podA](){
        DetailPageVisitor detailVisitor;
        podA->accept(&detailVisitor);
        emit requestMediaView(*detailVisitor.getWidget());
    });
    sezionePodA->setContentsMargins(20,0,20,0);

    QLabel *labelPuntate = new QLabel("Puntate correlate",rightSide);
    QFont fontPuntate = labelPuntate->font();
    fontPuntate.setPointSize(17);
    fontPuntate.setBold(true);
    labelPuntate->setFont(fontPuntate);
    
    QScrollArea* scrollPuntate = new QScrollArea(rightSide); //configurata dopo
    QWidget * sezionePuntate = new QWidget(scrollPuntate);
    QVBoxLayout * layoutPuntate = new QVBoxLayout(sezionePuntate);
    sezionePuntate->setObjectName("sp");

    for (Puntata* p : (puntPtr->getPodcast())->getElencoPuntate()) {
        if(p!=puntPtr){
            PreviewCard* cardPuntata = new PreviewCard(p);
            layoutPuntate->addWidget(cardPuntata,0,Qt::AlignCenter);
            connect(cardPuntata, &PreviewCard::viewMedia, this, 
                [this,p](){
                    DetailPageVisitor detailVisitor;
                    p->accept(&detailVisitor);
                    emit requestMediaView(*detailVisitor.getWidget());
                });
        }
    }
    layoutPuntate->setSpacing(20);  
    sezionePuntate->setContentsMargins(20,20,20,20);

    scrollPuntate->setWidget(sezionePuntate);
    scrollPuntate->setWidgetResizable(true);
    scrollPuntate->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollPuntate->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollPuntate->setMinimumHeight(180);

    rightLayout->addWidget(labelPodA);
    rightLayout->addWidget(sezionePodA,0,Qt::AlignTop);
    rightLayout->addSpacing(20);
    rightLayout->addWidget(labelPuntate);
    rightLayout->addWidget(scrollPuntate);
    splitterLayout->addWidget(rightSide);
}
void PuntataView::createButtons(){
    DetailsPageButtons * buttons = new DetailsPageButtons(puntPtr,leftSide);
    buttons->setDeleteButtonText("Elimina podcast");
    connect(buttons,&DetailsPageButtons::extendMedia,this,
        [this](){
            QMessageBox msgBox(this);
            auto fine = puntPtr->getDataFineRilascio();
            auto nuovaFine = sys_days(fine) + days{1};

            if(fine!=nuovaFine){
                msgBox.setWindowTitle("Conferma estensione data");
                msgBox.setText(QString::fromStdString(
                "La data di fine proiezione cambierà in\n" + dateToString(fine) + " → " + dateToString(nuovaFine) + "."));
                msgBox.setInformativeText(QString::fromStdString("Confermando l'estensione potrebbe cambiare la data di fine rilascio del podcast associato \n\nPremi conferma per continuare, annulla per non modificare."));
                msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
                msgBox.button(QMessageBox::Ok)->setText("Conferma");
                msgBox.button(QMessageBox::Cancel)->setText("Annulla");

                int ret = msgBox.exec();
                if (ret == QMessageBox::Ok) {
                    puntPtr->estendiDataFineRilascio();
                    emit extendMediaClicked();
                    endDateLabel->setText("<span style='color:white; font-weight:bold;'>Fine proiezione: </span>"
                    "<span style='color:black;'>" + QString::fromStdString(dateToString(puntPtr->getDataFineRilascio())) + "</span>");
                }
            }else{
                msgBox.setWindowTitle("Impossibile estendere la data");
                msgBox.setText("La data di fine rilascio del trailer non può superare quella del film");
                msgBox.setInformativeText("Estendere la proiezione del film in sala per poter estendere il rilascio dei suoi trailer");
            }
        });
           
    
    connect(buttons,&DetailsPageButtons::deleteMedia,this,[this](){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Conferma eliminazione");
        msgBox.setText("Sei sicuro di voler eliminare il trailer?");
        msgBox.setInformativeText("Premi conferma per continuare, annulla per non modificare.");
        msgBox.addButton("Annulla", QMessageBox::RejectRole);
        msgBox.addButton("Conferma", QMessageBox::AcceptRole);
        int ret = msgBox.exec();
        if (ret == QMessageBox::Ok) {
            emit deleteMediaClicked(puntPtr);
        }
        });
    cardLayout->addSpacing(40);
    cardLayout->addWidget(buttons,0,Qt::AlignCenter);


}