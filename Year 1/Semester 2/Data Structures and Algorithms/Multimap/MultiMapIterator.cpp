#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) 
{
	currentPos = col.head;
}
// BC = WC = TC: Theta(1)

TElem MultiMapIterator::getCurrent() const
{
	if (!valid())
		throw exception();

	return col.elems[currentPos];
}
// BC = WC = TC: Theta(1)

bool MultiMapIterator::valid() const 
{
	if (currentPos == -1)
		return false;

	return true;
}
// BC = WC = TC: Theta(1)

void MultiMapIterator::next() 
{
	if (!valid())
		throw exception();

	currentPos = col.next[currentPos];
}
// BC = WC = TC: Theta(1)

void MultiMapIterator::first() 
{
	currentPos = col.head;
}
// BC = WC = TC: Theta(1)

