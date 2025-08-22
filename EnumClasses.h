/**
 * @file EnumClasses.h
 * @brief Dichiarazioni di tipi enum definiti in metodi e campi dati della gerarchia di media. Definizione di metodi inline di utilità per la conversione in stringa dei tipi enum.
 */

#ifndef ENUMCLASSES_H
#define ENUMCLASSES_H


#include <map>
#include <string>
#include <QList>

enum class Formato {
    DCP,
    RealD_3D,
    MOV_ProRes,
    MXF,
    WAV_5_1,
    WAV_7_1,
    MP4,
    MOV_H264,
    TIFF,
    IMAX_3D
};

inline const char* toString(Formato f) {
    switch (f) {
        case Formato::DCP: return "DCP";
        case Formato::RealD_3D: return "RealD 3D";
        case Formato::MOV_ProRes: return "MOV ProRes";
        case Formato::MXF: return "MXF";
        case Formato::WAV_5_1: return "WAV 5.1";
        case Formato::WAV_7_1: return "WAV 7.1";
        case Formato::MP4: return "MP4";
        case Formato::MOV_H264: return "MOV H264";
        case Formato::TIFF: return "TIFF";
        case Formato::IMAX_3D: return "IMAX 3D";
        default: return "Non trovato";
    }
}

inline std::vector<Formato> tuttiIFormati() {
    return {
        Formato::DCP,
        Formato::RealD_3D,
        Formato::MOV_ProRes,
        Formato::MXF,
        Formato::WAV_5_1,
        Formato::WAV_7_1,
        Formato::MP4,
        Formato::MOV_H264,
        Formato::TIFF,
        Formato::IMAX_3D
    };
}



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

inline std::vector<FasciaOraria> tutteLeFasceOrarie() {
    return {
        FasciaOraria::Mattina,
        FasciaOraria::Pomeriggio,
        FasciaOraria::Sera
    };
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
        case Lingua::Giapponese: return "Giapponese";
        case Lingua::Cinese: return "Cinese";
        default: return "Non trovato";
    }
}

inline std::vector<Lingua> tutteLeLingue() {
    return {
        Lingua::Italiano,
        Lingua::Inglese,
        Lingua::Francese,
        Lingua::Spagnolo,
        Lingua::Tedesco,
        Lingua::Giapponese,
        Lingua::Cinese
    };
}


enum class Classificazione {
    TUTTI=0,        
    SEI_PIU=6,      
    QUATTORDICI_PIU=14, 
    DICIOTTO_PIU=18
};

inline const char* toString(Classificazione c) {
    switch (c) {
        case Classificazione::TUTTI: return "TUTTI";
        case Classificazione::SEI_PIU: return "6+";
        case Classificazione::QUATTORDICI_PIU: return "14+";
        case Classificazione::DICIOTTO_PIU: return "18+";
        default: return "Non trovato";
    }
}

inline std::vector<Classificazione> tutteLeClassificazioni() {
    return {
        Classificazione::TUTTI,
        Classificazione::SEI_PIU,
        Classificazione::QUATTORDICI_PIU,
        Classificazione::DICIOTTO_PIU
    };
}

enum class Genere {
    Azione, 
    Animazione,
    Avventura,
    Commedia, 
    Crime,
    Drama,
    Fantasy,
    Horror,
    Thriller,
    ScienceFiction,
    Mistero,
    Western,
    Documentario,
    Storico,
    Romantico,
    Supereroi
};

inline const char* toString(Genere g) {
    switch (g) {
        case Genere::Azione: return "Azione";
        case Genere::Animazione: return "Animazione";
        case Genere::Avventura: return "Avventura";
        case Genere::Commedia: return "Commedia";
        case Genere::Crime: return "Crime";
        case Genere::Drama: return "Drama";
        case Genere::Fantasy: return "Fantasy";
        case Genere::Horror: return "Horror";
        case Genere::Thriller: return "Thriller";
        case Genere::ScienceFiction: return "ScienceFiction";
        case Genere::Mistero: return "Mistero";
        case Genere::Western: return "Western";
        case Genere::Documentario: return "Documentario";
        case Genere::Storico: return "Storico";
        case Genere::Romantico: return "Romantico";
        case Genere::Supereroi: return "Supereroi";
        default: return "Non trovato";
    }
}

inline std::vector<Genere> tuttiIGeneri() {
    return {
        Genere::Azione, 
        Genere::Avventura,
        Genere::Commedia, 
        Genere::Crime,
        Genere::Drama,
        Genere::Fantasy,
        Genere::Horror,
        Genere::Thriller,
        Genere::ScienceFiction,
        Genere::Mistero,
        Genere::Western,
        Genere::Documentario,
        Genere::Animazione,
        Genere::Storico,
        Genere::Romantico,
        Genere::Supereroi
    };
}

enum class Risoluzione {
    SD_480p,    // 720x480
    HD_720p,    // 1280x720
    FullHD_1080p, // 1920x1080
    QHD_1440p,  // 2560x1440
    UHD_4K_2160p, // 3840x2160
    UHD_8K_4320p  // 7680x4320
};

inline const char* toString(Risoluzione r) {
    switch (r) {
        case Risoluzione::SD_480p: return "SD 480p";
        case Risoluzione::HD_720p: return "HD 720p";
        case Risoluzione::QHD_1440p: return "QHD 1440p";
        case Risoluzione::UHD_4K_2160p: return "UHD 4K 2160p";
        case Risoluzione::UHD_8K_4320p: return "UHD 8K 4320p";
        default: return "Non trovato";
    }
}

inline std::vector<Risoluzione> tutteLeRisoluzioni() {
    return {
        Risoluzione::SD_480p,
        Risoluzione::HD_720p,
        Risoluzione::QHD_1440p,
        Risoluzione::UHD_4K_2160p,
        Risoluzione::UHD_8K_4320p
    };
}


#endif // NOME_DEL_FILE_H

