#ifndef FILMVIEW_H
#define FILMVIEW_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "MediaView.h"
#include "../../Film.h"
class FilmView : public MediaView
{
    Q_OBJECT
public:
    explicit FilmView(Film *fPtr, QWidget *parent = nullptr);
public slots:
    void update() override;

private:
    Film *filmPtr;

    void createMediaDetails() override;
    void createScrollableSection() override;
    void createButtons() override;

    void updateMediaDetails() override;
    void updateScrollableSection() override;

    QVBoxLayout *layoutTrailer;

    QLabel *costoBiglietto;
    QLabel *valutazione;
    QLabel *postCredit;
    ExpandableLabel *attoriLabel;
    QLabel *genere;
    QLabel *classificazione;
    QLabel *casaProduzione;

private slots:
    void extendMediaMessage() override;
    void deleteMediaMessage() override;
};
#endif
