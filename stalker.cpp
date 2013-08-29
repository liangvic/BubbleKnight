/*********************************************************************************
  File Name: stalker.cpp
  Description: Qt Game Bubbleknight Game - Stalker Class Implementation File
  Game Base by: Yulu Luo
  Modified by: Victoria Liang
  Assignment: CSCI 102 Homework 3

*********************************************************************************/
#include "stalker.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <math.h>

Stalker::Stalker()
{
    type = 'w';
    ydirection = 0;
    xdirection = 0;
    setPos(-390, pow(-1, static_cast<int>((qrand()% 2)))*(qrand()% 290));       //set position by default on left side of screen
    bulletTimer= qrand()%190;
    pxloc = 0;
    pyloc = 0;
}

Stalker::~Stalker()
{}

void Stalker::setyDirection(float d){
    ydirection = d;
}

void Stalker::setxDirection(float d){
    xdirection = d;
}

int Stalker::getBulletTimer(){
   return bulletTimer++;
}

QRectF Stalker::boundingRect() const {
    return QRectF(-10, -10, 20, 20); // Return Stalker boundary parameters
}

void Stalker::givepLoc(float x, float y){
    pxloc = x;
    pyloc = y;
}

void Stalker::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::gray); // Make the gun grey
    painter->drawEllipse(-10, -10, 20, 20); // gun body
    painter->setPen(Qt::black); // Make the highlight black
    painter->setBrush(Qt::white);
    painter->drawEllipse(-2, 3, 4, 4); // gun highlight
}

void Stalker::advance(int step){
    xloc = scenePos().x();      //get npcs location
    yloc = scenePos().y();

        if (pyloc > yloc)            //makes stalker follow player in y dir
            setyDirection(1);
        else
            setyDirection(-1);

        setPos(mapToParent(xdirection, ydirection)); // Move gun forward at speed
        bulletTimer++;

}

