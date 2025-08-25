#ifndef FILMVIEW_H
#define FILMVIEW_H
#include <QWidget>
#include "../Film.h"
class FilmView : public QWidget
{
    Q_OBJECT
public:
    explicit FilmView(Film* film, QWidget* parent = nullptr);

signals:
    void trailerSelected(const Trailer* trailer);
    void extendMediaClicked();
    void deleteMediaClicked();

};
#endif
