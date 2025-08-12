#ifndef AddMedia_H
#define AddMedia_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QString>
#include <QPixmap>
#include <QPushButton>
#include <QStandardPaths>
#include <QTabWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QListWidget>
#include <QSpinBox>
#include <QFont>

#include "PathButton.h"

#include "../Film.h"
#include "../Inserzione.h"
#include "../Trailer.h"
#include "../Podcast.h"
#include "../Puntata.h"

class AddMedia:public QWidget{
    Q_OBJECT

    private:
    QStackedLayout* tipologia;
    PathButton* widgetPath;
    QListWidget* listLingue;
    QListWidget* listSottotitoli;
    void addInizio(QVBoxLayout* mainLayout);
    void addTab(QVBoxLayout* mainLayout);
    void indietro(QVBoxLayout* mainLayout);
    Media* media;
    void salva();

    //campi da passare
    void addTitolo(QHBoxLayout* baseH);
    void addTipologia(QHBoxLayout* baseH);
    void addLingua(QHBoxLayout* baseH, const QString& tipo);
    void addAutore(QHBoxLayout* baseH);
    void addDurata(QHBoxLayout* baseH);
    void addDescrizione(QHBoxLayout* baseH);
    void addRisoluzione(QHBoxLayout* baseH);
    /* void addDataInizioRilascio();
    void addDataFineRilascio();
    
    //film
    void addTarget(); //anche Inserzione
    void addGenere();
    void addAttori();
    void addCasaProd();
    void addCostoBiglietto();

    //trailer
    void addNumeroProiezioni(); //anche Inserzione
    void addFilm();

    //inserzione
    void addAzienzaInserzionistica();
    void addCostoBaseProiez();
    void addFasceOrarie();

    //Podcast
    void addConduttore();

    //Puntate
    void addOspiti();
    void NumeroPubblicita();
    void Podcast(); */

    template<class L, class T>
    void addInput(QLabel* label,  L* layout, T* inputWidget);

    public:
	explicit AddMedia(QWidget *parent);

    signals:
    void tornaIndietro();

};

#endif //AddMedia_H