#include "DetailPageVisitor.h"
#include <QVBoxLayout>
#include <QLabel>
#include "../Film.h"

DetailPageVisitor::DetailPageVisitor()
    : detailPage(nullptr)
{}

QWidget* DetailPageVisitor::getWidget() const {
    return detailPage;
}


void DetailPageVisitor::visit(Film* film) {
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);

    layout->addWidget(new QLabel(QString::fromStdString(film->getTitolo())));
    layout->addWidget(new QLabel("Durata: " + QString::number(film->getDurataMinuti()) + " min"));

    detailPage = page;
}
void DetailPageVisitor::visit(Trailer*) {}
void DetailPageVisitor::visit(Inserzione*) {}
void DetailPageVisitor::visit(Podcast*) {}
void DetailPageVisitor::visit(Puntata*) {}
