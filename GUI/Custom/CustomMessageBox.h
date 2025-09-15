#ifndef CUSTOMMESSAGEBOX_H
#define CUSTOMMESSAGEBOX_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class CustomMessageBox : public QDialog
{
    Q_OBJECT

public:
    explicit CustomMessageBox(QWidget *parent= nullptr);

    void setTitleText(const QString &text);
    void setMainMessage(const QString &text);
    void setInfoMessage(const QString &text="Premi conferma per continuare, annulla per non modificare.");
    void hideCancelButton();

private:
    QLabel *titleLabel;
    QLabel *mainMessageLabel;
    QLabel *infoMessageLabel;
    QPushButton *cancelButton;
    QPushButton *confirmButton;

    QPoint m_dragPosition; //per spostare la finestra
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};
#endif //COSTOMMESSAGEBOX_H
