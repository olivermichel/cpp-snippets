
#include "../include/test.h"

#include <list>

template <typename T>
class container
{
public:
	container() : _items() { }

	container(const container&) = default;
	container& operator=(const container&) = default;
	container(container&&) noexcept = default;
	container& operator=(container&&) noexcept = default;

	template <typename F>
	static void _times(unsigned n_, F f_)
	{
		for (unsigned i = 0; i < n_; i++) f_();
	}

	template <typename... Args>
	explicit container(unsigned n_, Args&&... args_) : _items()
	{
		_times(n_, [&]() { _items.emplace_back(std::forward<Args>(args_)...); });
	}

	template <typename... Args>
	void add(Args&&... args_)
	{
		_items.emplace_back(std::forward<Args>(args_)...);
	}

private:
	std::list<T> _items;
};

int main(int argc_, char** argv_)
{
	container<Test> c(3, 4);

	return 0;
}
