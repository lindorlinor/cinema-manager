#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "CinemaSelectionPage.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QStackedWidget *stackedWidget;
    CinemaSelectionPage * cinemaPage;
public:
    MainWindow(QWidget *parent = nullptr);
public slots:
    void showInsertCinemaPage();
    void showSelectedCinemaPage(const QString& xmlPath);
    void showCinemaSelectionPage();
};

#endif // MAINWINDOW_H
