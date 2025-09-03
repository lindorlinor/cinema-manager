#ifndef INSERZIONEVIEW_H
#define INSERZIONEVIEW_H
#include "MediaView.h"
#include "../Inserzione.h"
class InserzioneView: public MediaView{
     Q_OBJECT
public:
    explicit InserzioneView(Inserzione* iPtr,QWidget* parent = nullptr);
    void setMediaList(const std::list<Media*>& list);
private:
    Inserzione* insPtr;
    void createMediaDetails() override;
    void createScrollableSection() override;
    void createButtons() override;
    list<Media*> mediaList;
};

#endif //INSERZIONEVIEW_H