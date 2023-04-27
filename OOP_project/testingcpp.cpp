#include "pch.h"
#include <chrono>

struct Timer {
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> end;
	std::chrono::duration<float> duration;
	Timer() {
		start = std::chrono::high_resolution_clock::now();
	}
	~Timer() {
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		float ms = duration.count() * 1000;
		std::cout << "Timer took " << duration.count() << "s " << "which is "<<ms <<" ms"<<std::endl;
	}
};

void fun() {
	Timer timer;
	for (int i = 0;i < 101;i++)
		std::cout << "Hello\n" ;
}

using namespace std::literals::chrono_literals;

void pauseSys() {
	std::this_thread::sleep_for(1s);
	std::cout << "iteration" << std::endl;
}

static std::vector<std::future<void>> futures;
void normal() {
	Timer time;
	std::cout << "loading normal" << std::endl;
	for (int i = 0; i < 7;i++) {
		pauseSys();
		
	}
	std::cout << "The normal function: " << std::endl;
}

static std::mutex trying_locking;

void parallel() {
	Timer time;
	for (int i = 0; i < 21;i++) {
		
		futures.push_back(std::async(std::launch::async, pauseSys));

		
		
	}
	std::cout << "loading parallel" << std::endl;
	
	std::cout << "The parallel  function: " << std::endl;
}

int main2() {
	normal();
	parallel();
	return 0;
}
