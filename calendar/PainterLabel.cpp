#include "PainterLabel.h"
#include <QDate>

void PainterLabel::paintEvent(QPaintEvent *event){
       Q_UNUSED(event);
       QPixmap pixmap(size());
       pixmap.fill(Qt::black);
       QPixmap tempix=pixmap;
       QPainter painter(this);
//       painter->save();
       painter.setPen(QColor(0, 160, 230));
//       painter->begin(&tempix);
//       painter.begin(&tempix);
       painter.drawPixmap(0,0,this->width(),this->height(),tempix);
       painter.drawText(tempix.rect(),Qt::AlignCenter,QDate::currentDate().toString("dd"));
       this->QLabel::setPixmap(pixmap);
       painter.end();
}

PainterLabel::PainterLabel(){
}
