//Oniel Toledo    Assignment 13-header file   CS202
//This file is the header file for the linkedStack class, it contains both
//the class definiton and the class function definitons.
//Because all the class definitions are of template type there is no need
//for a seperate implementation file.
//The class perfoms various procedures that manipulate a linked list in
//the form of a stack, that is the linked list can only be modified
//from one end (refered to as FIFO data structure)


#ifndef LINKEDSTACKH
#define LINKEDSTACKH

#include<iostream>
#include<string>
#include"wordLadder.h"
using namespace std;

//linked list struct format
template<class myType>
struct nodeType{
    myType info;
    nodeType<myType> *link;
};

//class
template<class myType>
class linkedStack {
 public:
  //constructors/destructor
  linkedStack();
  linkedStack(const linkedStack<myType>&);
  ~linkedStack();
  //class functions
  void deleteStack();
  bool isStackEmpty() const;
  void push(const myType&);
  myType peek() const;
  myType pop();
  int stackCount() const;
  myType stackSum() const;
  //operator functions
  bool operator ==(const linkedStack<myType>&);
  bool operator !=(const linkedStack<myType>&);
  linkedStack<myType> operator =(const linkedStack<myType>&);
 private:
  //private functions
  myType rSum(nodeType<myType> *) const;
  void copyStack(const linkedStack<myType>&);
  //variables
  nodeType<myType> *stackTop;
  int count;
};


//Class function implementation via template declaration
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//default constructor sets stack to an empty state
//count and stackTop as set to 0 and NULL
template<class myType>
linkedStack<myType>::linkedStack(){
  stackTop = NULL;
  count = 0;
}

//copy constructor, will create a stack based on the passedStack class
//object by usage of the copyStack function
template<class myType>
linkedStack<myType>::linkedStack(const linkedStack<myType>& passedStack){
  stackTop = NULL;
  copyStack(passedStack);
}

//destructor, calls the deleteStack function to delete and free any memory associated with the stack
template<class myType>
linkedStack<myType>::~linkedStack(){
  deleteStack();
}

//deletes the entire stack and sets stack to an empty state
template<class myType>
void linkedStack<myType>::deleteStack(){
  nodeType<myType> *temp;
  //deletes stack from top to bottom, one list at a time
  while(stackTop != NULL){
        //set temp equal to the stack top list
    temp = stackTop;
    //set the stackTop pointer to point to the next list
    stackTop = stackTop->link;
    //delete the original stackTop list
    delete temp;
    }//at end of loop stackTop will be set to NULL
  count = 0;
}//stack has been deleted.

//copyStack function to deep copy the passed stack object to the current class object
template<class myType>
void linkedStack<myType>::copyStack(const linkedStack<myType>& passedStack){
  nodeType<myType> *newNode;
    nodeType<myType> *current;
    nodeType<myType> *last;

    //make sure the stackTop is empty
    if(stackTop != NULL)
        deleteStack();

    //current class stack is empty, make sure the passed stack is  not empty
    if(passedStack.stackTop == NULL)
        stackTop = NULL;
    else{
        //set current to the top of the passed stack, the 'current' pointer will run
        //though the nodes of the passed stack
        current = passedStack.stackTop;
        stackTop = new nodeType<myType>; //create a new node
        stackTop->info = current->info;//copy data over
        count++;
        stackTop->link = NULL;//make link null in case there will only be one list
        last = stackTop;
        //Now loop for any remaining lists
        current = current->link;//go to next list (if any);
        while(current!=NULL){//if the end of the linked list hasn't been reached -loop
            //create a new list and copy data over, set that link to null for if last
            newNode = new nodeType<myType>;
            newNode->info = current->info;
            count++;
            newNode->link = NULL;
            last->link = newNode;//now connect the last list link pointer to the new pointer
            last = newNode;
            current = current->link;
            }
    }
}

//returns true or false depending if the stack is empty
template<class myType>
bool linkedStack<myType>::isStackEmpty() const{
    return (stackTop == NULL);//if stack is null will return true, else returns false
}

//push function will create a new node and attach it to the top node assuming another node exists
template<class myType>
void linkedStack<myType>::push(const myType& newItem){
    nodeType<myType> *newNode;
    newNode = new nodeType<myType>;//create a new node list

    newNode->info = newItem;//add item to list
    newNode->link = stackTop;//make newNode point to next list
    stackTop = newNode;//set this new node as the stack top
    count++;
}

/*template<>
string linkedStack<std::string>::peek() const{
    if(stackTop!=NULL)
        return stackTop->info;
    else{
        cout << "Error (peek), stack is empty." << endl;
        return "";
    }
}
*/

