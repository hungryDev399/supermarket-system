#include "pch.h"
#include "useful_tools.h"
#include "useful_structs.h"





//std::atomic<bool> working(true);

int fun1() {
	std::cout << "Hello 1\n";
	return 0;
}

int fun3() {
	std::cout << "Hello 3\n";
	return 0;
}

int fun4() {
	std::cout << "Hello 4\n";
	return 0;
}

int* fun2(int num,int num2) {
	int* arr = new int[2];
	arr[0] = num;
	arr[1] = num2;
	return arr;
}


//fix void problems

template <typename T, size_t itrerations, typename... Args>
void asyncFor(T* results, dynamicFunctionPointer<T, Args...> func_ptr_in, Args... args) {
	//DynamicFutureVector<std::conditional_t<std::is_same_v<T, void>, T, std::decay_t<T>>> futures;
	DynamicFutureVector<T> futures;
	// reserving the numebr of returns to avoid coppying 
	futures.generated_vector.reserve(itrerations);
	for (int i = 0; i < itrerations;i++) {
		futures.generated_vector.push_back(std::async(std::launch::async, func_ptr_in.func_pointer, args...));
	}

	//ensure that all async tasks are done
	for (int i = 0; i < futures.generated_vector.size(); i++) {
		results[i] = (futures.generated_vector[i].get());

	}



}
 
bool intgerRangeValidation(int& variable, int lower_bound, int upperboud, int num_of_tials) {
	int trials = 0;
	bool success = 1;
	while ((variable < lower_bound || variable > upperboud)) {
		std::cout << "Input out of range please try again:" << std::endl;
		std::cin >> variable;
		if (trials <= num_of_tials) {
			success = 0;
			break;
		}
		trials++;
	}
	return success;
}

void intgerRangeValidation(int& variable, int lower_bound, int upperboud) {

	bool success = 1;
	while ((variable < lower_bound || variable > upperboud)) {
		std::cout << "Input out of range please try again:" << std::endl;
		std::cin >> variable;
	}

}

void intgerRangeValidation(int& variable, int lower_bound, int upperboud, std::string&& message) {

	bool success = 1;
	while ((variable < lower_bound || variable > upperboud)) {
		std::cout << message << std::endl;
		std::cin >> variable;
	}

}


void intgerRangeValidation(int& variable, int lower_bound, int upperboud, std::string& message) {

	bool success = 1;
	while ((variable < lower_bound || variable > upperboud)) {
		std::cout << message << std::endl;
		std::cin >> variable;
	}

}


/*int maintest() {
	const int iterations = 8000;

	int returns[iterations];
	{
		objectLifetimeTimer timer;
		asyncFor<int, iterations>(returns, dynamicFunctionPointer<int>{&fun1});

	}
	std::cin.get();



	{
		objectLifetimeTimer timer;
		std::array<int, (iterations)> returns3;
		for (int i = 0; i < 8000;i++) {
			std::cout << "Hello 2\n";
			returns3[i] = 0;
			//int* arr = new int[2];
			//arr[0] = 5;
			//arr[1] = 10;
			//returns.push_back(arr);
		}
	}
	//std::cout << returns[0][1];
	//delete the heap allocated pointers
	//for (auto ptr : returns) {
		//delete[] ptr;
	//}


	return 0;
}*/