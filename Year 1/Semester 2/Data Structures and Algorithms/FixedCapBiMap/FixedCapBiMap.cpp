#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"

FixedCapBiMap::FixedCapBiMap(int capacity) {
	if (capacity <= 0)
		throw exception();

	this->capacity = capacity;
	this->mapSize = 0;
	this->elements = new TElem[this->capacity];
}
// BC = WC = TC: Theta(1)

FixedCapBiMap::~FixedCapBiMap() {
	delete[] this->elements;
}
// BC = WC = TC: Theta(1)

bool FixedCapBiMap::add(TKey c, TValue v){
	if (this->mapSize == this->capacity)
		throw exception();

	int cnt = 0;
	int ind = 0;
	while (cnt < 2 && ind < this->mapSize)
	{
		if (this->elements[ind].first == c)
			cnt++;

		ind++;
	}

	if (cnt == 2)
		return false;

	this->elements[this->mapSize].first = c;
	this->elements[this->mapSize].second = v;
	this->mapSize++;
	return true;
}
// BC = Theta(1) - when the first 2 keys from the map are equal to c
// WC = Theta(mapSize) - when the key c appears only 1 or 0 times
// TC = O(mapSize) 

ValuePair FixedCapBiMap::search(TKey c) const{
	ValuePair vp;
	vp.first = NULL_TVALUE;
	vp.second = NULL_TVALUE;

	int cnt = 0;
	int ind = 0;

	while (cnt < 2 && ind < this->mapSize)
	{
		if (this->elements[ind].first == c)
		{
			if (cnt == 0)
				vp.first = this->elements[ind].second;

			if (cnt == 1)
				vp.second = this->elements[ind].second;

			++cnt;
		}

		++ind;
	}

	return vp;
}
// BC = Theta(1) - when the first 2 keys from the map are equal to c
// WC = Theta(mapSize) - when the key c appears only 1 or 0 times
// TC = O(mapSize) 

bool FixedCapBiMap::remove(TKey c, TValue v){
	for (int i = 0; i < mapSize; ++i)
		if (this->elements[i].first == c && this->elements[i].second == v)
		{
			this->elements[i] = this->elements[mapSize - 1];
			--mapSize;
			return true;
		}

	return false;
}
// BC = Theta(1) - when the first the pair is on the first position
// WC = Theta(mapSize) - when the pair is on the last position or is not in the array
// TC = O(mapSize) 

int FixedCapBiMap::size() const {
	return mapSize;
}
// BC = WC = TC: Theta(1)

bool FixedCapBiMap::isEmpty() const{
	return mapSize == 0;
}
// BC = WC = TC: Theta(1)

bool FixedCapBiMap::isFull() const {
	return this->capacity == this->mapSize;
}
// BC = WC = TC: Theta(1)

FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}
// BC = WC = TC: Theta(1)



