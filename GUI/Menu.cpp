#include "Menu.h"
#include "MainWindow.h"

Menu::Menu(QWidget* parent):QWidget(parent),menuBar(new QMenuBar(this)),file(new QMenu("File",menuBar)){
    QHBoxLayout* menuH = new QHBoxLayout; 

    QMenu* modifica = new QMenu("Modifica", menuBar);
    QMenu* visualizza = new QMenu("Visualizza", menuBar);
    QMenu* altro = new QMenu("Altro", menuBar);
    
    menuBar->addMenu(file);
    menuBar->addMenu(modifica);
    menuBar->addMenu(visualizza);
    menuBar->addMenu(altro);
    
    //Menu "File"
    file->addAction(new QAction("Aggiungi Media", file));
    file->addAction(new QAction("Importa Media", file));
    file->addAction(new QAction("Esporta Media", file));
    file->addAction(new QAction("Importa Sessione", file));
    file->addAction(new QAction("Esporta Sessione", file));
    file->addAction(new QAction("Torna a seleziona Cinema", file));
    file->addAction(new QAction("Esci", file));
    
    //Menu "Modifica"
    modifica->addAction(new QAction("Modifica Media", modifica));
    modifica->addAction(new QAction("Rimuovi Media", modifica));
    modifica->addAction(new QAction("Modifica Cinema", modifica));
    modifica->addAction(new QAction("Elimina Cinema", modifica));
    //Menu "Visualizza"
    visualizza->addAction(new QAction("Visualizza Film", visualizza));
    visualizza->addAction(new QAction("Visualizza Trailer", visualizza));
    visualizza->addAction(new QAction("Visualizza Inserzioni", visualizza));
    visualizza->addAction(new QAction("Visualizza Podcast", visualizza));
    //Menu "Altro"
    altro->addAction(new QAction("Cambia Vista", altro));
    altro->addAction(new QAction("Full Screen", altro));
    altro->addAction(new QAction("Exit Full Screen", altro));

    //action di File
    connect(file->actions()[1],&QAction::triggered, this, &Menu::importMediaList);
    connect(file->actions()[2],&QAction::triggered, this, &Menu::exportMediaList);
    connect(file->actions()[3],&QAction::triggered, this, &Menu::importSession);
    connect(file->actions()[4],&QAction::triggered, this, &Menu::exportSession);
    connect(file->actions()[5],&QAction::triggered, this, &Menu::backToCinemaSelection);
    connect(file->actions()[6], &QAction::triggered, qApp, &QApplication::quit);
    
    //action di modifica
    connect(modifica->actions()[2], &QAction::triggered, this, &Menu::editCinema);
    connect(modifica->actions()[3], &QAction::triggered, this, &Menu::deleteCinema);

    //action di Altro
    connect(altro->actions()[1], &QAction::triggered, this, &Menu::setFullScreen);
    connect(altro->actions()[2], &QAction::triggered, this, &Menu::escFullScreen);

    // Bottoni personalizzati
    QToolButton* minBtn = new QToolButton(this);
    QToolButton* maxBtn = new QToolButton(this);
    QToolButton* closeBtn = new QToolButton(this);

    minBtn->setIcon(QIcon(":/icons/min.png"));
    maxBtn->setIcon(QIcon(":/icons/max.png"));
    closeBtn->setIcon(QIcon(":/icons/esc.png"));

    minBtn->setIconSize(QSize(20,20));
    maxBtn->setIconSize(QSize(20,20));
    closeBtn->setIconSize(QSize(20,20));

    menuH->addWidget(menuBar);
    menuH->addWidget(minBtn);
    menuH->addWidget(maxBtn);
    menuH->addWidget(closeBtn);
    setLayout(menuH);

    // Azioni
    connect(minBtn, &QToolButton::clicked, this, &Menu::setNormalRequest);
    connect(maxBtn, &QToolButton::clicked, this, &Menu::setMaximizeRequest);
    connect(closeBtn, &QToolButton::clicked, this, &Menu::closeRequested);

    
    //style
    setContentsMargins(0,0,0,0);
    minBtn->setObjectName("minBtn");
    maxBtn->setObjectName("maxBtn");
    closeBtn->setObjectName("closeBtn");
    menuH->setContentsMargins(0,0,0,0);
    menuH->setSpacing(0);
    menuBar->setContentsMargins(0, 0, 0, 0); 
    menuBar->setObjectName("menuBar");
    file->setObjectName("file");
    modifica->setObjectName("modifica");
    visualizza->setObjectName("visualizza");
    altro->setObjectName("altro");
}

void Menu::setFileActionVisibility(int i, bool visible) {
    if(!file) return;
    
    QList<QAction*> actionsList = file->actions();

    if(i<0 || i>=actionsList.size()) 
        return; 

    actionsList[i]->setVisible(visible);
}
