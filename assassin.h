#ifndef ASSASSIN_H
#define ASSASSIN_H
#include "stalker.h"

class Assassin: public Stalker
{
    public:
        Assassin();
        ~Assassin();
        QRectF boundingRect() const; // Princess boundaries
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // Draw NPC

    protected:
        void advance(int i);

};

#endif // ASSASSIN_H
