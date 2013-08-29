/*********************************************************************************
  File Name: Popper.cpp
  Description: Qt Game Bubbleknight Game - Popper Class Implementation File
  Game Base by: Yulu Luo
  Modified by: Victoria Liang
  Assignment: CSCI 102 Homework 3

*********************************************************************************/
#include "popper.h"
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

/* Popper constructor */
Popper::Popper() {
    angle = 0;
    speed = 0.001;
    NPCDirection = 0;
    setRotation(qrand() % (360 * 16)); // Set a random initial rotation so the poppers don't all go the same way
    type = 'p';
    setRotation(qrand() % (360 * 16)); // Set a random initial rotation so the NPCs don't all go the same way
}

/* Popper destructor */
Popper::~Popper() {}

/* Popper boundaries */
QRectF Popper::boundingRect() const {
    return QRectF(-5, -5, 10, 10);
}

/* Draw Popper */
void Popper::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    /* Popper looks like an x */
    QPainterPath path1(QPointF(-5, -5));
    QPainterPath path2(QPointF(5, -5));
    path1.lineTo(5, 5);
    path2.lineTo(-5, 5);
    painter->drawPath(path1);
    painter->drawPath(path2);
}

/* Move Popper */
void Popper::advance(int step) {

    /* Keep popper within a radius of 300 of the center by making it rotate and change direction when it gets to the edge of the screen */
    QLineF distanceFromCenter(QPointF(0, 0), mapFromScene(0, 0));
    int distx = distanceFromCenter.dx();
    int disty = distanceFromCenter.dy();
    if (distx > 350 || distx < -350 || disty > 100 || disty < -100) {
        qreal angleToCenter = ::acos(distanceFromCenter.dx() / distanceFromCenter.length());
        if (distanceFromCenter.dy() < 0)
            angleToCenter = TwoPi - angleToCenter;
        angleToCenter = normalizeAngle((Pi - angleToCenter) + Pi / 2);

        /* Angle left or right to go back depending on what the popper angle is*/
        if (angleToCenter < Pi && angleToCenter > Pi / 4) {
            angle += (angle < -Pi/2) ? 0.25 : -0.25;
        }
        else if (angleToCenter >= Pi && angleToCenter < (Pi + Pi / 2 + Pi / 4)) {
            angle += (angle < Pi/2) ? 0.25 : -0.25;
        }
    }
    else if (::sin(angle) < 0) {
        angle += 0.25;
    }
    else if (::sin(angle) > 0) {
        angle -= 0.25;
    }

    qreal dx = ::sin(angle) * 10;
   NPCDirection = (qAbs(dx / 5) < 1) ? 0 : dx / 5;

    /* Now actually change the rotation */
    setRotation(rotation() + dx);
    setPos(mapToParent(0, -(1 + sin(speed))));

}
