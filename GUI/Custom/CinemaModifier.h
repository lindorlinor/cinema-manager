#ifndef CINEMAMODIFIER_H
#define CINEMAMODIFIER_H

#include <QDialog>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QPixmap>

#include "InsertImageFrame.h"
#include "DataFiles/CinemaRepositoryJson.h"
#include "../Cinema.h"

class CinemaModifier : public QDialog
{
    Q_OBJECT
    private:
        Cinema* editCinema;
        QLineEdit* lineEdit;
        QLabel* errorLabel;
        QPushButton* saveButton;
        bool nomeAvailable;
        bool nomeCambiato;
        bool copertinaCambiata;
        InsertImageFrame* imgFrame;
        QLabel* img;
        QString imagePath;
        void checkCinemaNameAvailability();
        void saveEdit();

    public:
        explicit CinemaModifier(Cinema* cinema, QWidget *parent=nullptr);

    public slots:
    void chooseImage();
    void removeImage();
    
};

#endif // CINEMAMODIFIER_H
