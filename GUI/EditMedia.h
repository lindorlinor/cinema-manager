#ifndef EDITMEDIA_H
#define EDITMEDIA_H

#include "MediaInterface.h"
#include "EditMediaVisitor.h"

class EditMedia:public MediaInterface{
    Q_OBJECT

    private:

    virtual void salvaMedia() override;
    void initValue();
    int index;
        
    virtual void setLimitTabTipologia(int index) override;     
                  
    public:
	explicit EditMedia(Media* media, QWidget *parent);
    
};

#endif //EDITMEDIA_H