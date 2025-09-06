#ifndef TRAILERVIEW_H
#define TRAILERVIEW_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "MediaView.h"
#include "../Trailer.h"
class TrailerView : public MediaView{
    Q_OBJECT
public:
    explicit TrailerView(Trailer* tPtr, QWidget* parent = nullptr);
public slots:
    void update() override;
private:
    Trailer* trailerPtr;
    void createMediaDetails() override;
    void createScrollableSection() override;
    void createButtons() override;
    void updateMediaDetails() override;

    QLabel* nProiezioniGiornaliere;
    QLabel *targetPubb;
};
#endif