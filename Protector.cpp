/*********************************************************************************
  File Name: Protectorcpp
  Description: Qt Game Bubbleknight Game - Protector Class Implementation File
  Game Base by: Yulu Luo
  Modified by: Victoria Liang
  Assignment: CSCI 102 Homework 3

*********************************************************************************/

#include "Protector.h"
#include <math.h>
#include <QString>
#include <QPainter>
#include <QApplication>
#include "linkedlist.h"
#include <QTime>
#include <iostream>

/* Protector constructor */
Protector::Protector() {
    gameStarted = false;
    gameOver = true;
    easymode = false;
    gameEnd = false;
    HP = 5, numSaved = 0;
    /* Convert score and HPs to QStrings for printing */
    sHP = QString::number(HP);
    snumSaved = QString::number(numSaved);
    /* Define instructions as QGraphicsTextItems and store in array */
    instructions[0] = new QGraphicsTextItem("BUBBLEKNIGHT");
    instructions[1] = new QGraphicsTextItem("You are a noble knight of Bubbleland.   Save the pink Princess bubbles!");
    instructions[2] = new QGraphicsTextItem("Use the Arrow Keys to Rotate Left/Right and Speed Up/Slow Down");
    instructions[3] = new QGraphicsTextItem("Green bubbles = +MaxSpeed                   Blue bubbles = +Size and +HP ");
    instructions[4] = new QGraphicsTextItem("Blue Pins (Look like || ) = -Size                 ");
    instructions[5] = new QGraphicsTextItem("You'll have a chance to grab upgrades before each princess-saving round");
    instructions[6] = new QGraphicsTextItem("(Press 'E' to activate easy mode) SPACE TO BEGIN");

    /* Print instructions */
    instructions[0]->setPos(-70, -180);
    addItem(instructions[0]);
    instructions[1]->setPos(-250, -100);
    instructions[2]->setPos(-250, -50);
    instructions[3]->setPos(-250, 0);
    instructions[4]->setPos(-250, 30);
    instructions[5]->setPos(-250, 80);
    instructions[6]->setPos(-170, 110);
    for (int i = 1; i <= 6; i++)
        addItem(instructions[i]);


    /* Define game stats as QGraphicsTextItems and store in array */
    stats[0] = new QGraphicsTextItem("HP: ");
    stats[1] = new QGraphicsTextItem(sHP);
    stats[2] = new QGraphicsTextItem("Princesses Saved: ");
    stats[3] = new QGraphicsTextItem(snumSaved);

    /* Define the position for the items */
    stats[0]->setPos(-380, -280);
    stats[1]->setPos(-335, -280);
    stats[2]->setPos(-400, -260);
    stats[3]->setPos(-280, -260);

    /* Define and position the game over text */
    endText = new QGraphicsTextItem("GAME OVER...PRESS 'SPACE' TO RESTART");
    endText1 = new QGraphicsTextItem("PRESS 'S' TO SENDSCORE");

    endText->setPos(-170, 0);
    endText1->setPos (-170, 250);
}

void Protector::reset(){
    /* Initialize conditions */
    if (bubbleknight != NULL)
    {
        delete bubbleknight;
        bubbleknight = NULL;
    }
    gameStarted = false;
    gameOver = true;
    easymode = false;
    gameEnd = false;
    HP = 5, numSaved = 0;
    /* Convert score and HPs to QStrings for printing */
    sHP = QString::number(HP);
    snumSaved = QString::number(numSaved);

    /* Print instructions */
    for (int i = 0; i <= 6; i++)
        addItem(instructions[i]);
}

/* Protector destructor */
Protector::~Protector() {
    delete bubbleknight;
    delete endText;
    delete endText1;
    clearGameLists();
    for (int i = 0; i < 7; i++)
        delete instructions[i];
    for (int i = 0; i < 4; i++)
        delete stats[i];
}
/* add npc based on selection*/
void Protector::addNPC(char npc){
    switch (npc)
    {
        case 'w':
            npcs.push_front(new Stalker);
            break;
        case 'p':
            npcs.push_front(new Popper);
            break;
        case 'r':
            npcs.push_front(new Princess);
            break;
        case 'u':
            npcs.push_front(new Stupidwallgun);
            break;
        case 'c':
            npcs.push_front(new Creeper);
            break;
        case 'i':
            npcs.push_front(new Assassin);
            break;
    }
    addItem(npcs.at(0));
}



