//  Main program
//	Test stack and queue implementation

#include <iostream>
#include <fstream>
#include <string>
#include "linkedStack.h"
#include "linkedQueue.h"

using namespace std;

int main()
{
// *****************************************************************
//  Headers...

	string bars = "--------------------------------------------------";

	cout << bars << endl << "CS 202 - Assignment #14" << endl;
	cout << "Basic Testing for Stacks and Queues" << endl;


// *****************************************************************
//  Test basic queue operations.
//	Create some integer queues, add items, delete items,
//	display queues, etc...

	cout << endl << bars << endl << "Queue Operations - Integers:" << endl << endl;

	linkedQueue<int> queue0, queue1;
	linkedQueue<int> queue2, queue3;
	int	j;

	for (int i=1; i<=20; i++)
		queue0.enqueue(i);


	cout << "Queue 0:  ";
	queue0.printQueue();
	cout << endl << endl;

	for (int i=1; i<=20; i+=2) {
		queue1.enqueue(queue0.dequeue());
		j = queue0.dequeue();
		queue2.enqueue(j);
	}

	cout << "Queue 1 (odds): ";
	queue1.printQueue();
	cout << endl << endl;

	cout << "Queue 2 (evens): ";
	queue2.printQueue();
	cout << endl << endl;

	queue3 = queue1;

	cout << "Queue 3 (copy of odds): ";
	queue3.printQueue();
	cout << endl;

	linkedQueue<int> queue4(queue3);

	while (!queue3.isEmptyQueue())
		j = queue3.dequeue();

	cout << "Queue 3 (now empty): ";
	queue3.printQueue();
	cout << endl << endl;

	cout << "Queue 4 (copy of odds): ";
	queue4.printQueue();
	cout << endl;

	cout << "Queue 4 (count): " << queue4.queueCount();
	cout << endl;
	cout << "Queue 4 (first item): " << queue4.front();
	cout << endl;
	cout << "Queue 4 (last item): " << queue4.back();
	cout << endl;


// --------------------------------------
//  Floating point tests
//	Create some queues for floating point items.

	cout << endl << bars << endl << "Queue Operations - Floats:" << endl << endl;

	linkedQueue<double> queue5;

	for (int i=1; i<=7; i++)
		queue5.enqueue(static_cast<double>(i)+0.5);

	linkedQueue<double> queue6(queue5);
	linkedQueue<double> queue7;

	cout << "Queue 5 (floats, original): ";
	queue5.printQueue();
	cout << endl;

	cout << endl << "Queue 6 (floats, original): ";		// => queue5 original
	queue6.printQueue();
	cout << endl;

	queue7 = queue6;
	cout << endl << "Queue 7 (floats, original): ";		// => queue5 original
	queue7.printQueue();
	cout << endl;

	cout << endl << "Queue 5 (floats, modified): ";
	queue5.enqueue(queue5.dequeue());			// move three items
	queue5.enqueue(queue5.dequeue());
	queue5.enqueue(queue5.dequeue());
	queue5.printQueue();
	cout << endl;

	cout << "Queue 5 (count): " << queue5.queueCount();
	cout << endl;
	cout << "Queue 5 (first item): " << queue5.front();
	cout << endl;
	cout << "Queue 5 (last item): " << queue5.back();
	cout << endl;

	cout << endl << "Queue 6 (floats, modified): ";
	queue6.printQueue();
	cout << endl;

	cout << "Queue 6 (count): " << queue6.queueCount();
	cout << endl;
	cout << "Queue 6 (first item): " << queue6.front();
	cout << endl;
	cout << "Queue 6 (last item): " << queue6.back();
	cout << endl;

// *****************************************************************
//  All done.

	cout << bars << endl << "Game Over, thank you for playing." << endl;

	return 0;
}
