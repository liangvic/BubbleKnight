#include "scoreboard.h"
#include "user.h"
#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdio.h>
#include <ctype.h>

using namespace std;

Scoreboard::Scoreboard()
{
   current = NULL;                          //initialize variables
   numUsers = 0, numRelations = 0;
   name = "Namu";
   ID = 0;
   year = 0, highscore = 0;
   isDuplicate = false;             //flag for duplicates
   isCorrupt = false;               //flag for corrupt data
};

Scoreboard::~Scoreboard()
{
    for (int i=0; i<users.size(); i++)
    {
        delete (users.at(users.size()-1));          //free dynamically allocated space
        users.pop_back();
    }

}

/* log-in prompt */
bool Scoreboard::loggedOn(){
    updateNums();

    isCorrupt = true;
    cout<<"\n Please enter Username: ";
    cin>>name;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');             //if invalid username, clear
    }
    else
    {
        for (int i = 0; i < numUsers; i++)              //check for name in user list
            if ((users.at(i)->getName()) == name)       //if user exists
            {
                current = users.at(i);                      //set current user
                isCorrupt = false;
            }
    }

    if (isCorrupt)                          //if user does not exist or name entry failed, print error, return false for loggedIn
    {
        cout<<"Login Failed \n";
        return false;
    }
    return true;
}

/* delete existing user account */
void Scoreboard::deleteAccount(){
    isCorrupt = true;
    User* temp = new User;

    cout<<"\n Please enter name of user to delete: ";
    cin>>name;
    if (cin.fail())             //if name entry fails, set corruptdata flag
    {
    isCorrupt = true;
    cin.clear();
    }
    else
        for (int i = 0; i < numUsers; i++)
        {
            if ((users.at(i)->getName()) == name)           //if user found, delete it
            {
                temp = users.at(i);
                isCorrupt = false;
                if (numUsers > 1)
                    users.at(i)= users.at(users.size()-1);
                users.pop_back();
                delete temp;
                cout<<"User "<<name<<" has been deleted \n";
                break;
            }
        }
    if (isCorrupt)                                   //else print error message
        cout<<"User does not exist \n";

    updateNums();                               //update numUsers and numRelations to reflect changes in scoreboard data

}
/* add user account */
void Scoreboard::addAccount(){
    isCorrupt = false, isDuplicate = false;
    User* temp = new User;

    cout<<"\n Please enter new user's name: ";              //prompt for new username
    cin>>name;
    if (cin.fail())
    isCorrupt = true;
    else
    {
        for (int i = 0; i < numUsers; i++)      //check for duplicates
            if ((users.at(i)->getName()) == name)
                isDuplicate = true;

        if (isAlphanum(name))                   //validate username
            temp->setName(name);
        else
            isCorrupt = true;
    }

    cout<<"\n Please enter new user's ID (integer): ";
    cin>>ID;
    if (cin.fail())
    isCorrupt = true;
    else
    {
        for (int i = 0; i < numUsers; i++)      //check for duplicates
            if ((users.at(i)->getID()) == ID)
                isDuplicate = true;

        if (ID >= 1 && ID <= 1000000000)            //validate ID
         temp->setID(ID);
        else
            isCorrupt = true;
    }

    cout<<"\n Please enter new user's year in school (1-5): ";
    cin>>year;
    if (cin.fail())
    isCorrupt = true;
    else
    {
        if (year >= 1 && year <= 5)         //validate year
        temp->setYear(year);
        else
            isCorrupt = true;
    }

    if (isCorrupt || isDuplicate)                   //if data entered is corrupt or doesn't satisfy requirements, don't add new user
    {
        delete temp;
        if (isCorrupt)
        {
        isCorrupt = false;
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Data input was corrupt. Failed to add new user \n";
        }
        if (isDuplicate)
        {
            isDuplicate = false;                        //if user already exists, print error
            cout<<"User already exists. \n";
        }

    }
    else
    {
        users.push_back(temp);
        cout<<"New User '" <<name<<"'' Created \n ";
    }

    updateNums();

}

