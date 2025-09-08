#ifndef PREVIEWCARD_H
#define PREVIEWCARD_H

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QMouseEvent>
#include <QEvent>
#include <QEnterEvent>
#include "../../Media.h"

// prima o poi diventera un cardMedia idk
class PreviewCard : public QFrame
{
    Q_OBJECT

public:
    explicit PreviewCard(const Media *mPtr, QWidget *parent = nullptr);
    const Media *mediaPtr;
signals:
    void viewMedia();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QLabel *imageLabel;
    QLabel *titleLabel;
    QLabel *statusLabel;
    QLabel *textLabel;
    QVBoxLayout *cardLayout;
};

#endif // PREVIEWCARD_H
