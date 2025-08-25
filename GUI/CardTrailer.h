#ifndef CARDTRAILER_H
#define CARDTRAILER_H

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QMouseEvent>
#include <QEvent>
#include <QEnterEvent>
#include "Trailer.h"

class CardTrailer : public QFrame {
    Q_OBJECT

public:
    explicit CardTrailer(const Trailer* trailer, QWidget* parent = nullptr);
    const Trailer* trailerPtr; 
signals:
    void viewTrailer(const Trailer* trailer);


protected:
    void mousePressEvent(QMouseEvent* event) override;
private:
    QLabel* imageLabel;
    QLabel* titleLabel;
    QLabel* statusLabel;
    QVBoxLayout* cardLayout;
};

#endif // CARDTRAILER_H
