#ifndef ADDPANEL_H
#define ADDPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QString>
#include <QPixmap>
#include <QPushButton>
#include <QStandardPaths>

#include "PathButton.h"

class AddPanel:public QWidget{
    Q_OBJECT

    private:
    PathButton* widgetPath;
    void addPagina(QVBoxLayout* mainLayout);

    public:
	explicit AddPanel(QWidget *parent);

};

#endif //ADDPANEL_H