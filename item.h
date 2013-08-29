
#ifndef ITEM_H
#define ITEM_H

/* Item class is a subclass of the QGraphicsItem class */
#include <QGraphicsItem>

/* Item class definition */
class Item : public QGraphicsItem {
    public:
        Item(); // Item constructor
        ~Item(); // Item destructor
        virtual QRectF boundingRect() const; // Item boundaries
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){}; // Draw Item
        char getType();     //return type of item
        bool isActive();    //check if it's supposed to be on or not
    protected:
        char type;
        int lifespan;       //time until erase
        void advance(int step);
    private:
};

#endif
