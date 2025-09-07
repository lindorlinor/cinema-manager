#ifndef PODCASTVIEW_H
#define PODCASTVIEW_H
#include "MediaView.h"
#include "../Podcast.h"
class PodcastView: public MediaView{
    Q_OBJECT
public:
    explicit PodcastView(Podcast* pPtr, QWidget* parent = nullptr);
public slots:
    void update() override;
private:
    Podcast* podPtr;
    void createMediaDetails() override;
    void createScrollableSection() override;
    void createButtons() override;
    void updateMediaDetails() override;
    void updateScrollableSection() override;

    QVBoxLayout * layoutPuntate;
    QLabel* conduttore;
    QLabel* puntate;
private slots:
    void extendMediaMessage() override;
    void deleteMediaMessage() override;
};
#endif //PODCASTVOEW_H