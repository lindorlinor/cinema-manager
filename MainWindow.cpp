#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    SearchPanel *searchPanel = new SearchPanel(this);
    setCentralWidget(searchPanel); 
}

MainWindow::~MainWindow()
{
}
