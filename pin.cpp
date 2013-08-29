#include "pin.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

Pin::Pin()
{
    lifespan = 400;
    type = 'p';
    setPos(qrand()%300 - 275, qrand()%200 - 275); // Position the Item randomly on the screen, but not too close to the edge
}

Pin::~Pin()
{}

QRectF Pin::boundingRect() const {
    return QRectF(-1, -10, 1, 20);
}

/* Draw Item */
void Pin::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setPen(Qt::blue); // Make the pin blue
    QPainterPath path1(QPointF(-1, -10));
    QPainterPath path2(QPointF(1, -10));
    path1.lineTo(-1, 10);
    path2.lineTo(1, 10);
    painter->drawPath(path1);
    painter->drawPath(path2);

}
