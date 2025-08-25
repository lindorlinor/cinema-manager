#include "MainWindow.h" 
#include "CinemaSelectionPage.h" 
#include "InsertCinemaPage.h" 
#include "SearchPanel.h" 
#include <QVBoxLayout>
#include <QDebug>
#include <QFile>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), cinemaPage(new CinemaSelectionPage(this)), insertPage(new InsertCinemaPage(this)), searchPage(new SearchPanel(this))
{
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);
   
    connect(cinemaPage,&CinemaSelectionPage::insertCinema,this,&MainWindow::showInsertCinemaPage);
    connect(cinemaPage,&CinemaSelectionPage::selectedCinema,this,&MainWindow::showSelectedCinemaPage);
    connect(searchPage,&SearchPanel::escSearchPanel,this,&MainWindow::showCinemaSelectionPage);
  
    connect(insertPage,&InsertCinemaPage::returnCinemaSelectionPage,this,&MainWindow::showCinemaSelectionPage);
    connect(cinemaPage, &CinemaSelectionPage::selectedCinema, searchPage, &SearchPanel::updateNomeCinema);
    connect(cinemaPage, &CinemaSelectionPage::selectedCinema, this, &MainWindow::showMaximized);
    connect(searchPage, &SearchPanel::setFullScreen, this, &MainWindow::showFullScreen);
    connect(searchPage, &SearchPanel::escFullScreen, this, &MainWindow::showMaximized);

    stackedWidget->addWidget(cinemaPage);
    stackedWidget->addWidget(insertPage);
    stackedWidget->addWidget(searchPage);
    stackedWidget->setCurrentIndex(0);
    stackedWidget->show();
    resize(800, 500); 
    QDir dir(QCoreApplication::applicationDirPath());
    dir.cdUp();  // Da /release → [PROJECT_ROOT]

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

void MainWindow::showSelectedCinemaPage(const QString& xmlPath){
    //TO DO
    stackedWidget->setCurrentIndex(2);
    qDebug() << "Cinema al path " << xmlPath ;
}
void MainWindow::showCinemaSelectionPage(){
    if (cinemaPage) {
        cinemaPage->refreshCinemaButtons();
    }
    stackedWidget->setCurrentIndex(0);
}