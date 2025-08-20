#ifndef CINEMASELECTIONPAGE_H
#define CINEMASELECTIONPAGE_H

#include <QMainWindow>
#include <QVector>
#include "CinemaButton.h"
#include "../DataFiles/CinemaXmlRepository.h"
#include <QHBoxLayout>

class CinemaSelectionPage : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout* cinemaButtonsLayout;
    QVBoxLayout *frameLayout;
    QList<Cinema> cinemas;
    void createCinemaButton(const QString& nomeC, const QString& imPath, const QString& xmlPath);
    void createHeader();
    void createCinemaScroll();
public:
    CinemaSelectionPage(QWidget *parent);
    void refreshCinemaButtons();
signals:
    void insertCinema();
    void selectedCinema(const QString& xmlPath);

};


#endif // CINEMASELECTIONPAGE_H
