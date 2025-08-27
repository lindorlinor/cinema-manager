#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "CinemaSelectionPage.h"
#include "InsertCinemaPage.h"
#include "SearchPanel.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QStackedWidget *stackedWidget;
    CinemaSelectionPage * cinemaPage;
    InsertCinemaPage * insertPage;
    SearchPanel * searchPage;
public:
    MainWindow(QWidget *parent = nullptr);
public slots:
    void showInsertCinemaPage();
    void showSelectedCinemaPage(const CinemaData& cinema);
    void showCinemaSelectionPage();
};

#endif // MAINWINDOW_H
