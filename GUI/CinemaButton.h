#ifndef CINEMABUTTON_H
#define CINEMABUTTON_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QMouseEvent>

class CinemaButton : public QFrame
{
    Q_OBJECT

public:
    explicit CinemaButton(const QString& cinemaName, const QPixmap& cinemaImage=QPixmap(":/images/image4.png"),QWidget *parent=nullptr);
signals:
    void selected();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QLabel* imageLabel;
    QLabel* nameLabel;
};

#endif // CINEMABUTTON_H
