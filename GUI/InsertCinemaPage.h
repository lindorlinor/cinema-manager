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
    QLabel* imageLabel;
    void checkCinemaNameAvailability(const QString& text);
    bool hasCustomImage;
    bool isAvailable;
public:
    explicit InsertCinemaPage(QWidget * parent= nullptr);
    void saveCinemaInXml();
    void reset();
    void resizeEvent(QResizeEvent* event) override;

public slots:
    void chooseImage();
    void removeImage();
signals:
    void returnCinemaSelectionPage();
    
};
#endif //INSERTCINEMAPAGE_H