/*#include "pch.h"
#include "useful_tools.h"
#include "useful_structs.cpp"





//std::atomic<bool> working(true);

int fun1() {
	std::cout << "Hello 2\n";
	return 0;
}

int* fun2(int num, int num2) {
	int* arr = new int[2];
	arr[0] = num;
	arr[1] = num2;
	return arr;
}


//fix void problems

template <typename T, int itrerations, typename... Args>
std::array<T,itrerations> asyncFor( dynamicFunctionPointer<T, Args...> func_ptr_in, Args... args) {
	DynamicFutureVector<std::conditional_t<std::is_same_v<T, void>, T, std::decay_t<T>>> futures;
	//DynamicFutureVector<T> futures;
	// reserving the numebr of returns to avoid coppying 
	futures.generated_vector.reserve(itrerations);
	for (int i = 0; i < itrerations;i++) {
		futures.generated_vector.push_back(std::async(std::launch::async, func_ptr_in.func_pointer, args...));
	}

	//ensure that all async tasks are done
	std::array<T,itrerations> results;
	
	for (int i = 0; i<futures.generated_vector.size();i++) {

		results[i] = futures.generated_vector[i].get();

	}
	return results;
}

/*template<typename T>
void print(T& T) {
	cout << *T;
}



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




int main() {
	const int iterations = 9000;
	std::array<int, (iterations)> returns;
	{
		objectLifetimeTimer timer;
		//dynamicFunctionPointer<int> fun2_ptr = { &fun1};
		//returns = asyncFor(8000, fun2_ptr);
		returns = asyncFor<int, (iterations)>(dynamicFunctionPointer<int>{&fun1});
		//dynamicFunctionPointer<int> fun2_ptr = { &fun1 };
		//returns = asyncFor(70000, fun2_ptr);
	}
	std::cin.get();

	{
		objectLifetimeTimer timer;
		auto returns = asyncFor<int>(iterations, dynamicFunctionPointer<int>{&fun1});
	}
	std::cin.get();

	{
		objectLifetimeTimer timer;
		std::array<int, (iterations)> returns2;
		for (int i = 0; i < 8000;i++) {
			std::cout << "Hello 2\n";
			returns2[i] = 0;
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

#include "pch.h"
//#include "useful_tools.h"
/*#include "useful_structs.cpp"

template <typename T>
struct DynamicFutureVector {
	std::vector<std::future<T>> generated_vector;
};

template <typename T, typename... Args>
struct dynamicFunctionPointer {
	T(*func_pointer)(Args...);
};



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

int* fun2(int num, int num2) {
	int* arr = new int[2];
	arr[0] = num;
	arr[1] = num2;
	return arr;
}
//template <typename T, typename... Args, size_t itrerations>
//void(T* results, dynamicFunctionPointer<T, Args...> func_ptr_in, Args... args);

//fix void problems

template <typename T, size_t itrerations, typename... Args>
void asyncFor(T* results , dynamicFunctionPointer<T, Args...> func_ptr_in, Args... args) {
	//DynamicFutureVector<std::conditional_t<std::is_same_v<T, void>, T, std::decay_t<T>>> futures;
	DynamicFutureVector<T> futures
	int 
	// reserving the numebr of returns to avoid coppying 
	futures.generated_vector.reserve(itrerations);
	for (int i = 0; i < itrerations;i++) {
		futures.generated_vector.push_back(std::async(std::launch::async, func_ptr_in.func_pointer, args...));
	}

	//ensure that all async tasks are done
	for (int i = 0; i < futures.generated_vector.size(); i++){
		results[i] =  (futures.generated_vector[i].get());
		
	}

	

}


template <typename T, typename... Args>
std::vector<T> asyncFor2(int itrerations, dynamicFunctionPointer<T, Args...> func_ptr_in, Args... args) {
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





int main() {
	const int iterations = 8000;

	int returns[iterations];
	{
		objectLifetimeTimer timer;
		asyncFor<int, iterations>(returns, dynamicFunctionPointer<int>{&fun1});

	}
	std::cin.get();
	std::array<int, 10> arr1;
	std::vector<int> returns2;
	returns2.reserve(iterations);

	{
		objectLifetimeTimer timer;
		auto returns2 = asyncFor2<int>(iterations, dynamicFunctionPointer<int>{&fun3});
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