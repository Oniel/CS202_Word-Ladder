//Oniel Toledo     Assignment 14 header file for linkedQueue    cs202
//header file for the linkedQueue class, contains class declarations, member declarations,
//and the node structure for the queue list
//function purposes are commented on below.

#ifndef LINKEDQUEUEH
#define LINKEDQUEUEH

#include<iostream>
#include<iomanip>
#include<string>
#include"wordLadder.h"
using namespace std;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~node structure~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<class type>
struct queueNodeType{
    type info;
  queueNodeType<type> *link;//used to link between nodes
};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~class~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<class type>
class linkedQueue {
 public:
  //constructors/destructors
  linkedQueue();
  linkedQueue(const linkedQueue<type>& otherQueue);
  ~linkedQueue();

  //member functions
  linkedQueue<type>& operator =(const linkedQueue<type>&);
  //determines if the queue is empty
  bool isEmptyQueue() const;
  //deletes the queue, ca;;ed on by the destructor
  void initializeQueue();
  //add an element to the queue
  void enqueue(const type& newItem);
  //return front element
  type front() const;
  //return back element
  type back() const;
  //delete element from the queue and return it
  type dequeue();
  //return the queue count
  int queueCount();
  //print out the entire queue
  void printQueue();
  
 private:
  //copy the queue of the passed queue, works for the copy constructor
  void copyQueue(const linkedQueue<type>& otherQueue);
  int count;
  queueNodeType<type> *queueFront;
  queueNodeType<type> *queueRear;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~class member definition~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//default constructor sets front and back pointers to NULL, and count to 0
template<class type>
linkedQueue<type>::linkedQueue(){
    queueFront = NULL;
    queueRear = NULL;
    count = 0;
}

//copy constructor-calls on copyQueue to perform deep copy of linked list
template<class type>
linkedQueue<type>::linkedQueue(const linkedQueue<type>& passedQueue){
    copyQueue(passedQueue);
}

//destructor calls on initializeQueue to delete linked list
template<class type>
linkedQueue<type>::~linkedQueue(){
    initializeQueue();
}

//copies queue of passed object
template<class type>
void linkedQueue<type>::copyQueue(const linkedQueue<type>& passedQueue){
    queueNodeType<type> *newNode;
    queueNodeType<type> *current;
    queueNodeType<type> *last;

    queueFront=NULL;
    queueRear=NULL;
    count=0;

    if(passedQueue.isEmptyQueue()==false){
        current = passedQueue.queueFront;//track passedQueue linked list...
        newNode = new queueNodeType<type>;//create new node for first
        newNode->info = current->info;//copy data over
        count++;
        newNode->link = NULL;//set to NULL in case there is only 1 entry
        queueFront = newNode;
        queueRear = newNode;
        last = newNode;//used to connect lists
        current = current->link;
        while(current!=NULL){
            //create a new list and copy data over, set that link to null for if last entry
            newNode = new queueNodeType<type>;
            newNode->info = current->info;
            count++;
            last->link =  newNode;//connect the last list link pointer to the new list
            newNode->link = NULL;
            queueRear = newNode;
            last = newNode;
            current = current->link;
        }
    }
}

//returns true if the queue is empty
template<class type>
bool linkedQueue<type>::isEmptyQueue() const{
    if(queueFront==NULL)
        return true;
    return false;
}

//create an empty queue
template<class type>
void linkedQueue<type>::initializeQueue(){
    queueNodeType<type> *temp;

    //if the queue is not empty, delete every linked list

        while(queueFront!=NULL){
            temp = queueFront;//copy location of queueFront
            queueFront = queueFront->link;//set queueFront to the next list or to NULL
            delete temp;
        }
        //at the end of the loop list will have beed delete, and queueFront will be NULL
        count=0;//set count to 0 and Rear to NULL
        queueRear=NULL;

}

//functon to return the value in the front list
template<class type>
type linkedQueue<type>::front() const{
    if(!isEmptyQueue())//if the list is not empty
        return queueFront->info;//return the info cell that queueFront is pointing to
}

//return the back value
template<class type>
type linkedQueue<type>::back() const{
    if(!isEmptyQueue())
        return queueRear->info;
}


//return count number
template<class type>
int linkedQueue<type>::queueCount(){
  return count;
}

//adds newItem to queue, if the queue is empty this will be set as the only item
//with front and back both pointing to it. If the list is not empty add new node to the rear
template<class type>
void linkedQueue<type>::enqueue(const type& newItem){
    queueNodeType<type> *newNode;
    newNode = new queueNodeType<type>;

    newNode->info = newItem;
    newNode->link = NULL;

    if(queueFront==NULL){
        queueFront=newNode;
        queueRear=newNode;
    }
    else{
        queueRear->link = newNode;
        queueRear = queueRear->link;
        }
        count++;
}


//delete the frontmost value in the queue
template<class type>
type linkedQueue<type>::dequeue(){
  queueNodeType<type> *tmp;
  type toReturn;
    if(!isEmptyQueue()){
        toReturn = queueFront->info;
        tmp = queueFront;
        queueFront = queueFront->link;
        delete tmp;
        count--;
        if(queueFront == NULL)
         queueRear =NULL;
        return toReturn;
        }
}

//creates a deep copy
template<class type>
linkedQueue<type>& linkedQueue<type>::operator =(const linkedQueue<type>& passedQueue){
   if(this != &passedQueue)
        copyQueue(passedQueue);//call the copyQueue function to perform deep copy
    return *this;//return the current classs object
}

//output the queue contents
template<class type>
void linkedQueue<type>::printQueue(){
    queueNodeType<type> *current;
    current = queueFront;
    while(current!=NULL){
      cout << current->info << " ";
      current = current->link;
    }
}

#endif
