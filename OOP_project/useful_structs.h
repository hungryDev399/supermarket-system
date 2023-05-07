#include "pch.h"
#include <chrono>

struct objectLifetimeTimer {
	// Create an object of this and it will measure the time till the object is distructed
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> end;
	std::chrono::duration<float> duration;
	objectLifetimeTimer() {
		start = std::chrono::high_resolution_clock::now();
	}
	~objectLifetimeTimer() {
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		float ms = duration.count() * 1000;
		std::cout << "Timer took " << duration.count() << "s " << "which is " << ms << " ms" << std::endl;
	}
};