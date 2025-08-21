#include "Queue.h"
#include <exception>
#include <iostream>

using namespace std;


Queue::Queue() :
	front { -1 }, rear { -1 }, size { 0 }, capacity { 0 }, elems { nullptr }
{}
// BC = WC = TC: Theta(1)

void Queue::push(TElem elem) {
	if (size == capacity)
		if (size == 0)
			resize(1);
		else
			resize(2 * capacity);

	if (isEmpty())
	{
		front = 0;
		rear = 0;
		elems[rear] = elem;
		++size;
		return;
	}
		

	rear = (rear + 1) % capacity;
	elems[rear] = elem;
	++size;
}
// BC: Theta(1) - if the size is different from the capacity or if the capacity is 0
// WC: Theta(size) - if the size is equal with the capacity and different from 0
// TC: O(size)

void Queue::resize(int cap)
{
	TElem* aux = new TElem[cap];
 
	for (int i = 0; i < size; ++i)
	{
		aux[i] = elems[front % size];
		++front;
	}
	
	delete[] elems;
	elems = aux;
	capacity = cap;
	front = 0;
	rear = size - 1;
}
// BC = WC = TC: Theta(size)

TElem Queue::top() const {
	if (isEmpty())
		throw std::exception();

	return elems[front];
}
// BC = WC = TC: Theta(1)

TElem Queue::pop() {
	if (isEmpty())
		throw std::exception();

	if (front == rear)
	{
		TElem e = elems[front];
		front = -1;
		rear = -1;
		--size;
		return e;
	}

	TElem e = elems[front];
	front = (front + 1) % capacity;
	--size;

	return e;
}
// BC = WC = TC: Theta(1)

bool Queue::isEmpty() const {
	if (front == -1 && rear == -1)
		return true;

	return false;
}
// BC = WC = TC: Theta(1)

Queue::~Queue() {
	delete[] elems;
}
// BC = WC = TC: Theta(1)

