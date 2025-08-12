#ifndef INSERTCINEMAPAGE_H
#define INSERTCINEMAPAGE_H
#include <QWidget>
#include <QLineEdit>
#include "InsertImageFrame.h"
class InsertCinemaPage : public QWidget{
    Q_OBJECT
private:
    QLineEdit *textInput;
    InsertImageFrame *imageArea;
    QString imagePath;
public:
    explicit InsertCinemaPage(QWidget * parent= nullptr);
public slots:
    void chooseImage();
signals:
    void returnCinemaSelectionPage();
};
#endif //INSERTCINEMAPAGE_H