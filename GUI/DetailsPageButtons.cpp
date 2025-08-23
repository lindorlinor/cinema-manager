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
    qDebug() << QFile::exists(":/../icons/enabled.svg");  // deve stampare true

    auto* mainLayout = new QVBoxLayout(this);

    btnEstendi = new QPushButton("Estendi data");
    btnEstendi->setCursor(Qt::PointingHandCursor);

    toolEstendi = new QToolButton();
    toolEstendi->setCheckable(true);
    toolEstendi->setAutoRaise(true);
    toolEstendi->setFixedSize(24, 24);
    toolEstendi->setToolTip("Attiva/Disattiva pulsante");

    btnEstendi->setEnabled(true);
    toolEstendi->setChecked(true);
    toolEstendi->setIcon(QIcon(":/icons/enabled.svg"));
    
    auto* row1 = new QHBoxLayout();
    row1->addWidget(btnEstendi);
    row1->addWidget(toolEstendi);
    mainLayout->addLayout(row1);
    
    
    btnElimina = new QPushButton("Elimina film");
    btnElimina->setCursor(Qt::PointingHandCursor);

    toolElimina = new QToolButton();
    toolElimina->setCheckable(true);
    toolElimina->setAutoRaise(true);
    toolElimina->setFixedSize(24, 24);
    toolElimina->setToolTip("Attiva/Disattiva pulsante");
    
    btnElimina->setEnabled(false);
    toolElimina->setChecked(false);
    toolElimina->setIcon(QIcon(":/icons/disabled.svg"));


    auto* row2 = new QHBoxLayout();
    row2->addWidget(btnElimina);
    row2->addWidget(toolElimina);
    mainLayout->addLayout(row2);

    connect(toolEstendi, &QToolButton::toggled, this, [this](bool checked) {
        btnEstendi->setEnabled(checked);
        toolEstendi->setIcon(QIcon(checked ? ":/icons/enabled.svg" : ":/icons/disabled.svg"));
    });

    connect(toolElimina, &QToolButton::toggled, this, [this](bool checked) {
        btnElimina->setEnabled(checked);
        toolElimina->setIcon(QIcon(checked ? ":/icons/enabled.svg" : ":/icons/disabled.svg"));
    });
}
