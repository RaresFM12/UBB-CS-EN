#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SortedMap::SortedMap(Relation r) :
	rel {r}, capacity {0}, length {0}, next{ nullptr },
	elems {nullptr}, root {-1}, firstEmpty {-1}
{}
// BC = WC = TC: Theta(1)

void SortedMap::resize(int cap)
{
	Node* new_elems = new Node[cap];
	int* new_next = new int[cap];

	for (int i = 0; i < capacity; ++i)
	{
		new_next[i] = next[i];
		new_elems[i] = elems[i];
	}

	for (int i = capacity; i < cap; ++i)
	{
		new_next[i] = i + 1;
		new_elems[i].info.first = NULL_TVALUE;
		new_elems[i].info.second = NULL_TVALUE;
		new_elems[i].left = -1;
		new_elems[i].right = -1;
	}
	new_next[cap - 1] = -1;
		
	if (firstEmpty == -1)
		firstEmpty = capacity;

	delete[] elems;
	delete[] next;

	elems = new_elems;
	next = new_next;
	capacity = cap;
}
// BC = WC = TC: Theta(capacity)

void SortedMap::addAccordingToRelation(int pos, TKey k, TValue v)
{
	if (elems[pos].info.first == NULL_TVALUE)
	{
		elems[pos].info.first = k;
		elems[pos].info.second = v;
		length++;
		return;
	}

	if (rel(k, elems[pos].info.first))
	{
		if (elems[pos].left == -1)
		{
			elems[pos].left = firstEmpty;
			firstEmpty = next[firstEmpty];
			addAccordingToRelation(elems[pos].left, k, v);
		}
		else
			addAccordingToRelation(elems[pos].left, k, v);
	}
	else
	{
		if (elems[pos].right == -1)
		{
			elems[pos].right = firstEmpty;
			firstEmpty = next[firstEmpty];
			addAccordingToRelation(elems[pos].right, k, v);
		}
		else
			addAccordingToRelation(elems[pos].right, k, v);
	}
}
// BC: Theta(1) - if the element is added on the leftside or the rightside 
//                of the root
// WC: Theta(n) - if the elements are in decreasing or increasing order
//                and our new element is the smallest or the largest
// TC: O(n)


TValue SortedMap::add(TKey k, TValue v) 
{
	if (firstEmpty == -1)
		if (capacity == 0)
			resize(3);
		else
			resize(capacity * 2);

	if (root == -1)
	{
		length++;
		elems[0].info.first = k;
		elems[0].info.second = v;
		elems[0].left = -1;
		elems[0].right = -1;
		root = firstEmpty;
		firstEmpty = next[firstEmpty];

		return NULL_TVALUE;
	}

	int currPos = root;
	while (currPos != -1)
	{
		if (elems[currPos].info.first == k)
		{
			TValue val = elems[currPos].info.second;
			elems[currPos].info.second = v;
			return val;
		}

		else if (rel(k, elems[currPos].info.first))
			currPos = elems[currPos].left;

		else
			currPos = elems[currPos].right;
	}

	addAccordingToRelation(root, k, v);
	return NULL_TVALUE;
}
// BC: Theta(1) - if it's the root
// WC: Theta(n) - if the elements are in decreasing or increasing order
//                and our new element is the smallest or the largest, 
//                or we have to resize
// TC: O(n)

TValue SortedMap::search(TKey k) const 
{
	int currPos = root;
	while (currPos != -1)
	{
		if (elems[currPos].info.first == k)
			return elems[currPos].info.second;

		else if (rel(k, elems[currPos].info.first))
			currPos = elems[currPos].left;

		else
			currPos = elems[currPos].right;
	}

	return NULL_TVALUE;
}
// BC: Theta(1) - if it's the root
// WC: Theta(n) - if the elements are in decreasing or increasing order
//                and our new element is the smallest or the largest
// TC: O(n)