/* imports data from preset file */
void Scoreboard::importData(){
    users.clear();
    fin.open("db1.txt");
    isCorrupt = false;

    if (fin.fail())
        isCorrupt = true;           //check that file opened successfully
    else
    {

        fin>>numUsers;
        if (fin.fail())             //check for numUsers
        isCorrupt = true;

        while (!fin.eof())          //loop until end of file reached
        {


            User* temp = new User;

            fin>>ID;
            if (fin.fail() && fin.eof())                    //if end of file, break loop
            {
                isCorrupt = false;
                cout<<"File imported successfully \n";
                break;
            }

            if (fin.fail() || !(ID >= 1 && ID <= 1000000000))       //validate ID
            {                
            isCorrupt = true;
            delete temp;
            break;
            }
            else
                 temp->setID(ID);

            fin>>name;
            if (fin.fail() || !(isAlphanum(name)))          //validate name
            {
            isCorrupt = true;            
            delete temp;
            break;
            }
            else
                    temp->setName(name);

            fin>>year;
            if (fin.fail() || !(year >= 1 && year <= 5))            //validate year
            {
                cout<<"failed here2 \n";
            isCorrupt = true;
            delete temp;
            break;
            }
            else
                temp->setYear(year);

            fin>>highscore;
            if (fin.fail() || !(highscore >= 0))            //validate highscore
            {
            isCorrupt = true;
            delete temp;
            break;
            }
            else
                temp->setHighscore(highscore);

           fin.ignore(1, '\n');
                                       //read in list of unknown length of friends


           if (fin.peek() == '\n')
            {
                cout<<"no friends!"<<endl;
                fin.ignore(1, '\n');
            }
           else
            {
               // fin.putback(check);
           while (fin.peek() != '\n')
            {

                    int friendID;
                    fin>>friendID;

                    if (fin.fail())
                    {
                        cout<<"failed! \n";
                        isCorrupt = true;
                        delete temp;
                        break;
                    }
                    else
                    {
                        if (friendID >= 1 && friendID <= 1000000000)            //validate friend ID
                        {
                            if (friendID != temp->getID())
                                 temp->friends.push_back(friendID);
                            else
                                 isCorrupt = true;
                        }
                        else
                            isCorrupt = true;
                    }


            }

            if (isCorrupt)                  //break file-reading loop if data was corrupt
                break;
            else
                users.push_back(temp);
            }

        }

    }

    if (isCorrupt || !checkFriends())               //if non-existing friends or data is corrupt, start with empty userlist
    {
        isCorrupt = false;
        users.clear();
         cout<<"Database file was corrupt. Upload failed \n";
    }

    fin.close();            //close file
    updateNums();
}

/* export data to file */
void Scoreboard::exportData(){
    updateNums();
    fout.open("db1.txt");
    if (!fout.fail())
    {
        fout.clear();
        fout<<numUsers<<endl;                //write number of Users
        for (int i= 0; i <users.size(); i++)
        {
            User* temp = users.at(i);
            fout<<temp->getID()<<'\n';                //write user ID
            fout<<'\t'<<temp->getName()<<'\n';                //write username
         //   cout<<'\t'<<temp->getName()<<'\n'; //***
            fout<<'\t'<<temp->getYear()<<'\n';                //write user year
            fout<<'\t'<<temp->getHighscore()<<'\n';                //write user highscore

          //  cout<<temp->friends.size()<<endl;
            if (temp->friends.size() > 0)
            {
            for (int a = 0; a <temp->friends.size(); a++)
                fout<<'\t'<<temp->friends.at(a);                //write list of friend ID's
            }
            else
                fout<<'\t';

            cout<<endl;
            fout<<'\n';
        }
        cout<<"Thanks for playing! \n";
    }
    else
        cout<<"Output File Corrupt/ Doesn't Exist \n";
    fout.close();                                           //close outpur stream
}

