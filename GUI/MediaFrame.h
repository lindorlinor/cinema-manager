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
    QString titoloMedia;
    QString autoreMedia;
    QLabel* imgLabel;
    QPixmap pix;

    public:
    explicit MediaFrame(const QString& titolo, const QString& imagePath, const QString& autore, QWidget* parent = nullptr);
    QString getTitolo() const;
    QString getAutore() const;
    void mousePressEvent(QMouseEvent* event)override;
    void setSelected(bool selected);

    signals:
    void selected(MediaFrame* frame);

};

#endif //MEDIAFRAME_H