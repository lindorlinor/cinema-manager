#ifndef INSERTCINEMAPAGE_H
#define INSERTCINEMAPAGE_H
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "InsertImageFrame.h"
class InsertCinemaPage : public QWidget{
    Q_OBJECT
private:
    QVBoxLayout* frameLayout;
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
    void createHeader();
    void createSplitView();
    void createLayoutInput(QVBoxLayout* layoutdx);
    void createButtonLayout(QVBoxLayout* layoutdx);
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