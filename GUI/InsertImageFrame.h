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
    void removeImage();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QString defaultText;    
    QLabel *label;
    QToolButton *closeButton;

public:
    void setText(const QString &text);
    void reset();
    void insertImage(const QString &text);
}; 

#endif // INSERTIMAGEFRAME_H
