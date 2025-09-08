#ifndef EXPANDABLELABEL_H
#define EXPANDABLELABEL_H

#include <QLabel>

class ExpandableLabel : public QLabel {
    Q_OBJECT
public:
    ExpandableLabel(const QString& fullText, QWidget* parent = nullptr);
    void setText(const QString& text);
private slots:
    void onLinkActivated(const QString&);

private:
    QString fullText;
    bool expanded;

    void updateText();
    void resizeEvent(QResizeEvent* event) override;
};

#endif // EXPANDABLELABEL_H
