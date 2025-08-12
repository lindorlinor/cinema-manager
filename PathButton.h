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

class PathButton : public QFrame{
    Q_OBJECT

    public:
    explicit PathButton(const QPixmap& mediaImage=QPixmap(":/images/image4.png"),QFrame *parent=nullptr);

    private:
    QLabel* imageLabel;
    QWidget* bottoni;
    QStackedLayout* stackPath;

    signals:
    void selected();

    protected:
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
};

#endif //PATHBUTTON_H