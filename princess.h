#ifndef PRINCESS_H
#define PRINCESS_H
#include "stalker.h"
#include <QGraphicsItem>

class Princess: public Stalker
{
    public:
        Princess();
        ~Princess();
        QRectF boundingRect() const; // Princess boundaries
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // Draw NPC

    protected:
        void advance(int i);

};

#endif // PRINCESS_H
