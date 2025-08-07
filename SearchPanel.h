#ifndef SEARCHPANEL_H
#define SEARCHPANEL_H

#include <QWidget>
#include <QMenu>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QApplication>
#include <QFile>

class SearchPanel:public QWidget{
    Q_OBJECT
    private:
    //menu
    void addMenus(QVBoxLayout* mainLayout);

    //selezione media
    QPushButton* tutto;
    QPushButton* film;
    QPushButton* trailer;
    QPushButton* inserzione;
    QPushButton* podcast;

    //ricerca
    QLineEdit* cerca;

    void updateCerca(const QString& filtro);
    void addRicerca(QVBoxLayout* mainLayout);
    void addLatoSinistra(QWidget* widgetSinistra);
    void addLatoDestra(QWidget* widgetDestra);

    //cambio pagina
    QStackedWidget* stack;

    public:
	explicit SearchPanel(QWidget *parent);
};

#endif //SEARCHPANEL_H