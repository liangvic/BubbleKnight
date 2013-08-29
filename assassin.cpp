#include "assassin.h"

/*********************************************************************************
  File Name: assasin.cpp
  Description: Qt Game Bubbleknight Game - Assasin Class Implementation File
  Game Base by: Yulu Luo
  Modified by: Victoria Liang
  Assignment: CSCI 102 Homework 3

*********************************************************************************/
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <math.h>

Assassin::Assassin()
{
    type = 'i';
    ydirection = 0;
    xdirection = 0;
    setPos(pow(-1, (qrand()% 2))*(qrand()% 90), pow(-1, (qrand()% 2))*(qrand()% 90));
    //set near the middle
}

Assassin::~Assassin()
{}


QRectF Assassin::boundingRect() const
{
    return QRectF(-5, -5, 20, 20);
}

void Assassin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::black); // Make the Assassin magenta!
    painter->drawEllipse(-5, -5, 20, 20);
    painter->setPen(Qt::black);
    painter->setBrush(Qt::red);
    painter->drawEllipse(-2, 3, 4, 4);
}

void Assassin::advance(int step){
    xloc = scenePos().x();      //get npcs location
    yloc = scenePos().y();

    if (bulletTimer%50 == 0)
    {
    if (xloc > pxloc)
        setxDirection(-1);
    else
        setxDirection(1);           //moves towards player

    if (yloc > pyloc)
        setyDirection(-1);
    else
        setyDirection(1);
    }

    setPos(mapToParent(xdirection, ydirection));
    bulletTimer++;
}
