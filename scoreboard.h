#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <vector>
#include "user.h"
#include <fstream>
class Scoreboard{

public:
    Scoreboard();
    ~Scoreboard();

    void importData();      //imports data from "db.txt" file
    void exportData();      //exports data to "dbout.txt" file
    bool checkFriends();   //checks imported data

    /* first level menu functions */
    void deleteAccount();   //deletes user account
    void addAccount();      //adds user account
    void listHighscores();  //prints sorted list of users/scores
    bool loggedOn();        //prompts for username and returns true if successful

    void LOffMenu();        //first level menu
    void LOnMenu();         //logged on menu

    /* 2nd level menu functions - accessible only if logged in*/
    void setScore(int score);   //sets score for currently logged in user
    void listAllUsers();        //lists all users
    void addFriend();           //add friend
    void deleteFriend();        //delete friend
    void sortFriendScores();    //sort friend's scores and printa
    void findShortestPath();    //find shortest path to user
    void printPath(User* target);           //BFS that prints route to user

    bool isAlphanum(string c);  //checks username
    void updateNums();          //updates user/ relationships counts
    int getnumUsers();          //returns number of users

    void quicksortScores(vector<User*>& list);  //sorts users by scores
    void quicksorthelper(vector<User*>& list, int left, int right);  //helper funciotn

protected:
    vector<User*> users;        //list of users
    int numUsers;               //number of users
    int numRelations;           //number of relations
    int year, highscore;        //universally used variables for placeholding
    int ID;
    string name;
    User* current;              //current user

    bool isCorrupt, isDuplicate;    //for ID and name checking
    ifstream fin;                   //file input stream
    ofstream fout;                  //file output stream

};

#endif
