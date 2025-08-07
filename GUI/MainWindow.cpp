#include "mainwindow.h" 
#include "CinemaSelectionPage.h" 
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);
    CinemaSelectionPage * cinemaPage = new CinemaSelectionPage(this);
    connect(cinemaPage,&CinemaSelectionPage::insertCinema,this,&MainWindow::showInsertCinemaPage);
    connect(cinemaPage,&CinemaSelectionPage::selectedCinema,this,&MainWindow::showSelectedCinemaPage);
    stackedWidget->addWidget(cinemaPage);
    stackedWidget->setCurrentIndex(0);
    stackedWidget->show();
    resize(800, 600); 
}


void MainWindow::showInsertCinemaPage(){
    //TO DO
    qDebug() << "Pagina Inserimento Cinema" ;
}

void MainWindow::showSelectedCinemaPage(const QString& xmlPath){
    //TO DO
    qDebug() << "Cinema al path " << xmlPath ;
}