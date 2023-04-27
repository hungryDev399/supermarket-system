#include "pch.h"
#include "useful_tools.h"
#include "useful_structs.cpp"





//std::atomic<bool> working(true);

int fun1() {
	std::cout << "Hello 2\n";
	return 0;
}

int* fun2(int num,int num2) {
	int* arr = new int[2];
	arr[0] = num;
	arr[1] = num2;
	return arr;
}


//fix void problems

template <typename T, typename... Args>
 std::vector<T> asyncFor(int itrerations, dynamicFunctionPointer<T, Args...> func_ptr_in, Args... args) {
	DynamicFutureVector<std::conditional_t<std::is_same_v<T, void>, T, std::decay_t<T>>> futures;
	//DynamicFutureVector<T> futures;
	// reserving the numebr of returns to avoid coppying 
	futures.generated_vector.reserve(itrerations);
	for (int i = 0; i <= itrerations;i++) {
		futures.generated_vector.push_back(std::async(std::launch::async, func_ptr_in.func_pointer, args...));
	}
	
	//ensure that all async tasks are done
	std::vector<T> results;
	results.reserve(itrerations);
	for (auto& future : futures.generated_vector) {
		
		results.push_back(future.get());
		
	}
	return results;
}

 /*template<typename T>
 void print(T& T) {
	 cout << *T;
 }*/



 int main() {
	 std::vector<int> returns;
	 {
		 objectLifetimeTimer timer;
		dynamicFunctionPointer<int> fun2_ptr = { &fun1};
		returns = asyncFor(8000, fun2_ptr);
		//dynamicFunctionPointer<int> fun2_ptr = { &fun1 };
		//returns = asyncFor(70000, fun2_ptr);
 }
	 std::cin.get();

	 {
		 objectLifetimeTimer timer;
		 std::vector<int> returns;
		 for (int i = 0; i <= 8000;i++) {
			 std::cout << "Hello 2\n";
			 //int* arr = new int[2];
			 //arr[0] = 5;
			 //arr[1] = 10;
			 //returns.push_back(arr);
		 }
	 }
	//std::cout << returns[0][1];
	//delete the heap allocated pointers
	for (auto ptr : returns) {
		//delete[] ptr;
	}
	
	 
	return 0;
}