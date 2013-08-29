#ifndef STALKER_H
#define STALKER_H
#include "npc.h"
#include <QGraphicsItem>

class Stalker: public NPC
{
public:
    Stalker();
    ~Stalker();
    QRectF boundingRect() const; // Stalker boundaries
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // Draw NPC
    void setyDirection(float d);       //set y direction movement
    void setxDirection(float d);    //set x direction movement
    int getBulletTimer();       //return time to next launch
    void givepLoc(float x, float y);

protected:
    virtual void advance(int step);     //move
    float xdirection, ydirection;
    int bulletTimer;
    float pxloc, pyloc;

};

#endif // Stalker_H