/* first level menu */
void Scoreboard::LOffMenu(){
    updateNums();

    cout<<endl<<endl<<endl<<endl<<endl;
    cout<<"*******************************************************"<<endl;
    cout<<"**                   BUBBLEKNIGHT                    **"<<endl;
    cout<<" Number of Users: "<<numUsers<<"            Number of Relations: "<<numRelations/2<<endl;
    cout<<"***************** Please Enter a Command **************"<<endl;
    cout<<"     '+' -> Add User             '-' -> Delete User      "<<endl;
    cout<<"     'L' -> Log In               'H' -> Highscore Board "<<endl;
    cout<<"                     'Q' -> Quit     "<<endl;
    cout<<"*******************************************************"<<endl;
    cout<<" Please properly quit the game to save to the database \n"<<endl<<endl<<endl<<endl;;
}

/* second-level (logged-in) menu */
void Scoreboard::LOnMenu(){
    updateNums();

           name = current->getName();
            year = current->getYear();
            highscore = current->getHighscore();

    /* print menu */
    cout<<endl<<endl<<endl<<endl<<endl;
    cout<<"*******************************************************************"<<endl;
    cout<<" Number of Users: "<<numUsers<<"                Number of Relations: "<<numRelations/2<<endl;
    cout<<" User Logged on: "<<name<<endl;
    cout<<" Year: "<<year<<endl;
    cout<<" Highscore: "<<highscore<<endl;
    cout<<" Friends: ";
    for (int i = 0; i <current->friends.size(); i++)            //print friends
    {
        string friendName;
        for (int a = 0; a < users.size(); a++)
        {
            if (current->friends.at(i) == users.at(a)->getID())
            {
                friendName = users.at(a)->getName();
                cout<<" "<<friendName;
            }
        }
    }
    cout<<"\n ********************** Please Enter a Command *********************"<<endl;
    cout<<"     'U' -> List All Users               'A' -> Add friend for "<<name<<endl;
    cout<<"     'D' -> Delete friend of "<<name<<"        'L' ->Logout "<<endl;
    cout<<"     'S' -> Sort "<<name<<"'s Friends by Score"<<endl;
    cout<<"     'B' -> Shortest Path to "<<name<<"        'H' -> Highscore Board "<<endl;
    cout<<"                     'P' -> Play Game     "<<endl;
    cout<<"******************************************************************* \n \n \n"<<endl;
}


/* validate name */
bool Scoreboard::isAlphanum(string c){
    int size = c.size();
      for (int i = 0; i < size; i++)
      {
          if (!(isalnum(c[i]) || c[i] =='_'))       //returns false if not alphanumeric or underscore
              return false;
      }
    return true;
}

/* updates number of users and number of relations variables */
void Scoreboard::updateNums(){
    numRelations = 0;
    numUsers = 0;

    if (users.size() > 0)           //if userlist isn't empty
    {
        vector<int> userIDs;

        for (int i=0; i <users.size(); i++)
            userIDs.push_back(users.at(i)->getID());            //create list of user IDs

        for (int i= 0; i <users.size(); i++)
        {
            User* temp = users.at(i);                               //pointer to user in userlist
            bool exists;
            for (int a = 0; a < temp->friends.size(); a++)       //check that all friends in a user's friends list exist
            {
                exists = false;
                for (int b = 0; b <userIDs.size(); b++)
                {
                    if (temp->friends.at(a) == userIDs.at(b))
                        exists = true;
                }
                if (!exists)
                {
                    temp->friends.at(a) = temp->friends.at(temp->friends.size()-1);             //otherwise, delete imaginary friend
                    temp->friends.pop_back();
                }
            }
        }
    }
    if (users.size() > 0)
    {
    numUsers = users.size();
    for (int i = 0; i < users.size(); i++)                  //update numUsers and numRelations
        numRelations += users.at(i)->friends.size();
    }
}

