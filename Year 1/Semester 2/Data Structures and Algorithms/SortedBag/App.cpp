#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <cassert>

using namespace std;

void testJumpForward();
bool relation(int a, int b);

int main() 
{
	testJumpForward();
	testAll();
	testAllExtended();
	
	cout << "Test over" << endl;
	system("pause");
}

bool relation(int a, int b)
{
	return a <= b;
}

void testJumpForward()
{
	SortedBag sb(relation);
	SortedBagIterator it = sb.iterator();
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);

	it.first();
	it.jumpForward(2);
	assert(it.getCurrent() == 5);

	it.first();
	it.jumpForward(3);
	assert(it.getCurrent() == 6);

	it.jumpForward(2);
	assert(it.getCurrent() == 10);

	it.jumpForward(1);
	assert(it.valid() == false);

	try {
		it.jumpForward(2);
	}
	catch (std::exception e) {
		assert(true);
	}

	try {
		it.jumpForward(-1);
	}
	catch (std::exception e) {
		assert(true);
	}

	try {
		it.jumpForward(0);
	}
	catch (std::exception e) {
		assert(true);
	}

	it.first();
	it.jumpForward(6);
	assert(it.valid() == false);

	std::cout << "Test new functionality!\n";
}
