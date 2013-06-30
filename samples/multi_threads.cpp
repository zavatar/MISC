//////////////////////////////////////////////////////////////////////////
//
//
//
//////////////////////////////////////////////////////////////////////////
#include <misc/misc.hpp>
#include <vector>
#include <thread>

void call_from_thread(int &sum, int i) {
	printf("%d, ", sum);
	sum += i;
	printf("%d\n", sum);
}

int main() {
	std::vector<std::thread> threads;
	int asum(0);
	for (int i=0; i<8; i++) {
		threads.push_back(std::thread(call_from_thread, std::ref(asum), i));
	}

	for (int i=0; i<8; i++)
		threads[i].join();

	printf("sum: %d\n", asum);
	return 0;
}