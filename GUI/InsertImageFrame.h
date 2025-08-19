#ifndef INSERTIMAGEFRAME_H
#define INSERTIMAGEFRAME_H

#include <QFrame>
#include <QLabel>
#include <QMouseEvent>
#include <QString>
#include <QToolButton>

class InsertImageFrame : public QFrame {
    Q_OBJECT
public:
    explicit InsertImageFrame(QWidget *parent = nullptr);

signals:
    void clicked();
    void removeImage();   // nuovo segnale

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QLabel defaultText;    
    QLabel *label;
    QToolButton *closeButton;   // bottone "x"

public:
    void setText(const QString &text);
    void reset();
    void insertImage(const QString &text);
}; 

#endif // INSERTIMAGEFRAME_H
