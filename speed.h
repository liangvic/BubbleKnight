#ifndef SPEED_H
#define SPEED_H
#include "item.h"

class Speed: public Item
{
    public:
        Speed();
        ~Speed();
        QRectF boundingRect() const; // Speed boundaries
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        virtual char getType(){};
    protected:

};

#endif // SPEED_H
