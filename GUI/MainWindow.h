#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QStackedWidget *stackedWidget;
public:
    MainWindow(QWidget *parent = nullptr);
public slots:
    void showInsertCinemaPage();
    void showSelectedCinemaPage(const QString& xmlPath);
};

#endif // MAINWINDOW_H
