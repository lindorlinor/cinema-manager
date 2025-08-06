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
    QMenu* file;
    QMenu* modifica;
    QMenu* visualizza;
    QMenu* altro;
    void addMenus(QVBoxLayout* mainLayout);

    //selezione cinema
    QComboBox* cinema;
    QPushButton* addCinema;

    //selezione media
    QPushButton* addMedia;
    QPushButton* tutto;
    QPushButton* film;
    QPushButton* trailer;
    QPushButton* inserzione;
    QPushButton* podcast;

    //ricerca
    QLineEdit* cerca;
    QPushButton* invioCerca;

    QComboBox* attivita;
    QComboBox* popolarita;
    QComboBox* recenti;

    QPushButton* filtri;
    QPushButton* vista;
    void updateCerca(const QString& filtro);
    void addRicerca(QVBoxLayout* mainLayout);
    void addLatoSinistra(QHBoxLayout* ricerca);
    void addLatoDestra(QHBoxLayout* ricerca);

    //cambio pagina
    QStackedWidget* stack;

    public:
	explicit SearchPanel(QWidget *parent);
};

#endif //SEARCHPANEL_H