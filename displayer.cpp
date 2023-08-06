/*
  By Brandon Frauenfeld, 2023
*/

#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>

using namespace std;

struct flist { // list of floors, with a vector of all the temps on that floor
  string floor;
  vector<int> temps;
  struct flist *next;
};
struct tlist { // list of temps, with corresponding floors
  string floor;
  int temp;
  struct tlist *next;
};
/*

splitter takes in a string and splits it based on the ',' delimiter.
it returns only one word at a time, or NULL if pos is incorrect.
think of it as treating the string as an array of strings split by ','.

@param string s: the string to be split
@param int pos: the position of the word in the string, 0-indexed

*/
string splitter(string s, int pos) { // to split up a string
  stringstream ss(s);
  string word;
  int index = 0; // 0th word, 1st word, 2nd ...
  while (!ss.eof()){ // go through the string up to index
    getline(ss, word, ',');
    if (pos == index) {
      return word; // index reached, return this word
    }
    ++index;
  }
  return NULL;
}

int main() {

  ifstream data("data.txt"); // assumed to always be data.txt
  string text = "";

  string warmestRoom = "";
  int warmestTemp = 0;
  int currTemp = -1;

  string currRoom = "";
  string currFloor = "";

  // split each line by ',' and get temps
  // define warmestRoom and warmestTemp
  // floor, room, temp
  tlist *tempHead = new tlist();
  tlist *tempList = tempHead;
  int head = 0;
  while(getline(data, text)) { // populate templist and find warmest temp / room
    if (head == 0) { // init head

      currFloor = splitter(text, 0);  // floor
      currRoom = splitter(text, 1);  // room
      currTemp = stoi(splitter(text, 2)); // temp 
      tempList->floor = currFloor;
      tempList->temp = currTemp;
      ++head;

      continue;
    }

    currFloor = splitter(text, 0);  // floor
    currRoom = splitter(text, 1);  // room
    currTemp = stoi(splitter(text, 2)); // temp 

    if (currTemp > warmestTemp) { 
      warmestTemp = currTemp;
      warmestRoom = currRoom;
    }
    
    tlist *newTemp = new tlist(); // add in new temp and floor 
    newTemp->floor = currFloor;
    newTemp->temp = currTemp;
    tempList->next = newTemp;

    tempList = tempList->next;
  }

  cout << "Warmest room: " << warmestRoom << "\n";
  printf("Warmest room temp: %d\n", warmestTemp);
  
  // run through linkedlist from head to calc avg temp per floor
  // assign each temp to floor num
  
  flist *flhead = new flist();
  cout << "\n"; // for style

  flist *floorList = flhead; // to navigate the list
  flist *temp = floorList; // to use if no match is found and have to retreat once in the singly-linked list
  int found = 0; // use if new floor is found

  // compile the temps
  // only make a new node if node doesn't exist in list

  while(tempHead != NULL) { // iterate through entire tempHead for all temps. tempList is currently at end, so use head

    while(floorList != NULL) { // iterate through all rooms, to find proper room to add temp

      if(floorList->floor.compare(tempHead->floor) == 0) {

        // matching floor found, add temp and break
        found = 1;
        floorList->temps.push_back(tempHead->temp);
        // return to head for next search
        floorList = flhead;
        break;

      }

      temp = floorList; // to be used in case we hit end, to go back a node
      floorList = floorList->next;

    }
    // if we are out of the previous loop, either found floor or didnt
    if (found == 1) { // floor found, no operation needed
      tempHead = tempHead->next;
      found = 0;
      continue;
    } 

    // floor not found, add to list. can assume we are at end of floorList

    floorList = temp; // go back a step, so we are no longer NULL
    flist *newFloor = new flist();

    newFloor->floor = tempHead->floor;
    newFloor->temps.push_back(tempHead->temp);

    floorList->next = newFloor;

    // continue
    floorList = flhead; // set back to head for next comparison
    tempHead = tempHead->next;
  }

  printf("Avg Temp per Floor\nFloor    Temp\n\n");

  // iterate thru floorList, print out stuff properly

  while (flhead != NULL) {
    if (!flhead->floor.empty()) {
      cout << flhead->floor << "        ";
      double tempsAdded = 0.0;
      double numTemps = 0.0;
      for (auto i = flhead->temps.begin(); i != flhead->temps.end(); i++) {
        tempsAdded += *i; // add each temp to a num
        ++numTemps; // keep track of num temps
      }
      double avg = tempsAdded / numTemps; // avg
      cout << avg << "\n";
    }
    
    flhead = flhead->next;
  }
  system("pause");
  return 0;
}



