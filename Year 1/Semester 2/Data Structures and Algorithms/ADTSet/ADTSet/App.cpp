#include "Set.h"
#include "SetIterator.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <stack>
#include <iostream>
#include <cassert>
using namespace std;

void TestDifference();

int main() 
{
	TestDifference();
	testAll();
	testAllExtended();

	cout << "That's all!" << endl;
	system("pause");
}

void TestDifference()
{
	Set s1;
	s1.add(1);
	s1.add(2);
	s1.add(3);
	s1.add(4);
	s1.add(5);
	s1.add(6);
	s1.add(8);

	Set s2;
	s2.add(3);
	s2.add(1);
	s2.add(5);
	s2.add(7);
	s2.add(9);
	s2.add(1);
	s2.add(2);
	s2.add(3);
	s2.add(4);
	s2.add(5);
	s2.add(6);
	s2.add(8);

	assert(s1.size() == 7);
	//assert(s2.size() == 5);

	int cnt = s1.difference(s2);
	//assert(cnt == 3);
	assert(s1.size() == 0);

	cout << "Test Difference Done!\n";
}



