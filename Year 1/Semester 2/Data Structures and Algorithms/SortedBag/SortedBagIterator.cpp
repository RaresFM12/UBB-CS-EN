#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) 
{	
	current = bag.head;
	curr_freq = 1;
}
// BC = WC = TC: Theta(1)

TComp SortedBagIterator::getCurrent() 
{
	if (!valid())
		throw std::exception();

	return current->info.first;
}
// BC = WC = TC: Theta(1)

bool SortedBagIterator::valid() 
{
	if (current == nullptr)
		return false;

	return true;
}
// BC = WC = TC: Theta(1)

void SortedBagIterator::next() 
{
	if (current == nullptr)
		throw std::exception();

	curr_freq++;
	if (curr_freq <= current->info.second)
		return;

	Node* n = current->next;
	current = n;
	curr_freq = 1;
}
// BC = WC = TC: Theta(1)

void SortedBagIterator::first() 
{
	current = bag.head;
	curr_freq = 1;
}
// BC = WC = TC: Theta(1)

void SortedBagIterator::jumpForward(int k)
{
	if (current == nullptr)
		throw std::exception();

	if (k <= 0)
		throw std::exception();

	int cnt = 0;
	while (current != nullptr && cnt < k)
	{
		curr_freq++;
		cnt++;

		if (curr_freq > current->info.second)
		{
			Node* n = current->next;
			current = n;
			curr_freq = 1;
		}
	}
}
// BC: Theta(1) - if current is on the last position
// WC: Theta(k) - if we have left in tha bag more than k elements in the bag
// TC: O(k)

