#ifndef HORIZONTAL_CARD
#define HORIZONTAL_CARD
#include <QWidget>
#include <QFrame>
#include <QPixmap>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../Media.h"

class HorizontalCard: public QFrame{
    Q_OBJECT

    private:
    void mousePressEvent(QMouseEvent* event)override;
    
    public:
    explicit HorizontalCard(const Media& media, QWidget * parent= nullptr);

    signals:
    void selected();
};

#endif //HORIZONTAL_CARD