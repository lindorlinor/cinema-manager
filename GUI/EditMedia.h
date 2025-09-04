#ifndef EDITMEDIA_H
#define EDITMEDIA_H

#include <string>
#include <vector>
#include <chrono>

#include "MediaInterface.h"

class EditMedia:public MediaInterface{
    Q_OBJECT

    private:

    virtual void checkMediaNameAvailability() override;
    virtual void salvaMedia() override;
    void setCheckListWidget(QListWidget* list, const QList<QString>& select);
    int index;
    Media* em_media;
    /* bool isModified();

    bool isLingueModified();
    bool isFasceOrarieModified(Inserzione* inserzione);
    bool isSottotitoliModified();
    bool isGeneriModified(Film* film);
    bool isAttoreModified(Film* film);
    bool isOspiteModified(Puntata* puntata); */
    
    virtual void setLimitTabTipologia(int index) override;     
    
    public:
	explicit EditMedia(Media* media, QWidget *parent);
    void initValue();
    
};

#endif //EDITMEDIA_H