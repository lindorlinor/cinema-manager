#ifndef LISTPERSONE_H
#define LISTPERSONE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStringListModel>
#include <QListView>
#include <QListWidgetItem>
#include <iostream>

using namespace std;

class ListPersone:public QWidget{
    Q_OBJECT

    private:
    QLineEdit* inputPersone;
    QPushButton* aggiungi; 
    QPushButton* rimuovi;
    QListView* listapersone;
    QWidget* WidgetAttori;
    QStringListModel* model;

    private slots:
    void addItem();
    void removeItem();
    
    public:
    explicit ListPersone(QWidget *parent=nullptr);
    vector<QString> getListaPersone();
    void resetWidget();
    void setItems(const QList<QString>& items);
};

#endif //LISTPERSONE_H