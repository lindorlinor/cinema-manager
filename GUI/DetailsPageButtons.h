#ifndef BUTTONCONTAINER_H
#define BUTTONCONTAINER_H

#include <QWidget>

class QPushButton;
class QToolButton;

class DetailsPageButtons : public QWidget {
    Q_OBJECT
public:
    explicit DetailsPageButtons(QWidget* parent = nullptr);

private:
    QPushButton* btnEstendi;
    QPushButton* btnElimina;
    QToolButton* toolEstendi;
    QToolButton* toolElimina;
};

#endif // BUTTONCONTAINER_H
