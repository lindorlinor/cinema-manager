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
    QMenu* modifica;
    QMenu* visualizza;
    QMenu* altro;
    public:
    explicit Menu(QWidget* parent = nullptr);
    void setFileActionEnabled(int i, bool visible);
    void setModifierActionEnabled(int i, bool visible);
    void setViewActionEnabled(int i, bool visible);
    void setOtherActionEnabled(int i, bool visible);

    signals:
    void changeView();
    void addMedia();
    void viewFilm();
    void viewTrailer();
    void viewInserzioni();
    void viewPodcast();
    void viewPuntate();
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