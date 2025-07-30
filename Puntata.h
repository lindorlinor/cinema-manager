#ifndef PUNTATA_H
#define PUNTATA_H

#include "Media.h"

class Podcast;

class Puntata: public Media{
    private:
        vector<string> p_ospiti;
        Podcast* p_podcast;
    public:

        
        void estendiDataFineRilascio() override; 
        double calcolaIncasso() override;
};

#endif //PUNTATA_H