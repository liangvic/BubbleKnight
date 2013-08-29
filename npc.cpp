/*********************************************************************************
  File Name: NPC.cpp
  Description: Qt Game Bubbleknight Game - NPC Class Implementation File
  Game Base by: Yulu Luo
  Modified by: Victoria Liang
  Assignment: CSCI 102 Homework 3

*********************************************************************************/
#include "npc.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <math.h>

/* Define the constants Pi and TwoPi to be pi and 2*pi respectively */
static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

/* Make sure angle is between 0 and 2*pi */
static qreal normalizeAngle(qreal angle) {
    while (angle < 0) {
        angle += TwoPi;
    }
    while (angle > TwoPi) {
        angle -= TwoPi;
    }
    return angle;
}

/* NPC constructor */
NPC::NPC() {
    angle = 0;          //popper class uses anges, speed and Direction
    speed = 0.001;
    setPos(pow(-1, (qrand()% 2))*(qrand()% 390), pow(-1, (qrand()% 2))*(qrand()% 290));
    outOfBounds = false;
    xloc = scenePos().x();      //get npcs location
    yloc = scenePos().y();
}

/* NPC destructor */
NPC::~NPC() {}

/* NPC boundaries */
QRectF NPC::boundingRect() const {
    return QRectF(-5, -5, 10, 10);
}

char NPC::getType()
{
    return type;
}

bool NPC::isOutOfBounds(){
    int xpos = scenePos().x();       // npc out of bounds?
    int ypos = scenePos().y();
    if ( xpos < -400 || xpos > 400 || ypos > 300 || ypos < -300)
        return true;
    else
        return false;
}