TValue SortedMap::remove(TKey k) 
{
	int currPos = root;
	int parent = -1;

	while (currPos != -1)
	{
		if (elems[currPos].info.first == k)
		{
			if (elems[currPos].left == -1 && elems[currPos].right == -1)
			{
				TValue val = elems[currPos].info.second;
				deleteNodeWithNoChildren(currPos, parent);
				length--;

				next[currPos] = firstEmpty;
				firstEmpty = currPos;
				elems[currPos].info.first = NULL_TVALUE;
				elems[currPos].info.second = NULL_TVALUE;
				return val;
			}

			if (elems[currPos].left == -1 || elems[currPos].right == -1)
			{
				TValue val = elems[currPos].info.second;
				deleteNodeWithOneChildren(currPos, parent);
				length--;

				next[currPos] = firstEmpty;
				firstEmpty = currPos;
				elems[currPos].info.first = NULL_TVALUE;
				elems[currPos].info.second = NULL_TVALUE;
				return val;
			}

			TValue val = elems[currPos].info.second;
			deleteNodeWithTwoChildren(currPos);
			length--;

			next[currPos] = firstEmpty;
			firstEmpty = currPos;
			return val;
		}
		else if (rel(k, elems[currPos].info.first))
		{
			parent = currPos;
			currPos = elems[currPos].left;
		}
		else
		{
			parent = currPos;
			currPos = elems[currPos].right;
		}

	}

	return NULL_TVALUE;
}
// BC: Theta(1) - if it's the root and it has no child, or 1 child
// WC: Theta(n) - if all the nodes are in ascending order or descending
//                and out node is the last
// TC: O(n)



void SortedMap::deleteNodeWithNoChildren(int curr, int par)
{
	if (par == -1)
		root = -1;

	else if (elems[par].left == curr)
		elems[par].left = -1;
	
	else
		elems[par].right = -1;
}
// BC = WC = TC: Theta(1)

void SortedMap::deleteNodeWithOneChildren(int curr, int par)
{
	if (elems[curr].left == -1)
	{
		if (par == -1)
			root = elems[curr].right;

		else if (elems[par].left == curr)
			elems[par].left = elems[curr].right;

		else
			elems[par].right = elems[curr].right;

		return;
	}

	if (par == -1)
		root = elems[curr].left;

	else if (elems[par].left == curr)
		elems[par].left = elems[curr].left;

	else
		elems[par].right = elems[curr].left;
}
// BC = WC = TC: Theta(1)

void SortedMap::deleteNodeWithTwoChildren(int curr)
{
	int minPos = elems[curr].right;
	int minParentPos = curr;

	while (elems[minPos].left != -1)
	{
		minParentPos = minPos;
		minPos = elems[minPos].left;
	}

	elems[curr].info.first = elems[minPos].info.first;
	elems[curr].info.second = elems[minPos].info.second;

	if (elems[minPos].right != -1)
		deleteNodeWithOneChildren(minPos, minParentPos);
	else
		deleteNodeWithNoChildren(minPos, minParentPos);

	elems[minPos].info.first = NULL_TVALUE;
	elems[minPos].info.second = NULL_TVALUE;
}
// BC: Theta(1) - if the right node has no left child
// WC: Theta(n) - if the right node has only left children
// TC: O(n)

int SortedMap::getKeyRange() const
{
	if (isEmpty())
		return -1;

	TKey minKey;
	TKey maxKey;
	SMIterator it = iterator();
	minKey = it.getCurrent().first;

	while (it.valid())
	{
		maxKey = it.getCurrent().first;
		it.next();
	}

	return maxKey - minKey;
}
// BC: Theta(1) - the list is empty
// WC: Theta(n)
// TC: O(n)

int SortedMap::size() const 
{
	return length;
}
// BC = WC = TC: Theta(1)

bool SortedMap::isEmpty() const 
{
	if (length == 0)
		return true;

	return false;
}
// BC = WC = TC: Theta(1)

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}
// BC = WC = TC: Theta(1)

SortedMap::~SortedMap() 
{
	delete[] elems;
	delete[] next;
}
// BC = WC = TC: Theta(1)
