#ifndef BUTTONCONTAINER_H
#define BUTTONCONTAINER_H

#include <QWidget>
#include <QString>
#include "../Media.h"

class QPushButton;
class QToolButton;
class QVBoxLayout;

class DetailsPageButtons : public QWidget {
    Q_OBJECT
public:
    explicit DetailsPageButtons(Media* mediaPtr, QWidget* parent = nullptr);
    void setDeleteButtonText(const QString&);
    void updateButtons();

private:
    void createButtons(QVBoxLayout* mainLayout);

    Media* mediaPtr;
    QPushButton* extendButton;
    QPushButton* deleteButton;
    QToolButton* extendTool;
    QToolButton* deleteTool;

signals:
    void extendMedia();
    void deleteMedia();
};

#endif // BUTTONCONTAINER_H
