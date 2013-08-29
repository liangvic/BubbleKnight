
#include "item.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <math.h>

/* Superclass for all static items*/
/* Item constructor */
Item::Item() {
    lifespan = 100;
    setRotation(180);
    setPos(pow(-1, (qrand()% 2))*(qrand()% 390), pow(-1, (qrand()% 2))*(qrand()% 290)); // Position the Item randomly on the screen, but not too close to the edge
}

/* Item destructor */
Item::~Item() {}

/* Item boundaries */
QRectF Item::boundingRect() const {
    return QRectF(-5, -5, 10, 10);
}

bool Item::isActive(){
    if (lifespan > 0)
        return true;
    return false;
}

void Item::advance(int step){
    lifespan--;
}

char Item::getType()
{
    return type;
}

