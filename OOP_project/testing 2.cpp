#include "pch.h"
//template <typename T, int N>
/*template <typename T>
struct DynamicFutureVector {
    std::vector<std::future<T>> generated_vector;
};

template <typename T, typename... Args>
struct dynamicFunctionPointer {
    T(*func_pointer)(Args...);
};

void fun1() {
    std::cout << "I am a function\n";
}

int* fun2(int num, int num2) {
    int* arr = new int[2];
    arr[0] = num;
    arr[1] = num2;
    return arr;
}

template <typename T, typename... Args>
std::vector<T> asyncFor(int iterations, dynamicFunctionPointer<T, Args...> func_ptr_in, Args... args) {
    DynamicFutureVector<std::conditional_t<std::is_same_v<T, void>, T, std::decay_t<T>>> futures;
    // reserving the number of returns to avoid copying
    futures.generated_vector.reserve(iterations);
    for (int i = 0; i < iterations; i++) {
        futures.generated_vector.push_back(std::async(std::launch::async, func_ptr_in.func_pointer, args...));
    }

    // ensure that all async tasks are done
    std::vector<T> results;
    for (auto& future : futures.generated_vector) {
        if constexpr (std::is_same_v<T, void>) {
            future.wait();
        }
        else {
            results.push_back(future.get());
        }
    }
    return results;
}

int main() {
    std::vector<int*> returns;
    dynamicFunctionPointer<int*, int, int> fun2_ptr = { &fun2 };
    returns = asyncFor(7, fun2_ptr, 5, 10);
    std::cout << returns[0][1];
    
    for (auto ptr : returns) {
        delete[] ptr;
    }

    return 0;
}*/


