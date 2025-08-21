#pragma once
//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -111111

class Stack
{
private:
	int size;
	int capacity;
	TElem* elems;

	void resize(int cap);
	
public:

	//constructor
	Stack();
	
	//pushes an element to the top of the Stack
	void push(TElem e);
	
	//returns the element from the top of the Stack
	//throws exception if the stack is empty
	TElem top() const;
	   
	//removes and returns the element from the top of the Stack
	//throws exception if the stack is empty
	TElem pop();
	   
	//checks if the stack is empty
	bool isEmpty() const;

	//returns the minimum element from the Stack
	//throws an exception if the Stack is empty
	TElem minimum() const;
	
	//destructor
	~Stack();
};

