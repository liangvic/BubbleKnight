
#ifndef POPPER_H
#define POPPER_H

/* Popper class is a subclass of the QGraphicsItem class as well as the enemy class*/
#include <QGraphicsItem>
#include "npc.h"
/* Popper class definition */
class Popper : public NPC{
    public:
        Popper(); // Popper constructor
        ~Popper(); // Popper destructor
        QRectF boundingRect() const; // Popper boundaries
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // Draw popper

    protected:
        void advance(int step); // Move Popper

};

#endif