void Protector::manageItems(){
    /* always have items to eat! */
    if (timer%50 == 0 && items.size() < 10)
    {
            if (qrand()*100 > 25)
            {
                items.push_front(new Food);
                addItem(items.at(0));
            }
            if (qrand()*100 < 25)
            {
                items.push_front(new Pin);
                addItem(items.at(0));
            }
            if (qrand()*100 < 25)
            {
                items.push_front(new Speed);
                addItem(items.at(0));
            }
    }
    for(int i = 0; i< items.size(); i++)    //delete items when time has passed
        if (!items.at(i)->isActive())
        {
            removeItem(items.at(i));
            items.erase(i);
        }

}

void Protector::clearGameLists(){
    while(!npcs.empty())        //clear list for npcs
    {
        removeItem(npcs.at(0));
        npcs.erase(0);
    }
    while (!items.empty())
    {
        removeItem(items.at(0));    //clear list for items
        items.erase(0);
    }

}

void Protector::upgradelevel()
{
    manageItems();

    if (timer == 1)     // Position poppers in a circle around the bubbleknight (center)
    {
        setBackgroundBrush(QBrush(Qt::yellow, Qt::Dense5Pattern)); // Make the background a happy yellow color

    for (int i = 0; i < 5; i++)                 //poppers in a ring!
        addNPC('p');
    for (int i = 0; i < 5; i++)
        npcs.at(i)->setPos(::sin((i*6.28)/5)*200, ::cos((i*6.28)/5)*200);
    }

    if (timer %100 == 0)        //add another popper!
        addNPC('p');

    if (timer == 800)      //you only get 800 cycles to grab upgrades
    {
        timer = 0;
        clearGameLists();
        isUpgradeLevel = false;
        princessPresent = false;
    }

}

void Protector::level1()
{
    if (timer == 1)
    {
        setBackgroundBrush(QBrush(Qt::gray, Qt::Dense5Pattern));
        for (int i = 0; i < 3; i++)
        {
            addNPC('u');                //add some wallguns onto the left side of the screen
            addNPC('u');
            npcs.at(0)->setPos(-390,  i*100);
            npcs.at(1)->setPos(-390,  -i*100);
        }
        for (int i = 0; i < 3; i++)
        {
            addNPC('u');
            addNPC('u');                    //add some wallguns onto the top edge of the screen
            npcs.at(0)->setPos(i*200, -290);
            static_cast<Stupidwallgun*>(npcs.at(0))->setShotdir('u');
            npcs.at(1)->setPos(-i*200, -290);
            static_cast<Stupidwallgun*>(npcs.at(1))->setShotdir('u');
        }
    }


    if (!princessPresent && timer > 100)       //if the princess isn't there, add another one!
    {
        addNPC('r');
        princessPresent = true;
    }

    for (int i = 0; i < npcs.size(); i++)
    {
        Stalker* stalker = static_cast<Stalker*>(npcs.at(i));
        int pxloc = bubbleknight->scenePos().x();
        int pyloc = bubbleknight->scenePos().y();

        int xloc = npcs.at(i)->scenePos().x();
        int yloc = npcs.at(i)->scenePos().y();

            if ( stalker->getType() == 'r')          //give player location
             stalker->givepLoc(pxloc, pyloc);

            if (stalker->getType() == 'u' && stalker->getBulletTimer()%200 == 0)
            {
                 Stupidwallgun* gun = static_cast<Stupidwallgun*>(npcs.at(i));
                 if (gun->getShotdir() == 'l')                      //shoots bullet to the right
                npcs.push_front(new Shot(xloc, yloc, 2, 0));
                 else if (gun->getShotdir() == 'u')                 //shoots bullet downwards
                    npcs.push_front(new Shot(xloc, yloc, 0, 2));
                addItem(npcs.at(0));

            }

    }

    if (numSaved == level*3)      //save 2 Princesses and move onto the next level!
    {
        timer = 0;
        clearGameLists();
        level++;
        isUpgradeLevel = true;
    }

}

void Protector::level2()
{
    int pxloc = bubbleknight->scenePos().x();
    int pyloc = bubbleknight->scenePos().y();

    if (timer == 1)
    {
        setBackgroundBrush(QBrush(Qt::blue, Qt::Dense5Pattern)); // Make the background a happy yellow color
    }
    if (timer %20 == 0)
        addNPC('c');

    if (!princessPresent && timer > 100)       //if the princess isn't there, add another one!
    {
        addNPC('r');
        princessPresent = true;
    }

    for (int i = 0; i < npcs.size(); i++)
    {
        Stalker* stalker = static_cast<Stalker*>(npcs.at(i));

        int xloc = npcs.at(i)->scenePos().x();
        int yloc = npcs.at(i)->scenePos().y();

        if ( stalker->getType() == 'r')          //give player location
         stalker->givepLoc(pxloc, pyloc);

            stalker = NULL;

    }

    if (numSaved == level*3)      //save 3 more prncesses and win!!
    {
        timer = 0;
        clearGameLists();
        level++;
        isUpgradeLevel = true;
    }

}


