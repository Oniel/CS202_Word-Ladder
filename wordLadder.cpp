//Oniel Toledo   Assignment 14 wordLadder Implementation file    CS202
//Implementation file for the wordLadder class, the function's functions are
//described below, given an appropriate dictionary provided from ladder.cpp
//the class via readDictionary created a linked list of dictionary words.
//A ladder through a large graph can be created to find words that differ
//by one letter from the first to the second word

#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include"wordLadder.h"
#include"linkedStack.h"
#include"linkedQueue.h"
using namespace std;

//constructor, initialize class variabls
wordLadder::wordLadder(){
  first = NULL;
  ladderEnd = NULL;
  count = 0;
}

//destructor empty both the dictionary and the class linked list
wordLadder::~wordLadder(){
  wordNode *current;
  wordNode *tmp;

  //first---deallocate the wordLadder linked list
  current = first;
  while(current!=NULL){
    tmp = current;
    current = current->link;
    delete tmp;
  }
  count=0;

  //second---deallocate the queue of pointers
  //linkedStack<string>::ladderStack.deleteStack();
}

//resets the prev field of every node to NULL
void wordLadder::resetLadder(){
  wordNode *current;
  current = first;

  do{//perform loop at least one time
    current->prev = NULL;//set prev field to null
    current =  current->link;//go to the next node
  }while(current->link!=NULL);
  //if link is NULL end has been reached stop
}

//function to read the dictionary, if invalid file name is provided returns false, else makes
//a linked list of all the files
bool wordLadder::readDictionary(const char *psdFileName){
  wordNode *firstNode;
  wordNode *newNode;
  wordNode *last;

  ifstream infile;
  string fileName, inputLine, word;
  char wordTemp[5];

  //convert to string format and open file
  fileName = string(psdFileName);
  infile.open(fileName.c_str());

  //if the file does not exist return false
  if(infile.fail()){
    //cout << "Error unable to open word file: " << argv[] << endl;
    return false;
  }

  //if the false was not returned the file begin linked list with first node
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  //store the first node, input data, get only first 5 words, and loop
  firstNode = new wordNode;

  //checks for comment lines, will ignore these lines
  do{
    getline(infile, inputLine);
  }while(inputLine[0]=='*');


  for(int i=0; i<5; i++)//copy only the first 5 chars
    wordTemp[i] = inputLine[i];
  word = string(wordTemp);//covert to string type
  firstNode->info = word;//store in first node
  firstNode->prev = NULL;//set prev to NULL
  firstNode->link = NULL;
  count++;//add to count
  first = firstNode;//point to the beginning of the list
  last = firstNode;//used to bridge nodes together
  
  //check for comment lines, will ignore these lines
  do{
    getline(infile, inputLine);
  }while(inputLine[0]=='*');

  //will loop for the remaining lines in the file as long as there is still data in the file or no comments are reached
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  while(infile && inputLine[0]!='*'){
    //same algorithm as for firstNode except... last->link to newNode
    newNode = new wordNode;

    for(int i=0; i<5; i++)
      wordTemp[i] = inputLine[i];
    word = string(wordTemp);
    newNode->info = word;
    newNode->prev = NULL;
    newNode->link = NULL;
    count++;

    last->link = newNode;//link last list to newNode
    last = newNode;//move last to this newNode for furthur list "bridg 
    getline(infile, inputLine);
  }
  //linked list has been created return true
  
  return true;
}

//returns true if the word given by the user is a word in the dictionary, false otherwise
bool wordLadder::validWord(const string word) const{
  wordNode *current;
  current = first;

  //loop to find word, stop and return true if found
  while(current!=NULL){
    if(current->info==word)//if the word at current info is the word, it is valid return true
      return true;
    current = current->link;//go to the next list
  }
  return false;//entire list was searched word is not there, return false
}


//returns the location of the pointer of a passed word, if not in dictionary return null
wordNode* wordLadder::searchPtr(const string& searchItem) const{
  wordNode *current;//track thru the list
  current = first;//search from the beginning
  //loop through the list to find a match
  while(current!=NULL){
    if(current->info==searchItem)
      return current;//if a match is found return that location of that node, else keep looping
    current = current->link;
  }
  //entire list was checked no match return NULL
  return NULL;
}

//determine if a word is one letter apart by brute force comparision of each letter
bool wordLadder::isOneApart(const string word1, const string word2) const{
  if(word1[0]==word2[0] && word1[1]==word2[1] && word1[2]==word2[2] && word1[3]==word2[3] &&  word1[4]!=word2[4])
    return true;
  else
    if(word1[0]==word2[0]&& word1[1]==word2[1] && word1[2]==word2[2] && word1[3]!=word2[3] &&  word1[4]==word2[4])
      return true;
    else
      if(word1[0]==word2[0]&& word1[1]==word2[1] && word1[2]!=word2[2] && word1[3]==word2[3] &&  word1[4]==word2[4])
	return true;
      else
	if(word1[0]==word2[0]&& word1[1]!=word2[1] && word1[2]==word2[2] && word1[3]==word2[3] &&  word1[4]==word2[4])
	  return true;
	else
	  if(word1[0]!=word2[0]&& word1[1]==word2[1] && word1[2]==word2[2] && word1[3]==word2[3] &&  word1[4]==word2[4])
	    return true;
	  else
	    return false;
}

//will find the ladder between the two words
bool wordLadder::findLadder(const string word1, const string word2){
  linkedQueue<wordNode*> ptrQueue;//create empty object
  wordNode *targetWord;
  
  wordNode *current = first;

  //find word in the dictionary first, set it's prev to itself, and add ptr to queue
  while(true){
    if(current->info == word1){
      current->prev = current;//set prev to point to its node
      ptrQueue.enqueue(current);//add to queue
      break;
    }
    current = current->link;
  }
  
  //now search for a ladder between the two words
  while(true){
    targetWord = ptrQueue.dequeue();
    current = first;
    //loop once for the entire dictionary
    while(current!=NULL){
      //if these two words are one apart do the following...
      if(isOneApart(targetWord->info, current->info)){
	//if the target word has been found designate ladderEnd to it and return true
	if(current->info==word2){
	  ladderEnd = current;
	  current->prev = targetWord;
	  return true;
	}
	//if the word is not the target word but it is one apart 
	//if prev is null-meaning the word hasn't been used before-add it to the queue and connect prev to preious word
	else{
	  if(current->prev==NULL){
	    ptrQueue.enqueue(current);
	    current->prev = targetWord;
	    }
	}
	  if(ptrQueue.isEmptyQueue()==true){
	    return false;
	  }
      }//end of statment fo one letter apart words
      current = current->link;
      
    }//end of search loop
  }//end of continuous loop

}	
    
//prints out the word ladder
void wordLadder::printLadder() const{
  //to print out word ladder in proper order a ladderStack needs to be used
  //since prev points to the word before it the ladder will be in reverse order
  //since a stack uses the for LIFO, we can print out the last string which would be the first word, 
  //and recursively print out the result
  linkedStack<string> ladderStack;
  wordNode *current;

  //add the ladder to a stack so that it can be outputted in reverse order
  current = ladderEnd;
  while(true){
    //if the first word has been reached stop
    if(current->prev==current){
      ladderStack.push(current->info);
      break;
    }
    ladderStack.push(current->info);
    current = current->prev;
    }
  
  cout << "Word Ladder:" << endl;
  //since a stack is FIFO the stack top(last node) will be outputted first, then the next until the first has been reached
  while(!ladderStack.isStackEmpty()){
    cout << ladderStack.pop() << endl;
  }

}
