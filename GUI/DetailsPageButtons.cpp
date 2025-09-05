#include "DetailsPageButtons.h"
#include <QPushButton>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>

DetailsPageButtons::DetailsPageButtons(Media* mPtr, QWidget* parent)
    : QWidget(parent), mediaPtr(mPtr)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    extendButton = new QPushButton("Estendi data");
    extendButton->setObjectName("extendButton");
    extendButton->setCursor(Qt::PointingHandCursor);
    extendButton->setMinimumHeight(53);
    extendButton->setFixedWidth(234);

    extendTool = new QToolButton();
    extendTool->setObjectName("extendTool");
    extendTool->setCheckable(true);
    extendTool->setAutoRaise(true);
    extendTool->setFixedSize(24, 24);
    extendTool->setToolTip("Attiva/Disattiva pulsante");

    extendButton->setEnabled(true);
    extendTool->setChecked(true);
    extendTool->setIcon(QIcon(":/icons/enabled.png"));

    QHBoxLayout* rigaExtend = new QHBoxLayout();
    rigaExtend->addWidget(extendButton,0,Qt::AlignLeft);
    rigaExtend->addWidget(extendTool,0,Qt::AlignLeft);
    mainLayout->addLayout(rigaExtend);

    if (mediaPtr && mediaPtr->FuoriProduzione()) {
        extendButton->setEnabled(false);
        extendTool->setVisible(false);
    }

    mainLayout->addSpacing(20);
    deleteButton = new QPushButton("Elimina media");
    deleteButton->setObjectName("deleteButton");
    deleteButton->setCursor(Qt::PointingHandCursor);
    deleteButton->setMinimumHeight(53);
    deleteButton->setFixedWidth(234);

    deleteTool = new QToolButton();
    deleteTool->setObjectName("deleteTool");
    deleteTool->setCheckable(true);
    deleteTool->setAutoRaise(true);
    deleteTool->setFixedSize(24, 24);
    deleteTool->setToolTip("Attiva/Disattiva pulsante");

    deleteButton->setEnabled(false);
    deleteTool->setChecked(false);
    deleteTool->setIcon(QIcon(":/icons/disabled.png"));

    QHBoxLayout* rigaDelete = new QHBoxLayout();
    rigaDelete->addWidget(deleteButton,0,Qt::AlignLeft);
    rigaDelete->addWidget(deleteTool,0,Qt::AlignLeft);
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

void DetailsPageButtons::setDeleteButtonText(const QString& text) {
    deleteButton->setText(text);
}

