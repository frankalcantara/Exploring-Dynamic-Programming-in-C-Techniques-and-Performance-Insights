#include <iostream>
#include <unordered_map>
#include <chrono>
#include <array>
#include <utility>

// Recursive function to calculate Fibonacci
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

// Recursive function with memoization to calculate Fibonacci
int fibonacci_memo(int n, std::unordered_map<int, int>& memo) {
    if (memo.find(n) != memo.end()) {
        return memo[n];
    }
    if (n <= 1) {
        return n;
    }
    memo[n] = fibonacci_memo(n - 1, memo) + fibonacci_memo(n - 2, memo);
    return memo[n];
}

// Iterative function with tabulation to calculate Fibonacci using C-style arrays
int fibonacci_tabulation(int n) {
    if (n <= 1) {
        return n;
    }
    int dp[41] = { 0 };  // array to support up to Fibonacci(41) biggest in int type
    dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

// structs for C style functions
const int MAXN = 100;
bool found[MAXN] = { false };
int memo[MAXN] = { 0 };

// New function with memoization using arrays
int cArray_fibonacci_memo(int n) {
    if (found[n]) return memo[n];
    if (n == 0) return 0;
    if (n == 1) return 1;

    found[n] = true;
    return memo[n] = cArray_fibonacci_memo(n - 1) + cArray_fibonacci_memo(n - 2);
}

// New function with tabulation using arrays
int cArray_fibonacci_tabulation(int n) {
    if (n <= 1) {
        return n;
    }
    int dp[MAXN] = { 0 };  // array to support up to MAXN
    dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

// Function to measure execution time and return the result
template <typename Func, typename... Args>
std::pair<long long, int> measure_time(Func func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    int result = func(std::forward<Args>(args)...);  // Get the function result
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<long long, std::nano> duration = end - start;
    return { duration.count(), result };
}

// Function to calculate average execution time and return the last calculated result
template <typename Func, typename... Args>
std::pair<long long, int> average_time(Func func, int iterations, Args&&... args) {
    long long total_time = 0;
    int last_result = 0;
    for (int i = 0; i < iterations; ++i) {
        auto [time, result] = measure_time(func, std::forward<Args>(args)...);
        total_time += time;
        last_result = result;
    }
    return { total_time / iterations, last_result };
}

int main() {
    
    const int iterations = 1000;
    int test_cases[] = { 10, 20, 30};  // C-style array for test cases

    for (int n : test_cases) {
        std::cout << "Calculating Fibonacci(" << n << ")\n";

        // Calculation and average time using the simple recursive function
        auto [avg_time_recursive, result_recursive] = average_time(fibonacci, iterations, n);
        std::cout << "Average time for recursive Fibonacci: " << avg_time_recursive << " ns\n";
        std::cout << "Fibonacci(" << n << ") = " << result_recursive << "\n";

        // Calculation and average time using the memoization function
        std::unordered_map<int, int> memo;
        auto fibonacci_memo_wrapper = [&memo](int n) { return fibonacci_memo(n, memo); };
        auto [avg_time_memo, result_memo] = average_time(fibonacci_memo_wrapper, iterations, n);
        std::cout << "Average time for memoized Fibonacci: " << avg_time_memo << " ns\n";
        std::cout << "Fibonacci(" << n << ") = " << result_memo << "\n";

        // Calculation and average time using the tabulation function
        auto [avg_time_tabulation, result_tabulation] = average_time(fibonacci_tabulation, iterations, n);
        std::cout << "Average time for tabulated Fibonacci: " << avg_time_tabulation << " ns\n";
        std::cout << "Fibonacci(" << n << ") = " << result_tabulation << "\n";

        // Calculation and average time using the new memoization function with arrays
        auto [avg_time_novofIbb, result_cArray_fibonacci_memo] = average_time(cArray_fibonacci_memo, iterations, n);
        std::cout << "Average time for new memoized Fibonacci: " << avg_time_novofIbb << " ns\n";
        std::cout << "Fibonacci(" << n << ") = " << result_cArray_fibonacci_memo << "\n";

        // Calculation and average time using the new tabulation function with arrays
        auto [avg_time_novo_tabulation, result_cArray_tabulation] = average_time(cArray_fibonacci_tabulation, iterations, n);
        std::cout << "Average time for new tabulated Fibonacci: " << avg_time_novo_tabulation << " ns\n";
        std::cout << "Fibonacci(" << n << ") = " << result_cArray_tabulation << "\n";

        std::cout << "-----------------------------------\n";
    }

    return 0;
}
