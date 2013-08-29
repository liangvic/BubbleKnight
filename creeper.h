
#ifndef CREEPER_H
#define CREEPER_H

#include "stalker.h"
#include <QGraphicsItem>

class Creeper: public Stalker
{
    public:
        Creeper();
        ~Creeper();
        QRectF boundingRect() const; // Creeper boundaries
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // Draw NPC

    protected:
        void advance(int step);
};

#endif // TAIL_H
