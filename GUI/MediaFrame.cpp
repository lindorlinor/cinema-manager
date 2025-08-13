#include "MediaFrame.h"

MediaFrame::MediaFrame(const QString& titolo, const QString& imagePath, QWidget* parent):QFrame(parent) {
    imgLabel = new QLabel;
    pix->load(imagePath);
    imgLabel->setPixmap(pix->scaled(100, 150));

    QLabel* titoloLabel = new QLabel(titolo);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(imgLabel);
    layout->addWidget(titoloLabel);

    setLayout(layout);
}