#ifndef MEDIALIBRARYGENERALE_H
#define MEDIALIBRARYGENERALE_H

#include <QWidget>

class MediaLibraryGenerale: public QWidget{

    private:

    
    public:
    explicit MediaLibraryGenerale(QWidget* parent = nullptr);
    void getFiltro(const QString& filtro);

};

#endif //MEDIALIBRARYGENERALE_H