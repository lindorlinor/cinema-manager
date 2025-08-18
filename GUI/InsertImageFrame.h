#ifndef INSERTIMAGEFRAME_h
#define INSERTIMAGEFRAME_h
#include <QFrame>
#include <QLabel>
#include <QMouseEvent>
#include <QString>

class InsertImageFrame : public QFrame {
    Q_OBJECT
public:
    explicit InsertImageFrame(QWidget *parent = nullptr);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QString defaultText;    
    QLabel *label;
public:
    void setText(const QString &text);
    void reset();
}; 
#endif//INSERTIMAGEFRAME_h
