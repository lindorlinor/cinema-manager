#ifndef INSERZIONEVIEW_H
#define INSERZIONEVIEW_H
#include "MediaView.h"
#include "../Inserzione.h"
class InserzioneView: public MediaView{
     Q_OBJECT
public:
    explicit InserzioneView(Inserzione* iPtr,QWidget* parent = nullptr);
    void setMediaList(const std::list<Media*>& list);
public slots:
    void update() override;
private:
    Inserzione* insPtr;
    void createMediaDetails() override;
    void createScrollableSection() override;
    void createButtons() override;
    const std::list<Media*>* mediaList;
    void updateMediaDetails() override;

    QLabel* nProiezioniGiornaliere;
    QLabel* fasce;
    QLabel* targetPubb;
    QLabel* costoFissoProiezioni;
};

#endif //INSERZIONEVIEW_H