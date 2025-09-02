#ifndef INSERZIONEVIEW_H
#define INSERZIONEVIEW_H
#include "MediaView.h"
#include "../Inserzione.h"
class InserzioneView: public MediaView{
     Q_OBJECT
public:
    explicit InserzioneView(Inserzione* iPtr,QWidget* parent = nullptr);
    private:
    Inserzione* insPtr;
    void createMediaDetails() override;
    void createScrollableSection() override;
    void createButtons() override;
signals:
    void puntataSelected(); //segnale emesso quando cliccato su un trailer del film, trailer è il puntatore al trailer cliccato

};

#endif //INSERZIONEVIEW_H