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

void PodcastView::createMediaDetails() {
    createRowDetails();
    leftSide->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leftSide->setContentsMargins(0, 0, 0, 0);
    leftLayout->setSpacing(0);
    leftLayout->setContentsMargins(0, 0, 0, 0);

    createMediaCard();
    copertina->setMaximumSize(390,266); //per evitare che mettendo una copertina più grande di quanto ci si aspetti questa crei problemi con il layout

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


    QWidget* sezioneProgrammazione = new QWidget(details);
    sezioneProgrammazione->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    QVBoxLayout* layoutProgrammazione = new QVBoxLayout(sezioneProgrammazione);

    QLabel* labelProgrammazione = new QLabel("Informazioni di distribuzione");
    layoutProgrammazione->addWidget(labelProgrammazione);

    QWidget* dettagliProgrammazione = new QWidget(sezioneProgrammazione);
    QHBoxLayout* layoutDettagliProgrammazione = new QHBoxLayout(dettagliProgrammazione);
    layoutDettagliProgrammazione->setSpacing(35);
    layoutDettagliProgrammazione->setAlignment(Qt::AlignLeft);
    dettagliProgrammazione->setContentsMargins(10, 10, 10, 10);

    inizioP = new QLabel(dettagliProgrammazione);
    inizioP->setTextFormat(Qt::RichText);
    inizioP->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    endDateLabel = new QLabel(dettagliProgrammazione);
    endDateLabel->setTextFormat(Qt::RichText);
    endDateLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    layoutDettagliProgrammazione->addWidget(inizioP);
    layoutDettagliProgrammazione->addWidget(endDateLabel);
    layoutProgrammazione->addWidget(dettagliProgrammazione);

    QWidget* sezionePerformance = new QWidget(details);
    QVBoxLayout* layoutPerformance = new QVBoxLayout(sezionePerformance);

    QLabel* labelPerformance = new QLabel("Performance e statistiche");
    layoutPerformance->addWidget(labelPerformance);

    QWidget* dettagliPerformance = new QWidget(sezionePerformance);
    QVBoxLayout* layoutDettagliPerformance = new QVBoxLayout(dettagliPerformance);
    dettagliPerformance->setContentsMargins(10, 10, 10, 10);
    sezionePerformance->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    incasso = new QLabel(dettagliPerformance);
    incasso->setTextFormat(Qt::RichText);

    visualizzazioni = new QLabel(dettagliPerformance);
    visualizzazioni->setTextFormat(Qt::RichText);

    layoutDettagliPerformance->addWidget(incasso);
    layoutDettagliPerformance->addWidget(visualizzazioni);
    layoutPerformance->addWidget(dettagliPerformance);

    QWidget* sezioneTecnica = new QWidget(details);
    QVBoxLayout* layoutTecnica = new QVBoxLayout(sezioneTecnica);
    sezioneTecnica->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    QLabel* labelTecnica = new QLabel("Caratteristiche tecniche");
    layoutTecnica->addWidget(labelTecnica);

    QWidget* dettagliTecnici = new QWidget(sezioneTecnica);
    QVBoxLayout* layoutDettagliTecnici = new QVBoxLayout(dettagliTecnici);
    dettagliTecnici->setContentsMargins(10, 10, 10, 10);

    risoluzione = new QLabel(dettagliTecnici);
    risoluzione->setTextFormat(Qt::RichText);

    formato = new QLabel(dettagliTecnici);
    formato->setTextFormat(Qt::RichText);

    layoutDettagliTecnici->addWidget(risoluzione);
    layoutDettagliTecnici->addWidget(formato);
    layoutTecnica->addWidget(dettagliTecnici);

    QWidget* sezioneDettagli = new QWidget(details);
    sezioneDettagli->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QVBoxLayout* layoutDettagli = new QVBoxLayout(sezioneDettagli);

    QLabel* labelDettagli = new QLabel("Dettagli sul film");
    layoutDettagli->addWidget(labelDettagli);
    labelDettagli->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QWidget* dettagliDettagli = new QWidget(sezioneDettagli);
    QVBoxLayout* layoutDettagliDettagli = new QVBoxLayout(dettagliDettagli);
    dettagliDettagli->setContentsMargins(10, 10, 10, 10);

    descrizione = new ExpandableLabel("", dettagliDettagli);
    conduttore = new QLabel(dettagliDettagli);
    conduttore->setTextFormat(Qt::RichText);
    conduttore->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    puntate = new QLabel(dettagliDettagli);
    puntate->setTextFormat(Qt::RichText);
    puntate->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    layoutDettagliDettagli->addWidget(descrizione);
    layoutDettagliDettagli->addWidget(conduttore);
    layoutDettagliDettagli->addWidget(puntate);
    layoutDettagli->addWidget(dettagliDettagli);

    detailsLayout->addWidget(sezioneProgrammazione);
    detailsLayout->addWidget(sezionePerformance);
    detailsLayout->addWidget(sezioneTecnica);
    detailsLayout->addWidget(sezioneDettagli);
    detailsLayout->addStretch();

    leftSide->setFixedHeight(700);
    splitterLayout->addWidget(leftSide);

    // stile
    labelProgrammazione->setObjectName("programmazione");
    labelPerformance->setObjectName("labelPerformance");
    labelTecnica->setObjectName("labelTecnica");
    labelDettagli->setObjectName("labelDettagli");
    scrollDetails->setObjectName("scrollDetails");

    updateMediaDetails();
}