void Protector::level3(){
    if (timer==1)        //add 6 wallguns to the level
    {
        setBackgroundBrush(QBrush(Qt::red, Qt::Dense5Pattern)); // Make the background red spotted!
        for (int i = 0; i < 5; i++)
        {
            addNPC('u');
            addNPC('u');
            npcs.at(0)->setPos(i*75, -290);
            static_cast<Stupidwallgun*>(npcs.at(0))->setShotdir('u');       //put some wallguns on the screen
            npcs.at(1)->setPos(-i*75, -290);
            static_cast<Stupidwallgun*>(npcs.at(1))->setShotdir('u');       //space em out
        }
        addNPC('w');
    }

    if (!princessPresent && timer > 100)       //if the princess isn't there, add another one!
    {
        addNPC('r');
        princessPresent = true;
    }

    for (int i = 0; i < npcs.size(); i++)
    {
        int pxloc = bubbleknight->scenePos().x();       //get player location
        int pyloc = bubbleknight->scenePos().y();

        Stalker* stalker = static_cast<Stalker*>(npcs.at(i));
        char type = stalker->getType();
        int xloc = stalker->scenePos().x();       //get player location
        int yloc = stalker->scenePos().y();

        if (type == 'r' || type == 'w' || type =='u')
            stalker->givepLoc(pxloc, pyloc);

            if (type == 'u' && stalker->getBulletTimer()%200 == 0)
            {
                  npcs.push_front(new Shot(xloc, yloc, 0, 2));      //normal wallguns shoot slowly
                  addItem(npcs.at(0));
            }
            else
            if (type == 'w' && stalker->getBulletTimer()%200 ==0) //stalker shoots fast bullet
            {
                  npcs.push_front(new Shot(xloc, yloc, 5, 0));
                  addItem(npcs.at(0));
            }

    }

    if (numSaved == level*3)      //save 3 more Princesses and move onto the next level!
    {
        timer = 0;
        clearGameLists();       //clear out npcs and itesm
        level++;
        isUpgradeLevel = true;      //go to upgradelevel!
    }

}

void Protector::level4(){
    int pxloc = bubbleknight->scenePos().x();
    int pyloc = bubbleknight->scenePos().y();

    if (timer == 1)
    {
        setBackgroundBrush(QBrush(Qt::green, Qt::Dense5Pattern)); // Make the background a happy yellow color
        addNPC('i');
    }

    if (timer%100 == 0 && timer < 200)
        addNPC('i');

    if (timer%50 == 0)
        addNPC('c');

    if (!princessPresent && timer > 100)       //if the princess isn't there, add another one!
    {
        addNPC('r');
        princessPresent = true;
    }

    for (int i = 0; i < npcs.size(); i++)
    {
        Stalker* stalker = static_cast<Stalker*>(npcs.at(i));

        int xloc = npcs.at(i)->scenePos().x();
        int yloc = npcs.at(i)->scenePos().y();
        char type =  stalker->getType();
        if (type == 'r' || type =='i')          //give player location
         stalker->givepLoc(pxloc, pyloc);

            stalker = NULL;

    }

    if (numSaved == level*3)      //save 3 more prncesses and win!!
    {
        timer = 0;
        clearGameLists();
        level++;
        gameOver = true;
        delete endText;
        endText = new QGraphicsTextItem("You won. GJ :D       Press 'S' to sendscore");
       endText->setPos(-170, 0);            //ending!
        addItem(endText);
    }

}

void Protector::timerEvent(QTimerEvent *event) {
    if (!gameOver)
    {
    checkCollision(); // Check for collision between bubbleknight and any objects

    if (isUpgradeLevel)
    {
        upgradelevel();
    }
    else
    {
        switch (level)
        {
            case 1:
                level1();
                break;
            case 2:
                level2();
                break;
            case 3:
                level3();
                break;
            case 4:
                level4();
                break;
        }
    }
    if (HP > 0)
    {
        /* Update stats*/
        sHP = QString::number(HP);
        delete stats[1];
        stats[1] = new QGraphicsTextItem(sHP);
        stats[1]->setPos(-335, -280);

        snumSaved = QString::number(numSaved);
        delete stats[3];
        stats[3] = new QGraphicsTextItem(snumSaved);
        stats[3]->setPos(-280, -260);

    addItem(stats[1]);
    addItem(stats[3]);
    }

    timer++;
    }
}

