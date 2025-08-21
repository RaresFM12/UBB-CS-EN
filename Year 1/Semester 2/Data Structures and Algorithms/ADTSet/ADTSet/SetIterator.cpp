#include "SetIterator.h"
#include "Set.h"


SetIterator::SetIterator(const Set& m) : set(m)
{
	currPos = 0;
	while (currPos < m.capacity && m.elems[currPos] == nullptr)
		++currPos;

	if (currPos < m.capacity)
		currNode = m.elems[currPos];
	else
		currNode = nullptr;
}
// BC: Theta(1) - if it is on the first location of the list
// WC: Theta(capacity) - if it is not in the list or is on the last pos
//                       of the array
// TC: O(capacity) 

void SetIterator::first() 
{
	currPos = 0;
	while (currPos < set.capacity && set.elems[currPos] == nullptr)
		++currPos;

	if (currPos < set.capacity)
		currNode = set.elems[currPos];
	else
		currNode = nullptr;
}
// BC: Theta(1) - if it is on the first location of the list
// WC: Theta(capacity) - if it is not in the list or is on the last pos
//                       of the array
// TC: O(capacity) 

void SetIterator::next() 
{
	if (!valid())
		throw std::exception();

	if (currNode->next != nullptr)
	{
		currNode = currNode->next;
		return;
	}

	currPos++;
	while (currPos < set.capacity && set.elems[currPos] == nullptr)
		currPos++;

	if (currPos < set.capacity)
		currNode = set.elems[currPos];
	else
		currNode = nullptr;
}
// BC: Theta(1) - if we have a next element with the same hash value
// WC: Theta(capacity) - if it is not in the list or is on the last pos
//                       of the array
// TC: O(capacity) 


TElem SetIterator::getCurrent()
{
	if (!valid())
		throw std::exception();

	return currNode->data;
}
// BC = WC = TC: Theta(1)

bool SetIterator::valid() const 
{
	if (currPos == set.capacity)
		return false;

	return true;
}
// BC = WC = TC: Theta(1)



