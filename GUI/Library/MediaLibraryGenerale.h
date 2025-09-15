#ifndef MEDIALIBRARYGENERALE_H
#define MEDIALIBRARYGENERALE_H

#include <QList>
#include <QHBoxLayout>
#include <QScrollArea>
#include "LibraryObserver.h"
#include "UpdateMediaLibrary.h"

class MediaLibraryGenerale : public UpdateMediaLibrary
{
    Q_OBJECT
private:
    const QString filtro;
    QScrollArea *scrollArea;

public:
    explicit MediaLibraryGenerale(const QString &filtro, QWidget *parent = nullptr);
};

#endif // MEDIALIBRARYGENERALE_H