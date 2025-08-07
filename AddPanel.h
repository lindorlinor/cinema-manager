#ifndef ADDPANEL_H
#define ADDPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

class AddPanel:public QWidget{
    Q_OBJECT
    private:
    void addPagina(QWidget* mainLayout);

    public:
	explicit AddPanel(QWidget *parent);
};

#endif //ADDPANEL_H