#ifndef LIBRARYOBSERVER_H
#define LIBRARYOBSERVER_H

#include <QString>

class LibraryObserver{
    private:
    public:
        virtual ~ LibraryObserver () = default ;
        virtual void update (int comboAttivita, int comboOrdinamento, const QString& filtroBottone, const QString& ricerca) = 0;

};

#endif //LIBRARYOBSERVER_H