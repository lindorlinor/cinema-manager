#ifndef PODCASTVIEW_H
#define PODCASTVIEW_H
#include "MediaView.h"
#include "../Podcast.h"
class PodcastView: public MediaView{
    Q_OBJECT
public:
    explicit PodcastView(Podcast* pPtr, QWidget* parent = nullptr);
private:
    Podcast* podPtr;
    void createMediaDetails() override;
    void createScrollableSection() override;
    void createButtons() override;
signals:
    //@to do non so se ha senso sta roba
    void puntataSelected(const Puntata* puntata); //segnale emesso quando cliccato su un trailer del film, trailer è il puntatore al trailer cliccato

};
#endif //PODCASTVOEW_H