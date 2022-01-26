#ifndef PAINTERLABEL_H
#define PAINTERLABEL_H

#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>

class PainterLabel:public QLabel{
public:
//    QPainter *painter;
    PainterLabel();
protected:
    void paintEvent(QPaintEvent *) override;
};

#endif // PAINTERLABEL_H
