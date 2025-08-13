#ifndef MEDIAFRAME_H
#define MEDIAFRAME_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QPixMap>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "../Media.h"

class MediaFrame: public QFrame{
    Q_OBJECT 
    
    private:
    QLabel* imgLabel;
    QPixmap* pix;


    public:
    explicit MediaFrame(const QString& titolo, const QString& imagePath, QWidget* parent = nullptr);

};

#endif //MEDIAFRAME_H