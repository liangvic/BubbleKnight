#ifndef FOOD_H
#define FOOD_H

#include "item.h"

class Food: public Item
{
public:
    Food();
    ~Food();
    QRectF boundingRect() const; // Item boundaries
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // Draw Item
    char getType();
};

#endif // FOOD_H
