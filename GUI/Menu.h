#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QToolButton>
#include <QMenu>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QApplication>
#include <QIcon>

class Menu: public QWidget{
    Q_OBJECT 
    
    private:
    QMenuBar* menuBar;
    QMenu* file;
    public:
    explicit Menu(QWidget* parent = nullptr);
    void setFileActionVisibility(int i, bool visible);
    signals:
    void backToCinemaSelection();
    void importMediaList();
    void importSession();
    void exportSession();
    void exportMediaList();
    void setFullScreen();
    void escFullScreen();
    void setNormalRequest();
    void setMaximizeRequest();
    void closeRequested();
    void editCinema();
    void deleteCinema();

};

#endif //MENU_H