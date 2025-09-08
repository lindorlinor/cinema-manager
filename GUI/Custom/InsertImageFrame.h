#ifndef INSERTIMAGEFRAME_H
#define INSERTIMAGEFRAME_H

#include <QFrame>
#include <QLabel>
#include <QMouseEvent>
#include <QString>
#include <QToolButton>

class InsertImageFrame : public QFrame {
    Q_OBJECT

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
    explicit InsertImageFrame(const QString& testo, const QString& style, QWidget *parent = nullptr);
    void setText(const QString &text);
    void reset();
    void insertImage(const QString &text);

    //nota, mettere chooseImage negli slot?
}; 

#endif // INSERTIMAGEFRAME_H
