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
    QLabel *titolo;
    QScrollArea *scrollArea;

public:
    explicit MediaLibraryGenerale(const QString &filtro, QWidget *parent = nullptr);
    virtual void update(const bool &view, int comboAttivita, int comboOrdinamento, const QString &filtro, const QString &ricerca, QList<Media *> &mediaList) override;
};

#endif // MEDIALIBRARYGENERALE_H