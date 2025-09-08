#ifndef TRAILERVIEW_H
#define TRAILERVIEW_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "MediaView.h"
#include "../../Trailer.h"
class TrailerView : public MediaView
{
    Q_OBJECT
public:
    explicit TrailerView(Trailer *tPtr, QWidget *parent = nullptr);
public slots:
    void update() override;

private:
    Trailer *trailerPtr;
    void createMediaDetails() override;
    void createScrollableSection() override;
    void createButtons() override;
    void updateMediaDetails() override;
    void updateScrollableSection() override;

    QVBoxLayout *layoutFilmA;
    QVBoxLayout *layoutTrailer;
    QLabel *nProiezioniGiornaliere;
    QLabel *targetPubb;
private slots:
    void extendMediaMessage() override;
    void deleteMediaMessage() override;
};
#endif