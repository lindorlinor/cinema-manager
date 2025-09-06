#include "HorizontalCard.h"

HorizontalCard::HorizontalCard(const Media& media, QWidget* parent): QFrame(parent){

    QVBoxLayout* layoutV = new QVBoxLayout; 
    QHBoxLayout* layoutH = new QHBoxLayout();
    QWidget* widget = new QWidget(this);  

    QLabel* imgLabel = new QLabel(this);
    QLabel* titolo = new QLabel(this);
    QLabel* autore = new QLabel(this);
    QLabel* durata = new QLabel(this);
    QLabel* visualizzazioni = new QLabel(this);
    QLabel* lingue = new QLabel(this);
    QLabel* sottotitoli = new QLabel(this);

    titolo->setWordWrap(true);
    autore->setWordWrap(true);
    lingue->setWordWrap(true);
    sottotitoli->setWordWrap(true);

    QPixmap pix(QString::fromStdString(media.getImPath()));
    imgLabel->setPixmap(pix.scaled(450,270, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imgLabel->setContentsMargins(0,0,0,0);
    imgLabel->setAlignment(Qt::AlignCenter);
    imgLabel->setStyleSheet("border:none");

    //creazione label lingue
    std::vector<Lingua> lingueDisponibili = media.getLingue();
    QString lingueText;
    for (size_t i = 0; i < lingueDisponibili.size(); ++i) {
        lingueText += QString::fromUtf8(toString(lingueDisponibili[i]));
        if (i != lingueDisponibili.size() - 1) {
            lingueText += ", ";
        }
    }

    //creazione label sottotitoli
    std::vector<Lingua> sottotitoliDisponibili = media.getSottotitoli();
    QString sottotitoliText;
    for (size_t i = 0; i < sottotitoliDisponibili.size(); ++i) {
        sottotitoliText += QString::fromUtf8(toString(sottotitoliDisponibili[i]));
        if (i != sottotitoliDisponibili.size() - 1) sottotitoliText += ", ";
    }

    titolo->setText("<span style='color: #bdced3; font-weight:bold; font-size: 12pt;'>Titolo: </span>""<span style='color: #bdced3; font-size: 12pt;'>"+QString::fromStdString(media.getTitolo())+"</span>");
    autore->setText("<span style='color: #bdced3; font-weight:bold; font-size: 12pt;'>Autore: </span>""<span style='color: #bdced3; font-size: 12pt;'>"+QString::fromStdString(media.getAutore())+"</span>");
    durata->setText("<span style='color: #bdced3; font-weight:bold; font-size: 12pt;'>Durata: </span>""<span style='color: #bdced3; font-size: 12pt;'>"+QString::number(media.getDurataMinuti())+" min </span>");
    visualizzazioni->setText("<span style='color: #bdced3; font-weight:bold; font-size: 12pt;'>Visualizzazioni: </span>""<span style='color: #bdced3; font-size: 12pt;'>"+QString::number(media.getVisualizzazioni())+"</span>");
    lingue->setText(
        "<span style='color: #bdced3; font-size: 12pt; font-weight:bold;'>Lingue: </span>"
        "<span style='color: #bdced3; font-size: 12pt;'>" + lingueText + "</span>");

    sottotitoli ->setText(
        "<span style='color: #bdced3;font-size: 12pt; font-weight:bold;'>Sottotitoli: </span>"
        "<span style='color: #bdced3; font-size: 12pt; '>" + sottotitoliText + "</span>");


    layoutV->addWidget(titolo);
    layoutV->addWidget(autore);
    layoutV->addWidget(durata);
    layoutV->addWidget(visualizzazioni);
    layoutV->addWidget(lingue);
    layoutV->addWidget(sottotitoli);
    widget->setLayout(layoutV);
    widget->setLayout(layoutV);
    layoutH->addWidget(imgLabel);
    layoutH->addWidget(widget);
    setLayout(layoutH);
    layoutH->setAlignment(Qt::AlignLeft);

    setStyleSheet("background-color: #05313c; border-radius: 10px; padding: 5px 12px;");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
 }

void HorizontalCard::mousePressEvent(QMouseEvent* event){
    emit selected();
    QFrame::mousePressEvent(event);
}