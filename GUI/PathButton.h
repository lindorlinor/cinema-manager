#ifndef PATHBUTTON_H
#define PATHBUTTON_H

#include <QWidget>
#include <QFrame>
#include <QMouseEvent>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStackedLayout>
#include <QFileDialog>

class PathButton : public QFrame{
    Q_OBJECT

    public:
    explicit PathButton(const QPixmap& mediaImage=QPixmap(":/images/image4.png"),QFrame *parent=nullptr);

    private:
    QLabel* imageLabel;
    QString pathImage;
    QWidget* bottoni;
    QStackedLayout* stackPath;

    signals:
    void selected();

    protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

    public:
    QString getPath();
};

#endif //PATHBUTTON_H