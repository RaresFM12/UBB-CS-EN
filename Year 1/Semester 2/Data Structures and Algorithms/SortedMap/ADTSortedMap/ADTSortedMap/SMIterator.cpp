#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

void SMIterator::DFS(int node)
{
	if (node == -1)
		return;

	DFS(map.elems[node].left);

	elems[nrElems].info.first = map.elems[node].info.first;
	elems[nrElems].info.second = map.elems[node].info.second;
	elems[nrElems].left = map.elems[node].left;
	elems[nrElems].right = map.elems[node].right;
	nrElems++;

	DFS(map.elems[node].right);
}
// BC: Theta(1) - if the list is empty
// WC: Theta(n)
// TC: O(n)

SMIterator::SMIterator(const SortedMap& m) : map(m)
{
	capacity = map.capacity;
	elems = new Node[capacity];
	currentPos = 0;
	nrElems = 0;
	DFS(map.root);
}
// BC: Theta(1)
// WC: Theta(n)
// TC: O(n)

void SMIterator::first()
{
	currentPos = 0;
}
// BC = WC = TC: Theta(1)

void SMIterator::next()
{
	if (!valid())
		throw exception();

	currentPos++;
}
// BC = WC = TC: Theta(1)

bool SMIterator::valid() const
{
	if (currentPos < nrElems)
		return true;

	return false;
}
// BC = WC = TC: Theta(1)

TElem SMIterator::getCurrent() const
{
	if (!valid())
		throw exception();

	return elems[currentPos].info;
}
// BC = WC = TC: Theta(1)

SMIterator::~SMIterator()
{
	delete[] elems;
}
// BC = WC = TC: Theta(1)

