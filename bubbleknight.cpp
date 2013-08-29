/*********************************************************************************
  File Name: Bubbleknight.cpp
  Description: Qt Game Bubbleknight Game - Bubbleknight Class Implementation File
  Game Base by: Yulu Luo
  Modified by: Victoria Liang
  Assignment: CSCI 102 Homework 3

*********************************************************************************/

#include "bubbleknight.h"
#include <math.h>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

/* Bubbleknight constructor */
Bubbleknight::Bubbleknight() {
    speed = 0; // Bubbleknight floats slowly at first
    maxSpeed = 1;
    increase = 4; // Some increase in size initially
    setRotation(180);
    QGraphicsItem::setFlags(this->flags() | QGraphicsItem::ItemIsFocusable); // Allow keyPress to focus on Bubbleknight
    HP = 5;

    keepLeft = false;
    keepRight = false;
    keepDown = false;
    keepUp = false;

}

/* Bubbleknight boundaries */
QRectF Bubbleknight::boundingRect() const {
    return QRectF(-(10 + increase), -(10 + increase), 2*(10 + increase), 2*(10 + increase)); // Define Bubbleknight boundaries as a function of initial parameters and increase
}

/* Increase Bubbleknight size and Bubbleknight boundaries */
void Bubbleknight::getBigger() {
    if (increase < 15)
    increase++; // get Bigger!
}

void Bubbleknight::getSmaller() {
    if (increase > 1)
    increase-=2; // get Smaller!
}

void Bubbleknight::increaseMaxSpeed(){
    if (maxSpeed <= 3)
    maxSpeed+= 0.25;        //increase maximum speed
}

void Bubbleknight::setHP(int newHP)
{
    HP = newHP;
}

int Bubbleknight::getHP(){
        return HP;
}
/* Draw Bubbleknight */
void Bubbleknight::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::cyan); // Make the Bubbleknight cyan
    painter->drawEllipse(-(10 + increase), -(10 + increase), 2*(10 + increase), 2*(10 + increase)); // Bubbleknight body
    painter->setPen(Qt::white); // Make the highlight white
    painter->setBrush(Qt::white);
    painter->drawEllipse(-(2 + increase/3), 3 + increase/3, 2*(2 + increase/3), 2*(2 + increase/3)); // Bubbleknight highlight
}

/* Move Bubbleknight */
void Bubbleknight::advance(int step) {
    if (keepUp)
    {
       if (speed <= maxSpeed) // Don't go too fast
            speed += 0.2; // Speed up little by little
    }
    if (keepDown)
    {
        if (speed >= -maxSpeed) // Don't go backwards too fast
            speed -= 0.2; // Slow down/reverse
    }

    if (keepLeft)
        setRotation(rotation() - 5); // Rotate left a little

    if (keepRight)
        setRotation(rotation() + 5); // Rotate right a little

    int x = scenePos().x();
    int y = scenePos().y();
    if (x < -390+increase || x > 390-increase || y < -290+increase || y > 290-increase)
    {
        if (x < -390+increase)
            setPos(-390+increase+1, y);         //don't mvoe off the map!
        else
        if (x > 390-increase)
            setPos(390-increase-1, y);

        if (y < -290+increase)
            setPos(x, -290+increase+1);
        else
        if (y > 290-increase)
            setPos(x, 290-increase-1);

    }
    else
    setPos(mapToParent(0, speed)); // Move Bubbleknight forward at speed



}

/* Determine what Bubbleknight does when a key is pressed */
void Bubbleknight::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
        case Qt::Key_Left:
            {
            keepLeft = true;
             }
            break;
        case Qt::Key_Right:
            {
            keepRight = true;
            }
            break;
        case Qt::Key_Up:
            {
            keepUp = true;
            }
            break;
        case Qt::Key_Down:
            {
            keepDown = true;
            }
            break;
        default:
            QGraphicsItem::keyPressEvent(event);
    }
}


//aids in making smoother movements
void Bubbleknight::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
    switch(event->key())
    {
        case Qt::Key_Left:
        {
            keepLeft = false;
            break;
        }
        case Qt::Key_Right:
        {
           keepRight = false;
           break;
        }
        case Qt::Key_Up:
        {
            keepUp = false;
            break;
        }
        case Qt::Key_Down:
        {
            keepDown = false;
            break;
        }
    }
    }
}
