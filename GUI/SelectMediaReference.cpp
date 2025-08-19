#include "SelectMediaReference.h"

SelectMediaReference::SelectMediaReference(const QString& tipo, QWidget *parent):QWidget(parent), currentSelected(nullptr){
    QFile file(QDir(QCoreApplication::applicationDirPath()).filePath("../FileJson/" + tipo + ".json"));

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "File non trovato, creo un file vuoto:" << file.fileName();

        if (file.open(QIODevice::WriteOnly)) {
            file.write("[]");
            file.close();
        } else {
            qWarning() << "Impossibile creare il file:" << file.errorString();
            return;
        }
            
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "Impossibile aprire il file neanche dopo averlo creato:" << file.errorString();
            return;
        }
    }
    
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    if (!doc.isArray()) return;
    QJsonArray media = doc.array();

    // Scroll area
    QWidget* container = new QWidget;
    container->setMinimumSize(300,400); 
    QVBoxLayout* layout = new QVBoxLayout(container);
    layout->addSpacerItem(new QSpacerItem(20, 400, QSizePolicy::Minimum, QSizePolicy::Expanding));
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true); 
    scrollArea->setMinimumSize(300, 400);  
    scrollArea->setWidget(container);
    
    MediaFrame* currentSelected = nullptr;

    // Creazione dei widget per ciascun media (film o podcast)
    for (const auto& m : media) {
        QJsonObject obj = m.toObject();
    
        QString titolo = obj["titolo"].toString();
        QString autore = obj["autore"].toString();
        QString imagePath = obj["path"].toString();
        MediaFrame* mediaframe = new MediaFrame(titolo, imagePath, autore, container);
    
        layout->addWidget(mediaframe);

        connect(mediaframe, &MediaFrame::selected, this, [this](MediaFrame* f){
            if (this->currentSelected) 
                this->currentSelected->setSelected(false);
            this->currentSelected = f;
            this->currentSelected->setSelected(true);
            emit mediaSelected(f);
        });

    }

    container->setLayout(layout);
}

void SelectMediaReference::setSelectFalse() {
    if (currentSelected) {
        currentSelected->setSelected(false);
        currentSelected = nullptr;
    }
}

    