/*********************************************************************************
  File Name: User class
  Description: Qt Game Bubbleknight Game - Player class 
  Assignment: CSCI 102 Homework 4

*********************************************************************************/

#ifndef USER_H
#define USER_H

#include <vector>
#include <string>

using namespace std;

class User{
public:
	User();
	~User(){};
    string getName();                       //return name
    int getID();                            //return ID
    int getYear();                          //return year
    int getHighscore();                     //return highscore
    void setName(string newname);           //set name
    void setID( int newID);                 //set ID
    void setYear (int newyear);             //set year
    void setHighscore (int newhighscore);   //set highscore
    void addfriend(int ID);                 //add friend
    void deletefriend(int ID);              //delete friend
    bool isFriend(int ID);                  //check if friend ID is in friend list

    vector<int> friends;                    //vector of friend's list

protected:
	string name;
    int ID;
	int year;
    int highscore;

};

#endif 
