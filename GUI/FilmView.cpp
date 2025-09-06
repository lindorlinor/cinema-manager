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

#include "GUI/PreviewCard.h"
#include "GUI/DetailsPageButtons.h"

#include <QDebug>

FilmView::FilmView(Film* fPtr, QWidget* parent):MediaView(fPtr,parent),filmPtr(fPtr){
    createMediaDetails();
    createScrollableSection();
    createButtons();
    layoutPage->addSpacing(30);
}


void FilmView::createMediaDetails() {
    createRowDetails(); //da MediaView

    leftSide->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    leftSide->setObjectName("leftSide");
    leftSide->setContentsMargins(0,0,0,0);
    leftLayout->setSpacing(0);
    leftLayout->setContentsMargins(0,0,0,0);

    createMediaCard(); //da MediaView

    QScrollArea* scrollDetails = new QScrollArea(leftSide);
    details->setParent(scrollDetails);
    detailsLayout->setContentsMargins(0, 0, 0, 0);
    scrollDetails->setWidget(details);
    scrollDetails->setWidgetResizable(true);
    scrollDetails->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollDetails->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    leftLayout->addWidget(scrollDetails);
    detailsLayout->setSpacing(10);

    // --- Programmazione ---
    QWidget* sezioneProgrammazione = new QWidget(details);
    QVBoxLayout* layoutProgrammazione = new QVBoxLayout(sezioneProgrammazione);
    QLabel* labelProgrammazione = new QLabel("Informazioni di programmazione");
    layoutProgrammazione->addWidget(labelProgrammazione);

    QWidget* dettagliProgrammazione = new QWidget(sezioneProgrammazione);
    QGridLayout* layoutDettagliProgrammazione = new QGridLayout(dettagliProgrammazione);
    layoutDettagliProgrammazione->setContentsMargins(10,10,10,10);
    layoutDettagliProgrammazione->setHorizontalSpacing(35);
    layoutDettagliProgrammazione->setAlignment(Qt::AlignLeft);

    inizioP = new QLabel(dettagliProgrammazione);
    inizioP->setTextFormat(Qt::RichText);
    endDateLabel = new QLabel(dettagliProgrammazione);
    endDateLabel->setTextFormat(Qt::RichText);
    costoBiglietto = new QLabel(dettagliProgrammazione);
    costoBiglietto->setTextFormat(Qt::RichText);

    layoutDettagliProgrammazione->addWidget(inizioP,0,0);
    layoutDettagliProgrammazione->addWidget(endDateLabel,0,1);
    layoutDettagliProgrammazione->addWidget(costoBiglietto,1,0);

    layoutProgrammazione->addWidget(dettagliProgrammazione);

    QWidget* sezionePerformance = new QWidget(details);
    QVBoxLayout* layoutPerformance = new QVBoxLayout(sezionePerformance);
    QLabel* labelPerformance = new QLabel("Performance e statistiche");
    layoutPerformance->addWidget(labelPerformance);

    QWidget* dettagliPerformance = new QWidget(sezionePerformance);
    QVBoxLayout* layoutDettagliPerformance = new QVBoxLayout(dettagliPerformance);
    dettagliPerformance->setContentsMargins(10,10,10,10);

    incasso = new QLabel(dettagliPerformance);
    incasso->setTextFormat(Qt::RichText);
    visualizzazioni = new QLabel(dettagliPerformance);
    visualizzazioni->setTextFormat(Qt::RichText);
    valutazione = new QLabel(dettagliPerformance);
    valutazione->setTextFormat(Qt::RichText);

    layoutDettagliPerformance->addWidget(incasso);
    layoutDettagliPerformance->addWidget(visualizzazioni);
    layoutDettagliPerformance->addWidget(valutazione);
    layoutPerformance->addWidget(dettagliPerformance);

    QWidget* sezioneTecnica = new QWidget(details);
    QVBoxLayout* layoutTecnica = new QVBoxLayout(sezioneTecnica);
    QLabel* labelTecnica = new QLabel("Caratteristiche tecniche");
    layoutTecnica->addWidget(labelTecnica);

    QWidget* dettagliTecnici = new QWidget(sezioneTecnica);
    QVBoxLayout* layoutDettagliTecnici = new QVBoxLayout(dettagliTecnici);
    dettagliTecnici->setContentsMargins(10,10,10,10);

    risoluzione = new QLabel(dettagliTecnici);
    risoluzione->setTextFormat(Qt::RichText);
    formato = new QLabel(dettagliTecnici);
    formato->setTextFormat(Qt::RichText);
    postCredit = new QLabel(dettagliTecnici);
    postCredit->setTextFormat(Qt::RichText);

    layoutDettagliTecnici->addWidget(risoluzione);
    layoutDettagliTecnici->addWidget(formato);
    layoutDettagliTecnici->addWidget(postCredit);
    layoutTecnica->addWidget(dettagliTecnici);

    QWidget* sezioneDettagli = new QWidget(details);
    QVBoxLayout* layoutDettagli = new QVBoxLayout(sezioneDettagli);
    QLabel* labelDettagli = new QLabel("Dettagli sul film");
    layoutDettagli->addWidget(labelDettagli);

    QWidget* dettagliDettagli = new QWidget(sezioneDettagli);
    QVBoxLayout* layoutDettagliDettagli = new QVBoxLayout(dettagliDettagli);
    dettagliDettagli->setContentsMargins(10,10,10,10);

    descrizione = new ExpandableLabel("",dettagliDettagli);
    descrizione->setTextFormat(Qt::RichText);
    attoriLabel = new ExpandableLabel("",dettagliDettagli);
    attoriLabel->setTextFormat(Qt::RichText);
    genere = new QLabel(dettagliDettagli);
    genere->setTextFormat(Qt::RichText);
    classificazione = new QLabel(dettagliDettagli);
    classificazione->setTextFormat(Qt::RichText);
    casaProduzione = new QLabel(dettagliDettagli);

    layoutDettagliDettagli->addWidget(descrizione);
    layoutDettagliDettagli->addWidget(attoriLabel);
    layoutDettagliDettagli->addWidget(genere);
    layoutDettagliDettagli->addWidget(classificazione);
    layoutDettagliDettagli->addWidget(casaProduzione);

    layoutDettagli->addWidget(dettagliDettagli);

    detailsLayout->addWidget(sezioneProgrammazione);
    detailsLayout->addWidget(sezionePerformance);
    detailsLayout->addWidget(sezioneTecnica);
    detailsLayout->addWidget(sezioneDettagli);
    detailsLayout->addStretch();

    splitterLayout->addWidget(leftSide);

    // style
    labelProgrammazione->setObjectName("programmazione");
    labelPerformance->setObjectName("labelPerformance");
    labelTecnica->setObjectName("labelTecnica");
    labelDettagli->setObjectName("labelDettagli");
    scrollDetails->setObjectName("scrollDetails");

    setStyleSheet("border: none;");

    updateMediaDetails();
}
void FilmView::updateMediaDetails() {
    if (!filmPtr) return;

    inizioP->setText("<span style='color: #bdced3; font-weight:bold;'>Inizio proiezione: </span>"
                     "<span style='color: #4e7f8b;'>" + QString::fromStdString(dateToString(filmPtr->getDataInizioRilascio())) + "</span>");
    endDateLabel->setText("<span style='color: #bdced3; font-weight:bold;'>Fine proiezione: </span>"
                          "<span style='color: #4e7f8b;'>" + QString::fromStdString(dateToString(filmPtr->getDataFineRilascio())) + "</span>");
    costoBiglietto->setText("<span style='color: #bdced3; font-weight:bold;'>Costo biglietto: </span>"
                            "<span style='color: #4e7f8b;'>" + QString::number(filmPtr->getCostoBiglietto()) + " €</span>");

    incasso->setText("<span style='color: #bdced3; font-weight:bold;'>Incasso totale: </span>"
                     "<span style='color: #4e7f8b;'>" + QString::number(filmPtr->calcolaIncasso()) + " €</span>");
    visualizzazioni->setText("<span style='color: #bdced3; font-weight:bold;'>Visualizzazioni: </span>"
                             "<span style='color: #4e7f8b;'>" + QString::number(filmPtr->getVisualizzazioni()) + "</span>");
    valutazione->setText("<span style='color: #bdced3; font-weight:bold;'>Valutazione: </span>"
                         "<span style='color: #4e7f8b;'>" + QString::number(filmPtr->getValutazione()) + "/5</span>");

    risoluzione->setText("<span style='color: #bdced3; font-weight:bold;'>Risoluzione: </span>"
                         "<span style='color: #4e7f8b;'>" + QString::fromStdString(toString(filmPtr->getRisoluzione())) + "</span>");
    formato->setText("<span style='color: #bdced3; font-weight:bold;'>Formato: </span>"
                     "<span style='color: #4e7f8b;'>" + QString::fromStdString(toString(filmPtr->getFormato())) + "</span>");
    postCredit->setText("<span style='color: #bdced3; font-weight:bold;'>Post credit: </span>"
                        "<span style='color: #4e7f8b;'>" + QString::number(filmPtr->getNPostCredit()) + "</span>");

    descrizione->setText("<span style='color: #bdced3; font-weight:bold;'>Descrizione: </span><br>"
                         + QString::fromStdString(filmPtr->getDescrizione()));


    QString attoriText;
    for (const auto& attore : filmPtr->getAttoriPrincipali()) {
        attoriText += QString::fromStdString(attore) + ", ";
    }
    if (!attoriText.isEmpty()) attoriText.chop(2); //rimuove gli ultimi due caratteri (ossia , )
    attoriLabel->setText("<span style='color: #bdced3; font-weight:bold;'>Attori principali: </span>" + attoriText);

    QString generiText;
    for (const auto& g : filmPtr->getGeneri()) {
        generiText += QString::fromUtf8(toString(g)) + ", "; 
    }
    if (!generiText.isEmpty()) generiText.chop(2); //rimuove gli ultimi due caratteri (ossia , )

    genere->setText("<span style='color: #bdced3; font-weight:bold;'>Genere: </span><span style='color: #4e7f8b;'>" + generiText + "</span>");

    classificazione->setText("<span style='color: #bdced3; font-weight:bold;'>Classificazione: </span>"
                             "<span style='color: #4e7f8b;'>" + QString::fromUtf8(toString(filmPtr->getTarget())) + "</span>");
    casaProduzione->setText("<span style='color: #bdced3; font-weight:bold;'>Casa di produzione: </span>"
                             "<span style='color: #4e7f8b;'>" + QString::fromStdString(filmPtr->getCasaDiProduzione()) + "</span>");
}

