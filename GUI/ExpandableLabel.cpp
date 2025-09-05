#include "ExpandableLabel.h"

ExpandableLabel::ExpandableLabel(const QString& fullText, QWidget* parent)
    : QLabel(parent), fullText(fullText), expanded(false) 
{
    setWordWrap(true);
    setTextFormat(Qt::RichText);
    setTextInteractionFlags(Qt::TextBrowserInteraction);
    setOpenExternalLinks(false);
    connect(this, &QLabel::linkActivated, this, &ExpandableLabel::onLinkActivated);

    updateText();
}


void ExpandableLabel::onLinkActivated(const QString&) {
    expanded = !expanded;
    updateText();
}

void ExpandableLabel::updateText() {
    if (expanded) {
        setText("<span style=\"color: #4e7f8b\">"+ fullText + "</span>"  "<a href=\"#\"><span style=\"color: #4e7f8b\"><b><u>mostra meno</u></b></span></a>");
    } else {
        QFontMetrics fm(font());
        int maxWidth = this->width() > 0 ? this->width() : 300;

        QString truncated = fm.elidedText(fullText, Qt::ElideRight, maxWidth * 2); 

        if (truncated != fullText) {
            setText("<span style=\"color: #4e7f8b\">"+truncated + "</span>" "<a href=\"#\"><span style=\"color: #4e7f8b\"><b><u>...leggi tutto</u></b></span></a>");
        } else {
            setText("<span style=\"color: #4e7f8b\">"+fullText+ "</span>");
        }
    }
}

void ExpandableLabel::resizeEvent(QResizeEvent* event) {
    QLabel::resizeEvent(event);
    if (!expanded) updateText();
}
