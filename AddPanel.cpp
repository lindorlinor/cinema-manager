#include "AddPanel.h"

void AddPanel::addPagina(QVBoxLayout* mainLayout){
    QLabel* titolo = new QLabel("Aggiungi un elemento alla libreria");
    widgetPath = new PathButton;

    mainLayout->addWidget(titolo);
    mainLayout->addWidget(widgetPath);
}

AddPanel::AddPanel(QWidget *parent): QWidget(parent){
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0); 
    mainLayout->setSpacing(0);

    addPagina(mainLayout);

    setLayout(mainLayout);
}