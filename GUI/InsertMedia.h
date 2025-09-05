#ifndef INSERTMEDIA_H
#define INSERTMEDIA_H

#include "MediaInterface.h"

class InsertMedia:public MediaInterface{
    Q_OBJECT

    private:

    //reset dell'input messo sui widget, divisi per tipologia. Sono necessari quando si premono i pulsanti: salva, annulla, indietro o quando si cambia tipologia
    void resetInputFilm();
    void resetInputTrailer();
    void resetInputPodcast();
    void resetInputPuntata();
    void resetInputInserzione();

    virtual void salvaMedia() override;
        
    //metodi funzionali per il corretto comportamento della pagina
    virtual void setLimitTabTipologia(int index) override;     
                  
    public:
	explicit InsertMedia(QList<Media*>& mediaList, QWidget *parent);
    
    signals:
    void tornaAllaLibreria();
    
    public slots:
    void resetAllInput();
    
};

#endif //INSERTMEDIA_H