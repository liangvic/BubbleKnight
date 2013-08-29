#ifndef PIN_H
#define PIN_H
#include <item.h>

class Pin: public Item
{
public:
    Pin();
    ~Pin();
    QRectF boundingRect() const; // Item boundaries
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // Draw Item
};

#endif // PIN_H
