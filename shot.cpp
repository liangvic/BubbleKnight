/*********************************************************************************
  File Name: shot.cpp
  Description: Qt Game Bubbleknight Game - Shot Class Implementation File
  Game Base by: Yulu Luo
  Modified by: Victoria Liang
  Assignment: CSCI 102 Homework 3

*********************************************************************************/
#include "shot.h"

#include <QStyleOption>
#include <QGraphicsScene>
#include <math.h>
#include <QPainter>

Shot::Shot(int x, int y, float xdir, float ydir)
{
    type = 's';
    xdirection = xdir;      //set right, left movement
    ydirection = ydir;
    setPos(x, y);
}

Shot::~Shot()
{}

char Shot::getType()
{
    return type;
}


void Shot::setxDirection(float d){      //new xspeed
    xdirection = d;
}

void Shot::setyDirection(float d){      //new yspeed
    ydirection = d;
}

QRectF Shot::boundingRect() const {
    return QRectF(-5, -5, 5, 5);
}

void Shot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::black);
    painter->drawEllipse(-5, -5, 5, 5);
    painter->setPen(Qt::gray);
    painter->setBrush(Qt::gray);
    painter->drawEllipse(-1, 2, 2, 2);
}

void Shot::advance(int step){
        setPos(mapToParent(xdirection, ydirection));
}
