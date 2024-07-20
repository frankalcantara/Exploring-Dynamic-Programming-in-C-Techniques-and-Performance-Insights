#include <iostream>
#include <stack>
#include <chrono>
#include <vector>
#include <array>

const int MAX_SIZE = 100;

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

// Structure to represent a position in the matrix
struct Position {
    int i, j;
    int pathCount;
};

// Function to count paths using brute force
int countPathsBruteForce(int m, int n) {
    std::stack<Position> stk;
    stk.push({ 0, 0, 1 });
    int totalPaths = 0;

    while (!stk.empty()) {
        Position pos = stk.top();
        stk.pop();

        int i = pos.i, j = pos.j, pathCount = pos.pathCount;

        // If we reach the bottom-right corner, add to total paths
        if (i == m - 1 && j == n - 1) {
            totalPaths += pathCount;
            continue;
        }

        // Move right if within bounds
        if (j + 1 < n) {
            stk.push({ i, j + 1, pathCount });
        }

        // Move down if within bounds
        if (i + 1 < m) {
            stk.push({ i + 1, j, pathCount });
        }
    }

    return totalPaths;
}

// Function to count paths using dynamic programming with memoization
int countPathsMemoization(int m, int n, std::vector<std::vector<int>>& dp) {
    if (m == 1 || n == 1) return 1;  // Base case
    if (dp[m - 1][n - 1] != -1) return dp[m - 1][n - 1];  // Return memoized result
    dp[m - 1][n - 1] = countPathsMemoization(m - 1, n, dp) + countPathsMemoization(m, n - 1, dp);  // Memoize result
    return dp[m - 1][n - 1];
}

int countPathsMemoizationWrapper(int m, int n) {
    std::vector<std::vector<int>> dp(m, std::vector<int>(n, -1));
    return countPathsMemoization(m, n, dp);
}

// Function to count paths using dynamic programming with tabulation
int countPathsTabulation(int m, int n) {
    std::array<std::array<int, MAX_SIZE>, MAX_SIZE> dp = {};

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 || j == 0) {
                dp[i][j] = 1;
            }
            else {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
    }

    return dp[m - 1][n - 1];
}

int main() {
    int m = 3, n = 3;
    int iterations = 1000;

    std::cout << "-----------------------------------\n";
    std::cout << "Calculating Paths in a " << m << "x" << n << " matrix\n";

    // Measure average execution time for Brute Force Solution
    auto bruteForceTime = average_time([](int m, int n) {
        countPathsBruteForce(m, n);
        }, iterations, m, n);
    std::cout << "Average time for Brute Force: " << bruteForceTime << " ns\n";

    // Measure average execution time for Memoization Solution
    auto memoizationTime = average_time([](int m, int n) {
        countPathsMemoizationWrapper(m, n);
        }, iterations, m, n);
    std::cout << "Average time for Memoization: " << memoizationTime << " ns\n";

    // Measure average execution time for Tabulation Solution
    auto tabulationTime = average_time([](int m, int n) {
        countPathsTabulation(m, n);
        }, iterations, m, n);
    std::cout << "Average time for Tabulation: " << tabulationTime << " ns\n";

    std::cout << "-----------------------------------\n";

    return 0;
}
