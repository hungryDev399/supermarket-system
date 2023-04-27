#pragma once
template <typename T>
struct DynamicFutureVector {
	std::vector<std::future<T>> generated_vector;
};

template <typename T, typename... Args>
struct dynamicFunctionPointer {
	T(*func_pointer)(Args...);
};

template <typename T, typename... Args>
std::vector<T> asyncFor(int itrerations, dynamicFunctionPointer<T, Args...> func_ptr_in, Args... args);