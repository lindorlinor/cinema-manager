#ifndef PUNTATAVIEW_H
#define PUNTATAVIEW_H
#include "MediaView.h"
#include "Puntata.h"

class PuntataView:public MediaView{
    Q_OBJECT
public:
    explicit PuntataView(Puntata* pPtr, QWidget* parent = nullptr);
public slots:
    void update() override;
private:
    Puntata* puntPtr;
    void createMediaDetails() override;
    void createScrollableSection() override;
    void createButtons() override;
    void updateMediaDetails() override;
    QLabel* conduttore;
    QLabel* nPubblicita;
};
#endif