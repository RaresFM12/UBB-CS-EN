#include "ExtendedTest.h"
#include "ShortTest.h"

#include "SortedMap.h"

#include <iostream>
#include <cassert>
using namespace std;

void TestGetKeyRange();

bool relatieTest(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

int main() {
	testAll();
	testAllExtended();
	TestGetKeyRange();

	cout << "That's all!" << endl;
	system("pause");
	return 0;
}

void TestGetKeyRange()
{
	SortedMap sm(relatieTest);
	sm.add(4, 5);
	sm.add(6, 2);
	sm.add(3, 1);
	sm.add(5, 5);
	sm.add(2, 8);
	sm.add(4, 5);

	assert(sm.getKeyRange() == 4);
	sm.remove(5);
	sm.remove(2);
	sm.remove(3);
	assert(sm.getKeyRange() == 2);

	sm.remove(4);
	sm.remove(6);
	assert(sm.isEmpty() == true);
	assert(sm.getKeyRange() == -1);
	cout << "Test has finished!\n";
}
