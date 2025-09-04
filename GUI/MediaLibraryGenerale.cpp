#include "MediaLibraryGenerale.h"

MediaLibraryGenerale::MediaLibraryGenerale(const QString& filtroBottone, QWidget* parent): UpdateMediaLibrary(parent), filtro(filtroBottone){
    

    titolo = new QLabel(filtroBottone+" in Sala",this);
    titolo->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    QVBoxLayout* mainLayout = new QVBoxLayout;
    container = new QWidget(this);
    FlowLayoutContainer = new FlowLayout(this);
    container->setLayout(FlowLayoutContainer);
    
    setPreferredLayout(FlowLayoutContainer);

    mainLayout->addWidget(titolo);
    mainLayout->addWidget(container);
    setLayout(mainLayout);

    //style
    FlowLayoutContainer->setAlignment(Qt::AlignTop);
    titolo->setStyleSheet("color: #fed36a; font-size: 18pt; font-weight: bold;");
}

void MediaLibraryGenerale::update(int comboAttivita, int comboOrdinamento, const QString& filtro, const QString& ricerca, QList<Media*>& mediaList){
    QString prefisso;
    for (const auto &f : allFiltri) { //recupero del prefisso a seconda del filtro ("Film","Inserzioni" etc)
        if (f.first == filtro) {
            prefisso = f.second;
            break;
        }
    }

    if(comboAttivita==0)
        titolo->setText(filtro + " in Sala");
    else if(comboAttivita==1)
        titolo->setText(filtro + " fuori produzione");
    else
        titolo->setText(prefisso + filtro);
    
    UpdateMediaLibrary::update(comboAttivita, comboOrdinamento,  filtro, ricerca, mediaList);
}