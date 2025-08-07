#include "AddPanel.h"


AddPanel::AddPanel(QWidget *parent): QWidget(parent){
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0); 
    mainLayout->setSpacing(0);

    addPagina(mainLayout);

    setLayout(mainLayout);
}