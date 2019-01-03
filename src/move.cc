#include <iostream>
#include <vector>
#include <map>
#include <list>

#include "test.h"

int main()
{
//	Test t1 = 1, t2 = 2;
	std::list<Test*> l;

	Test* t1 = new Test(1);
	Test* t2 = new Test(2);


	l.push_back(t1);
	l.push_back(std::move(t2));

	delete t1;
	delete t2;

	return 0;
}
