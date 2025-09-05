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
    MediaManagerXml* m_xmlManager;
    CinemaRepositoryJson* m_jsonManager;
    SearchPanel * searchPage;
    QStackedWidget *stackedWidget;
    
    bool isFS = true;
public:
    MainWindow(QWidget *parent = nullptr);
public slots:
    void showInsertCinemaPage();
    void showSelectedCinemaPage();
    void showCinemaSelectionPage();
    void deleteCinemaFromList(Cinema* cinema);
};

#endif // MAINWINDOW_H
