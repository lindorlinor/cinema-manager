#include "SelectMediaReference.h"
#include "MediaFrame.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

SelectMediaReference::SelectMediaReference(const QString& tipo, QWidget *parent)
    : QWidget(parent), tipo(tipo), currentSelected(nullptr)
{
    // Container interno per gli item
    container = new QWidget;
    layoutContainer = new QVBoxLayout(container);
    layoutContainer->addSpacerItem(new QSpacerItem(20, 400, QSizePolicy::Minimum, QSizePolicy::Expanding));
    container->setLayout(layoutContainer);

    // Scroll area
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    scrollArea->setMinimumSize(300, 400);
    scrollArea->setWidget(container);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);

    // Carica inizialmente i media
    reloadMedia();
}

void SelectMediaReference::reloadMedia() {
    // Pulisce i widget esistenti
    QLayoutItem* child;
    while ((child = layoutContainer->takeAt(0)) != nullptr) {
        if (child->widget()) child->widget()->deleteLater();
        delete child;
    }

    QFile file(QDir(QCoreApplication::applicationDirPath()).filePath("../media.json"));
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "File JSON non trovato:" << file.fileName();
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    if (!doc.isArray()) return;

    QJsonArray media = doc.array();

    for (const auto& m : media) {
        QJsonObject obj = m.toObject();
        QString tip = obj["tipologia"].toString();
        if (tip != tipo) continue;

        QString titolo = obj["titolo"].toString();
        QString autore = obj["autore"].toString();
        QString imagePath = obj["path"].toString();

        MediaFrame* mediaframe = new MediaFrame(titolo, imagePath, autore, container);
        layoutContainer->addWidget(mediaframe);

        mediaframe->setCursor(Qt::PointingHandCursor);

        connect(mediaframe, &MediaFrame::selected, this, [this](MediaFrame* f){
            if (currentSelected)
                currentSelected->setSelected(false);
            currentSelected = f;
            currentSelected->setSelected(true);
            emit mediaSelected(f);
        });
    }
}

void SelectMediaReference::setSelectFalse() {
    if (currentSelected) {
        currentSelected->setSelected(false);
        currentSelected = nullptr;
    }
}
