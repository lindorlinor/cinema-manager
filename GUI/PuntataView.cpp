#include "PuntataView.h"
#include "Podcast.h"
#include <QScrollArea>
#include "ExpandableLabel.h"
#include "DetailsPageButtons.h"
#include "PreviewCard.h"
#include <QAbstractButton>
PuntataView::PuntataView(Puntata* pPtr,QWidget* parent):MediaView(pPtr,parent),puntPtr(pPtr){
    createMediaDetails();
    createScrollableSection();
    createButtons();
    layoutPage->addSpacing(30);
}

void PuntataView::createMediaDetails() {
    createRowDetails();
    leftSide->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leftSide->setContentsMargins(0,0,0,0);
    leftLayout->setSpacing(0);
    leftLayout->setContentsMargins(0,0,0,0);

    createMediaCard();
    copertina->setMaximumSize(390,266); //per evitare che mettendo una copertina più grande di quanto ci si aspetti questa crei problemi con il layout

    QScrollArea* scrollDetails = new QScrollArea(leftSide);
    detailsLayout->setParent(details);
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
    QGridLayout * layoutDettagliProgrammazione = new QGridLayout(dettagliProgrammazione);
    layoutDettagliProgrammazione->setHorizontalSpacing(35);
    layoutDettagliProgrammazione->setAlignment(Qt::AlignLeft);
    dettagliProgrammazione->setContentsMargins(10,10,10,10);

    inizioP = new QLabel(dettagliProgrammazione);
    inizioP->setTextFormat(Qt::RichText);
    endDateLabel = new QLabel(dettagliProgrammazione);
    endDateLabel->setTextFormat(Qt::RichText);
    nPubblicita = new QLabel(dettagliProgrammazione);
    nPubblicita->setTextFormat(Qt::RichText);

    inizioP->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    endDateLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    nPubblicita->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

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

    incasso = new QLabel(dettagliPerformance);
    incasso->setTextFormat(Qt::RichText);
    visualizzazioni = new QLabel(dettagliPerformance);
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

    risoluzione = new QLabel(dettagliTecnici);
    risoluzione->setTextFormat(Qt::RichText);
    formato = new QLabel(dettagliTecnici);
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

    QWidget * dettagliDettagli = new QWidget(sezioneDettagli);
    QVBoxLayout * layoutDettagliDettagli = new QVBoxLayout(dettagliDettagli);
    dettagliDettagli->setContentsMargins(10,10,10,10);

    descrizione = new ExpandableLabel("", dettagliDettagli);
    conduttore = new QLabel(dettagliDettagli);
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

    labelProgrammazione->setObjectName("programmazione");
    labelPerformance->setObjectName("labelPerformance");
    labelTecnica->setObjectName("labelTecnica");
    labelDettagli->setObjectName("labelDettagli");
    scrollDetails->setObjectName("scrollDetails");

    updateMediaDetails();
}

void PuntataView::updateMediaDetails() {
    updateRowDetails();
    inizioP->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Inizio proiezione: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromStdString(dateToString(puntPtr->getDataInizioRilascio())) + "</span>");
    
    endDateLabel->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Fine proiezione: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromStdString(dateToString(puntPtr->getDataFineRilascio())) + "</span>");
    
    nPubblicita->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Numero di pubblicità: </span>"
        "<span style='color: #4e7f8b;'>" + QString::number(puntPtr->getNumeroPubblicita()) + "</span>");
    
    incasso->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Incasso totale: </span>"
        "<span style='color: #4e7f8b;'>" + QString::number(puntPtr->calcolaIncasso()) + " €</span>");
    
    visualizzazioni->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Visualizzazioni: </span>"
        "<span style='color: #4e7f8b;'>" + QString::number(puntPtr->getVisualizzazioni()) + "</span>");
    
    risoluzione->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Risoluzione: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromUtf8(toString(puntPtr->getRisoluzione())) + "</span>");
    
    formato->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Formato: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromUtf8(toString(puntPtr->getFormato())) + "</span>");
    
    descrizione->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Descrizione: </span><br>" 
        + QString::fromStdString(puntPtr->getDescrizione()));
    
    conduttore->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Conduttore: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromStdString((puntPtr->getPodcast())->getConduttore()) + "</span>");
}