//peek function (AKA top) returns the value at the top of the stack
template<class myType>
myType linkedStack<myType>::peek() const{
    if(stackTop!=NULL)
        return stackTop->info;
    else{
        cout << "Error (peek), stack is empty." << endl;
        return 0;
    }
}

//pop function for non-numeric string, only difference is the return for error is ""
/*template<>
string linkedStack<std::string>::pop(){
    nodeType<string> *tmp;
    string toReturn;
    if(stackTop!=NULL){
        tmp = stackTop;
        toReturn = stackTop->info;
        stackTop = stackTop->link;
        delete tmp;
        count--;
        return toReturn;
    }
    else{
        cout << "Error (pop), stack is empty." << endl;
        return "";
    }
}
*/


//pop function removes the top node, if there is none error is outputted
template<class myType>
myType linkedStack<myType>::pop(){
    nodeType<myType> *tmp;
    myType toReturn;
    if(stackTop!=NULL){
        tmp = stackTop;
        toReturn = stackTop->info;
        stackTop = stackTop->link;
        delete tmp;
        count--;
        return toReturn;
    }
    else{
        cout << "Error (pop), stack is empty." << endl;
        return 0;
    }
}

//returns the number of items in the stack
template<class myType>
int linkedStack<myType>::stackCount() const{
    return count;
}

//(=) operator performs deep copy by calling the copyStack function
template<class myType>
linkedStack<myType> linkedStack<myType>::operator =(const linkedStack<myType>& passedStack){
    if(this != &passedStack)
        copyStack(passedStack);
    return *this;
}

//== operator to verify if the stacks are the same
template<class myType>
bool linkedStack<myType>::operator ==(const linkedStack<myType>& passedStack){
    nodeType<myType> *stack1;
    nodeType<myType> *stack2;
    bool same = true;

    stack1 = stackTop;
    stack2 = passedStack.stackTop;
    //4 possible cases:
    //  both the stack are empty-return true
    //  one of the stacks is empty-return false
    //  first stack is different-return false,else go to next step
    //  look at all list entries return true/false at the end of search

    if(stack1 == NULL && stack2 == NULL)
        return true;//if the lists both do not exist
    else
    if((stack1 == NULL && stack2 != NULL) || (stack1 != NULL && stack2 == NULL))
        return false;//if one of the lists is empty but not the other, false
    else{
        if(stack1->info != stack2->info)//if the stack tops are not equal return false
            return false;
        else{//if they are equal begin looping
            stack1 = stack1->link;
            stack2 = stack2->link;
            while(stack1!=NULL && stack2!=NULL && same){
                if(stack1->info != stack2->info)//if nodes are not equal exit loop and return false
                    same = false;
                else{
                    stack1 = stack1->link;
                    stack2 = stack2->link;
                    //in case one of the lists finishes before the other
                    if((stackTop == NULL && passedStack.stackTop != NULL) || (stackTop != NULL && passedStack.stackTop == NULL))
                        same = false;
                }
            }
            return same;
        }
    }
}


// != operator function returns false if the two stacks are equal
template<class myType>
bool linkedStack<myType>::operator !=(const linkedStack<myType>& passedStack){
    nodeType<myType> *stack1;
    nodeType<myType> *stack2;
    bool same = true;

    stack1=stackTop;
    stack2=passedStack.stackTop;

    if(stack1==NULL && stack2==NULL)
        return false;
    else
    if((stack1 == NULL && stack2 != NULL) || (stack1 != NULL && stack2 == NULL))
        return true;//if one of the stacks is empty
    else{
        if(stack1->info == stack2->info)
            return false;
        stack1 = stack1->link;//point to next node in the linked stack
        stack2 = stack2->link;
        while(stack1!=NULL && stack2!=NULL && same){
            if(stack1->info == stack2->info)
                same = false;
            else{
                stack1 = stack1->link;
                stack2 = stack2->link;
                if((stack1 == NULL && stack2 != NULL) || (stack1 != NULL && stack2 == NULL))
                    same = false;
            }
        }
        return same;
    }
}


//calls rSum which recursively sums data in linked list and returns that value
template<class myType>
myType linkedStack<myType>::stackSum() const{
    nodeType<myType> *first = stackTop;//make a temp pointer to point to stack top
    return rSum(first);//return the value of rSum function
}

//recursive function that adds up data for the entire stack
template<class myType>
myType linkedStack<myType>::rSum(nodeType<myType> *first) const{
    if(first!=NULL)
        return (first->info + rSum(first->link));//return info + and recurse for each info cell
    else
        return 0;//NULL is the base case if base case is reached return 0 to stop recursion
}

#endif
