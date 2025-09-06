#include "TrailerView.h"
#include <QPushButton>
#include <QScrollArea>
#include "Film.h"
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
    createRowDetails(); // da MediaView
    leftSide->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    leftSide->setContentsMargins(0,0,0,0);
    leftLayout->setSpacing(0);
    leftLayout->setContentsMargins(0,0,0,0);

    createMediaCard(); // da MediaView

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

    QWidget* sezioneProgrammazione = new QWidget(details);
    sezioneProgrammazione->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    QVBoxLayout* layoutProgrammazione = new QVBoxLayout(sezioneProgrammazione);
    layoutProgrammazione->setContentsMargins(0,0,0,0);

    QLabel* labelProgrammazione = new QLabel("Informazioni di programmazione");
    layoutProgrammazione->addWidget(labelProgrammazione);

    QWidget* dettagliProgrammazione = new QWidget(sezioneProgrammazione);
    QGridLayout* layoutDettagliProgrammazione = new QGridLayout(dettagliProgrammazione);
    layoutDettagliProgrammazione->setAlignment(Qt::AlignLeft);
    dettagliProgrammazione->setContentsMargins(10,10,10,10);

    inizioP = new QLabel(dettagliProgrammazione);
    endDateLabel = new QLabel(dettagliProgrammazione);
    nProiezioniGiornaliere = new QLabel(dettagliProgrammazione);
    targetPubb = new QLabel(dettagliProgrammazione);

    layoutDettagliProgrammazione->addWidget(inizioP,0,0);
    layoutDettagliProgrammazione->addWidget(endDateLabel,0,1);
    layoutDettagliProgrammazione->addWidget(nProiezioniGiornaliere,1,0);
    layoutDettagliProgrammazione->addWidget(targetPubb,2,0);
    layoutProgrammazione->addWidget(dettagliProgrammazione);

    QWidget* sezionePerformance = new QWidget(details);
    QVBoxLayout* layoutPerformance = new QVBoxLayout(sezionePerformance);
    sezionePerformance->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);

    QLabel* labelPerformance = new QLabel("Performance e statistiche");
    layoutPerformance->addWidget(labelPerformance);

    QWidget* dettagliPerformance = new QWidget(sezionePerformance);
    QVBoxLayout* layoutDettagliPerformance = new QVBoxLayout(dettagliPerformance);
    dettagliPerformance->setContentsMargins(10,10,10,10);

    incasso = new QLabel(dettagliPerformance);
    visualizzazioni = new QLabel(dettagliPerformance);

    layoutDettagliPerformance->addWidget(incasso);
    layoutDettagliPerformance->addWidget(visualizzazioni);
    layoutPerformance->addWidget(dettagliPerformance);

    QWidget* sezioneTecnica = new QWidget(details);
    QVBoxLayout* layoutTecnica = new QVBoxLayout(sezioneTecnica);
    sezioneTecnica->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);

    QLabel* labelTecnica = new QLabel("Caratteristiche tecniche");
    layoutTecnica->addWidget(labelTecnica);

    QWidget* dettagliTecnici = new QWidget(sezioneTecnica);
    QVBoxLayout* layoutDettagliTecnici = new QVBoxLayout(dettagliTecnici);
    dettagliTecnici->setContentsMargins(10,10,10,10);

    risoluzione = new QLabel(dettagliTecnici);
    formato = new QLabel(dettagliTecnici);

    layoutDettagliTecnici->addWidget(risoluzione);
    layoutDettagliTecnici->addWidget(formato);
    layoutTecnica->addWidget(dettagliTecnici);

    QWidget* sezioneDettagli = new QWidget(details);
    sezioneDettagli->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    QVBoxLayout* layoutDettagli = new QVBoxLayout(sezioneDettagli);

    QLabel* labelDettagli = new QLabel("Dettagli sul trailer");
    layoutDettagli->addWidget(labelDettagli);

    QWidget* dettagliDettagli = new QWidget(sezioneDettagli);
    QVBoxLayout* layoutDettagliDettagli = new QVBoxLayout(dettagliDettagli);
    dettagliDettagli->setContentsMargins(10,10,10,10);

    descrizione = new ExpandableLabel(" ",dettagliDettagli);
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
    scrollDetails->setObjectName("scrollDetails");

    sezioneProgrammazione->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    endDateLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    inizioP->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    nProiezioniGiornaliere->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    targetPubb->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sezionePerformance->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    sezioneTecnica->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    sezioneDettagli->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    labelDettagli->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    descrizione->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    updateMediaDetails();
}




