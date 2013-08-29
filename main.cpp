/*********************************************************************************
  File Name: main.cpp
  Description: Qt Game Bubbleknight Game - Main Function
  Author: Victoria Liang
  Assignment: CSCI 102 Homework 2

*********************************************************************************/

#include <iostream>
#include <fstream>
#include "Protector.h"
#include "scoreboard.h"
#include <QtGui> // To use QGraphicsScene and QGraphicsView

int main(int argc, char **argv) {
     Scoreboard scoreboard;

     scoreboard.importData();

    int userIndex = 0;
    bool loggedOn = false;

    /* first level menu */
        do{
        scoreboard.LOffMenu();
        char selection;
        cin>>selection;
        switch (selection){
        case '+':                                //add account
            scoreboard.addAccount();
            break;
        case '-':                                //delete account
            scoreboard.deleteAccount();
            break;
        case 'L':                                //log on
        case 'l':
            if (scoreboard.getnumUsers() > 0)
            {
            if (scoreboard.loggedOn())
                 loggedOn = true;
            }
            else
                cout<<"No Users \n";
            break;
        case 'H':                                //print sorted list of high scores
        case 'h':
            scoreboard.listHighscores();
            break;
        case 'Q':                                //quit game
        case 'q':
            scoreboard.exportData();
            return 0;
            break;
        default:
            cout<<"Bad Selection"<<endl;
        }

          /* Second level menu */
          while (loggedOn)
        {
            scoreboard.LOnMenu();
            char selection;
            cin>>selection;

            switch (selection){
            case 'U':           //list all users
            case 'u':
                scoreboard.listAllUsers();
                break;
            case 'A':       //add friend
            case 'a':
                scoreboard.addFriend();
                break;
            case 'D':       //delete friend
            case 'd':
                scoreboard.deleteFriend();
                break;
            case 'L':       //Logout
            case 'l':
                loggedOn = false;
                break;
            case 'S':       //sort friends by score
            case 's':
                scoreboard.sortFriendScores();
                break;
            case 'B':       //shortest path to user
            case 'b':
                scoreboard.findShortestPath();
                break;
            case 'H':       //highscore table
            case 'h':
                scoreboard.listHighscores();
                break;

            case 'P':           //playgame
            case 'p':
            {
                QApplication app(argc, argv);

                /* Create a Protector and set up the scene*/
                Protector protector;

                protector.setSceneRect(-200, -150, 400, 300); // Make the scene 800x600
                protector.setItemIndexMethod(QGraphicsScene::NoIndex); // Ideal indexing for dynamic scenes

                /* View the Bubbleknight Game scene in a window*/
                QGraphicsView view(&protector); // Create a window to view the Protector
                view.setWindowTitle("Protector"); // Title it "Protector"
                view.resize(800, 600); // Set the window a little bigger than the scene to account for GUI changes from Mac to Linux

                view.setRenderHint(QPainter::Antialiasing); // Smooth graphics
                view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate); // Redraw bounding rectangle changes (ideal for collision detection)
                /* Start QGraphicsItems Timer */
                QTimer timer;
                QObject::connect(&timer, SIGNAL(timeout()), &protector, SLOT(advance())); // Call the advance() function of the objects
                timer.start(1000/33); // Update at around 30fps

            view.show();
            app.exec();

            if (protector.gameEnd)              //if game ends, get endscore
            {
                int score  = 0;
                score = protector.sendScore();
                cout<<"Final score: " <<score<<endl;
                protector.reset();
                scoreboard.setScore(score);         //set current User's highscore
            }
            }
                break;
            default:
                cout<<"Bad Selection"<<endl;
            }


        }

}
         while (!loggedOn);


}

