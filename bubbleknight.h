
#ifndef BubbleknightKNIGHT_H
#define BubbleknightKNIGHT_H

/* Bubbleknightknight class is a subclass of the QGraphicsItem class */
#include <QGraphicsItem>
#include <QKeyEvent>

/* Bubbleknightknight class definition */
class Bubbleknight : public QGraphicsItem {
    public:
        Bubbleknight(); // Bubbleknight constructor
        QRectF boundingRect() const; // Bubbleknight boundaries
        void getBigger(); // Increase Bubbleknight size and Bubbleknight boundaries
        void getSmaller(); // Decrease Bubbleknight size and Bubbleknight boundaries
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); // Draw Bubbleknight
        int getHP();
        void setHP(int newHP);
        void increaseMaxSpeed();

    protected:
        void advance(int step); // Move Bubbleknight
        void keyPressEvent(QKeyEvent* event); // Determine what Bubbleknight does when keys are pressed
        void keyReleaseEvent(QKeyEvent *);          //helps for smoother movement

    private:
        int increase; // Used in getBigger();
        int HP;
        float speed, maxSpeed; // Used to determine speed/maxSpeed of Bubbleknight
        bool keepLeft, keepRight, keepDown, keepUp;

};
#endif
