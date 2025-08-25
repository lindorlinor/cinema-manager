#include "DetailsPageButtons.h"
#include <QPushButton>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QFile>

DetailsPageButtons::DetailsPageButtons(QWidget* parent)
    : QWidget(parent)
{

    auto* mainLayout = new QVBoxLayout(this);

    extendButton = new QPushButton("Estendi data");
    extendButton->setCursor(Qt::PointingHandCursor);
    extendButton->setMinimumHeight(53);
    extendTool = new QToolButton();
    extendTool->setCheckable(true);
    extendTool->setAutoRaise(true);
    extendTool->setFixedSize(24, 24);
    extendTool->setToolTip("Attiva/Disattiva pulsante");
    
    extendButton->setEnabled(true);
    extendTool->setChecked(true);
    extendTool->setIcon(QIcon(":/icons/enabled.png"));
    
    auto* row1 = new QHBoxLayout();
    row1->addWidget(extendButton);
    row1->addWidget(extendTool);
    mainLayout->addLayout(row1);
    
    
    deleteButton = new QPushButton("Elimina media");
    deleteButton->setCursor(Qt::PointingHandCursor);
    deleteButton->setMinimumHeight(53);
    
    deleteTool = new QToolButton();
    deleteTool->setCheckable(true);
    deleteTool->setAutoRaise(true);
    deleteTool->setFixedSize(24, 24);
    deleteTool->setToolTip("Attiva/Disattiva pulsante");
    
    deleteButton->setEnabled(false);
    deleteTool->setChecked(false);
    deleteTool->setIcon(QIcon(":/icons/disabled.png"));


    auto* row2 = new QHBoxLayout();
    row2->addWidget(deleteButton);
    row2->addWidget(deleteTool);
    mainLayout->addLayout(row2);

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

