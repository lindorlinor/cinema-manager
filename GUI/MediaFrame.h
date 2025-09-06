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
    QLabel* titoloLabel;
    QPixmap pix;
    const Media* mf_media;
    void mousePressEvent(QMouseEvent* event)override;

    public:
    explicit MediaFrame(const Media& media, QWidget* parent = nullptr);
    QString getTitolo() const;
    QString getAutore() const;
    void setSelected(bool selected);
    void editImageScale(int w, int h);

    signals:
    void selected(MediaFrame* frame);

};

#endif //MEDIAFRAME_H