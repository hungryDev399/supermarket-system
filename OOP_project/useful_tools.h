#pragma once
template <typename T>
struct DynamicFutureVector {
	std::vector<std::future<T>> generated_vector;
};

template <typename T, typename... Args>
struct dynamicFunctionPointer {
	T(*func_pointer)(Args...);
};

template <typename T, int itrerations, typename... Args>
std::array<T, itrerations> asyncFor(dynamicFunctionPointer<T, Args...> func_ptr_in, Args... args);

template <typename T, typename... Args>
std::vector<T> asyncFor(int itrerations, dynamicFunctionPointer<T, Args...> func_ptr_in, Args... args);


bool intgerRangeValidation(int& variable, int lower_bound, int upperboud, int num_of_tials);
void intgerRangeValidation(int& variable, int lower_bound, int upperboud, std::string& message);
void intgerRangeValidation(int& variable, int lower_bound, int upperboud, std::string&& message);
void intgerRangeValidation(int& variable, int lower_bound, int upperboud);