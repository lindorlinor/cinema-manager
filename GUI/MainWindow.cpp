#include "MainWindow.h"
#include "CinemaSelectionPage.h"
#include "InsertCinemaPage.h"
#include "SearchPanel.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), cinemaPage(new CinemaSelectionPage(w_cinema, this)), insertPage(new InsertCinemaPage(w_cinema, this)),
                                          m_xmlManager(new MediaManagerXml()), m_jsonManager(new CinemaRepositoryJson()),
                                          searchPage(new SearchPanel(m_jsonManager, m_xmlManager, this))
{
    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint |
                   Qt::WindowMinimizeButtonHint |
                   Qt::WindowMaximizeButtonHint |
                   Qt::WindowCloseButtonHint);

    QVBoxLayout *layoutV = new QVBoxLayout;
    QWidget *central = new QWidget(this);
    Menu *menu = new Menu(this);

    stackedWidget = new QStackedWidget(this);
    layoutV->addWidget(menu);
    layoutV->addWidget(stackedWidget);
    central->setLayout(layoutV);

    setCentralWidget(central);
    resize(800, 500);

    connect(cinemaPage, &CinemaSelectionPage::insertCinema, this, &MainWindow::showInsertCinemaPage);
    connect(cinemaPage, &CinemaSelectionPage::selectedCinema, this, &MainWindow::showSelectedCinemaPage);
    connect(cinemaPage, &CinemaSelectionPage::selectedCinema, searchPage, &SearchPanel::updateInfoCinema);
    connect(cinemaPage, &CinemaSelectionPage::selectedCinema, this, &MainWindow::showFullScreen);

    connect(insertPage, &InsertCinemaPage::returnCinemaSelectionPage, this, &MainWindow::showCinemaSelectionPage);

    connect(menu, &Menu::setNormalRequest, this, &MainWindow::showNormal);
    connect(menu, &Menu::setMaximizeRequest, this, [this]()
            {
        if (windowState() & Qt::WindowFullScreen) {
            showMaximized();
        } else {
            showFullScreen();
        } });

    connect(stackedWidget, &QStackedWidget::currentChanged, this, [menu](int index)
            {
        if(index == 0 || index == 1) {
            menu->setFileActionEnabled(0,false);
            menu->setFileActionEnabled(1,false);
            menu->setFileActionEnabled(2,false);
            menu->setFileActionEnabled(4,false);
            menu->setFileActionEnabled(5,false);
        }else{
            menu->setFileActionEnabled(0,true);
            menu->setFileActionEnabled(1,true);
            menu->setFileActionEnabled(2,true);
            menu->setFileActionEnabled(4,true);
            menu->setFileActionEnabled(5,true);
        } });

    connect(stackedWidget, &QStackedWidget::currentChanged, this, [menu, this](int index)
            {
        if(index == 0 || index == 1) {
            menu->setModifierActionEnabled(0,false);
            menu->setModifierActionEnabled(1,false);
            menu->setModifierActionEnabled(2,false);
        }else{
            menu->setModifierActionEnabled(0,true);
            menu->setModifierActionEnabled(1,true);
            menu->setModifierActionEnabled(2,true);
        } });

    connect(stackedWidget, &QStackedWidget::currentChanged, this, [menu](int index)
            {
        if(index == 0 || index == 1) {
            menu->setViewActionEnabled(0,false);
            menu->setViewActionEnabled(1,false);
            menu->setViewActionEnabled(2,false);
            menu->setViewActionEnabled(3,false);
            menu->setViewActionEnabled(4,false);
        }else{
            menu->setViewActionEnabled(0,true);
            menu->setViewActionEnabled(1,true);
            menu->setViewActionEnabled(2,true);
            menu->setViewActionEnabled(3,true);
            menu->setViewActionEnabled(4,true);
        } });

    connect(stackedWidget, &QStackedWidget::currentChanged, this, [menu](int index)
            {
        if(index == 0 || index == 1) {
            menu->setViewActionEnabled(0,false);
        }else{
            menu->setViewActionEnabled(0,true);
        } });

    connect(menu, &Menu::closeRequested, this, &MainWindow::close);
    /* connect(menu,&Menu::backToCinemaSelection,searchPage,&SearchPanel::removeMediaView); */
    connect(menu, &Menu::addMedia, searchPage, &SearchPanel::acceptAddMedia);
    connect(menu, &Menu::viewFilm, searchPage, &SearchPanel::acceptViewFilm);
    connect(menu, &Menu::viewTrailer, searchPage, &SearchPanel::acceptViewTrailer);
    connect(menu, &Menu::viewInserzioni, searchPage, &SearchPanel::acceptViewInserzione);
    connect(menu, &Menu::viewPodcast, searchPage, &SearchPanel::acceptViewPodcast);
    connect(menu, &Menu::viewPuntate, searchPage, &SearchPanel::acceptViewPuntata);

    connect(menu, &Menu::backToCinemaSelection, this, &MainWindow::showCinemaSelectionPage);
    connect(menu, &Menu::changeView, searchPage, &SearchPanel::acceptChangeView);
    connect(menu, &Menu::backToCinemaSelection, searchPage, &SearchPanel::resetSearchPanel);
    connect(menu, &Menu::setFullScreen, this, &MainWindow::showFullScreen);
    connect(menu, &Menu::escFullScreen, this, &MainWindow::showMaximized);
    connect(menu, &Menu::addMedia, searchPage, &SearchPanel::acceptAddMedia);
    connect(menu, &Menu::editCinema, searchPage, &SearchPanel::acceptEditCinema);
    connect(menu, &Menu::deleteCinema, searchPage, &SearchPanel::acceptDeleteCinema);
    connect(menu, &Menu::importMediaList, this, [this]()
            {
                m_xmlManager->importMediaListFromXml(*m_jsonManager);
                // searchPage->updateInfoCinema(m_xmlManager->getCurrentCinema());
                searchPage->updateMediaList();
                searchPage->updateFiltroTutto(); });
    connect(menu, &Menu::importSession, this, [this]()
            {
                                                m_xmlManager->importSessionFromXml(*m_jsonManager);
                                                m_jsonManager->loadCinema(w_cinema);
                                                cinemaPage->refreshCinemaButtons(); });
    connect(menu, &Menu::exportMediaList, this, [this]()
            { m_xmlManager->exportMediaListToXml(); });
    connect(menu, &Menu::exportSession, this, [this]()
            { m_xmlManager->exportSessionToXml(); });

    connect(searchPage, &SearchPanel::deleteCinemaInSearchPanel, this, &MainWindow::deleteCinemaFromList);
    connect(searchPage, &SearchPanel::escSearchPanel, this, &MainWindow::showCinemaSelectionPage);
    connect(searchPage, &SearchPanel::escSearchPanelAfterDeleteCinema, this, &MainWindow::showCinemaSelectionPage);
    connect(searchPage, &SearchPanel::escSearchPanel, searchPage, &SearchPanel::resetSearchPanel);
    connect(searchPage, &SearchPanel::setQMenuEnabled, this, [menu, this]()
            {   if(stackedWidget->currentIndex() == 2) menu->setOtherActionEnabled(0,true); 
                else menu->setOtherActionEnabled(0,false); });
    connect(searchPage, &SearchPanel::setQMenuDisabled, this, [menu]()
            { menu->setOtherActionEnabled(0, false); });
    connect(searchPage, &SearchPanel::deleteCinema, this, [this]()
            {
        /* debug perchè non capivo perchè non si aggiornasse nel json ma il metodo non aggiorna il json veramente ciao
        qDebug() << "aggiorna il json perchè ho chiamato la funzione";
        qDebug() << QString::fromStdString(w_cinema[2]->getNomeCinema());
        qDebug() << w_cinema[2]->getListaMedia().size();
        for (Media* media : w_cinema[2]->getListaMedia()) {
            qDebug() << QString::fromStdString(media->getTitolo()) << " " << QString::fromStdString(dateToString(media->getDataFineRilascio()));
        } */
        m_jsonManager->deleteCinemaInJson(w_cinema); });

    stackedWidget->addWidget(cinemaPage);
    stackedWidget->addWidget(insertPage);
    stackedWidget->addWidget(searchPage);
    stackedWidget->setCurrentIndex(0);
    central->show();

    QDir dir(QCoreApplication::applicationDirPath());
    dir.cdUp(); // Da /release → [PROJECT_ROOT]

    // style
    menu->setObjectName("menuWidget");
    central->setObjectName("central");
    layoutV->setContentsMargins(0, 0, 0, 0);
    layoutV->setSpacing(0);

    QFile file(dir.filePath("GUI/style.qss"));
    if (file.open(QFile::ReadOnly))
    {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
        file.close();
        qDebug() << "Style sheet applicato correttamente.";
    }
    else
        qDebug() << "Impossibile aprire il file style.qss";
}

void MainWindow::showInsertCinemaPage()
{
    insertPage->reset();
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::showSelectedCinemaPage()
{
    stackedWidget->setCurrentIndex(2);
}
void MainWindow::showCinemaSelectionPage()
{

    searchPage->deleteViewPages();

    if (cinemaPage)
    {
        cinemaPage->refreshCinemaButtons();
    }
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::deleteCinemaFromList(Cinema *cinema)
{
    if (w_cinema.removeOne(cinema))
    {
        delete cinema;
        cinema = nullptr;
    }
    m_jsonManager->deleteCinemaInJson(w_cinema);
}