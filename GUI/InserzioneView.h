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
signals:
    void inserzioneSelected(Inserzione * i); //segnale emesso quando cliccato su un trailer del film, trailer è il puntatore al trailer cliccato

};

#endif //INSERZIONEVIEW_H