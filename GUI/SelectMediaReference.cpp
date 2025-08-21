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
    container->setLayout(layoutContainer);
    
    // Scroll area
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(container);
    
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);
    
    // Carica inizialmente i media
    reloadMedia();
    
    //style
    layoutContainer->addSpacerItem(new QSpacerItem(20, 400, QSizePolicy::Minimum, QSizePolicy::Expanding));
    scrollArea->setStyleSheet(
                                "QScrollArea QWidget{"
                                    "border-radius: 10px;"
                                    "background-color: #073c47;"
                                    "border: none}"
                                    "QScrollArea{"
                                    "background: transparent;}"
                                "QScrollBar:vertical {"
                                    "background: #4e7f8b;"
                                    "width: 12px;"
                                    "margin: 0px;"
                                    "border: 1px solid #4e7f8b;}"
                                "QScrollBar::handle:vertical {"
                                    "background: #d9d9d9;"
                                    "min-height: 20px;"
                                    "border-radius: 3px;}"
                                "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
                                    "background: #4e7f8b;"
                                    "border: 1px solid #4e7f8b;"
                                    "height: 12px;"
                                    "border-radius: 5px;"
                                    "subcontrol-position: top;"
                                    "subcontrol-origin: margin;}"
                                "QScrollBar::add-line:vertical:hover, QScrollBar::sub-line:vertical:hover {"
                                    "background: #4e7f8b;}"
                            );
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainLayout->setAlignment(Qt::AlignRight);
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

    //style
    layoutContainer->setAlignment(Qt::AlignCenter);
}

void SelectMediaReference::setSelectFalse() {
    if (currentSelected) {
        currentSelected->setSelected(false);
        currentSelected = nullptr;
    }
}
