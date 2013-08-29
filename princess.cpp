#include "princess.h"
/*********************************************************************************
  File Name: princess.cpp
  Description: Qt Game Bubbleknight Game - Princess Class Implementation File
  Game Base by: Yulu Luo
  Modified by: Victoria Liang
  Assignment: CSCI 102 Homework 3

*********************************************************************************/
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <math.h>

Princess::Princess()
{
    type = 'r';
    ydirection = 0;
    xdirection = 0;
    setPos(pow(-1, (qrand()% 2))*(qrand()% 150 +70), pow(-1, (qrand()% 2))*(qrand()% 100 +70));
    //set randomly on screen but closer to the middle than items would be
}

Princess::~Princess()
{}

QRectF Princess::boundingRect() const
{
    return QRectF(-5, -5, 15, 15);
}

void Princess::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::magenta); // Make the princess magenta!
    painter->drawEllipse(-5, -5, 15, 15);
    painter->setPen(Qt::black);
    painter->setBrush(Qt::white);
    painter->drawEllipse(-2, 3, 4, 4);
}

void Princess::advance(int step){
    xloc = scenePos().x();      //get npcs location
    yloc = scenePos().y();

    if (xloc < pxloc)
        setxDirection(-0.4);
    else
        setxDirection(0.4);             //moves away from player

    if (yloc < pyloc)
        setyDirection(-0.4);
    else
        setyDirection(0.4);

    setPos(mapToParent(xdirection, ydirection));
}