void FilmView::createScrollableSection(){
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
    layoutTrailer->setAlignment(Qt::AlignTop);
    for (Trailer* t : filmPtr->getTrailers()) {
        PreviewCard* card = new PreviewCard(t);
        layoutTrailer->addWidget(card);
        connect(card, &PreviewCard::viewMedia, this, [this,t](){
            DetailPageVisitor detailVisitor;
            t->accept(&detailVisitor);
            emit requestMediaView(*detailVisitor.getWidget());
        });
    }
    layoutTrailer->setSpacing(20);  
    sezioneTrailer->setContentsMargins(20,20,20,33);

    scrollTrailer->setWidget(sezioneTrailer);
    scrollTrailer->setWidgetResizable(true);
    scrollTrailer->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollTrailer->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollTrailer->setMinimumHeight(500);
    rightLayout->addWidget(scrollTrailer,0,Qt::AlignTop);

    splitterLayout->addWidget(rightSide);
    
    labelTrailer->setObjectName("labelTrailer");
    sezioneTrailer->setObjectName("sezioneScroll");
    scrollTrailer->setObjectName("scrollDetails");
}
void FilmView::createButtons(){
    DetailsPageButtons * buttons = new DetailsPageButtons(filmPtr,rightSide);
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
                filmPtr->estendiDataFineRilascio();
                emit extendMediaClicked();
                endDateLabel->setText("<span style='color: #bdced3; font-weight:bold;'>Fine proiezione: </span>"
                "<span style='color: #4e7f8b;'>" + QString::fromStdString(dateToString(filmPtr->getDataFineRilascio())) + "</span>");
            }
        });
    
        connect(buttons, &DetailsPageButtons::deleteMedia, this, [this](){
            QMessageBox msgBox;
            msgBox.setWindowTitle("Conferma eliminazione");
            msgBox.setText("Sei sicuro di voler eliminare il film? "
                        "Avrà l'effetto di eliminare tutti i trailer ad esso associati");

            QPushButton* annullaBtn = msgBox.addButton("Annulla", QMessageBox::RejectRole);
            QPushButton* confermaBtn = msgBox.addButton("Conferma", QMessageBox::AcceptRole);

            msgBox.exec();

            if (msgBox.clickedButton() == confermaBtn) {
                emit deleteMediaClicked(filmPtr);
            }
            else if(msgBox.clickedButton() == annullaBtn){
                qDebug()<<"Eliminazione del media annullata";
            }
        });

    rightLayout->addSpacing(60);
    rightLayout->addWidget(buttons);
    rightLayout->addSpacing(60);
}


void FilmView::update(){
    MediaView::update();
    updateMediaDetails();
}

