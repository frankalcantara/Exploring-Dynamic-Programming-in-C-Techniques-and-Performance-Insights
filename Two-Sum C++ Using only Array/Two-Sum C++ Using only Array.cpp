#include <iostream>
#include <vector>
#include <array>
#include <chrono>
#include <cstring> // Para usar memset

// Function to measure execution time
template <typename Func, typename... Args>
long long measure_time(Func func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    func(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<long long, std::nano> duration = end - start;
    return duration.count();
}

// Function to calculate average execution time
template <typename Func, typename... Args>
long long average_time(Func func, int iterations, Args&&... args) {
    long long total_time = 0;
    for (int i = 0; i < iterations; ++i) {
        total_time += measure_time(func, std::forward<Args>(args)...);
    }
    return total_time / iterations;
}

// Brute Force Solution
std::array<int, 2> ValuesBruteForce(const std::vector<int>& sequence, int targetSum) {
    int n = sequence.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (sequence[i] + sequence[j] == targetSum) {
                return { sequence[i], sequence[j] };
            }
        }
    }
    return { -1, -1 };
}

// Naive Recursive Solution
std::array<int, 2> findPairRecursively(const std::vector<int>& arr, int target, int start, int end) {
    if (start >= end) {
        return { -1, -1 };
    }
    if (arr[start] + arr[end] == target) {
        return { arr[start], arr[end] };
    }
    std::array<int, 2> result = findPairRecursively(arr, target, start + 1, end);
    if (result[0] != -1) {
        return result;
    }
    return findPairRecursively(arr, target, start, end - 1);
}

std::array<int, 2> ValuesRecursive(const std::vector<int>& sequence, int targetSum) {
    return findPairRecursively(sequence, targetSum, 0, sequence.size() - 1);
}

// Memoized Recursive Solution
std::array<int, 2> findPairRecursivelyMemo(
    const std::vector<int>& arr, int target, int start, int end,
    std::array<std::array<int, 2>, 1000>& memo) {
    if (start >= end) {
        return { -1, -1 };
    }
    if (memo[start][end][0] != -1) {
        return memo[start][end];
    }
    if (arr[start] + arr[end] == target) {
        memo[start][end] = { arr[start], arr[end] };
        return { arr[start], arr[end] };
    }
    std::array<int, 2> result = findPairRecursivelyMemo(arr, target, start + 1, end, memo);
    if (result[0] != -1) {
        memo[start][end] = result;
        return result;
    }
    result = findPairRecursivelyMemo(arr, target, start, end - 1, memo);
    memo[start][end] = result;
    return result;
}

std::array<int, 2> ValuesMemoized(const std::vector<int>& sequence, int targetSum) {
    std::array<std::array<int, 2>, 1000> memo;
    for (auto& row : memo) {
        row = { -1, -1 };
    }
    return findPairRecursivelyMemo(sequence, targetSum, 0, sequence.size() - 1, memo);
}

// Tabulation Solution using C-style arrays
std::array<int, 2> ValuesTabulationCStyle(const int* sequence, int length, int targetSum) {
    const int MAX_VAL = 1000; // Assuming the values in the sequence are less than 1000
    std::array<int, 2> result = { -1, -1 }; // Static array to return the result
    int table[MAX_VAL];
    memset(table, -1, sizeof(table));

    for (int i = 0; i < length; ++i) {
        int complement = targetSum - sequence[i];
        if (complement >= 0 && table[complement] != -1) {
            result[0] = sequence[i];
            result[1] = complement;
            return result;
        }
        table[sequence[i]] = i;
    }
    return result;
}

int main() {
    std::vector<int> sequence = { 8, 10, 2, 9, 7, 5 }; // Example sequence
    int targetSum = 11;
    int iterations = 1000;

    std::cout << "-----------------------------------\n";
    std::cout << "Calculating Two-Sum (" << targetSum << ")\n";

    // Measure average execution time for Brute Force Solution
    auto bruteForceTime = average_time([](const std::vector<int>& seq, int target) {
        ValuesBruteForce(seq, target);
        }, iterations, sequence, targetSum);
    std::cout << "Average time for Brute Force: " << bruteForceTime << " ns\n";

    // Measure average execution time for Naive Recursive Solution
    auto recursiveTime = average_time([](const std::vector<int>& seq, int target) {
        ValuesRecursive(seq, target);
        }, iterations, sequence, targetSum);
    std::cout << "Average time for Recursive: " << recursiveTime << " ns\n";

    // Measure average execution time for Memoized Recursive Solution
    auto memoizedTime = average_time([](const std::vector<int>& seq, int target) {
        ValuesMemoized(seq, target);
        }, iterations, sequence, targetSum);
    std::cout << "Average time for Memoized: " << memoizedTime << " ns\n";

    // Measure average execution time for Tabulation Solution using C-style arrays
    auto tabulationCStyleTime = average_time([](const int* seq, int length, int target) {
        ValuesTabulationCStyle(seq, length, target);
        }, iterations, sequence.data(), sequence.size(), targetSum);
    std::cout << "Average time for Tabulation C-Style: " << tabulationCStyleTime << " ns\n";

    std::cout << "-----------------------------------\n";

    return 0;
}
