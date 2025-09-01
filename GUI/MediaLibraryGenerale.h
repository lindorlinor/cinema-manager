#ifndef MEDIALIBRARYGENERALE_H
#define MEDIALIBRARYGENERALE_H

#include <QList>
#include <QHBoxLayout>
#include "LibraryObserver.h"
#include "UpdateMediaLibrary.h"


class MediaLibraryGenerale: public UpdateMediaLibrary, public LibraryObserver{
    Q_OBJECT
    private:

    const QString filtro;
    QLabel* titolo;
    
    public:
    explicit MediaLibraryGenerale(const QString& filtro, QWidget* parent = nullptr);
    virtual void update(int comboAttivita, int comboOrdinamento, const QString& filtro, const QString& ricerca, QList<Media*>& mediaList) override;

};

#endif //MEDIALIBRARYGENERALE_H