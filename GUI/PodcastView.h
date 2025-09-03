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
};
#endif //PODCASTVOEW_H