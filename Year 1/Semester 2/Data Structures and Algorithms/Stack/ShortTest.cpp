#include "ShortTest.h"
#include "Stack.h"
#include <assert.h>
#include <exception>

void testAll() { 
	Stack s;
	assert(s.isEmpty() == true);
	s.push(5);
	s.push(1);
	s.push(10);
	assert(s.isEmpty() == false);
	assert(s.top() == 10);
	assert(s.pop() == 10);
	assert(s.top() == 1);
	assert(s.pop() == 1);
	assert(s.top() == 5);
	assert(s.pop() == 5);
	assert(s.isEmpty() == true);
	
	try {
		s.minimum();
	}
	catch (const std::exception& e)
	{
		assert(true);
	}
		

	s.push(5);
	s.push(3);
	s.push(10);
	s.push(11);
	assert(s.minimum() == 3);
	s.pop();
	assert(s.minimum() == 3);
}