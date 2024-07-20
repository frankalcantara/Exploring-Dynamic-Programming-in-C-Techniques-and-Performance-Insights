#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

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

// Iterative Brute Force LIS function
int longestIncreasingSubsequenceBruteForce(const std::vector<int>& arr) {
    int n = arr.size();
    int maxLen = 0;

    // Generate all possible subsequences using bitmasking
    for (int mask = 1; mask < (1 << n); ++mask) {
        std::vector<int> subsequence;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                subsequence.push_back(arr[i]);
            }
        }

        // Check if the subsequence is strictly increasing
        bool isIncreasing = true;
        for (int i = 1; i < subsequence.size(); ++i) {
            if (subsequence[i] <= subsequence[i - 1]) {
                isIncreasing = false;
                break;
            }
        }

        if (isIncreasing) {
            maxLen = std::max(maxLen, (int)subsequence.size());
        }
    }

    return maxLen;
}

// Recursive function to find the length of LIS ending at index i with memoization
int LIS(int i, const std::vector<int>& arr, std::vector<int>& dp) {
    if (dp[i] != -1) return dp[i];

    int maxLength = 1; // Minimum LIS ending at index i is 1
    for (int j = 0; j < i; ++j) {
        if (arr[j] < arr[i]) {
            maxLength = std::max(maxLength, LIS(j, arr, dp) + 1);
        }
    }
    dp[i] = maxLength;
    return dp[i];
}

// Function to find the length of the Longest Increasing Subsequence using memoization
int longestIncreasingSubsequenceMemoization(const std::vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;

    std::vector<int> dp(n, -1);
    int maxLength = 1;
    for (int i = 0; i < n; ++i) {
        maxLength = std::max(maxLength, LIS(i, arr, dp));
    }

    return maxLength;
}

// Function to find the length of the Longest Increasing Subsequence using tabulation
int longestIncreasingSubsequenceTabulation(const std::vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;

    std::vector<int> dp(n, 1);
    int maxLength = 1;

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (arr[i] > arr[j]) {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
        }
        maxLength = std::max(maxLength, dp[i]);
    }

    return maxLength;
}

int main() {
    std::vector<int> arr = { 5, 2, 8, 6, 3, 6, 9, 7 };
    int iterations = 1000;

    std::cout << "-----------------------------------\n";
    std::cout << "Calculating LIS in the array\n";

    // Measure average execution time for LIS using brute force
    auto bruteForceTime = average_time([](const std::vector<int>& arr) {
        longestIncreasingSubsequenceBruteForce(arr);
        }, iterations, arr);
    std::cout << "Average time for LIS (Brute Force): " << bruteForceTime << " ns\n";

    // Measure average execution time for LIS using memoization
    auto memoizationTime = average_time([](const std::vector<int>& arr) {
        longestIncreasingSubsequenceMemoization(arr);
        }, iterations, arr);
    std::cout << "Average time for LIS (Memoization): " << memoizationTime << " ns\n";

    // Measure average execution time for LIS using tabulation
    auto tabulationTime = average_time([](const std::vector<int>& arr) {
        longestIncreasingSubsequenceTabulation(arr);
        }, iterations, arr);
    std::cout << "Average time for LIS (Tabulation): " << tabulationTime << " ns\n";

    std::cout << "-----------------------------------\n";

    return 0;
}
