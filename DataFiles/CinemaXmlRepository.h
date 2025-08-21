
#ifndef CINEMAXMLREPOSITORY_H
#define CINEMAXMLREPOSITORY_H
#include <QString>
#include <QList>

struct Cinema {
    QString nome;
    QString imagePath;
    QString xmlPath;
};

class CinemaXmlRepository {
public:
    explicit CinemaXmlRepository(const QString& basePath);
    QList<Cinema> loadAllCinemas() const;

    bool saveCinema(const Cinema& cinema);
    bool isNameAvailable(const QString& name) const;


private:
    QString m_basePath;
};
#endif// CINEMAXMLREPOSITORY_H
