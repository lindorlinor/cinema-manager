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
    QVector<CinemaButton*> cinemaButtons;
    void creaBottoneCinema(const QString& nomeC, const QString& imPath, const QString& xmlPath, QHBoxLayout* layout);
    void caricaCinemaDaXML(const QString& path,QHBoxLayout * layout);
public:
    CinemaSelectionPage(QWidget *parent);
signals:
    void insertCinema();
    void selectedCinema(const QString& xmlPath);

};


#endif // CINEMASELECTIONPAGE_H
