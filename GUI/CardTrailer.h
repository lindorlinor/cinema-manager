#ifndef CARDTRAILER_H
#define CARDTRAILER_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>

#include "Trailer.h"  // assumo che esista la classe Trailer con i metodi richiesti

class CardTrailer : public QFrame {
    Q_OBJECT

public:
    explicit CardTrailer(const Trailer* trailer, QWidget* parent = nullptr);

private:
    QLabel* imageLabel;
    QLabel* titleLabel;
    QLabel* statusLabel;
    QVBoxLayout* cardLayout;
};

#endif // CARDTRAILER_H
