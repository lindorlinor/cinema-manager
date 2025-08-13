#ifndef CINEMASELECTIONPAGE_H
#define CINEMASELECTIONPAGE_H

#include <QMainWindow>
#include <QVector>
#include "CinemaButton.h"
#include <QHBoxLayout>
class CinemaSelectionPage : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout* layoutPulsanti;
    QVector<CinemaButton*> cinemaButtons;
    void creaBottoneCinema(const QString& nomeC, const QString& imPath, const QString& xmlPath);
public:
    CinemaSelectionPage(QWidget *parent);
    void refresh();
signals:
    void insertCinema();
    void selectedCinema(const QString& xmlPath);

};


#endif // CINEMASELECTIONPAGE_H
