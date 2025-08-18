#ifndef MEDIAFRAME_H
#define MEDIAFRAME_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>

#include "../Media.h"

class MediaFrame: public QFrame{
    Q_OBJECT 
    
    private:
    QLabel* imgLabel;
    QPixmap pix;
    QString titoloMedia;
    QString casaProd;

    public:
    explicit MediaFrame(const QString& titolo, const QString& imagePath, const QString& casaProduzione, QWidget* parent = nullptr);
    QString getTitolo() const;
    QString getCasaProd() const;
    void mousePressEvent(QMouseEvent* event)override;
    void setSelected(bool selected);

    signals:
    void selected(MediaFrame* frame);

};

#endif //MEDIAFRAME_H