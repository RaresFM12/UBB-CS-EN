#include "Stack.h"
#include <exception>
using namespace std;


Stack::Stack() :
	size { 0 }, capacity { 0 }, elems { nullptr }
{}
// BC = WC = TC: Theta(1)

void Stack::push(TElem e) {
	if (size == capacity)
		if (size == 0)
			resize(2);
		else
			resize(2 * capacity);

	elems[size++] = e;
}
// BC: Theata(1) - if the size is different from the capacity or if the capacity is 0
// WC: Theta(size) - if the size is equal with the capacity and different from 0
// TC: O(size)

void Stack::resize(int cap)
{
	TElem* aux = new TElem[cap];
	for (int i = 0; i < size; ++i)
		aux[i] = elems[i];

	delete[] elems;
	elems = aux;
	capacity = cap;
}
// BC = WC = TC: Theta(size)

TElem Stack::top() const {
	if (isEmpty())
		throw std::exception();

	return elems[size - 1];
}
// BC = WC = TC: Theta(1)

TElem Stack::pop() {
	if (isEmpty())
		throw std::exception();

	TElem e = elems[size - 1];
	--size;
	return e;
}
// BC = WC = TC: Theta(1)

bool Stack::isEmpty() const {
	if (size == 0)
		return true;

	return false;
}
// BC = WC = TC: Theta(1)

TElem Stack::minimum() const
{
	if (isEmpty())
		throw std::exception();

	int min = 2e9;
	for (int i = 0; i < size; ++i)
		if (elems[i] < min)
			min = elems[i];

	return min;
}
// BC: Theta(1) - if the stack is empty
// WC: Theta(size) - I have to go through all the elements anyways
// TC: O(size) 

Stack::~Stack() {
	delete[] elems;
}
// BC = WC = TC: Theta(1)
