
#include <chrono>
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

template<typename T>
class concurrent_queue
{
public:
	concurrent_queue() = default;

	void push(T new_value)
	{
		std::lock_guard<std::mutex> lk(_mutex);
		_queue.push(std::move(new_value));
		_condition.notify_one();
	}

/*
	void wait_and_pop(T& value)
	{
		std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk,[this]{return !data_queue.empty();});
		value=std::move(data_queue.front());
		data_queue.pop();
	}
	std::shared_ptr<T> wait_and_pop()
	{
		std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk,[this]{return !data_queue.empty();});
		std::shared_ptr<T> res(std::make_shared<T>(std::move(data_queue.front())));
		data_queue.pop();
		return res;
	}
*/

	bool try_pop(T& value)
	{
		std::lock_guard<std::mutex> lk(_mutex);

		if(_queue.empty())
			return false;

		value = std::move(_queue.front());
		_queue.pop();
		return true;
	}

	std::shared_ptr<T> try_pop()
	{
		std::lock_guard<std::mutex> lk(_mutex);

		if(_queue.empty())
			return std::shared_ptr<T>();

		std::shared_ptr<T> res(std::make_shared<T>(std::move(_queue.front())));
		_queue.pop();
		return res;
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lk(_mutex);
		return _queue.empty();
	}

private:
	mutable std::mutex _mutex;
	std::queue<T> _queue;
	std::condition_variable _condition;
};

class thread_joiner
{
public:
	explicit thread_joiner(std::vector<std::thread>& threads_) : _threads(threads_) { }

	~thread_joiner()
	{
		for (auto& t : _threads)
			if (t.joinable()) t.join();
	}

private:
	std::vector<std::thread>& _threads;
};

class thread_pool
{
public:
	thread_pool() : _done(false), _joiner(_threads)
	{
		unsigned const thread_count=std::thread::hardware_concurrency();

		try {
			for (unsigned i=0; i < thread_count; ++i)
				_threads.emplace_back(std::thread(&thread_pool::_worker_thread, this));
		} catch(...) {
			_done = true;
			throw;
		}
	}

	~thread_pool()
	{
		_done = true;
	}

	template<typename FunctionType>
	void submit(FunctionType f)
	{
		_task_queue.push(std::function<void()>(f));
	}

private:
	std::atomic_bool _done;
	concurrent_queue<std::function<void()>> _task_queue;
	std::vector<std::thread> _threads;
	thread_joiner _joiner;

	void _worker_thread()
	{
		while (!_done) {
			std::function<void()> task;

			if (_task_queue.try_pop(task)) {
				task();
			} else {
				std::this_thread::yield();
			}
		}
	}
};

int main(int argc_, char** argv_)
{
	thread_pool pool;
	pool.submit([]() { std::this_thread::sleep_for(std::chrono::seconds(1)); });
	return 0;
}
