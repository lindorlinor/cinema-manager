#ifndef ENUMCLASSES_H
#define ENUMCLASSES_H


#include <map>
#include <string>

enum class Lingua {
    Italiano,
    Inglese,
    Francese,
    Spagnolo,
    Tedesco,
    Giapponese,
    Cinese
};

const std::map<Lingua, std::string> linguaToString = {
    {Lingua::Italiano, "Italiano"},
    {Lingua::Inglese, "Inglese"},
    {Lingua::Francese, "Francese"},
    {Lingua::Spagnolo, "Spagnolo"},
    {Lingua::Tedesco, "Tedesco"}
};


enum class Classificazione {
    TUTTI=0,        
    SEI_PIU=6,      
    QUATTORDICI_PIU=14, 
    DICIOTTO_PIU=18
};

const std::map<Classificazione, std::string> classificazioneToString = {
    {Classificazione::TUTTI, "T"},
    {Classificazione::SEI_PIU, "6+"},
    {Classificazione::QUATTORDICI_PIU, "14+"},
    {Classificazione::DICIOTTO_PIU, "18+"},
};

#endif // NOME_DEL_FILE_H

