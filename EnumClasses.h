/**
 * @file EnumClasses.h
 * @brief Dichiarazioni di tipi enum definiti in metodi e campi dati della gerarchia di media. Definizione di metodi inline di utilità per la conversione in stringa dei tipi enum.
 */

#ifndef ENUMCLASSES_H
#define ENUMCLASSES_H


#include <map>
#include <string>
#include <QList>
#include <chrono>
using namespace std::chrono;


inline year_month_day stringToDate(const std::string& s) {
    unsigned d, m;
    int y;
    char sep1, sep2;

    std::istringstream iss(s);
    iss >> d >> sep1 >> m >> sep2 >> y;

    if (!iss || sep1 != '/' || sep2 != '/') {
        throw std::runtime_error("Formato data non valido: " + s);
    }

    return year{y}/month{m}/day{d};
}

inline std::string dateToString(const year_month_day& d) {
    std::ostringstream oss;
    oss << unsigned(d.day()) << "/"
        << unsigned(d.month()) << "/"
        << int(d.year());
    return oss.str();
}


enum class Formato {
    MP4,
    DCP,
    RealD_3D,
    MOV_ProRes,
    MXF,
    WAV_5_1,
    WAV_7_1,
    MOV_H264,
    TIFF,
    IMAX_3D
};

inline const char* toString(Formato f) {
    switch (f) {
        case Formato::MP4: return "MP4";
        case Formato::DCP: return "DCP";
        case Formato::RealD_3D: return "RealD 3D";
        case Formato::MOV_ProRes: return "MOV ProRes";
        case Formato::MXF: return "MXF";
        case Formato::WAV_5_1: return "WAV 5.1";
        case Formato::WAV_7_1: return "WAV 7.1";
        case Formato::MOV_H264: return "MOV H264";
        case Formato::TIFF: return "TIFF";
        case Formato::IMAX_3D: return "IMAX 3D";
        default: return "Non trovato";
    }
}

inline std::vector<Formato> tuttiIFormati() {
    return {
        Formato::MP4,
        Formato::DCP,
        Formato::RealD_3D,
        Formato::MOV_ProRes,
        Formato::MXF,
        Formato::WAV_5_1,
        Formato::WAV_7_1,
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
        case Risoluzione::FullHD_1080p: return "FullHD 1080p";
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

inline Formato toFormato(const std::string& s) {
    if (s == "DCP") return Formato::DCP;
    if (s == "RealD 3D") return Formato::RealD_3D;
    if (s == "MOV ProRes") return Formato::MOV_ProRes;
    if (s == "MXF") return Formato::MXF;
    if (s == "WAV 5.1") return Formato::WAV_5_1;
    if (s == "WAV 7.1") return Formato::WAV_7_1;
    if (s == "MP4") return Formato::MP4;
    if (s == "MOV H264") return Formato::MOV_H264;
    if (s == "TIFF") return Formato::TIFF;
    if (s == "IMAX 3D") return Formato::IMAX_3D;
}

inline FasciaOraria toFasciaOraria(const std::string& s) {
    if (s == "Mattina") return FasciaOraria::Mattina;
    if (s == "Pomeriggio") return FasciaOraria::Pomeriggio;
    if (s == "Sera") return FasciaOraria::Sera;
}

inline Lingua toLingua(const std::string& s) {
    if (s == "Italiano") return Lingua::Italiano;
    if (s == "Inglese") return Lingua::Inglese;
    if (s == "Francese") return Lingua::Francese;
    if (s == "Spagnolo") return Lingua::Spagnolo;
    if (s == "Tedesco") return Lingua::Tedesco;
    if (s == "Giapponese") return Lingua::Giapponese;
    if (s == "Cinese") return Lingua::Cinese;
}

inline Classificazione toClassificazione(const std::string& s) {
    if (s == "TUTTI") return Classificazione::TUTTI;
    if (s == "6+") return Classificazione::SEI_PIU;
    if (s == "14+") return Classificazione::QUATTORDICI_PIU;
    if (s == "18+") return Classificazione::DICIOTTO_PIU;
    return Classificazione::TUTTI;
}

inline Genere toGenere(const std::string& s) {
    if (s == "Azione") return Genere::Azione;
    if (s == "Animazione") return Genere::Animazione;
    if (s == "Avventura") return Genere::Avventura;
    if (s == "Commedia") return Genere::Commedia;
    if (s == "Crime") return Genere::Crime;
    if (s == "Drama") return Genere::Drama;
    if (s == "Fantasy") return Genere::Fantasy;
    if (s == "Horror") return Genere::Horror;
    if (s == "Thriller") return Genere::Thriller;
    if (s == "ScienceFiction") return Genere::ScienceFiction;
    if (s == "Mistero") return Genere::Mistero;
    if (s == "Western") return Genere::Western;
    if (s == "Documentario") return Genere::Documentario;
    if (s == "Storico") return Genere::Storico;
    if (s == "Romantico") return Genere::Romantico;
    if (s == "Supereroi") return Genere::Supereroi;
}

inline Risoluzione toRisoluzione(const std::string& s) {
    if (s == "SD 480p") return Risoluzione::SD_480p;
    if (s == "HD 720p") return Risoluzione::HD_720p;
    if (s == "FullHD 1080p") return Risoluzione::FullHD_1080p;
    if (s == "QHD 1440p") return Risoluzione::QHD_1440p;
    if (s == "UHD 4K 2160p") return Risoluzione::UHD_4K_2160p;
    if (s == "UHD 8K 4320p") return Risoluzione::UHD_8K_4320p;
}

#endif //ENUMCLASSES_H

