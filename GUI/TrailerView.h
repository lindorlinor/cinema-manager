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
private:
    Trailer* trailerPtr;
    void createMediaDetails() override;
    void createScrollableSection() override;
    void createButtons() override;
signals:
    void filmSelected(const Film* film); //segnale emesso quando cliccato sul film associato del film, film è il puntatore al film cliccato
    void trailerSelected(const Trailer* trailer); //segnale emesso quando cliccato su un trailer correlato (associato allo stesso film), trailer è il puntatore al trailer cliccato

};
#endif