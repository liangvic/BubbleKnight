
#ifndef Protector_H
#define Protector_H

#include <string>
#include "bubbleknight.h"
#include "popper.h"
#include "item.h"
#include "linkedlist.h"
#include "food.h"
#include "stalker.h"
#include "pin.h"
#include "shot.h"
#include "speed.h"
#include "princess.h"
#include "stupidwallgun.h"
#include "creeper.h"
#include "assassin.h"

/* Protector class is a subclass of the QGraphicsScene class */
#include <QGraphicsScene>
#include <QString>

/* Protector class definition */
class Protector : public QGraphicsScene {

    public:
        Protector(); // Protector constructor
        ~Protector(); // Protector destructor
        int sendScore(); //returns score to user
        void reset();
        bool gameEnd; //game is finished

    protected:
        void timerEvent(QTimerEvent *event); // Updates based on timerID
        void keyPressEvent(QKeyEvent *event); // Determines what happens when a key is pressed

        void startGame(); // Function to start game
        void newGame(); //for the first instance of the game
        void restartGame();
        void stopGame(); // Function to end game

        void checkCollision(); // Function to check for Bubble colliding into other objects
        void checkNPCCollision();   //check collision with NPC's
        void checkItemCollision();  //check collision with  items


        void addNPC(char npc);  //adds NPC of specific type
        void manageItems(); //manages statis objects during game
        void clearGameLists(); //clears Lists and screen of npcs and items

        void upgradelevel();    //brief respite and upgrading time
        void level1();
        void level2();
        void level3();
        void level4();

    private:
        bool gameStarted; // Game started flag
        QWidget *widget;

        bool gameOver; // Game over flag
        int timerID; // Used to trigger timerEvent();
        int timer; // game timer
        int HP; // Number of lives
        int level, numSaved; //number of pink bubbles caught
        bool princessPresent, isUpgradeLevel;
        bool easymode;

        QString Score; // score converted to a string
        QString sHP, snumSaved; // HP and numSaved converted to strings
        Bubbleknight *bubbleknight;
        LinkedList<NPC*> npcs;      //list of npcs        
        LinkedList<Item*> items;        //list of items

        QGraphicsTextItem *instructions[7]; // Array of QGraphicsTextItems that display instructions
        QGraphicsTextItem *stats[4]; // Array of QGRaphicsTextItems that display the score and lives
        QGraphicsTextItem *endText, *endText1; // Game over text

};

#endif
