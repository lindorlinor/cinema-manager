#ifndef PUNTATAVIEW_H
#define PUNTATAVIEW_H
#include "MediaView.h"
#include "Puntata.h"
class PuntataView:public MediaView{
    Q_OBJECT
public:
    explicit PuntataView(Puntata* pPtr, QWidget* parent = nullptr);
private:
    Puntata* puntPtr;
    void createMediaDetails() override;
    void createScrollableSection() override;
    void createButtons() override;
signals:
    /*@to do come in tutti le altre MediaView non so se hanno senso,appena finisco cerco di capire (potrei direttamente fare la connect dentro qui ma non so
    se dovrei invece passare per searchPanel idk)*/
    void podcastSelected(const Podcast* podcast); 
    void puntataSelected(const Puntata* puntata); 
};
#endif