
#include <iostream>
#include <thread>
#include <pthread.h>
#include <cpuid.h>

#ifdef LINUX
void set_core_affinity(std::thread& thread_, unsigned core_)
{
	pthread_t thread = thread_.native_handle();

	cpu_set_t cpu_set;
	CPU_ZERO(&cpu_set);
	CPU_SET(core_, &cpu_set);

	int s = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpu_set);

	if (s != 0)
		throw std::runtime_error("set_node_affinity: failed");
}
#endif

int main(int argc_, char** argv_)
{
	auto thread_main = []() {
		std::this_thread::sleep_for(std::chrono::seconds(5));
	};

	std::thread t1(thread_main), t2(thread_main);
	t1.join();
	t2.join();

	return 0;
}

