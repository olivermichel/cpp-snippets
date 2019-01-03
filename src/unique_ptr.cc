
#include <memory>
#include <iostream>
#include <list>

#include "../include/test.h"

auto test_deleter = [](Test* t){
	std::cout << "deallocate test" << std::endl;
	delete t;
};

void set_test_number(std::unique_ptr<Test, decltype(test_deleter)>& t, int number)
{
	t->set_number(5);
}

int main()

{
//	auto test_deleter = [](Test* t) {
//		std::cout << "deallocate Test" << std::endl;
//		delete t;
//	};

	{
		std::list<std::unique_ptr<Test, decltype(test_deleter)>> list;

//		Test* t1 = new Test(1);
		std::unique_ptr<Test, decltype(test_deleter)> t2(new Test(2), test_deleter);

//		list.push_back(t2); // will cause compile time error because t2 is unique
		list.push_back(std::move(t2));

		for (auto& t : list)
			set_test_number(t, 5);

		list.remove(list.front());




		std::cout << "going out of scope" << std::endl;
	} // t2 deconstructed, t1 leaked

	return 0;
}
