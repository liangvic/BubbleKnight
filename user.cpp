#include "user.h"
#include <string>
#include <fstream>

using namespace std;

// initialize user
User::User(){
    name = "ZZZZ";
    ID = 00000000;
    year = 0;
    highscore = 0;
   // friends.push_back(0);
}

//return name
string User::getName(){
    return name;
}

//return ID
int User::getID(){
    return ID;
}

// return year
int User::getYear(){
    return year;
}

// return highscore
int User::getHighscore(){
    return highscore;
}

/* set name */
void User::setName(string newname){
    name = newname;
}

/* set user ID */
void User::setID( int newID){
    ID = newID;
}

/* set year */
void User::setYear (int newyear){
    year = newyear;
}

/* set highscore */
void User::setHighscore (int newhighscore){
    highscore = newhighscore;
}

/* add friend to friend's list */
void User::addfriend(int ID){
    friends.push_back(ID);
}

/*delete friend from friends list */
void User::deletefriend(int ID){
    for (int i = 0; i <friends.size(); i++)
    {
        if (ID == friends.at(i))
        {
            friends.at(i) = friends.at(friends.size()-1);
            friends.pop_back();
        }
    }
}

/* check if user is a friend */
bool User::isFriend(int ID){
    for (int i = 0; i <friends.size(); i++)
        if (friends.at(i) == ID)
            return true;
    return false;
}
