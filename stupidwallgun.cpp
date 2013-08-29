/*********************************************************************************
  File Name: stupidwallgun.cpp
  Description: Qt Game Bubbleknight Game - Stupidwallgun Class Implementation File
  Game Base by: Yulu Luo
  Modified by: Victoria Liang
  Assignment: CSCI 102 Homework 3

*********************************************************************************/

#include "stupidwallgun.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <math.h>

Stupidwallgun::Stupidwallgun()
{
    type = 'u';
    ydirection = 0.4;
    xdirection = 0;
    shotdir = 'l';      //l = left to right, u = up to
}

Stupidwallgun::~Stupidwallgun()
{}

void Stupidwallgun::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::white); // Make the gun grey
    painter->drawEllipse(-10, -10, 20, 20); // gun body
    painter->setPen(Qt::black); // Make the highlight black
    painter->setBrush(Qt::white);
    painter->drawEllipse(-2, 3, 4, 4); // gun highlight
}
void Stupidwallgun::setShotdir(char a){
    shotdir = a;
    if (shotdir == 'u')                         //shoots up to down? then it moves left to right
      xdirection = 0.4, ydirection = 0;
    if (shotdir == 'l')
      xdirection = 0, ydirection = 0.4;     //shoots left to right? moves up and down
}

char Stupidwallgun::getShotdir(){
    return shotdir;
}

void Stupidwallgun::advance(int step){
    if (shotdir == 'u' )
    {
        if (scenePos().x() > 390)              // move along and bounce back on borders
                setxDirection(-0.4);
        else if (scenePos().x() < -390)
            setxDirection(0.4);
    }
    else
    if (shotdir == 'l')                     //move along and bounce back
    {
        if (scenePos().y() > 290)
                setyDirection(-0.4);
        else if (scenePos().y() < -290)
                setyDirection(0.4);
    }
        setPos(mapToParent(xdirection, ydirection)); // Move gun forward at speed
        bulletTimer++;
}

