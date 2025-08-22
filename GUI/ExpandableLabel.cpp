#include "ExpandableLabel.h"

ExpandableLabel::ExpandableLabel(const QString& fullText, QWidget* parent)
    : QLabel(parent), fullText(fullText), expanded(false) 
{
    setWordWrap(true);
    setTextFormat(Qt::RichText);
    setTextInteractionFlags(Qt::TextBrowserInteraction);
    setOpenExternalLinks(false); // importante per intercettare il click
    connect(this, &QLabel::linkActivated, this, &ExpandableLabel::onLinkActivated);

    updateText();
}


void ExpandableLabel::onLinkActivated(const QString&) {
    expanded = !expanded;
    updateText();
}

void ExpandableLabel::updateText() {
    if (expanded) {
        setText(fullText + " <a href=\"#\"><u>mostra meno</u></a>");
    } else {
        // tronca a due righe
        QFontMetrics fm(font());
        int maxWidth = this->width() > 0 ? this->width() : 300; // fallback

        QString truncated = fm.elidedText(fullText, Qt::ElideRight, maxWidth * 2); 

        if (truncated != fullText) {
            // Se il testo è stato troncato, mostra "...leggi tutto"
            setText(truncated + " <a href=\"#\"><u>...leggi tutto</u></a>");
        } else {
            // Altrimenti mostra il testo completo senza link
            setText(fullText);
        }
    }
}

void ExpandableLabel::resizeEvent(QResizeEvent* event) {
    QLabel::resizeEvent(event);
    if (!expanded) updateText(); // ricalcola il truncation se la label cambia dimensione
}
