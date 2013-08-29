/*********************************************************************************
  File Name: Creepwecpp
  Description: Qt Game Bubbleknight Game - Creeper Class Implementation File
  Game Base by: Yulu Luo
  Modified by: Victoria Liang
  Assignment: CSCI 102 Homework 3

*********************************************************************************/
#include "creeper.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <math.h>

Creeper::Creeper()
{
    type = 'c';
    setPos(-350, pow(-1, (qrand()% 2))*(qrand()% 250));     //random position of left edge
    xdirection = qrand()% 3 + 1;        //random speed in x direction
    ydirection = pow(-1, (qrand()% 2))*(qrand()% 2);
            size = qrand()%60 + 20;     //random size!
}

Creeper::~Creeper()
{}

QRectF Creeper::boundingRect() const {
    return QRectF(-50, -50, size, size); // Return Creeper boundary parameters
}

void Creeper::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::black);
    painter->drawEllipse(-50, -50, size, size);
    painter->setPen(Qt::black);
    painter->setBrush(Qt::gray);
    painter->drawEllipse(-50, -50, size/2, size/2);
}

void Creeper::advance(int step){
    setPos(mapToParent(xdirection, ydirection));
}
