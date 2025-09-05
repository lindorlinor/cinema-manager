#include "TrailerView.h"
#include <QPushButton>
#include <QScrollArea>
#include "Film.h"
#include "ExpandableLabel.h"
#include "PreviewCard.h"
#include "PreviewCard.h"
#include "DetailsPageButtons.h"
#include <QMessageBox>
#include <QPushButton>

TrailerView::TrailerView(Trailer* tPtr, QWidget* parent)
    : MediaView(tPtr,parent),trailerPtr(tPtr)
{
    createMediaDetails();
    createScrollableSection();
    createButtons();
    layoutPage->addSpacing(30);
}


void TrailerView::createMediaDetails() {
    createRowDetails();
    leftSide->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    leftSide->setObjectName("pupu");
    leftSide->setContentsMargins(0,0,0,0);
    leftLayout->setSpacing(0);
    leftLayout->setContentsMargins(0,0,0,0);
    
    createMediaCard();

    QScrollArea* scrollDetails = new QScrollArea(leftSide);
    details->setParent(scrollDetails);
    detailsLayout->setContentsMargins(0, 0, 0, 0);
    scrollDetails->setMinimumHeight(550);
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
    
    QLabel * labelProgrammazione = new QLabel("Informazioni di programmazione");
    layoutProgrammazione->addWidget(labelProgrammazione);

    QWidget * dettagliProgrammazione = new QWidget(sezioneProgrammazione);
    QGridLayout * layoutDettagliProgrammazione = new QGridLayout(dettagliProgrammazione);
    layoutDettagliProgrammazione->setAlignment(Qt::AlignLeft);
    dettagliProgrammazione->setContentsMargins(10,10,10,10);
    
    
    QLabel* inizioP = new QLabel(
        "<span style='color: #bdced3; font-weight:bold;'>Inizio proiezione: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromStdString(dateToString(trailerPtr->getDataInizioRilascio())) + "</span>",dettagliProgrammazione);
    inizioP->setTextFormat(Qt::RichText);
    endDateLabel = new QLabel(
        "<span style='color: #bdced3; font-weight:bold;'>Fine proiezione: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromStdString(dateToString(trailerPtr->getDataFineRilascio())) + "</span>",dettagliProgrammazione);
    endDateLabel->setTextFormat(Qt::RichText);
    inizioP->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    endDateLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    inizioP->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    QLabel* nProiezioniGiornaliere = new QLabel(
        "<span style='color: #bdced3; font-weight:bold;'>Numero proiezioni giornaliere: </span>"
        "<span style='color: #4e7f8b;'>" + QString::number(trailerPtr->getNProiezioniGiornaliere()) + "</span>",dettagliProgrammazione);
    nProiezioniGiornaliere->setTextFormat(Qt::RichText);
    nProiezioniGiornaliere->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        
    QLabel* targetPubb = new QLabel(
        "<span style='color: #bdced3; font-weight:bold;'>Target pubblico: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromStdString(toString((trailerPtr->getFilm())->getTarget())) + "</span>",dettagliProgrammazione);

    targetPubb->setTextFormat(Qt::RichText);
    targetPubb->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    layoutDettagliProgrammazione->addWidget(inizioP,0,0);
    layoutDettagliProgrammazione->addWidget(endDateLabel,0,1);
    layoutDettagliProgrammazione->addWidget(nProiezioniGiornaliere,1,0);
    layoutDettagliProgrammazione->addWidget(targetPubb,2,0);
    layoutProgrammazione->addWidget(dettagliProgrammazione);
    
    
    QWidget * sezionePerformance = new QWidget(details);
    QVBoxLayout * layoutPerformance = new QVBoxLayout(sezionePerformance);
    
    QLabel * labelPerformance = new QLabel("Performance e statistiche");
    layoutPerformance->addWidget(labelPerformance);
    
    QWidget * dettagliPerformance = new QWidget(sezionePerformance);
    QVBoxLayout * layoutDettagliPerformance = new QVBoxLayout(dettagliPerformance);
    dettagliPerformance->setContentsMargins(10,10,10,10);
    sezionePerformance->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    

    QLabel* incasso = new QLabel(
        "<span style='color: #bdced3; font-weight:bold;'>Stima incasso totale: </span>"
        "<span style='color: #4e7f8b;'>" + QString::number(trailerPtr->calcolaIncasso()) + " €</span>",dettagliPerformance);
    incasso->setTextFormat(Qt::RichText);
    QLabel* visualizzazioni = new QLabel(
        "<span style='color: #bdced3; font-weight:bold;'>Visualizzazioni: </span>"
        "<span style='color: #4e7f8b;'>" + QString::number(trailerPtr->getVisualizzazioni()) + "</span>",dettagliPerformance);
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
        "<span style='color: #4e7f8b;'>" + QString::fromUtf8(toString(trailerPtr->getRisoluzione())) + "</span>",dettagliTecnici);
    risoluzione->setTextFormat(Qt::RichText);
    QLabel* formato = new QLabel(
        "<span style='color: #bdced3; font-weight:bold;'>Formato: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromUtf8(toString(trailerPtr->getFormato())) + "</span>",dettagliTecnici);
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
         "<span style='color:white; font-weight:bold;'>Descrizione: </span><br>" + QString::fromStdString(trailerPtr->getDescrizione()),dettagliDettagli);
   
    descrizione->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    layoutDettagliDettagli->addWidget(descrizione,0,Qt::AlignTop);
   
    layoutDettagli->addWidget(dettagliDettagli);

    detailsLayout->addWidget(sezioneProgrammazione);
    detailsLayout->addWidget(sezionePerformance);
    detailsLayout->addWidget(sezioneTecnica);
    detailsLayout->addWidget(sezioneDettagli);
    detailsLayout->addStretch();

    splitterLayout->addWidget(leftSide);

    labelProgrammazione->setObjectName("programmazione");
    labelPerformance->setObjectName("labelPerformance");
    labelTecnica->setObjectName("labelTecnica");
    labelDettagli->setObjectName("labelDettagli");
    //stile
    details->setStyleSheet(
        "QLabel {"
            "font-size: 11pt;"
            "color: #4e7f8b;"
        "}"
        "QLabel#programmazione,"
        "QLabel#labelPerformance,"
        "QLabel#labelTecnica,"
        "QLabel#labelDettagli {"
            "font-size: 13pt;"
            "font-weight: bold;"
            "color: #bdced3;"
        "}"
    );
    scrollDetails->setObjectName("scrollDetails");
   
}
void TrailerView::createScrollableSection(){
    rightSide->setObjectName("gaga");
    rightSide->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    
    QLabel *labelFilmA = new QLabel("Film associato",rightSide);
    labelFilmA->setObjectName("labelCorrelati");
    QFont fontFilmA = labelFilmA->font();
    fontFilmA.setPointSize(17);
    fontFilmA.setBold(true);
    labelFilmA->setFont(fontFilmA);
    
    rightLayout->addWidget(labelFilmA);

    QWidget * sezioneFilmA = new QWidget(rightSide);
    QVBoxLayout* layoutFilmA = new QVBoxLayout(sezioneFilmA);

    Film* filmA = trailerPtr->getFilm();
    PreviewCard* cardFilmA = new PreviewCard(filmA);
    cardFilmA->setFixedSize(210, 320);   
    layoutFilmA->addWidget(cardFilmA,0,Qt::AlignCenter);
    connect(cardFilmA, &PreviewCard::viewMedia, this, [this,filmA](){
        DetailPageVisitor detailVisitor;
        filmA->accept(&detailVisitor);
        emit requestMediaView(*detailVisitor.getWidget());
    });
    sezioneFilmA->setContentsMargins(20,0,20,0);
    
    QLabel *labelTrailer = new QLabel("Trailer correlati",rightSide);
    labelTrailer->setObjectName("labelCorrelati");
    QFont fontTrailer = labelTrailer->font();
    fontTrailer.setPointSize(17);
    fontTrailer.setBold(true);
    labelTrailer->setFont(fontTrailer);
    
    QScrollArea* scrollTrailer = new QScrollArea(rightSide); //configurata dopo
    QWidget * sezioneTrailer = new QWidget(scrollTrailer);
    QVBoxLayout * layoutTrailer = new QVBoxLayout(sezioneTrailer);
    
    for (Trailer* t : (trailerPtr->getFilm())->getTrailers()) {
        if(t!=trailerPtr){
            PreviewCard* cardTrailer = new PreviewCard(t);
            layoutTrailer->addWidget(cardTrailer,0,Qt::AlignCenter);
            connect(cardTrailer, &PreviewCard::viewMedia, this, 
                [this,t](){
                    DetailPageVisitor detailVisitor;
                    t->accept(&detailVisitor);
                    emit requestMediaView(*detailVisitor.getWidget());
                });
            }
    }
    layoutTrailer->setSpacing(20);  
    sezioneTrailer->setContentsMargins(20,20,20,20);
    
    scrollTrailer->setWidget(sezioneTrailer);
    scrollTrailer->setWidgetResizable(true);
    scrollTrailer->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollTrailer->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollTrailer->setMinimumHeight(180);


    rightLayout->addWidget(sezioneFilmA,0,Qt::AlignTop);
    rightLayout->addSpacing(20);
    rightLayout->addWidget(labelTrailer);
    rightLayout->addWidget(scrollTrailer);
    splitterLayout->addWidget(rightSide);
    
    sezioneFilmA->setObjectName("sezioneScroll");
    sezioneTrailer->setObjectName("sezioneScroll");
    scrollTrailer->setObjectName("scrollDetails");
}
void TrailerView::createButtons(){
    DetailsPageButtons * buttons = new DetailsPageButtons(trailerPtr,leftSide);
    buttons->setDeleteButtonText("Elimina trailer");
    connect(buttons,&DetailsPageButtons::extendMedia,this,
        [this](){
            QMessageBox msgBox(this);
            auto fine = trailerPtr->getDataFineRilascio();
            auto nuovaFine = (trailerPtr->getFilm())->getDataFineRilascio();

            if(fine!=nuovaFine){
                msgBox.setWindowTitle("Conferma estensione data");
                msgBox.setText(QString::fromStdString(
                "La data di fine proiezione cambierà in\n" + dateToString(fine) + " → " + dateToString(nuovaFine) + "in accordo con la data di fine rilascio del film associato"));

                msgBox.setInformativeText("Premi conferma per continuare, annulla per non modificare.");
                msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
                msgBox.button(QMessageBox::Ok)->setText("Conferma");
                msgBox.button(QMessageBox::Cancel)->setText("Annulla");

                int ret = msgBox.exec();
                if (ret == QMessageBox::Ok) {
                    trailerPtr->estendiDataFineRilascio();
                    emit extendMediaClicked();
                    endDateLabel->setText("<span style='color:white; font-weight:bold;'>Fine proiezione: </span>"
                    "<span style='color:black;'>" + QString::fromStdString(dateToString(trailerPtr->getDataFineRilascio())) + "</span>");
                }
            }else{
                msgBox.setWindowTitle("Impossibile estendere la data");
                msgBox.setText("La data di fine rilascio del trailer non può superare quella del film");
                msgBox.setInformativeText("Estendere la proiezione del film in sala estenderà anche la data di fine rilascio dei trailer associati.");
                msgBox.exec();
            }
        });
           
    
    connect(buttons,&DetailsPageButtons::deleteMedia,this,[this](){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Conferma eliminazione");
        msgBox.setText("Sei sicuro di voler eliminare il trailer?"
                    "Premi conferma per continuare, annulla per non modificare.");
        
        QPushButton* annullaBtn = msgBox.addButton("Annulla", QMessageBox::RejectRole);
        QPushButton* confermaBtn = msgBox.addButton("Conferma", QMessageBox::AcceptRole);
        
        msgBox.exec();
        
        if (msgBox.clickedButton() == confermaBtn) {
            emit deleteMediaClicked(trailerPtr);
        }
        else if(msgBox.clickedButton() == annullaBtn){
            qDebug()<<"Eliminazione del media annullata";
        }
    });
    cardLayout->addSpacing(40);
    cardLayout->addWidget(buttons,0,Qt::AlignCenter);
}