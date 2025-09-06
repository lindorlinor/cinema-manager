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

InserzioneView::InserzioneView(Inserzione* iPtr, QWidget* parent):MediaView(iPtr,parent),insPtr(iPtr),mediaList(nullptr){
    createMediaDetails();
    createButtons();
}


void InserzioneView::createMediaDetails() {
    createRowDetails(); //da MediaView
    leftSide->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leftSide->setContentsMargins(0,0,0,0);
    leftLayout->setSpacing(0);
    leftLayout->setContentsMargins(0,0,0,0);

    createMediaCard(); //da MediaView

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

    QLabel* labelProgrammazione = new QLabel("Informazioni di programmazione");
    layoutProgrammazione->addWidget(labelProgrammazione);

    QWidget* dettagliProgrammazione = new QWidget(sezioneProgrammazione);
    QGridLayout* layoutDettagliProgrammazione = new QGridLayout(dettagliProgrammazione);
    layoutDettagliProgrammazione->setAlignment(Qt::AlignLeft);
    dettagliProgrammazione->setContentsMargins(10,10,10,10);

    inizioP = new QLabel(dettagliProgrammazione);
    inizioP->setTextFormat(Qt::RichText);
    inizioP->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    endDateLabel = new QLabel(dettagliProgrammazione);
    endDateLabel->setTextFormat(Qt::RichText);
    endDateLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    nProiezioniGiornaliere = new QLabel(dettagliProgrammazione);
    nProiezioniGiornaliere->setTextFormat(Qt::RichText);
    nProiezioniGiornaliere->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    fasce = new QLabel(dettagliProgrammazione);
    fasce->setTextFormat(Qt::RichText);
    fasce->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    targetPubb = new QLabel(dettagliProgrammazione);
    targetPubb->setTextFormat(Qt::RichText);
    targetPubb->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    layoutDettagliProgrammazione->addWidget(inizioP,0,0);
    layoutDettagliProgrammazione->addWidget(endDateLabel,0,1);
    layoutDettagliProgrammazione->addWidget(nProiezioniGiornaliere,1,0);
    layoutDettagliProgrammazione->addWidget(fasce,2,0);
    layoutDettagliProgrammazione->addWidget(targetPubb,3,0);
    layoutProgrammazione->addWidget(dettagliProgrammazione);

    QWidget* sezionePerformance = new QWidget(details);
    QVBoxLayout* layoutPerformance = new QVBoxLayout(sezionePerformance);

    QLabel* labelPerformance = new QLabel("Performance e statistiche");
    layoutPerformance->addWidget(labelPerformance);

    QWidget* dettagliPerformance = new QWidget(sezionePerformance);
    QVBoxLayout* layoutDettagliPerformance = new QVBoxLayout(dettagliPerformance);
    dettagliPerformance->setContentsMargins(10,10,10,10);
    sezionePerformance->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);

    costoFissoProiezioni = new QLabel(dettagliPerformance);
    costoFissoProiezioni->setTextFormat(Qt::RichText);

    incasso = new QLabel(dettagliPerformance);
    incasso->setTextFormat(Qt::RichText);

    visualizzazioni = new QLabel(dettagliPerformance);
    visualizzazioni->setTextFormat(Qt::RichText);

    layoutDettagliPerformance->addWidget(costoFissoProiezioni);
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
    risoluzione->setTextFormat(Qt::RichText);

    formato = new QLabel(dettagliTecnici);
    formato->setTextFormat(Qt::RichText);

    layoutDettagliTecnici->addWidget(risoluzione);
    layoutDettagliTecnici->addWidget(formato);
    layoutTecnica->addWidget(dettagliTecnici);

    QWidget* sezioneDettagli = new QWidget(details);
    sezioneDettagli->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    QVBoxLayout* layoutDettagli = new QVBoxLayout(sezioneDettagli);

    QLabel* labelDettagli = new QLabel("Dettagli sull'inserzione");
    labelDettagli->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    layoutDettagli->addWidget(labelDettagli);

    QWidget* dettagliDettagli = new QWidget(sezioneDettagli);
    QVBoxLayout* layoutDettagliDettagli = new QVBoxLayout(dettagliDettagli);
    dettagliDettagli->setContentsMargins(10,10,10,10);

    descrizione = new ExpandableLabel("", dettagliDettagli);
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

    updateMediaDetails(); //aggiorna subito con il contenuto corrente
}

