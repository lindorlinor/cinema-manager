#ifndef INSERTCINEMAPAGE_H
#define INSERTCINEMAPAGE_H
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "InsertImageFrame.h"
class InsertCinemaPage : public QWidget{
    Q_OBJECT
private:
    QLineEdit *textInput;
    InsertImageFrame *imageArea;
    QString imagePath;
    QLabel * errorLabel;
    QPushButton * escButton;
    QPushButton * saveButton; 
    void checkCinemaNameAvailability(const QString& text);
public:
    explicit InsertCinemaPage(QWidget * parent= nullptr);
    void saveCinemaInXml();
public slots:
    void chooseImage();
signals:
    void returnCinemaSelectionPage();
    
};
#endif //INSERTCINEMAPAGE_H