void TrailerView::updateMediaDetails() {
    inizioP->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Inizio proiezione: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromStdString(dateToString(trailerPtr->getDataInizioRilascio())) + "</span>");
    
    endDateLabel->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Fine proiezione: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromStdString(dateToString(trailerPtr->getDataFineRilascio())) + "</span>");

    nProiezioniGiornaliere->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Numero proiezioni giornaliere: </span>"
        "<span style='color: #4e7f8b;'>" + QString::number(trailerPtr->getNProiezioniGiornaliere()) + "</span>");

    targetPubb->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Target pubblico: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromStdString(toString(trailerPtr->getFilm()->getTarget())) + "</span>");

    incasso->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Stima incasso totale: </span>"
        "<span style='color: #4e7f8b;'>" + QString::number(trailerPtr->calcolaIncasso()) + " €</span>");

    visualizzazioni->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Visualizzazioni: </span>"
        "<span style='color: #4e7f8b;'>" + QString::number(trailerPtr->getVisualizzazioni()) + "</span>");

    risoluzione->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Risoluzione: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromUtf8(toString(trailerPtr->getRisoluzione())) + "</span>");

    formato->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Formato: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromUtf8(toString(trailerPtr->getFormato())) + "</span>");

    descrizione->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Descrizione: </span><br>" +
        QString::fromStdString(trailerPtr->getDescrizione()));
}


void TrailerView::createScrollableSection() {
    rightSide->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel* labelFilmA = new QLabel("Film associato", rightSide);
    labelFilmA->setObjectName("labelCorrelati");
    QFont fontFilmA = labelFilmA->font();
    fontFilmA.setPointSize(17);
    fontFilmA.setBold(true);
    labelFilmA->setFont(fontFilmA);
    rightLayout->addWidget(labelFilmA);

    QWidget * sezioneFilmA = new QWidget(rightSide);
    layoutFilmA = new QVBoxLayout(sezioneFilmA);
    sezioneFilmA->setContentsMargins(20,0,20,0);

    QLabel* labelTrailer = new QLabel("Trailer correlati", rightSide);
    labelTrailer->setObjectName("labelCorrelati");
    QFont fontTrailer = labelTrailer->font();
    fontTrailer.setPointSize(17);
    fontTrailer.setBold(true);
    labelTrailer->setFont(fontTrailer);

    QScrollArea* scrollTrailer = new QScrollArea(rightSide);
    QWidget* sezioneTrailer = new QWidget(scrollTrailer);
    layoutTrailer = new QVBoxLayout(sezioneTrailer);
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

    updateScrollableSection();
}

void TrailerView::updateScrollableSection() {
    QLayoutItem* item;
    while ((item = layoutFilmA->takeAt(0)) != nullptr) {
        if (QWidget* w = item->widget()) w->deleteLater();
        delete item;
    }

    Film* filmA = trailerPtr->getFilm();
    PreviewCard* cardFilmA = new PreviewCard(filmA);
    cardFilmA->setFixedSize(210, 320);
    layoutFilmA->addWidget(cardFilmA,0,Qt::AlignCenter);
    connect(cardFilmA, &PreviewCard::viewMedia, this, [this,filmA](){
        DetailPageVisitor detailVisitor;
        filmA->accept(&detailVisitor);
        emit requestMediaView(*detailVisitor.getWidget());
    });

    while ((item = layoutTrailer->takeAt(0)) != nullptr) {
        if (QWidget* w = item->widget()) w->deleteLater();
        delete item;
    }

    for (Trailer* t : filmA->getTrailers()) {
        if (t != trailerPtr) {
            PreviewCard* cardTrailer = new PreviewCard(t);
            layoutTrailer->addWidget(cardTrailer,0,Qt::AlignCenter);
            connect(cardTrailer, &PreviewCard::viewMedia, this, [this,t](){
                DetailPageVisitor detailVisitor;
                t->accept(&detailVisitor);
                emit requestMediaView(*detailVisitor.getWidget());
            });
        }
    }
    layoutTrailer->addStretch();
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
                    endDateLabel->setText("<span style='color: #bdced3; font-weight:bold;'>Fine proiezione: </span>"
                    "<span style='color: #4e7f8b;'>" + QString::fromStdString(dateToString(trailerPtr->getDataFineRilascio())) + "</span>");
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
            // qDebug()<<"Eliminazione del media annullata";
        }
    });
    cardLayout->addSpacing(40);
    cardLayout->addWidget(buttons,0,Qt::AlignCenter);
}



void TrailerView::update(){
    MediaView::update();
    updateMediaDetails();
    updateScrollableSection();
}