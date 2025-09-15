#ifndef MEDIAVIEW_H
#define MEDIAVIEW_H
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "../Custom/CustomMessageBox.h"
#include "DetailPageVisitor.h"
#include "../Custom/ExpandableLabel.h"
#include "../Custom/DetailsPageButtons.h"
#include "../../Media.h"

class MediaView : public QWidget
{
    Q_OBJECT

public:
    explicit MediaView(Media *mediaPtr, QWidget *parent = nullptr);

protected:
    Media *mediaPtr;         // puntatore al Media
    QVBoxLayout *layoutPage; // tutto il layout
    QWidget *splitter;       // crea le due parti della schemata: sinistra e destra
    QHBoxLayout *splitterLayout;
    QWidget *leftSide; // parte sinistra che contiene la copertina del film e i dettagli
    QHBoxLayout *leftLayout;
    QFrame *details;            // frame dettagli
    QVBoxLayout *detailsLayout; // layout frame dettagli
    QLabel *endDateLabel;       // questa si trova qui per permettere la visualizzazione del cambiamento della data quando si clicca su "Estendi data"
    QWidget *rightSide;         // parte destra che contiene la/l sezione/i scrollable
    QVBoxLayout *rightLayout;
    QWidget *card;
    QVBoxLayout *cardLayout;
    DetailsPageButtons *buttons;

    QLabel *copertina;
    QLabel *inizioP;
    QLabel *incasso;
    QLabel *risoluzione;
    QLabel *formato;
    ExpandableLabel *descrizione;
    QLabel *visualizzazioni;

    void createHeader();
    void createMediaCard();
    void createRowDetails();
    void updateRowDetails();

    void resizeEvent(QResizeEvent *event) override;

private:
    QWidget *box;
    QLabel *regista;
    QLabel *durata;
    QLabel *lingue;
    QLabel *sottotitoli;
    QLabel *titolo;
    QLabel *statusLabel;
    QLabel *textLabel;
    void updateMediaCard();
    void updateHeader();

    // metodi di create che i figli devono overridare
    virtual void createMediaDetails() = 0;
    virtual void createScrollableSection() = 0;
    virtual void createButtons() = 0;

    // metodi di update che i figli devono overridare
    virtual void updateMediaDetails() = 0;
    virtual void updateScrollableSection() = 0;

signals:
    void editMediaClicked(Media *mPtr);       // segnale emesso quando cliccato sull'icona di modifica media
    void extendMediaClicked();                // segnale emesso dopo aver confermato l'estensione del media
    void deleteMediaClicked(Media *mPtr);     // sengale emesso dopo aver confermato l'eliminazione del media
    void returnButton();                      // segnale emesso quando cliccato il pulsante "Torna indietro"
    void requestMediaView(MediaView &widget); // segnale emesso quando cliccato su un altro media all'interno della pagina (p.es trailer correlato)

public slots:
    virtual void update(); // metodo di update virtuale, i figli overridano richiamando i metodi di update per i loro campi privati

private slots:
    virtual void extendMediaMessage() = 0;
    virtual void deleteMediaMessage() = 0;
};

#endif // MEDIAVIEW_H
