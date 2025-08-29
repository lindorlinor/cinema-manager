#ifndef FILMVIEW_H
#define FILMVIEW_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "MediaView.h"
#include "../Film.h"
class FilmView : public MediaView{
    Q_OBJECT
public:
    explicit FilmView(Film* fPtr, QWidget* parent = nullptr);
private:
    Film* filmPtr;
    void createMediaDetails() override;
    void createScrollableSection() override;
    void createButtons() override;
signals:
    void trailerSelected(const Trailer* trailer); //segnale emesso quando cliccato su un trailer del film, trailer è il puntatore al trailer cliccato

};
#endif
