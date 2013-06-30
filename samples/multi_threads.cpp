//////////////////////////////////////////////////////////////////////////
//
//
//
//////////////////////////////////////////////////////////////////////////
#include <misc/misc.hpp>
#include <vector>
#include <atomic>
#include <thread>

void call_from_thread(std::atomic<int> &sum, int i) {
	sum += i;
}

int main() {
	std::vector<std::thread> threads;
	std::atomic<int> asum(0);
	for (int i=0; i<8; i++) {
		threads.push_back(std::thread(call_from_thread, std::ref(asum), i));
	}

	for (int i=0; i<8; i++)
		threads[i].join();

	printf("sum: %d\n", asum);
	return 0;
}