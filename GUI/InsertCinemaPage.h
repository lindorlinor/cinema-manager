#ifndef INSERTCINEMAPAGE_H
#define INSERTCINEMAPAGE_H
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "Custom/InsertImageFrame.h"
#include "../Cinema.h"
#include "../DataFiles/CinemaRepositoryJson.h"

/**
 * @brief Pagina di inserimento di un nuovo cinema
 *
 * @details I campi dati sono:
 * - frameLayout che rappresenta il layout centrale della pagina (contiene tutto),
 * - textInput per inserire il nome del cinema,
 * - imageArea di tipo @ref InsertImageFrame::InsertImageFrame per inserire l'immagine,
 * - imagePath che memorizza il percorso scelto dall'utente per inserire l'immagine (il path viene inserito nell'xml quindi se ci si passa i
 * file xml i percorsi dell'immagine devonoe essere gli stessi). Ha un path per l'immagine di default all'inizio
 * - imageLabel che contiene l'immagine e viene mostrata solo quando c'è abbastanza spazio nella finestra
 * - errorLabel che appare solo se il nome per il cinema non è disponibile
 * - escButton
 * - saveButton che è non-clickable quando il nome nella textLabel non è disponibile tra quelli permessi (quindi anche quando vuota)
 *   - isAvailable serve per gestire la logica di "nome non disponibile" e saveButton non-clickable
 * - hasCostumeImage serve per poter mandare un messaggio di informazione che l'immagine inserita sarà di default se non selezionata
 * @see @ref InsertImageFrame::InsertImageFrame
 *
 * @note si potrebbe miglirare la cosa dei percorsi dell'immagine...cosa succede se i percorsi cambiano e/o le immagini
 * non vengono trovate?? immagine di default obv!
 * @note ci sono un po di commenti da togliere nel .cpp
 *
 */
class InsertCinemaPage : public QWidget
{
    Q_OBJECT
private:
    QList<Cinema *> &ic_cinema;
    QVBoxLayout *frameLayout;
    QLineEdit *textInput;        // per il nome del cinema
    InsertImageFrame *imageArea; // per inserire l'immagine
    QString imagePath;           // path dell'immagine che viene inserito nel json quando si clicca su salva
    QLabel *imageLabel;

    QLabel *errorLabel; // messaggio nome non disponibile

    // due pulsanti per uscire e salvare rispettivamente
    QPushButton *escButton;
    QPushButton *saveButton;

    bool hasCustomImage;
    bool isAvailable;

    void checkCinemaNameAvailability(const QString &text);
    void createHeader();
    void createSplitView();
    void createLayoutInput(QVBoxLayout *layoutdx);
    void createButtonLayout(QVBoxLayout *layoutdx);

public:
    explicit InsertCinemaPage(QList<Cinema *> &w_cinema, QWidget *parent = nullptr);
    void saveCinemaInJson();
    void reset();
    void resizeEvent(QResizeEvent *event) override;

public slots:
    void chooseImage();
    void removeImage();
signals:
    void returnCinemaSelectionPage();
};
#endif // INSERTCINEMAPAGE_H