#include "MainWindow.h"
#include "SearchPanel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    stack = new QStackedWidget(this);
    searchPage = new SearchPanel(this);
    searchPage->setObjectName("SearchPanel");

    stack->addWidget(searchPage);

    setCentralWidget(stack); 
    stack->setCurrentIndex(0);
    resize(800,600);

    // QFile file("style.qss");
    // if (file.open(QFile::ReadOnly))
    // {
    //     QString styleSheet = QLatin1String(file.readAll());
    //     qApp->setStyleSheet(styleSheet);
    //     file.close();
    //     qDebug() << "Style sheet applicato correttamente.";
    // }
    // else qDebug() << "Impossibile aprire il file style.qss";
}

MainWindow::~MainWindow()
{
}
