#include "AddPanel.h"

QWidget* addPath(){
    QWidget* widgetPath = new QWidget;
    
}

void AddPanel::addPagina(QVBoxLayout* mainLayout){
    QLabel* titolo = new QLabel("Aggiungi un elemento alla libreria");

}

AddPanel::AddPanel(QWidget *parent): QWidget(parent){
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0); 
    mainLayout->setSpacing(0);

    addPagina(mainLayout);

    setLayout(mainLayout);
}