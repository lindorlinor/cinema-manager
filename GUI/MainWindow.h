#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "CinemaSelectionPage.h"
#include "InsertCinemaPage.h"
#include "SearchPanel.h"
#include "../Cinema.h"
#include "Menu.h"
#include "DataFiles/MediaManagerXml.h" 
#include "DataFiles/CinemaRepositoryJson.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QList<Cinema*> w_cinema;
    CinemaSelectionPage * cinemaPage;
    InsertCinemaPage * insertPage;
    CinemaRepositoryJson* m_jsonManager;
    MediaManagerXml* m_xmlManager;
    SearchPanel * searchPage;
    QStackedWidget *stackedWidget;
    
    bool isFS = true;
public:
    MainWindow(QWidget *parent = nullptr);
public slots:
    void showInsertCinemaPage();
    void showSelectedCinemaPage(const Cinema* cinema);
    void showCinemaSelectionPage();
};

#endif // MAINWINDOW_H
