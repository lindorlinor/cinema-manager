#include "MediaLibraryGenerale.h"

MediaLibraryGenerale::MediaLibraryGenerale(const QString &filtroBottone, QWidget *parent) : UpdateMediaLibrary(parent), filtro(filtroBottone)
{

    titolo = new QLabel(filtroBottone + " in Sala", this);
    titolo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    container = new QWidget(this);
    FlowLayoutContainer = new FlowLayout(this);
    container->setLayout(FlowLayoutContainer);

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(container);

    setPreferredLayout(FlowLayoutContainer);

    mainLayout->addWidget(titolo);
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);

    // style
    FlowLayoutContainer->setAlignment(Qt::AlignTop);
    titolo->setStyleSheet("color: #fed36a; font-size: 18pt; font-weight: bold;");
    scrollArea->setStyleSheet("QScrollArea QWidget{"
                              "border-radius: 10px;"
                              "background-color: #073c47;"
                              "border: none}"
                              "QScrollArea{"
                              "background: transparent;}"
                              "QScrollBar:vertical {"
                              "background: #05313c;"
                              "width: 12px;"
                              "margin: 0px;"
                              "border-radius: 5px;"
                              "border: 1px solid #05313c;}"
                              "QScrollBar::handle:vertical {"
                              "background: #4e7f8b;"
                              "min-height: 20px;"
                              "border-radius: 5px;}"
                              "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
                              "width: 0px;"
                              "height: 0px;"
                              "subcontrol-origin: margin;"
                              "subcontrol-position: none;}"
                              "QScrollBar::add-line:vertical:hover, QScrollBar::sub-line:vertical:hover {"
                              "background: #05313c;}");
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MediaLibraryGenerale::update(const bool &view, int comboAttivita, int comboOrdinamento, const QString &filtro, const QString &ricerca, QList<Media *> &mediaList)
{
    QString prefisso;
    for (const auto &f : allFiltri)
    { // recupero del prefisso a seconda del filtro ("Film","Inserzioni" etc) ; -> "Tutte le inserzioni, Tutti i film"
        if (f.first == filtro)
        {
            prefisso = f.second;
            break;
        }
    }

    if (comboAttivita == 0)
        titolo->setText(filtro + " in Sala");
    else if (comboAttivita == 1)
        titolo->setText(filtro + " fuori produzione");
    else
        titolo->setText(prefisso + filtro);

    UpdateMediaLibrary::update(view, comboAttivita, comboOrdinamento, filtro, ricerca, mediaList);
}