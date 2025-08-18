#include "InsertImageFrame.h"
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>

InsertImageFrame::InsertImageFrame(QWidget *parent)
    //TO DO aggiungere il drag and drop
    : QFrame(parent), defaultText("Clicca per inserire un'immagine"), label(new QLabel(defaultText, this))
{
    setFrameStyle(QFrame::Box | QFrame::Plain);
    setLineWidth(2);
    setStyleSheet("QFrame { border: 2px dashed gray; } QLabel { qproperty-alignment: AlignCenter; }");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
}

void InsertImageFrame::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit clicked();
    }
    QFrame::mousePressEvent(event);
}

void InsertImageFrame::setText(const QString &text) {
    label->setText(text);
}
void InsertImageFrame::reset() {
    label->setText(defaultText);
}