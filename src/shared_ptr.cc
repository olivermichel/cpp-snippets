
#include <memory>
#include <iostream>
#include <list>

#include "test.h"

void set_test_number(std::shared_ptr<Test>& t, int number)
{
	t->set_number(number);
	std::cout << "set_test_number: t.use_count(): " << t.use_count() << std::endl;
}

int main()
{
	std::list<std::shared_ptr<Test>> list;

	{
		// raw pointer to new object that will be leaked
//		Test* t1 = new Test(1);

//		auto t2(std::make_shared<Test>(2)); // prefer over std::shared_ptr<Test> t2(new Test(2))

		std::shared_ptr<Test> t2(new Test(2), [](Test* t) {
			std::cout << "deallocate Test";
			delete t;
		});

		// reference count 1
		std::cout << "t2.use_count(): " << t2.use_count() << std::endl;

//		list.push_back(t2); // will copy -> reference count 2
		list.push_back(std::move(t2)); // will move -> reference count 1

		// reference count 2 if copied, 1 if moved
		std::cout << "t2.use_count(): " << t2.use_count() << std::endl;

		for (auto& t : list) {
			std::cout << "for(auto t : list): t.use_count(): " << t.use_count() << std::endl;
			set_test_number(t, 5);
		}



	} // t1 leaked

	// list is still in scope and holds a copy of the t2 object if t2 got copied
	std::cout << list.front().use_count() << std::endl;

	return 0;
}
