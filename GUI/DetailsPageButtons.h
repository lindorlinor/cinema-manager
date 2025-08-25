#ifndef BUTTONCONTAINER_H
#define BUTTONCONTAINER_H

#include <QWidget>
#include <QString>

class QPushButton;
class QToolButton;

class DetailsPageButtons : public QWidget {
    Q_OBJECT
public:
    explicit DetailsPageButtons(QWidget* parent = nullptr);
    void setDeleteButtonText(const QString&);
private:
    QPushButton* extendButton;
    QPushButton* deleteButton;
    QToolButton* extendTool;
    QToolButton* deleteTool;
signals:
    void extendMedia();
    void deleteMedia();
};

#endif // BUTTONCONTAINER_H