void InserzioneView::updateMediaDetails() {
    if (!insPtr) return;

    
    inizioP->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Inizio proiezione: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromStdString(dateToString(insPtr->getDataInizioRilascio())) + "</span>"
    );
    
    endDateLabel->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Fine proiezione: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromStdString(dateToString(insPtr->getDataFineRilascio())) + "</span>"
    );

    nProiezioniGiornaliere->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Numero proiezioni giornaliere: </span>"
        "<span style='color: #4e7f8b;'>" + QString::number(insPtr->getNProiezioniGiornaliere()) + "</span>"
    );

    QString fasceTxt;
    for (size_t i = 0; i < insPtr->getFasceOrarie().size(); ++i) {
        fasceTxt += QString::fromUtf8(toString(insPtr->getFasceOrarie()[i]));
        if (i != insPtr->getFasceOrarie().size() - 1)
            fasceTxt += ", ";
    }
    fasce->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Fasce orarie: </span>"
        "<span style='color: #4e7f8b;'>" + fasceTxt + "</span>"
    );

    targetPubb->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Target pubblico: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromStdString(toString(insPtr->getTarget())) + "</span>"
    );

    costoFissoProiezioni->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Costo fisso proiezioni: </span>"
        "<span style='color: #4e7f8b;'>" + QString::number(insPtr->getCostoFissoProiezione()) + " €</span>"
    );

    incasso->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Stima incasso totale: </span>"
        "<span style='color: #4e7f8b;'>" + QString::number(insPtr->calcolaIncasso()) + " €</span>"
    );

    visualizzazioni->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Visualizzazioni: </span>"
        "<span style='color: #4e7f8b;'>" + QString::number(insPtr->getVisualizzazioni()) + "</span>"
    );

    risoluzione->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Risoluzione: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromUtf8(toString(insPtr->getRisoluzione())) + "</span>"
    );

    formato->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Formato: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromUtf8(toString(insPtr->getFormato())) + "</span>"
    );

    descrizione->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Descrizione: </span><br>"
        + QString::fromStdString(insPtr->getDescrizione())
    );
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
                    insPtr->estendiDataFineRilascio();
                    emit extendMediaClicked();
                    endDateLabel->setText("<span style='color: #bdced3; font-weight:bold;'>Fine proiezione: </span>"
                    "<span style='color: #4e7f8b;'>" + QString::fromStdString(dateToString(insPtr->getDataFineRilascio())) + "</span>");
                }
            }
        });

        connect(buttons, &DetailsPageButtons::deleteMedia, this, [this](){
            QMessageBox msgBox;
            msgBox.setWindowTitle("Conferma eliminazione");
            msgBox.setText("Sei sicuro di voler eliminare l'inserzione? "
                        "Premi conferma per continuare, annulla per non modificare.");

            QPushButton* annullaBtn = msgBox.addButton("Annulla", QMessageBox::RejectRole);
            QPushButton* confermaBtn = msgBox.addButton("Conferma", QMessageBox::AcceptRole);

            msgBox.exec();

            if (msgBox.clickedButton() == confermaBtn) {
                emit deleteMediaClicked(insPtr);
            }
            else if(msgBox.clickedButton() == annullaBtn){
                qDebug()<<"Eliminazione del media annullata";
            }
        });

    cardLayout->addSpacing(40);
    cardLayout->addWidget(buttons,0,Qt::AlignCenter);
}

//@to do non so come farla al momento, devo passare la lista di media WOPSIEE COME FACCIO AAGHHH
void InserzioneView::createScrollableSection() {
    rightSide->setObjectName("gaga");
    rightSide->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel* labelInserzioni = new QLabel("Altre inserzioni", rightSide);
    labelInserzioni->setObjectName("labelCorrelati");
    QFont fontIns = labelInserzioni->font();
    fontIns.setPointSize(17);
    fontIns.setBold(true);
    labelInserzioni->setFont(fontIns);
    rightLayout->addWidget(labelInserzioni);

    QScrollArea* scrollInserzioni = new QScrollArea(rightSide);
    QWidget* sezioneInserzioni = new QWidget(scrollInserzioni);
    layoutInserzioni = new QVBoxLayout(sezioneInserzioni);
    layoutInserzioni->setAlignment(Qt::AlignTop);
    layoutInserzioni->setSpacing(20);
    sezioneInserzioni->setContentsMargins(20,20,20,33);

    scrollInserzioni->setWidget(sezioneInserzioni);
    scrollInserzioni->setWidgetResizable(true);
    scrollInserzioni->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollInserzioni->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollInserzioni->setMinimumHeight(600);

    rightLayout->addWidget(scrollInserzioni,0,Qt::AlignTop);
    splitterLayout->addWidget(rightSide);

    sezioneInserzioni->setObjectName("sezioneScroll");
    scrollInserzioni->setObjectName("scrollDetails");

    updateScrollableSection();
}

void InserzioneView::updateScrollableSection() {
    QLayoutItem* item;
    while ((item = layoutInserzioni->takeAt(0)) != nullptr) {
        if (QWidget* w = item->widget()) w->deleteLater();
        delete item;
    }

    for (Media* m : *mediaList) {
        Inserzione* i = dynamic_cast<Inserzione*>(m);
       
        if (i && i != insPtr) {
            PreviewCard* card = new PreviewCard(i);
            layoutInserzioni->addWidget(card);
            connect(card, &PreviewCard::viewMedia, this, [this, i]() {
                DetailPageVisitor detailVisitor;
                i->accept(&detailVisitor);
                emit requestMediaView(*detailVisitor.getWidget());
            });
        }
    }
    layoutInserzioni->addStretch();
}



void InserzioneView::setMediaList(const QList<Media*>* list) {
    mediaList = list;
    createScrollableSection();
}


void InserzioneView::update(){
    MediaView::update();
    updateMediaDetails();
    updateScrollableSection();
}
