#include "ListPersone.h"

ListPersone::ListPersone(QWidget *parent):QWidget(parent){
    inputPersone = new QLineEdit(this);
    inputPersone->setPlaceholderText("Nome");
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
    connect(inputPersone, &QLineEdit::returnPressed, this, &ListPersone::addItem);

    //style
    inputPersone->setObjectName("inputPersone");
    aggiungi->setObjectName("aggiungi");
    rimuovi->setObjectName("rimuovi");
    listapersone->setObjectName("listapersone");
    listapersone->setStyleSheet(    "QListView::item:selected{"
                                    "background-color: #315057}"
                                    
                                    "QScrollBar:vertical { background: #04303b;"       
                                    "width: 12px;"              
                                    "margin: 0px 0px 0px 0px;"
                                    "border: 1px solid #04303b;"
                                    "border-radius: 5px; }"

                                    "QScrollBar::handle:vertical {background: #285965;"       
                                    "min-height: 20px;"
                                    "border-radius: 3px;}"

                                    "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
                                    "background: #04303b;"         
                                    "border: 1px solid #04303b;" 
                                    "height: 12px;"
                                    "border-radius: 5px;"
                                    "subcontrol-position: top;"  
                                    "subcontrol-origin: margin;}"

                                    "QScrollBar::add-line:vertical:hover, QScrollBar::sub-line:vertical:hover {"
                                    "background: #04303b;}");
    rimuovi->setStyleSheet("QPushButton:hover{color: #fed36a; font-weight: bold; background-color: #285965}");
    aggiungi->setStyleSheet("QPushButton:hover{color: #fed36a; font-weight: bold; background-color: #285965}");
    aggiungi->setCursor(Qt::PointingHandCursor);
    rimuovi->setCursor(Qt::PointingHandCursor);
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


void ListPersone::resetWidget(){
    inputPersone->clear();            
    model->setStringList(QStringList()); 
}