#include <iostream>
#include "MultiMap.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "MultiMapIterator.h"
#include <cassert>

using namespace std;

void TestRemoveKey();

int main() 
{
	TestRemoveKey();
	testAll();
	testAllExtended();
	cout << "End" << endl;
	system("pause");

}

void TestRemoveKey()
{
	MultiMap m;
	m.add(1, 100);
	m.add(2, 200);
	m.add(3, 400);
	m.add(1, 200);
	m.add(1, 200);
	m.add(2, 150);

	assert(m.size() == 6);
	vector<TValue> vec = m.removeKey(1);
	assert(m.size() == 3);
	assert(vec.size() == 3);
	
	vec = m.removeKey(2);
	assert(m.size() == 1);
	assert(vec.size() == 2);

	MultiMapIterator it = m.iterator();
	assert(it.getCurrent().second == 400);
	assert(it.getCurrent().first == 3);

	cout << "Remove Key works!!!\n";
}
