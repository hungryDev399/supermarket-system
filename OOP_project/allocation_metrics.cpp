#include "pch.h"

/*

struct allocstionmetrics {
	uint32_t total_allocated = 0;
	uint32_t total_freed = 0;
	uint32_t currentUsage() { return total_allocated - total_freed; }
};

static allocstionmetrics allocation_metrics;

/*void* operator new(size_t size) {
	allocation_metrics.total_allocated += size;
	return malloc(size);
}

void operator delete(void* mem, size_t size) {
	allocation_metrics.total_freed += size;
	free(mem);
}

struct object {
	int x, y, z;
};

static void printMemoryUsage() {
	std::cout << "The current memory usage = " << allocation_metrics.currentUsage()
		<< " bytes"<<std::endl;
}

int mainallocation() {
	printMemoryUsage();
	object* obj = new object;
	printMemoryUsage();
	std::string str = "hi!";
	printMemoryUsage();
	return 0;
}*/