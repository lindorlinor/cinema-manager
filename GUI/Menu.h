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

    public:
    explicit Menu(QWidget* parent = nullptr);

    signals:
    void escSearchPanel();
    void setFullScreen();
    void escFullScreen();
    void setNormalRequest();
    void setMaximizeRequest();
    void closeRequested();

};

#endif //MENU_H