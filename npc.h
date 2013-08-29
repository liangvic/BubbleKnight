#ifndef NPC_H
#define NPC_H

/* NPC class is a subclass of the QGraphicsItem class */
#include <QGraphicsItem>

/* NPC class definition */
class NPC : public QGraphicsItem {
    public:
        NPC(); // NPC constructor
        ~NPC(); // NPC destructor
        virtual QRectF boundingRect() const; // NPC boundaries
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){}; // Draw NPC
        char getType(); //return NPC type
        virtual void setDirection(float d){};
        bool isOutOfBounds();

    protected:
        virtual void advance(int step){}; // Move NPC
        char type; //type of NPC
        qreal angle; // Used to determine angle of NPC
        qreal speed; // Used to determine speed of NPC
        qreal NPCDirection; // Used to determine direction of NPC
        bool outOfBounds;   //checks if offscreen
        int size;
        float xloc, yloc;
};

#endif
