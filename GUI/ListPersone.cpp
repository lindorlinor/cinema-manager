#include "ListPersone.h"

ListPersone::ListPersone(QWidget *parent):QWidget(parent){
    inputPersone = new QLineEdit(this);
    aggiungi = new QPushButton("+",this); 
    rimuovi = new QPushButton("rimuovi",this);
    listapersone = new QListView(this);

    model = new QStringListModel(this);
    listapersone->setModel(model);
    
    QHBoxLayout* layoutH = new QHBoxLayout;
    QVBoxLayout* layoutV = new QVBoxLayout;

    layoutH->addWidget(inputPersone);
    layoutH->addWidget(aggiungi);

    layoutV->addLayout(layoutH);
    layoutV->addWidget(rimuovi);
    layoutV->addWidget(listapersone);

    setLayout(layoutV);

    connect(aggiungi, &QPushButton::clicked, this, &ListPersone::addItem);
    connect(rimuovi, &QPushButton::clicked, this, &ListPersone::removeItem);
}

void ListPersone::addItem() {
    QString item = inputPersone->text();
    if (!item.isEmpty()) {
        QStringList currentList = model->stringList();
        currentList.append(item);
        model->setStringList(currentList);
        inputPersone->clear();
    }
}

void ListPersone::removeItem() {
    QModelIndex selectedIndex = listapersone->currentIndex();
    if (selectedIndex.isValid()) {
        QStringList currentList = model->stringList();
        currentList.removeAt(selectedIndex.row());
        model->setStringList(currentList);
    }
}

#include <vector>
#include <QStringListModel>

std::vector<QString> ListPersone::getListaPersone() {
    std::vector<QString> result;
    QStringList list = model->stringList(); 
    result.assign(list.begin(), list.end()); 
    return result;
}
