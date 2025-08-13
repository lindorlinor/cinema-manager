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

template<class L, class T>
void AddMedia::addEnumList(L* base, const QString& labelText, const std::vector<T>& items, QListWidget*& listWidget){
    QLabel* label = new QLabel(labelText);
    listWidget = new QListWidget(this);

    //lista degli enum
    for (T e : items) {
        const char* str = toString(e);
        if (QString::fromUtf8(str) == "Non trovato") {
            continue; // salto quelli con stringa "Non trovato"
        }
        QListWidgetItem* item = new QListWidgetItem(QString::fromUtf8(str), listWidget);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        item->setData(Qt::UserRole, static_cast<int>(e));
    }

    addInput(label, base, listWidget);
}

//tab Base

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

    addInput(label, baseH, combo);

    connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index){
        updateTabTipologia(index);
    });
}

void AddMedia::updateTabTipologia(int index){
    stackTipologia->setCurrentIndex(index);
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
    label->setAlignment(Qt::AlignTop);
    addInput(label, baseH, spin);
}

void AddMedia::addTipologia(QHBoxLayout* baseH){
    stackTipologia = new QStackedLayout;

    TipoFilm = new QWidget;
    TipoTrailer = new QWidget;
    TipoInserzione = new QWidget;
    TipoPodcast = new QWidget;
    TipoPuntata = new QWidget;

    stackTipologia->addWidget(TipoFilm);
    stackTipologia->addWidget(TipoTrailer);
    stackTipologia->addWidget(TipoInserzione);
    stackTipologia->addWidget(TipoPodcast);
    stackTipologia->addWidget(TipoPuntata);

    stackTipologia->setCurrentIndex(0);

}

//tab Descrizione

void AddMedia::addDescrizione(QHBoxLayout* baseH){
    QLabel* label = new QLabel("Descrizione");
    QTextEdit* textEdit = new QTextEdit(this);
    textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textEdit->setFixedSize(300,200);
    textEdit->setStyleSheet("margin-bottom: 10px;");
    addInput(label, baseH, textEdit);
}

//tab Tipologia

//tipologia Film



void AddMedia::addAttori(){
    QLineEdit* inputAttore = new QLineEdit(this);
    QPushButton* aggiunti = new QPushButton("+",this); 
    QPushButton* rimuovi = new QPushButton("Rimuovi selezionati",this);
    QListWidget* listAttori = new QListWidget(this);
    
    QHBoxLayout* layoutH = new QHBoxLayout;
    QVBoxLayout* layoutV = new QVBoxLayout;

    layoutH->addWidget(inputAttore);
    layoutH->addWidget(aggiunti);

    layoutV->addLayout(layoutH);
    layoutV->addWidget(listAttori);
    layoutV->addWidget(listAttori);

    
}

//aggiunta dei Tab

void AddMedia::addBase(QWidget* base){
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
    addEnumList(baseH2, "Lingue", tutteLeLingue(), listLingue);
    addEnumList(baseH2, "Sottotitoli", tutteLeLingue(), listSottotitoli);
    widget2->setLayout(baseH2);
    
    baseV->addWidget(widget1,2);
    baseV->addWidget(widget2,2);
    
    base->setLayout(baseV);
}

void AddMedia::addDescrizione(QWidget* descrizione){
    QVBoxLayout* descrizioneV = new QVBoxLayout;
    QHBoxLayout* descrizioneH = new QHBoxLayout;
    QWidget* widget = new QWidget;

    addEnumList(descrizioneV, "Formato", tuttiIFormati(), listFormato);
    addEnumList(descrizioneV, "Risoluzione", tutteLeRisoluzioni(), listRisoluzione);
    widget->setLayout(descrizioneV);
    descrizioneH->addWidget(widget);
    addDescrizione(descrizioneH);
    descrizione->setLayout(descrizioneH);
}

void AddMedia::addTab(QHBoxLayout* layout){
    QTabWidget* tab = new QTabWidget(this);
    tab->setFixedSize(500,300);
    
    QWidget* base = new QWidget;
    QWidget* descrizione = new QWidget;
    QWidget* tipologia = new QWidget;
    
    addBase(base);
    addDescrizione(descrizione);

    tab->addTab(base, "Informazioni Base");
    tab->addTab(descrizione, "Descrizione");

    layout->addWidget(tab,2);
}

//pulsante indietro

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

//funzione per salvare gli input in un json

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

void AddMedia::addPagina(QVBoxLayout* mainLayout){
    QLabel* titolo = new QLabel("Aggiungi un elemento alla libreria");
    widgetPath = new PathButton;
    QVBoxLayout* sinistra = new QVBoxLayout();
    QHBoxLayout* layout = new QHBoxLayout();
    QWidget* widgetSinistra = new QWidget();
    QWidget* widgetLayout = new QWidget();

    QFont font = titolo->font();
    font.setPointSize(14);
    font.setBold(true);
    titolo->setFont(font);

    sinistra->addWidget(titolo);
    sinistra->addWidget(widgetPath);
    widgetSinistra->setLayout(sinistra);
    layout->addWidget(widgetSinistra);
    addTab(layout);
    widgetLayout->setLayout(layout);
    mainLayout->addWidget(widgetLayout);
}

AddMedia::AddMedia(QWidget *parent): QWidget(parent){
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0); 
    mainLayout->setSpacing(0);
    
    indietro(mainLayout);
    addPagina(mainLayout);
    
    setLayout(mainLayout);
}