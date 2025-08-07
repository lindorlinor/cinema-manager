#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    SearchPanel *searchPanel = new SearchPanel(this);
    setCentralWidget(searchPanel); 
    resize(800,600);
}

MainWindow::~MainWindow()
{
}
