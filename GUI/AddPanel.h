#ifndef ADDPANEL_H
#define ADDPANEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class AddPanel:public QWidget{
    Q_OBJECT
    private:
    QWidget* addPath();
    void addPagina(QVBoxLayout* mainLayout);

    public:
	explicit AddPanel(QWidget *parent);
};

#endif //ADDPANEL_H