#include "food.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

Food::Food()
{
    type = 'f';
    lifespan = 400;
}

Food::~Food()
{}

QRectF Food::boundingRect() const {
    return QRectF(-5, -5, 10, 10);
}

/* Draw Item */
void Food::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::cyan);
    painter->drawEllipse(-5, -5, 10, 10);
    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    painter->drawEllipse(-1, 2, 2, 2);
}