void PodcastView::updateMediaDetails() {
    updateRowDetails(); // da MediaView, aggiorna la scritta "Fuori produzione" o "Attualmente in distribuzione"
    inizioP->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Inizio proiezione: </span>"
        "<span style='color: #4e7f8b;'>" +
        QString::fromStdString(dateToString(podPtr->getDataInizioRilascio())) + "</span>");

    endDateLabel->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Fine proiezione: </span>"
        "<span style='color: #4e7f8b;'>" +
        QString::fromStdString(dateToString(podPtr->getDataFineRilascio())) + "</span>");

    incasso->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Incasso totale: </span>"
        "<span style='color: #4e7f8b;'>" +
        QString::number(podPtr->calcolaIncasso()) + " €</span>");

    visualizzazioni->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Visualizzazioni: </span>"
        "<span style='color: #4e7f8b;'>" +
        QString::number(podPtr->getVisualizzazioni()) + "</span>");

    risoluzione->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Risoluzione: </span>"
        "<span style='color: #4e7f8b;'>" +
        QString::fromUtf8(toString(podPtr->getRisoluzione())) + "</span>");

    formato->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Formato: </span>"
        "<span style='color: #4e7f8b;'>" +
        QString::fromUtf8(toString(podPtr->getFormato())) + "</span>");

    descrizione->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Descrizione: </span><br>" +
        QString::fromStdString(podPtr->getDescrizione()));

    conduttore->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Conduttore: </span>"
        "<span style='color: #4e7f8b;'>" +
        QString::fromStdString(podPtr->getConduttore()) + "</span>");

    puntate->setText(
        "<span style='color: #bdced3; font-weight:bold;'>Numero di puntate: </span>"
        "<span style='color: #4e7f8b;'>" +
        QString::number(podPtr->getElencoPuntate().size()) + "</span>");
}

void PodcastView::createScrollableSection() {
    rightSide->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QLabel* labelPuntate = new QLabel("Puntate", rightSide);
    labelPuntate->setObjectName("labelCorrelati");
    QFont fontPuntate = labelPuntate->font();
    fontPuntate.setPointSize(17);
    fontPuntate.setBold(true);
    labelPuntate->setFont(fontPuntate);
    rightLayout->addWidget(labelPuntate);

    QScrollArea* scrollPuntate = new QScrollArea(rightSide);
    scrollPuntate->setObjectName("scrollDetails");

    QWidget* sezionePuntate = new QWidget(scrollPuntate);
    sezionePuntate->setObjectName("sezioneScroll");

    layoutPuntate = new QVBoxLayout(sezionePuntate);
    layoutPuntate->setAlignment(Qt::AlignTop);
    layoutPuntate->setSpacing(20);
    sezionePuntate->setContentsMargins(20, 20, 20, 33);

    scrollPuntate->setWidget(sezionePuntate);
    scrollPuntate->setWidgetResizable(true);
    scrollPuntate->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollPuntate->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollPuntate->setMinimumHeight(600);
    rightLayout->addWidget(scrollPuntate, 0, Qt::AlignTop);
    splitterLayout->addWidget(rightSide);

    updateScrollableSection();
}

void PodcastView::updateScrollableSection() {
    QLayoutItem* item;
    while ((item = layoutPuntate->takeAt(0)) != nullptr) {
        if (QWidget* w = item->widget())
            w->deleteLater();
        delete item;
    }

    for (Puntata* p : podPtr->getElencoPuntate()) {
        PreviewCard* card = new PreviewCard(p);
        layoutPuntate->addWidget(card);
        connect(card, &PreviewCard::viewMedia, this, [this, p]() {
            DetailPageVisitor detailVisitor;
            p->accept(&detailVisitor);
            emit requestMediaView(*detailVisitor.getWidget());
        });
    }

    layoutPuntate->addStretch();
}

void PodcastView::createButtons(){
    buttons = new DetailsPageButtons(podPtr,leftSide);
    buttons->setDeleteButtonText("Elimina podcast");
    cardLayout->addSpacing(40);
    cardLayout->addWidget(buttons,0,Qt::AlignCenter);
    connect(buttons,&DetailsPageButtons::extendMedia,this,&PodcastView::extendMediaMessage);
    connect(buttons,&DetailsPageButtons::deleteMedia,this,&PodcastView::deleteMediaMessage);
}

void PodcastView::update(){
    MediaView::update();
    updateMediaDetails();
    updateScrollableSection();
    buttons->update();
}


void PodcastView::extendMediaMessage(){
    CustomMessageBox msgBox(this);
    auto fine = podPtr->getDataFineRilascio();
    auto nuovaFine = sys_days(fine) + days{1};

    msgBox.setTitleText("Sei sicuro di voler estendere la data fine rilascio del media?");
    msgBox.setMainMessage(QString::fromStdString(
    "La data di fine proiezione cambierà in<br/>" + dateToString(fine) + " → " + dateToString(nuovaFine) + ".") +
    QString::fromStdString("<br/>La data di fine rilascio delle sue puntate attualmente in distribuzione verrà posticipata di un giorno ciascuna."));
    msgBox.setInfoMessage();

    if (msgBox.exec() == QDialog::Accepted){
        podPtr->estendiDataFineRilascio();
        emit extendMediaClicked();
        endDateLabel->setText("<span style='color: #bdced3; font-weight:bold;'>Fine proiezione: </span>"
        "<span style='color: #4e7f8b;'>" + QString::fromStdString(dateToString(podPtr->getDataFineRilascio())) + "</span>");
    }

}
void PodcastView::deleteMediaMessage(){
    CustomMessageBox msgBox;
    msgBox.setTitleText("<span style='color: #E44043;'>Conferma eliminazione</span>");
    msgBox.setMainMessage("Sei sicuro di voler eliminare il podcast? Avrà l'effetto di eliminare tutti le puntate ad essa associate. <br/> L'operazione è irreversibile.");
    msgBox.setInfoMessage();

    if(msgBox.exec() == QDialog::Accepted){
        emit deleteMediaClicked(podPtr);
    }
}