/* Determine what happens when a key is pressed */
void Protector::keyPressEvent(QKeyEvent* event) {
    switch(event->key()) {
        case Qt::Key_Space: // Space starts the game
            if (!gameStarted || gameOver)
            {
                startGame();
            }
            break;
        case Qt::Key_E:
            if (!gameStarted)
                easymode = true;
            break;
        case Qt::Key_S: // S ends the game
        if (gameOver)
            {
            gameEnd = true;
            qApp->closeAllWindows();
             }
            break;
        default:
            QGraphicsScene::keyPressEvent(event);
    }
}

//second and beyond instances
void Protector::restartGame(){
    removeItem(endText); // Remove game over text
    removeItem(endText1);
    gameOver = false; // Game has restarted

}

/* Tasks to start game */
void Protector::startGame() {
    /* If restarting the game */
    if (gameOver == true)
    {
        if (gameStarted == false)
        {
            for (int i = 0; i <= 6; i++)
                removeItem(instructions[i]); // Remove instructions
            gameStarted = true;
        }
        restartGame();

    for (int i = 0; i < 4; i ++)
        addItem(stats[i]); // Print stats

    bubbleknight = new Bubbleknight; // Create a bubbleknight
    addItem(bubbleknight); // Add bubbleknight created in new game
    setFocusItem(bubbleknight); // Key presses control the bubbleknight
    if (easymode)
    {
        bubbleknight->setHP(30);
        for (int i = 0; i < 3; i++)
            bubbleknight->increaseMaxSpeed();
    }
    timerID = startTimer(1000/33); // Start the timer
    qsrand (QTime::currentTime().msec());
    level = 1;
    numSaved = 0;
    timer = 0;   /* Reset timer*/
    princessPresent = false, isUpgradeLevel = true;
    }

}

/* Tasks to stop game */
void Protector::stopGame()
{
    clearGameLists();
    killTimer(timerID); // Stop the timer

    removeItem(bubbleknight);
    gameOver = true; // Game has ended
    princessPresent = true;
    addItem(endText); // Display game over text
    addItem(endText1);
    setBackgroundBrush(QBrush(Qt::white, Qt::Dense5Pattern)); // Make the background a happy yellow color
    for (int i = 0; i < 4; i++)
        removeItem(stats[i]);
}

void Protector::checkItemCollision()
{
    /* If bubbleknight collides with food */
    for (int i = 0; i< items.size(); i++)
    if (bubbleknight->collidesWithItem(items.at(i), Qt::IntersectsItemBoundingRect)) {
        Item* check = items.at(i);
        if (check->getType() == 'f')    //food
        {
            bubbleknight->getBigger(); // Make bubbleknight bigger
            bubbleknight->setHP(bubbleknight->getHP()+1);
        }
        if (check->getType() == 'p')    //pin
            bubbleknight->getSmaller(); //Make bubbleknight smaller
        if (check->getType() == 's')    //speed
            bubbleknight->increaseMaxSpeed();
        check = NULL;
        removeItem(items.at(i));
        items.erase(i);
    }
}

void Protector::checkNPCCollision()
{
        NPC* check;
    for (int i = 0; i < npcs.size(); i++) {
        check = npcs.at(i);
        if (bubbleknight->collidesWithItem(check, Qt::IntersectsItemBoundingRect))
        {
            if (check->getType() == 'p' || check->getType() == 's' || check->getType() == 'c')
            {
            bubbleknight->setHP(bubbleknight->getHP()-1); // Lose a life
            removeItem(npcs.at(i));
            npcs.erase(i);
            }

            if (check->getType() == 'r')        //check if collision with princess
            {
                numSaved++;
                princessPresent = false;
                removeItem(npcs.at(i));
                npcs.erase(i);
            }

            if (check->getType() == 'i')
            {
                bubbleknight->setHP(bubbleknight->getHP()-1); // Lose a life
                removeItem(npcs.at(i));
                npcs.erase(i);
                addNPC('i');                //add a new assasin
            }
        }

        if (check->isOutOfBounds())         //check if npc has passed screen border
        {
            if (check->getType() == 'r')
                princessPresent = false;
            if (check->getType() == 'i')
                check->setPos(0, 0);
            removeItem(npcs.at(i));
            npcs.erase(i);
        }
    }
     check = NULL;
}

/* Check for collision between bubbleknight and other items in scene */
void Protector::checkCollision() {
    checkItemCollision();
    checkNPCCollision();

        HP = bubbleknight->getHP();
        if (HP < 1)
            stopGame();

}

int Protector::sendScore(){
    if (easymode)
        return numSaved *7;
   return numSaved*100;
}
