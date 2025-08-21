#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap& mapionar);
	void DFS(int node);

	//TODO - Representation
	int currentPos;
	int capacity;
	int nrElems;
	Node* elems;

public:
	~SMIterator();
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;
};

