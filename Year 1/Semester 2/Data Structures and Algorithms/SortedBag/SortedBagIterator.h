#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	Node* current;
	int curr_freq;

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
	void jumpForward(int k);
};

