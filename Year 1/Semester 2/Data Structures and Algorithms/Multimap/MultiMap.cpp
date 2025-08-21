#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() :
	length {0}, capacity {0}, elems {nullptr}, next {nullptr},
	prev{nullptr}, head {-1}, tail {-1}, firstEmpty {-1}
{}
// BC = WC = TC: Theta(1)

void MultiMap::add(TKey c, TValue v) 
{
	if (firstEmpty == -1)
		if (capacity == 0)
			resize(2);
		else
			resize(2 * capacity);

	int currPos = firstEmpty;
	firstEmpty = next[firstEmpty];

	elems[currPos] = make_pair(c, v);
	next[currPos] = -1;
	prev[currPos] = tail;

	if (tail != -1)
		next[tail] = currPos;

	if (head == -1)
		head = currPos;

	tail = currPos;
	++length;
}
// BC: Theta(1) - if we have empty spaces in the array
// WC: Theta(capacity) - if there are no empty spaces in the array
// TC: O(capacity)

void MultiMap::resize(int cap)
{
	TElem* new_elems = new TElem[cap];
	int* new_next = new int[cap];
	int* new_prev = new int[cap];

	for (int i = 0; i < capacity; ++i)
	{
		new_elems[i] = elems[i];
		new_next[i] = next[i];
		new_prev[i] = prev[i];
	}
		
	for (int i = capacity; i < cap - 1; ++i)
	{
		new_next[i] = i + 1;
		new_prev[i] = -1;
	}
	new_next[cap - 1] = -1;

	if (firstEmpty == -1) 
		firstEmpty = capacity;
	
	delete[] elems;
	delete[] next;
	delete[] prev;

	elems = new_elems;
	next = new_next;
	prev = new_prev;
	capacity = cap;
}
// BC = WC = TC: Theta(capacity)

bool MultiMap::remove(TKey c, TValue v) 
{
	if (head == -1 || tail == -1)
		return false;

	if (elems[head].first == c && elems[head].second == v)
	{
		int curr = head;
		head = next[head];

		if (head != -1)
			prev[head] = -1;
		length--;

		next[curr] = firstEmpty;
		prev[curr] = -1;
		firstEmpty = curr;

		return true;
	}

	if (elems[tail].first == c && elems[tail].second == v)
	{
		int curr = tail;
		tail = prev[tail];

		if (tail != -1)
			next[tail] = -1;
		length--;

		next[curr] = firstEmpty;
		prev[curr] = -1;
		firstEmpty = curr;

		
		return true;
	}

	for (int i = head; i != tail; i = next[i])
		if (elems[i].first == c && elems[i].second == v)
		{
			int pred = prev[i];
			int suc = next[i];
			next[pred] = next[i];
			prev[suc] = prev[i];
			length--;

			next[i] = firstEmpty;
			prev[i] = -1;
			firstEmpty = i;

			return true;
		}

	return  false;
}
// BC: Theta(1) - if the value is on the head or the tail 
// WC: Theta(length) - if the value is on the second to last position in the array
//					   or is not in the array
// TC: O(length)

vector<TValue> MultiMap::removeKey(TKey key)
{
	vector<TValue> vec;
	int i = head;
	while (i != -1)
		if (elems[i].first == key)
		{
			vec.push_back(elems[i].second);
			TValue val = elems[i].second;
			i = next[i];
			remove(key, val);
		}
		else
			i = next[i];

	return vec;
}
// BC: Theta(n)
// WC: Theta(n^2)
// TC: O(n^2)

vector<TValue> MultiMap::search(TKey c) const 
{
	vector<TValue> vec;
	for (int i = head; i != -1; i = next[i])
		if (elems[i].first == c)
			vec.push_back(elems[i].second);

	return vec;
}
// BC = WC = TC: Theta(length)

int MultiMap::size() const 
{
	return length;
}
// BC = WC = TC: Theta(1)

bool MultiMap::isEmpty() const 
{
	if (length == 0)
		return true;

	return false;
}
// BC = WC = TC: Theta(1)

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}
// BC = WC = TC: Theta(1)

MultiMap::~MultiMap() 
{
	delete[] elems;
	delete[] next;
	delete[] prev;
}
// BC = WC = TC: Theta(1)

