//Oniel Toledo Assignment 14 wordLadder header file    CS202
//header file for the wordLadder object class, contains class declarations
//for the wordLadder implementation file as well as the structure of each
//node that will be used to store dictionary words

//header gaurds
#ifndef WORDLADDERH
#define WORDLADDERH

#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include"linkedStack.h"
#include"linkedQueue.h"
using namespace std;

//~~~~~~~~~~~~~~~~~~~~~~~~linked list structure~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct wordNode{
  string info;
  wordNode *prev;
  wordNode *link;
};


//~~~~~~~~~~~~~~~~~~~~~~~~Class definition~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class wordLadder{
 public:
  //constructor
  wordLadder();
  //destructor
  ~wordLadder();
  //reads dictionary and creates a linked list
  bool readDictionary(const char*);
  //find a ladder between the two words
  bool findLadder(const string, const string);
  //determines if the word exists in the dictionary
  bool validWord(const string) const;
  //prints the ladder that has been previously found in reverse order
  void printLadder() const;
  //resets the prev fields of wordNode linked list to NULL
  void resetLadder();//done
 private:
  //returns true/false given that the two words differ by only one letter
  bool isOneApart(const string, const string) const;
  //inserts a word....not used 
  void insertWord(const string newItem);
  //searches for a pointer
  wordNode* searchPtr(const string& searchItem) const;
  
  int count;
  wordNode *first;
  wordNode *ladderEnd;
};

#endif
