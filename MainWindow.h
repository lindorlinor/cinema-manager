#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

class SearchPanel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QStackedWidget* stack;
    SearchPanel* searchPage;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H
