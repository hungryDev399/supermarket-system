#include "pch.h"


// Example function that takes an integer argument and returns an integer
int someFunction(int num) {
    // Perform some computation
    return num * num;
}

int main3() {
    int numIterations = 10; // Number of iterations in the loop
    int sum = 0; // Variable to store the sum of return values

    // Vector to store the futures returned by async calls
    std::vector<std::future<int>> futures;

    for (int i = 0; i < numIterations; ++i) {
        // Launch an asynchronous task for each iteration of the loop
        futures.push_back(std::async(std::launch::async, someFunction, i));
    }
    int futures_size = futures.size();
    std::vector<int> results; // Vector to store the return values
    results.reserve(futures_size);
    // Retrieve the return values and store them
    
    for (int i = 0;i< futures_size;i++) {
        results.push_back(futures[i].get());
        sum += results[i];
    }

    std::cout << "Sum of return values: " << sum << std::endl; // Print the final sum
    for (const auto& result : results) {
        sum += result;
    }

    std::cout << "Contents of futures vector: ";


    for (const auto& result : results) {
        std::cout << result << " ";
    }
    std::cout << std::endl;

    return 0;
}
