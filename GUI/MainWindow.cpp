#include "MainWindow.h" 
#include "CinemaSelectionPage.h" 
#include "InsertCinemaPage.h" 
#include "SearchPanel.h" 
#include <QVBoxLayout>
#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), cinemaPage(new CinemaSelectionPage(w_cinema, this)), insertPage(new InsertCinemaPage(w_cinema, this)), searchPage(new SearchPanel(w_cinema, this))
{
    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | 
               Qt::WindowMinimizeButtonHint | 
               Qt::WindowMaximizeButtonHint | 
               Qt::WindowCloseButtonHint);

    QVBoxLayout* layoutV = new QVBoxLayout;
    QWidget* central = new QWidget(this);
    Menu* menu = new Menu(this);

    stackedWidget = new QStackedWidget(this);
    layoutV->addWidget(menu);
    layoutV->addWidget(stackedWidget);
    central->setLayout(layoutV);

    setCentralWidget(central);
    resize(800, 500);

   
    connect(cinemaPage,&CinemaSelectionPage::insertCinema,this,&MainWindow::showInsertCinemaPage);
    connect(cinemaPage,&CinemaSelectionPage::selectedCinema,this,&MainWindow::showSelectedCinemaPage);
    connect(cinemaPage, &CinemaSelectionPage::selectedCinema, searchPage, &SearchPanel::updateInfoCinema);
    connect(cinemaPage, &CinemaSelectionPage::selectedCinema, this, &MainWindow::showFullScreen);

    connect(insertPage,&InsertCinemaPage::returnCinemaSelectionPage,this,&MainWindow::showCinemaSelectionPage);

    connect(menu, &Menu::setNormalRequest, this, &MainWindow::showNormal);
    connect(menu, &Menu::setMaximizeRequest, this, [this]() {
        if (windowState() & Qt::WindowFullScreen) {
            showMaximized();
        } else {
            showFullScreen();
        }
    });
    connect(menu, &Menu::closeRequested, this, &MainWindow::close);
    connect(menu,&Menu::escSearchPanel,searchPage,&SearchPanel::removeMediaView);
    connect(menu,&Menu::escSearchPanel,this,&MainWindow::showCinemaSelectionPage);
    connect(menu,&Menu::escSearchPanel,searchPage,&SearchPanel::resetSearchPanel);
    connect(menu, &Menu::setFullScreen, this, &MainWindow::showFullScreen);
    connect(menu, &Menu::escFullScreen, this, &MainWindow::showMaximized);

    connect(searchPage,&SearchPanel::escSearchPanel,this,&MainWindow::showCinemaSelectionPage);
    connect(searchPage,&SearchPanel::escSearchPanel,searchPage,&SearchPanel::resetSearchPanel);
  

    stackedWidget->addWidget(cinemaPage);
    stackedWidget->addWidget(insertPage);
    stackedWidget->addWidget(searchPage);
    stackedWidget->setCurrentIndex(0);
    central->show();
     
    QDir dir(QCoreApplication::applicationDirPath());
    dir.cdUp();  // Da /release → [PROJECT_ROOT]

    //style
    menu->setObjectName("menuWidget");
    central->setObjectName("central");
    layoutV->setContentsMargins(0, 0, 0, 0); 
    layoutV->setSpacing(0);

    QFile file(dir.filePath("GUI/style.qss"));
    if (file.open(QFile::ReadOnly))
    {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
        file.close();
        qDebug() << "Style sheet applicato correttamente.";
    }
    else qDebug() << "Impossibile aprire il file style.qss"; 
}


void MainWindow::showInsertCinemaPage(){
    insertPage->reset();   
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::showSelectedCinemaPage(const Cinema* cinema){
    //TO DO
    stackedWidget->setCurrentIndex(2);
    qDebug() << "Selezionato il cinema: " << QString::fromStdString(cinema->getNomeCinema());
}
void MainWindow::showCinemaSelectionPage(){
    if (cinemaPage) {
        cinemaPage->refreshCinemaButtons();
    }
    stackedWidget->setCurrentIndex(0);
}