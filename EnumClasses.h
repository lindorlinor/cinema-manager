#ifndef ENUMCLASSES_H
#define ENUMCLASSES_H


#include <map>
#include <string>

 enum class Formato {
    DCP,
    RealD_3D,
    MOV_ProRes,
    MXF,
    WAV_5_1,
    WAV_7_1,
    MP4,
    MOV_H264,
    GIF,
    PNG,
    JPG,
    WEBP,
    PDF,
    TIFF,
    AI,
    EPS,
    HTML,
    IMAX_3D,
    Unknown
};


enum class FasciaOraria{
    Mattina,
    Pomeriggio,
    Sera
};



inline const char* toString(FasciaOraria fo) {
    switch (fo) {
        case FasciaOraria::Mattina: return "Mattina";
        case FasciaOraria::Pomeriggio: return "Pomeriggio";
        case FasciaOraria::Sera: return "Sera";
        default: return "Non trovato";
    }
}

enum class Lingua {
    Italiano,
    Inglese,
    Francese,
    Spagnolo,
    Tedesco,
    Giapponese,
    Cinese
};

inline const char* toString(Lingua l) {
    switch (l) {
        case Lingua::Italiano: return "Italiano";
        case Lingua::Inglese: return "Inglese";
        case Lingua::Francese: return "Francese";
        case Lingua::Spagnolo: return "Spagnolo";
        case Lingua::Tedesco: return "Tedesco";
        default: return "Non trovato";
    }
}

enum class Classificazione {
    TUTTI=0,        
    SEI_PIU=6,      
    QUATTORDICI_PIU=14, 
    DICIOTTO_PIU=18
};

inline const char* toString(Classificazione c) {
    switch (c) {
        case Classificazione::TUTTI: return "T";
        case Classificazione::SEI_PIU: return "6+";
        case Classificazione::QUATTORDICI_PIU: return "14+";
        case Classificazione::DICIOTTO_PIU: return "18+";
        default: return "Non trovato";
    }
}

#endif // NOME_DEL_FILE_H

