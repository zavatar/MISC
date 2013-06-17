#include "head.h"
T combine4(T*data) {
	T acc=1;
	int i=0;
	for (; i < __SIZE_; i++) {
		acc = acc __OP_ data[i];
	}
	return acc;
}