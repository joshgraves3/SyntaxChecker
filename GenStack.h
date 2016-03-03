#ifndef GENSTACK_H
#define GENSTACK_H
#include <iostream>
#include <string>
using namespace std;

template <typename StackItem> //use a template to be able to use any type of data
class GenStack {

	public:
		GenStack(int maxSize);
		~GenStack();

		void push(StackItem item); 
		StackItem pop();
		StackItem peek(); 
		bool isFull(); 
		bool isEmpty(); 
		int max; 
		int top; 
		int stackLength; 
		StackItem *stackArr; 
};

template <typename StackItem> //need this above every method for templates
GenStack<StackItem>::GenStack(int maxSize) {
	stackArr = new StackItem[maxSize]; //set the stack size based on what number is passed in 
	top = -1; //set top = -1 so that you can start at zero when top incremented by 1 when pushed
	stackLength = 0; //start length at zero
	max = maxSize; //get the original max size
}

template <typename StackItem>
GenStack<StackItem>::~GenStack() {
	delete [] stackArr; //delete allocated array
}

template <typename StackItem>
void GenStack<StackItem>::push(StackItem item) { //take in a data type to add to stack array

	if (!isFull()) { 
		stackArr[++top] = item; //as long as top isn't full, add new item to the "top" of the array
		stackLength++; //increase stack length
	}
	else {
		
		max*=2; 
		StackItem *stackArr2 = new StackItem[max]; //if stack is full, double the size 

		for (int i = 0; i < stackLength; ++i) {
			stackArr2[i] = stackArr[i]; //transfer over the data from the original stack 
		}
				
		delete [] stackArr; //delete original stack data
		stackArr = stackArr2; //switch pointer to the new stack of double the size 

		stackArr[++top] = item; //add item 
		stackLength++; //increase stack length
	}
}

template <typename StackItem>
StackItem GenStack<StackItem>::pop() { //method to view and delete item

	if (isEmpty()) { 
		try {
			throw "The stack is empty (peek)."; //if the stack is empty throw an exception
		}
		catch (const char* message) {
			cerr << message << endl;
		}
	}

	return stackArr[top--]; //else return top and decrement top by 1
	stackLength--; //decrease stack length
}

template <typename StackItem>
StackItem GenStack<StackItem>::peek() {

	if(isEmpty()) {
		try {
			throw "The stack is empty (peek).";
		}
		catch (const char* message) {
			cerr << message << endl;
		}
	}
	return stackArr[top]; //return the top of the stack array 
}

template <typename StackItem>
bool GenStack<StackItem>::isFull() { return (top+1 == max); } //if the stack is full, top+1 will be equal to max because top is intially -1

template <typename StackItem>
bool GenStack<StackItem>::isEmpty() { return (top == -1); } //if top == -1, the stack is empty

#endif

