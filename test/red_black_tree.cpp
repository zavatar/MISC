#include <misc/misc.hpp>

int main()
{
	int Error(0);
	misc::red_black_tree<int> rbt;

	// data from CLRS p310 Figure 13.1
	rbt.insert(47);
	rbt.insert(41);
	rbt.insert(39);
	rbt.insert(38);
	rbt.insert(35);
	rbt.insert(30);
	rbt.insert(28);
	rbt.insert(26);

	rbt.insert(23);
	rbt.insert(21);
	rbt.insert(20);
	rbt.insert(19);
	rbt.insert(17);
	rbt.insert(16);
	rbt.insert(15);
	rbt.insert(14);
	rbt.insert(12);
	rbt.insert(10);
	rbt.insert(7);
	rbt.insert(3);

	for (auto val: rbt)
		printf("%d ",val);
	printf("\n");

	rbt.erase(41);
	rbt.erase(--rbt.end()); // 47
	printf("max: %d\n", *(--rbt.end()));

	return Error;
}