/* return number of users */
int Scoreboard::getnumUsers(){
    return numUsers;
}

/* set current User's highscore */
void Scoreboard::setScore(int score){
    if (score > current->getHighscore())                //only if new score beats old score
    {
        cout<<"Congratulations! You beat your old highscore! \n";
        current->setHighscore(score);
    }
    else
        cout<<"Sorry, you failed to top your best score. \n";
}

/* check friend lists do not have corrupt data*/
bool Scoreboard::checkFriends(){
    bool friendsOk = false;
    if (numUsers > 0)
    {
        vector<int> userIDs;

        for (int i=0; i <users.size(); i++)
            userIDs.push_back(users.at(i)->getID());            //list of user IDs

        for (int i= 0; i <users.size(); i++)
        {
            User* temp = users.at(i);
            if (temp->friends.size() > 0)
            {
            for (int a = 0; a < temp->friends.size(); a++)
            {
                friendsOk = false;
                for (int b = 0; b <userIDs.size(); b++)
                {
                    if (temp->friends.at(a) == userIDs.at(b))
                    {
                        friendsOk = true;
                    }
                    if (temp->friends.at(a) == 0)
                    {
                        friendsOk = true;
                        if (temp->friends.size() > 0)
                        {
                            temp->friends[a] = temp->friends[temp->friends.size()-1];
                            temp->friends.pop_back();
                        }
                        else
                            temp->friends.clear();
                    }
                }
                if (!friendsOk)
                {
                    cout<<"You can't have imaginary friends! Data Corrupt \n";
                    return false;
                }
            }
            }
        }
    }
    return true;
}

/* add friend to current user's list */
void Scoreboard::addFriend()
{
    User* newFriend;
    bool exists = false, alreadyFriends = false;                        //flags for friend status
    cout<<" Please enter the name of the friend you want to add: \n";
    cin>>name;
    if (name == current->getName())
        cout<<"You can't add yourself as a friend! \n";
    else
    {
        for (int i = 0; i <users.size(); i++)
            if (users.at(i)->getName() == name)     //look for friend
            {
                newFriend = users.at(i);
                if (current->isFriend(newFriend->getID()))
                {
                       alreadyFriends = true;
                       break;
                }
                current->addfriend(newFriend->getID());  //add new friend to current user's friend list
                newFriend->addfriend (current->getID());   //add current user to friend's list
                exists = true;
                break;
            }
        if (alreadyFriends)
            cout<<"You guys are already friends! \n";
        else
        {
            if (exists)
                cout<<"New friend '"<<newFriend->getName()<<"' was added! \n";
            else
                cout<<"This user does not exist! \n";
        }
    }

    updateNums();
}

/* delete friend from current user's friend list */
void Scoreboard::deleteFriend()
{
    User* oldFriend;
    bool exists = false, alreadyUnfriended = true;            //flag for friend exists
    cout<<" Please enter the name of the friend you want to delete: \n";
    cin>>name;
    if (name == current->getName())
        cout<<"You can't delete yourself as a friend! \n";
    else
    {
        for (int i = 0; i <users.size(); i++)
            if (users.at(i)->getName() == name)     //look for oldfriend
            {
                oldFriend = users.at(i);
                if (current->isFriend(oldFriend->getID()))
                       alreadyUnfriended = false;
                current->deletefriend(oldFriend->getID());  //delete friend from current user's friend list
                oldFriend->deletefriend (current->getID());   //delete user from old friend's friend list
                exists = true;
                break;
            }
        if (alreadyUnfriended)
            cout<<"You guys weren't friends to begin with!' \n";
        else
        {
            if (exists)
                cout<<"Old friend '"<<oldFriend->getName()<<"'' was deleted \n";
            else
                cout<<"This user does not exist! \n";
        }
    }

    updateNums();
}

