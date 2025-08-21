#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std;


FixedCapBiMapIterator::FixedCapBiMapIterator(const FixedCapBiMap& d) : map(d)
{
	this->currentPos = 0;
}
// BC = WC = TC: Theta(1)

void FixedCapBiMapIterator::first() 
{
	this->currentPos = 0;
}
// BC = WC = TC: Theta(1)

void FixedCapBiMapIterator::next() {
	if (this->currentPos == this->map.mapSize)  // fac operatorul invalid
		throw exception();

	this->currentPos++;
}
// BC = WC = TC: Theta(1)

void FixedCapBiMapIterator::previous() {
	if (this->currentPos < 0)  // fac operatorul invalid
		throw exception();

	this->currentPos--;
}
// BC = WC = TC: Theta(1)

TElem FixedCapBiMapIterator::getCurrent(){
	if (this->currentPos == this->map.mapSize)
		throw exception();

	return this->map.elements[this->currentPos];
}
// BC = WC = TC: Theta(1)

bool FixedCapBiMapIterator::valid() const {
	return (this->currentPos < this->map.mapSize) && (this->currentPos >= 0);
}
// BC = WC = TC: Theta(1)