void PuntataView::createScrollableSection() {
    rightSide->setFixedHeight(650);
    rightSide->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel* labelPodA = new QLabel("Podcast associato", rightSide);
    labelPodA->setObjectName("labelCorrelati");
    QFont fontPodA = labelPodA->font();
    fontPodA.setPointSize(17);
    fontPodA.setBold(true);
    labelPodA->setFont(fontPodA);

    QWidget* sezionePodA = new QWidget(rightSide);
    layoutPodA = new QVBoxLayout(sezionePodA);
    sezionePodA->setContentsMargins(20, 0, 20, 0);

    QLabel* labelPuntate = new QLabel("Puntate correlate", rightSide);
    labelPuntate->setObjectName("labelCorrelati");
    QFont fontPuntate = labelPuntate->font();
    fontPuntate.setPointSize(17);
    fontPuntate.setBold(true);
    labelPuntate->setFont(fontPuntate);

    QScrollArea* scrollPuntate = new QScrollArea(rightSide);
    QScrollArea* sezionePuntate = new QScrollArea(scrollPuntate);
    layoutPuntate = new QVBoxLayout(sezionePuntate);
    layoutPuntate->setAlignment(Qt::AlignTop);
    layoutPuntate->setSpacing(20);
    sezionePuntate->setContentsMargins(20, 20, 20, 20);

    scrollPuntate->setWidget(sezionePuntate);
    scrollPuntate->setWidgetResizable(true);
    scrollPuntate->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollPuntate->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollPuntate->setMinimumHeight(180);

    rightLayout->addWidget(labelPodA);
    rightLayout->addWidget(sezionePodA, 0, Qt::AlignTop);
    rightLayout->addSpacing(20);
    rightLayout->addWidget(labelPuntate);
    rightLayout->addWidget(scrollPuntate);
    splitterLayout->addWidget(rightSide);

    sezionePodA->setObjectName("sezioneScroll");
    sezionePuntate->setObjectName("sezioneScroll");
    scrollPuntate->setObjectName("scrollDetails");

    updateScrollableSection();
}

void PuntataView::updateScrollableSection() {
    QLayoutItem* item;

    while ((item = layoutPodA->takeAt(0)) != nullptr) {
        if (QWidget* w = item->widget())
            w->deleteLater();
        delete item;
    }

    Podcast* podA = puntPtr->getPodcast();
    PreviewCard* cardPodA = new PreviewCard(podA);
    layoutPodA->addWidget(cardPodA, 0, Qt::AlignCenter);
    connect(cardPodA, &PreviewCard::viewMedia, this, [this, podA]() {
        DetailPageVisitor detailVisitor;
        podA->accept(&detailVisitor);
        emit requestMediaView(*detailVisitor.getWidget());
    });

    while ((item = layoutPuntate->takeAt(0)) != nullptr) {
        if (QWidget* w = item->widget())
            w->deleteLater();
        delete item;
    }

    for (Puntata* p : podA->getElencoPuntate()) {
        if (p != puntPtr) {
            PreviewCard* cardPuntata = new PreviewCard(p);
            layoutPuntate->addWidget(cardPuntata, 0, Qt::AlignCenter);
            connect(cardPuntata, &PreviewCard::viewMedia, this, [this, p]() {
                DetailPageVisitor detailVisitor;
                p->accept(&detailVisitor);
                emit requestMediaView(*detailVisitor.getWidget());
            });
        }
    }

    layoutPuntate->addStretch();
}


void PuntataView::createButtons(){
    buttons = new DetailsPageButtons(puntPtr,leftSide);
    buttons->setDeleteButtonText("Elimina puntata");
    cardLayout->addSpacing(40);
    cardLayout->addWidget(buttons,0,Qt::AlignCenter);

    connect(buttons,&DetailsPageButtons::extendMedia,this,&PuntataView::extendMediaMessage);
    connect(buttons,&DetailsPageButtons::deleteMedia,this,&PuntataView::deleteMediaMessage);

}

void PuntataView::update(){
    MediaView::update();
    updateMediaDetails();
    updateScrollableSection();
    buttons->updateButtons();
}


void PuntataView::extendMediaMessage(){
    CustomMessageBox msgBox(this);
    auto fine = puntPtr->getDataFineRilascio();
    auto nuovaFine = sys_days(fine) + days{1};

    msgBox.setTitleText("Sei sicuro di voler estendere la data fine rilascio del media?");
    msgBox.setMainMessage(QString::fromStdString(
    "La data di fine proiezione cambierà in<br/>" + dateToString(fine) + " → " + dateToString(nuovaFine) + ".") + QString::fromStdString("<br/>Confermando l'estensione potrebbe cambiare la data di fine rilascio del podcast associato."));
    msgBox.setInfoMessage();

    if (msgBox.exec() == QDialog::Accepted){
        puntPtr->estendiDataFineRilascio();
        emit extendMediaClicked();
        endDateLabel->setText("<span style='color: #bdced3; font-weight:bold;'>Fine proiezione: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromStdString(dateToString(puntPtr->getDataFineRilascio())) + "</span>");
    }
}
void PuntataView::deleteMediaMessage(){
    CustomMessageBox msgBox;
    msgBox.setTitleText("<span style='color: #E44043;'>Conferma eliminazione</span>");
    msgBox.setMainMessage("Sei sicuro di voler eliminare la puntata? L'operazione è irreversibile.");
    msgBox.setInfoMessage();

    if(msgBox.exec() == QDialog::Accepted){
        emit deleteMediaClicked(puntPtr);
    }
}