/* sort current user's friends highscores and print */
void Scoreboard::sortFriendScores(){
    updateNums();
    vector<int> friendIDs = current->friends;               //list of friend's IDs
    vector<User*> friendsList;                              //create list of friends
    friendsList.push_back(current);
    for (int i = 0; i < friendIDs.size(); i++)
    {
        for (int a = 0; a < users.size(); a++)
            if (friendIDs.at(i) == users.at(a)->getID())
                friendsList.push_back(users.at(a));
    }
    cout<<endl<<endl<<endl;

    /* if list of friends isn't empty, sort the list and then print out names and scores */
    if (friendsList.size() > 0)
    {
        quicksortScores(friendsList);

        cout<<endl<<endl<<endl<<endl;
        cout<<"********************************************* \n";
        cout<<"**"<<setw(11)<<current->getName()<<"'s Friends' High Scores       **\n";
        cout<<"********** User ************** Score ******** \n";
        for (int i = 0; i < friendsList.size(); i++)
            cout<<"**  "<<setw(10)<<friendsList.at(i)->getName()<<right<<setw(20)<<friendsList.at(i)->getHighscore()<<setw(11)<<"**"<<endl;
        cout<<"********************************************* \n \n";
        cout<<"Enter any key to continue \n";
        int pause;
        cin>>pause;
        cin.clear();
        cin.ignore(1000, '\n');
    }
    else
        cout<<"You have no friends... \n";
}

/* print list of all current users if userlist isn't empty*/
void Scoreboard::listAllUsers(){
    updateNums();
    cout<<endl<<endl<<endl<<endl;;
    if (numUsers > 0)
    {
        cout<<"********************************************** \n";
        cout<<"**                 User List                **  \n";
        for (int i = 0; i <users.size(); i++)
        {
            if (i%2 == 0)
                cout<<endl;
            cout<<setw(15)<<users.at(i)->getName()<<setw(20);
        }
        cout<<"\n**********************************************"<<endl;
        cout<<"Enter any key to continue \n";
        int pause;
        cin>>pause;
        cin.clear();
        cin.ignore(1000, '\n');
    }
    else
        cout<<"No High Scores Yet! \n";
}

/* print out a sorted list of all player's high scores if user list isn't empty*/
void Scoreboard::listHighscores(){
    updateNums();
    cout<<endl<<endl<<endl;
    if (numUsers > 0)
    {
        quicksortScores(users);         //sort users

        cout<<"********************************************* \n";
        cout<<"**              High Scores                **\n";
        cout<<"********** User ************** Score ******** \n";
        for (int i = 0; i < users.size(); i++)
            cout<<"**  "<<setw(10)<<users.at(i)->getName()<<right<<setw(20)<<users.at(i)->getHighscore()<<setw(11)<<"**"<<endl;
        cout<<"********************************************* \n \n";
        cout<<"Enter any key to continue \n";
        int pause;
        cin>>pause;
        cin.clear();
        cin.ignore(1000, '\n');
    }
    else
        cout<<"No High Scores Yet! \n";

}

