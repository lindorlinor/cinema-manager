#include "DetailsPageButtons.h"
#include <QPushButton> 
#include <QToolButton> 
#include <QVBoxLayout> 
#include <QHBoxLayout> 
#include <QIcon>

DetailsPageButtons::DetailsPageButtons(Media* mPtr, QWidget* parent)
    : QWidget(parent), mediaPtr(mPtr),mainLayout(new QVBoxLayout(this)){
    
    createButtons();
    updateButtons();
}

void DetailsPageButtons::createButtons() {
    extendButton = new QPushButton("Estendi data");
    extendButton->setObjectName("extendButton");
    extendButton->setCursor(Qt::PointingHandCursor);
    extendButton->setMinimumHeight(53);
    extendButton->setFixedWidth(234);

    extendTool = new QToolButton();
    extendTool->setCursor(Qt::PointingHandCursor);
    extendTool->setObjectName("extendTool");
    extendTool->setCheckable(true);
    extendTool->setAutoRaise(true);
    extendTool->setFixedSize(24, 24);
    extendTool->setToolTip("Attiva/Disattiva pulsante");

    QHBoxLayout* rigaExtend = new QHBoxLayout();
    rigaExtend->addWidget(extendButton, 0, Qt::AlignLeft);
    rigaExtend->addWidget(extendTool, 0, Qt::AlignLeft);
    
    deleteButton = new QPushButton("Elimina media");
    deleteButton->setObjectName("deleteButton");
    deleteButton->setCursor(Qt::PointingHandCursor);
    deleteButton->setMinimumHeight(53);
    deleteButton->setFixedWidth(234);

    deleteTool = new QToolButton();
    deleteTool->setCursor(Qt::PointingHandCursor);
    deleteTool->setObjectName("deleteTool");
    deleteTool->setCheckable(true);
    deleteTool->setAutoRaise(true);
    deleteTool->setFixedSize(24,24);
    deleteTool->setToolTip("Attiva/Disattiva pulsante");
    
    QHBoxLayout* rigaDelete = new QHBoxLayout();
    rigaDelete->addWidget(deleteButton, 0, Qt::AlignLeft);
    rigaDelete->addWidget(deleteTool, 0, Qt::AlignLeft);


    mainLayout->addLayout(rigaExtend);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(rigaDelete);

    connect(extendTool, &QToolButton::toggled, this, [this](bool checked) {
        extendButton->setEnabled(checked);
        extendTool->setIcon(QIcon(checked ? ":/icons/enabled.png" : ":/icons/disabled.png"));
    });

    connect(deleteTool, &QToolButton::toggled, this, [this](bool checked) {
        deleteButton->setEnabled(checked);
        deleteTool->setIcon(QIcon(checked ? ":/icons/enabled.png" : ":/icons/disabled.png"));
    });

    connect(extendButton, &QPushButton::clicked, this, &DetailsPageButtons::extendMedia);
    connect(deleteButton, &QPushButton::clicked, this, &DetailsPageButtons::deleteMedia);
}

void DetailsPageButtons::updateButtons() {
    if (!mediaPtr) return;

    if (mediaPtr->FuoriProduzione()) {
        extendButton->setEnabled(false);
        extendTool->setVisible(false);
    } else {
        extendButton->setEnabled(extendTool->isChecked());
        extendTool->setVisible(true);
        extendTool->setIcon(QIcon(extendTool->isChecked() ? ":/icons/enabled.png" : ":/icons/disabled.png"));
    }

    deleteButton->setEnabled(deleteTool->isChecked());
    deleteTool->setIcon(QIcon(deleteTool->isChecked() ? ":/icons/enabled.png" : ":/icons/disabled.png"));
}

void DetailsPageButtons::setDeleteButtonText(const QString& text) {
    deleteButton->setText(text);
}
