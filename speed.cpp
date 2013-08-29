#include "speed.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

Speed::Speed()
{
    type = 's';
    lifespan = 600;
}

Speed::~Speed()
{}


QRectF Speed::boundingRect() const {
    return QRectF(-5, -5, 10, 10);
}

/* Draw Item */
void Speed::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::green);
    painter->drawEllipse(-5, -5, 10, 10);
    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    painter->drawEllipse(-1, 2, 2, 2);
}

