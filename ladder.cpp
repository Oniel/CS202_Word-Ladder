//Oniel Toledo      Assignment 14 Main file for wordLadder      CS202
// Client program for the wordLadder class.
// The following program takes in 3 arguements at terminal run time,
// it will error check that the arguments are indeed 3, are in proper
// order and that the final argument is a valid file 
// Given the form ./ladder -w <dictionaryFile> the program reads the dictionary
// and creates a linked list via wordLadder, it then prompts the user for 2 words
// to find a word ladder for. If there is no path for a ladder a message is displayed
// if there is a path then the path is outputted and the user is prompted for a new
// set of words, this will occur infinitely until the user enters enters an empy argument
// for the first word.

#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include"wordLadder.h"
#include"linkedStack.h" 
#include"linkedQueue.h"
using namespace std;

int main(int argc, char *argv[]){
  
  string first, second;
  wordLadder dictionary;
  
  //error check for proper program arguments
  //------------------------------------------------------------------------------------------------

  //if program was executed inappropriately
  if(argc==0){
    cout << "Usage: ./ladder -w <wordFile>" << endl;
    return 0;
  }

  //if no dictionary is provided
  if(argc==2){
    cout <<"Error, must provide word file name." << endl;
    return 0;
  }

  //if 3 arguments weren't passed
  if(argc!=3){
    cout << "Usage: ./ladder -w <wordFile>" << endl;
    return 0;
  }
  
  //if '-w' wasn't specified
  if(string(argv[1])!="-w"){
    cout << "Error, invalid word file specifier." << endl;
    return 0;
  }
  
  //if the word file is not valid
  if(dictionary.readDictionary(argv[2])==false){
    cout << "Error, unable to open word file: " << argv[2] << endl;
    return 0;
  }
  //if the word file is valid, then the word file dictionary has been set to the
  //wordLadder linked list, and prev has been set to NULL, ready for word
  //-----------------------------------------------------------------------------------------------
  else{

    cout << "CS 202 Word Ladder Program." << endl;

    while(true){
      //prompt for first word, check it is a word via validWord() if invalid error msg, and prompt again
      cout << "---------------------------" << endl;
      cout << "Enter First Word: ";
      getline(cin, first);
      //terminate if empty string is entered
      if(first==""){
	return 0;}
      //if invalid word is ented, prompt until valid word is entered
      while(dictionary.validWord(first)==false){
	cout << "Error, first word is not in dictionary." << endl;
	cout << "Enter First Word: ";
	getline(cin, first);
      }
      
      //prompt for second word
      cout << "Enter Second Word: ";
      getline(cin, second);
      while(dictionary.validWord(second)==false){
	cout << "Error, second word is not in dictionary." << endl;
	cout << "Enter Second Word: ";
	getline(cin, second);
      }

      //both words are valid check if a ladder is possible
      //if there is not ladder possible for  the two words display message
      if(dictionary.findLadder(first, second)==false){
	cout << "There is no path from " << first << " to " << second << endl;
      }
      else{//if there is a ladder display it via printLadder() functon
	cout << endl;
	dictionary.printLadder();
      } 
      //reset the ladder and loop again
      dictionary.resetLadder();
    }

  }//end of else
   
  return 0;
}
