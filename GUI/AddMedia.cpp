#include "AddMedia.h"
#include "SearchPanel.h"

template<class L, class T>
void AddMedia::addInput(QLabel* label,  L* layout, T* inputWidget){
    QWidget* widget = new QWidget; 
    QVBoxLayout* l = new QVBoxLayout(this);
    l->addWidget(label,1);
    l->addWidget(inputWidget,4);
    widget->setLayout(l);
    layout->addWidget(widget);
}

void AddMedia::addTitolo(QHBoxLayout* baseH){
    QLabel* label = new QLabel("Titolo");
    QLineEdit* lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText("Titolo");
    addInput(label, baseH, lineEdit);
}

void AddMedia::addTipologia(QHBoxLayout* baseH){
    QLabel* label = new QLabel("Tipologia");
    QComboBox* combo = new QComboBox(this);
    combo->addItem("Film");
    combo->addItem("Trailer");
    combo->addItem("Podcast");
    combo->addItem("Puntata");
    combo->addItem("Inserzione");

    // TO DO
    // connect(combo, &QComboBox::currentTextChanged, this, [](const QString& testo){
        
    // });
    addInput(label, baseH, combo);
}

void AddMedia::addLingua(QHBoxLayout* baseH, const QString& tipo){
    QLabel* label = new QLabel(tipo);

    if(tipo=="Lingue"){
        listLingue = new QListWidget(this);
        listLingue->setFixedSize(150,40);
    }
    else if(tipo=="Sottotitoli"){
        listSottotitoli = new QListWidget(this);
        listSottotitoli->setFixedSize(150,40);
    }
    else return;


    //lista degli enum
    std::vector<Lingua> lingue = tutteLeLingue();
    
    for (Lingua l : lingue) {
        const char* str = toString(l);
        if (QString::fromUtf8(str) == "Non trovato") {
            continue; // salto quelli con stringa "Non trovato"
        }
        QListWidgetItem* item = new QListWidgetItem(QString::fromUtf8(str), (tipo == "Lingue") ? listLingue : listSottotitoli);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        item->setData(Qt::UserRole, static_cast<int>(l));
    }

    addInput(label, baseH, (tipo=="Lingue")? listLingue: listSottotitoli);
}

void AddMedia::addAutore(QHBoxLayout* baseH){
    QLabel* label = new QLabel("Autore");
    QLineEdit* lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText("Autore");
    addInput(label, baseH, lineEdit);
}

void AddMedia::addDurata(QHBoxLayout* baseH){
    QLabel* label = new QLabel("Durata");
    QSpinBox * spin = new QSpinBox (this);
    spin->setRange(0,300);
    spin->setValue(0);
    addInput(label, baseH, spin);
}

void AddMedia::addTab(QVBoxLayout* mainLayout){
    QTabWidget* tab = new QTabWidget(this);
    tipologia = new QStackedLayout;
    tab->setFixedSize(500,300);
    
    QWidget* base = new QWidget;
/*     QWidget* descrizione = new QWidget;
    QWidget* tipologia = new QWidget; */
    
    QVBoxLayout* baseV = new QVBoxLayout;
    QHBoxLayout* baseH1 = new QHBoxLayout;
    QHBoxLayout* baseH2 = new QHBoxLayout;
    QWidget* widget1 = new QWidget;
    QWidget* widget2 = new QWidget;

    addTitolo(baseH1);
    addAutore(baseH1);
    addTipologia(baseH1);
    widget1->setLayout(baseH1);

    addDurata(baseH2);
    addLingua(baseH2, "Lingue");
    addLingua(baseH2, "Sottotitoli");
    widget2->setLayout(baseH2);

    baseV->addWidget(widget1,2);
    baseV->addWidget(widget2,2);

    base->setLayout(baseV);
    tab->addTab(base, "Informazioni Base");

    mainLayout->addWidget(tab,2);
}

void AddMedia::addInizio(QVBoxLayout* mainLayout){
    QLabel* titolo = new QLabel("Aggiungi un elemento alla libreria");
    widgetPath = new PathButton;
    QVBoxLayout* inizio = new QVBoxLayout();
    QWidget* inizioW = new QWidget();

    QFont font = titolo->font();
    font.setPointSize(14);
    font.setBold(true);
    titolo->setFont(font);

    inizio->addWidget(titolo);
    inizio->addWidget(widgetPath);
    inizioW->setLayout(inizio);
    mainLayout->addWidget(inizioW);
}

void AddMedia::indietro(QVBoxLayout* mainLayout){
    QHBoxLayout* bottone = new QHBoxLayout(this);
    QPushButton* indietro = new QPushButton("←");
    QWidget* indietroW = new QWidget;
    bottone->addWidget(indietro);
    bottone->setAlignment(Qt::AlignLeft);
    indietroW->setLayout(bottone);
    mainLayout->addWidget(indietroW);

    connect(indietro, &QPushButton::clicked, this, &AddMedia::tornaIndietro);
}

AddMedia::AddMedia(QWidget *parent): QWidget(parent){
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0); 
    mainLayout->setSpacing(0);

    indietro(mainLayout);
    addInizio(mainLayout);
    addTab(mainLayout);

    setLayout(mainLayout);
}

void AddMedia::salva(){

    //salva l'immagine
    

    //imposta le lingue selezionate
    for (int i = 0; i < listLingue->count(); ++i) {
        QListWidgetItem* item = listLingue->item(i);
        if (item->checkState() == Qt::Checked) {
            int val = item->data(Qt::UserRole).toInt();
            //aggiunge le lingue selezionate
            media->aggiungiLingua(static_cast<Lingua>(val));
        }
    }

    //imposta i sottotitoli selezionati
    for (int i = 0; i < listSottotitoli->count(); ++i) {
        QListWidgetItem* item = listSottotitoli->item(i);
        if (item->checkState() == Qt::Checked) {
            int val = item->data(Qt::UserRole).toInt();
            //aggiunge le lingue selezionate
            media->aggiungiSottotitolo(static_cast<Lingua>(val));
        }
    }
}