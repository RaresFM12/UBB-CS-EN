#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>

SortedBag::SortedBag(Relation r) : 
	rel {r}, head {nullptr}, tail {nullptr}, len {0}
{}
// BC = WC = TC: Theta(1)

void SortedBag::add(TComp e) 
{
	// in case the bag is empty
	if (isEmpty())
	{
		head = new Node();
		head->info.first = e;
		head->info.second = 1;
		head->next = nullptr;
		head->prev = nullptr;
		tail = head;
		++len;

		return;
	}

	// in case is smaller than the head
	if (rel(e, head->info.first))
	{
		if (e == head->info.first) // if has the same value as the head
		{
			head->info.second++;
			++len;
			return;
		}

		Node* new_node = new Node();
		new_node->info.first = e;
		new_node->info.second = 1;
		new_node->next = head;
		new_node->prev = nullptr;
		head->prev = new_node;
		head = new_node;
		++len;

		return;
	}

	// in case is bigger than the tail
	if (!rel(e, tail->info.first))
	{
		if (e == tail->info.first) // if has the same value as the tail
		{
			tail->info.second++;
			++len;
			return;
		}

		Node* new_node = new Node();
		new_node->info.first = e;
		new_node->info.second = 1;
		new_node->next = nullptr;
		new_node->prev = tail;
		tail->next = new_node;
		tail = new_node;
		++len;

		return;
	}

	// if the node is somewhere in the bag
	Node* curr = head;
	while (curr->next != nullptr && rel(curr->next->info.first, e))
	{
		
		Node* n = curr->next;
		curr = n;
		n = nullptr;
	}

	if (curr->info.first == e) // if the value is equal
	{
		curr->info.second++;
		++len;
		return;
	}
	
	Node* new_node = new Node();
	new_node->info.first = e;
	new_node->info.second = 1;
	new_node->prev = curr;
	new_node->next = curr->next;
	
	Node* n = curr->next;
	curr->next = new_node;
	n->prev = new_node;
	++len;

	return;
}
// BC: Theta(1) - if the element is smaller or equal than the head, or larger or equal than the tail
// WC: Theta(size) - if it's on the second to last position
// TC: O(size) - if it's somewhere in the list


bool SortedBag::remove(TComp e) 
{
	if (head == nullptr)
		return false;

	Node* node = head;

	while (node != nullptr)
	{
		if (e == node->info.first)
		{
			if (node->info.second == 1) // if it's the last occurence of that value
			{
				if (node == head)
				{
					Node* n = node->next;
					delete node;
					head = n;

					if (head != nullptr)
						head->prev = nullptr;
					--len;

					return true;
				}

				if (node == tail)
				{
					Node* n = node->prev;
					delete node;
					tail = n;

					if (tail != nullptr)
						tail->next = nullptr;
					--len;

					return true;
				}

				Node* n = node->next;
				Node* p = node->prev;
				p->next = n;
				n->prev = p;
				delete node;
				--len;

				return true;
			}

			node->info.second--;
			--len;
			return true;
		}

		Node* n = node->next;
		node = n;
	}

	return false;
}
// BC: Theta(1) - if it's the head, on the first position
// WC: Theta(size) - if it's the tail, on the last position or is not in the list
// TC: O(size) - if it's somewhere on the list


bool SortedBag::search(TComp elem) const 
{
	if (head == nullptr)
		return false;

	if (elem == head->info.first)
		return true;

	if (elem == tail->info.first)
		return true;

	Node* node = head;
	while (node->next != nullptr)
	{
		if (elem == node->info.first)
			return true;

		Node* n = node->next;
		node = n;
	}

	return false;
}
// BC: Theta(1) - if it's the head or the tail
// WC: Theta(size) - if it's on the second to last position in the list or is not in the list
// TC: O(size) - if it's somewhere in the list

int SortedBag::nrOccurrences(TComp elem) const 
{
	if (head == nullptr)
		return false;

	if (elem == head->info.first)
		return head->info.second;

	if (elem == tail->info.first)
		return tail->info.second;

	Node* node = head;
	while (node->next != nullptr)
	{
		if (node->info.first == elem)
			return node->info.second;

		Node* n = node->next;
		node = n;
	}
		
	return 0;
}
// BC: Theta(1) - if it's the head or the tail
// WC: Theta(size) - if it's on the second to last position or is not in the list
// TC: O(size) - if it's somewhere in the list

int SortedBag::size() const 
{
	return len;
}
// BC = WC = TC: Theta(1)


bool SortedBag::isEmpty() const 
{
	if (len == 0)
		return true;

	return false;
}
// BC = WC = TC: Theta(1)

SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}
// BC = WC = TC: Theta(1)

void SortedBag::deleteList(Node* curr)
{
	if (curr == nullptr)
		return;

	deleteList(curr->next);
	delete curr;
}
// BC = WC = TC: Theta(size)

SortedBag::~SortedBag() 
{
	deleteList(head);
}
// BC = WC = TC: Theta(size)
