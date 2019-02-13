
#include <iostream>

class Test
{
public:
	Test()
		: _number(-1)
	{
		std::cout << "Test()" << std::endl;
	};

	explicit Test(int number)
		: _number(number)
	{
		std::cout << "Test(" << number << ")" << std::endl;
	}

	Test(const Test& copy_from)
		: _number(copy_from._number)
	{
		std::cout << "Test(const Test&) : " << _number << std::endl;
	}

	Test(Test&& move_from) noexcept
		: _number(move_from._number)
	{
		std::cout << "Test(Test&&) : " << _number << std::endl;
	}

	Test& operator=(const Test& copy_from)
	{
		_number = copy_from._number;
		std::cout << "operator=(const Test&) : " << _number << std::endl;
		return *this;
	}

	Test& operator=(Test&& move_from) noexcept
	{
		_number = move_from._number;
		std::cout << "operator=(Test&&) : " << _number << std::endl;
		return *this;
	}

	int number() const
	{
		return _number;
	}

	void set_number(int n)
	{
		_number = n;
	}

	virtual ~Test()
	{
		std::cout << "~Test() : " << _number << std::endl;
	}

private:
	int _number;
};
