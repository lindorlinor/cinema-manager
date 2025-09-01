#include "MediaLibraryGenerale.h"

MediaLibraryGenerale::MediaLibraryGenerale(const QString& filtroBottone, QWidget* parent): UpdateMediaLibrary(parent), filtro(filtroBottone){

    titolo = new QLabel(filtroBottone+" in Sala",this);
    QVBoxLayout* mainLayout = new QVBoxLayout;
    container = new QWidget(this);

    layoutContainer = new FlowLayout(this);
    container->setLayout(layoutContainer);

    mainLayout->addWidget(titolo);
    mainLayout->addWidget(container);
    setLayout(mainLayout);
}

void MediaLibraryGenerale::update(int comboAttivita, int comboOrdinamento, const QString& filtro, const QString& ricerca, QList<Media*>& mediaList){
    titolo->setText(filtro+ "in Sala");
    UpdateMediaLibrary::update(comboAttivita, comboOrdinamento,  filtro, ricerca, mediaList);
}