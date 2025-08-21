#include "Set.h"
#include "SetITerator.h"

Set::Set() :
	capacity{ 17 }, length{ 0 }
{
	elems = new Node* [capacity];
	for (int i = 0; i < capacity; ++i)
		elems[i] = nullptr;
}
// BC = WC = TC: Theta(capacity)

int Set::hashFunction(TElem val) const
{
	return abs(val) % capacity;
}
// BC = WC = TC: Theta(1)

void Set::resize(int cap)
{
	int oldCap = capacity;
	capacity = cap;

	Node** new_elems = new Node*[cap];
	for (int i = 0; i < cap; ++i)
		new_elems[i] = nullptr;

	for (int i = 0; i < oldCap; ++i)
	{
		Node* currNode = elems[i];
		while (currNode != nullptr)
		{
			Node* next = currNode->next;
			int pos = hashFunction(currNode->data);
			currNode->next = new_elems[pos];
			new_elems[pos] = currNode;
			currNode = next;
		}
	}

	delete[] elems;
	elems = new_elems;
}
// BC = WC = TC: Theta(capacity)

bool Set::add(TElem elem) 
{
	if (search(elem))
		return false;

	if (length == capacity)
		resize(capacity * 2);

	int pos = hashFunction(elem);
	Node* newNode = new Node;
	newNode->data = elem;
	newNode->next = elems[pos];
	elems[pos] = newNode;

	++length;
	return true;
}
// BC: Theta(1) - if we don't have an element with that hash value
//                or if we have one and is located on the first pos of the list
// WC: Theta(capacity) - if we have to resize
// TC: O(capacity)


bool Set::remove(TElem elem) 
{
	int pos = hashFunction(elem);
	Node* currNode = elems[pos];

	if (currNode == nullptr)
		return false;

	if (currNode->data == elem)
	{
		elems[pos] = currNode->next;
		delete currNode;
		--length;

		if (length < capacity / 4)
			resize(capacity / 2);

		return true;
	}

	while (currNode->next != nullptr)
	{
		if (currNode->next->data == elem)
		{
			Node* del = currNode->next;
			currNode->next = del->next;
			delete del;
			--length;

			if (length < capacity / 4)
				resize(capacity / 2);

			return true;
		}

		currNode = currNode->next;
	}

	return false;
}
// BC: Theta(1) - if we remove the head of one of the linked-lists
//                or if there in no element with that hash value
// WC: Theta(n^2) - if all the elements have the same hash value
//                and our number is located on the last pos of the list
//                and we also have to resize
// TC: O(n^2)

bool Set::search(TElem elem) const 
{
	int pos = hashFunction(elem);
	Node* currNode = elems[pos];

	while (currNode != nullptr && currNode->data != elem)
		currNode = currNode->next;

	if (currNode != nullptr)
		return true;

	return false;
}
// BC: Theta(1) - if there is no element with the same hash value
//                or is located on the first pos of the list
// WC: Theta(n) - if all the elements have the same hash value
//                and our number is located on the last pos of the list
// TC: O(n)


int Set::size() const 
{
	return length;
}
// BC = WC = TC: Theta(1)


bool Set::isEmpty() const 
{
	if (length == 0)
		return true;

	return false;
}
// BC = WC = TC: Theta(1)

Set::~Set() 
{
	for (int i = 0; i < capacity; ++i)
		if (elems[i] != nullptr)
		{
			Node* currNode = elems[i];

			while (currNode != nullptr)
			{
				Node* del = currNode;
				currNode = currNode->next;
				delete del;
			}
		}

	delete[] elems;
}
// BC = WC = TC: Theta(capacity)

int Set::difference(const Set& s)
{
	int cnt = 0;
	SetIterator it = s.iterator();

	while (it.valid())
	{
		if (remove(it.getCurrent()))
			cnt++;

		it.next();
	}

	return cnt;
}
// BC: Theta(n); n - size of the given set
// WC: Thete(n * m); n - size of the given set
//                   m - size of our set
// TC: O(n * m)


SetIterator Set::iterator() const {
	return SetIterator(*this);
}
// BC = WC = TC: Theta(1)


