
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

    bool saveCinema(const Cinema& cinema);
    QList<Cinema> loadAllCinemas();

private:
    QString m_basePath;
};
#endif// CINEMAXMLREPOSITORY_H