/* prints assuming that user exists */
void Scoreboard::printPath(User* target){
    bool isLinked = false;  //assume target isn't connected
    vector<int> visited;           //correspond to actual list of users
    vector<int> rank;               //rank (level) of every user
    vector<User*> previous = users;     //parent friend
    queue<User*> searchList;           //list of users left to traverse
    User* temp = current;

    /* Breadth First Search to organize Data */
    for (int i=0; i<users.size(); i++)          //empty list of whether visted or not
    {
        visited.push_back(0);               //0 = not yet visited;  1 = visited
        rank.push_back(-1);                 //all users have no levels
    }

    for (int i =0; i<users.size(); i++)     //mark current user as visited
        if (users.at(i) == temp)
        {
            visited.at(i) = 1;
            rank.at(i)  = 0;            //current user is level 0;
            previous.at(i) = NULL;      //current user has no parent friend
        }

    searchList.push(temp);      //add current user to list

    while (searchList.size() > 0)
    {
        temp = searchList.front();        //set check to first user in list
        searchList.pop();            //get rid of first user
        int temprank;

        for (int i = 0; i <users.size(); i++)
            if (temp == users.at(i))
                temprank = rank.at(i);


        vector<int> friendIDs = temp->friends;               //list of adjacent friends' IDs
        vector<User*> friendsList;                              //create list of adjacent friends

        for (int i = 0; i < friendIDs.size(); i++)      //fill list of adjacent friends
        {
            for (int a = 0; a < users.size(); a++)
                if (friendIDs.at(i) == users.at(a)->getID())
                    friendsList.push_back(users.at(a));
        }

        for (int i = 0; i < friendsList.size(); i++)      //check list of friends to see if visited
        {
            User* check = friendsList.at(i);
            for (int a = 0; a < users.size(); a++)      //go through userlist to find friend
            {
                if (visited.at(a) == 0)
                {
                    if (users.at(a) == check)
                    {
                        visited.at(a) = 1;      //mark friend as visited if not
                        rank.at(a) = temprank+1; //rank is 1 higher than parent friend
                        searchList.push(check);    //add friend to searchList
                        previous.at(a) = temp;
                    }
;
                }
            }

            if (check == target)            //if target is found to be adjacent through BFS
            {
                isLinked = true;
                break;              //stop traversing to find target
            }
        }
    }

    /* Printing the Path*/
    if (isLinked)
    {
        cout<<"Shortest path from "<<target->getName()<<" to "<<current->getName()<<" is: ";

        vector<User*> reversePath;
        int targetIndex;
        for (int i =0; i< users.size(); i++)
            if (users.at(i) == target)
                targetIndex = i;

        int currentrank = rank.at(targetIndex);     //target rank
        reversePath.push_back(users.at(targetIndex));   //pushback target user

        while (currentrank != 0)
        {
            temp = previous.at(targetIndex);       //temporary User is parent friend
            reversePath.push_back(temp);        //add temp user to reversed path

            for (int i =0; i< users.size(); i++)    //find Index of parent friend
                if (users.at(i) == temp)
                    targetIndex = i;        //set targetIndex to index of parent friend

            currentrank--;
        }

        /* Print each user in path */
        for (int i= 0; i <reversePath.size(); i++)
            cout<<reversePath.at(i)->getName()<<" ";
        cout<<endl;

    }
    else
        cout<<"Path to user'"<<target->getName()<<"' could not be found \n";


}


/* find shortest path to user */
void Scoreboard::findShortestPath(){

    User* target;
    bool exists = false;          //flag for user existance
    cout<<" Please enter the name of the user: ";
    cin>>name;
    if (name == current->getName())
        cout<<"You are the shortest path to you! \n";
    else
    {
        for (int i = 0; i <users.size(); i++)
            if (users.at(i)->getName() == name)     //look for user
            {
                target = users.at(i);
                exists = true;
                break;
            }

            if (exists)
            {
                printPath(target);
                cout<<"Enter any key to continue \n";
                int pause;
                cin>>pause;
                cin.clear();
                cin.ignore(1000, '\n');
            }
            else
                cout<<"This user does not exist! \n";
    }
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }

}

/* quicksort list of users by score */
void Scoreboard::quicksorthelper (vector<User*>& list, int left, int right)
{
    int l = left, r = right, pivot = (left+right)/2;
    while (l <= r)
    {
        while (list.at(l)->getHighscore() > list.at(pivot)->getHighscore())
            l++;
        while (list.at(r)->getHighscore() < list.at(pivot)->getHighscore())
            r--;
        if (l <= r)
        {
            User* temp = list.at(l);
            list.at(l) = list.at(r);
            list.at(r) = temp;
            temp = NULL;

            l++; r--;
        }
    }
    if (left < r)
        quicksorthelper(list, left, r);
    if (l < right)
        quicksorthelper(list, l, right);


}
void Scoreboard::quicksortScores(vector<User*>& list)
{
    quicksorthelper(list, 0, list.size()-1);
}
