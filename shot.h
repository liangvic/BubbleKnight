
#ifndef SHOT_H
#define SHOT_H

#include "npc.h"
#include <QGraphicsItem>

class Shot: public NPC
{
public:
    Shot(int x, int y, float xdir, float ydir);
    ~Shot();
    QRectF boundingRect() const; // Shot boundaries
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // Draw NPC
    char getType();     //return type
    void setxDirection(float d);    //set x-movement
    void setyDirection(float d);    //set y movement

protected:
    void advance(int step);
    float xdirection, ydirection;

};

#endif // SHOT_H

