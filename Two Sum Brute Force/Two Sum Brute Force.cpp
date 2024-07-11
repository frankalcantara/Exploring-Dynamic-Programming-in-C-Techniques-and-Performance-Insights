#include <iostream>
#include <vector>
#include <utility>

// Function to find a pair of numbers that add up to the target sum Brute Force
std::pair<int, int> Values(const std::vector<int>& sequence, int targetSum) {
    int n = sequence.size();

    // Iterate over all possible pairs
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // Check if the current pair sums to the target
            if (sequence[i] + sequence[j] == targetSum) {
                return std::make_pair(sequence[i], sequence[j]); // Pair found
            }
        }
    }

    // No pair found
    return std::make_pair(-1, -1);
}

int main() {
    // Example usage
    std::vector<int> sequence = { 8, 10, 2, 9, 7, 5 };
    int targetSum = 11;

    // Call the function and print the result
    std::pair<int, int> result = Values(sequence, targetSum);
    if (result.first != -1) {
        std::cout << "Pair found: (" << result.first << ", " << result.second << ")" << std::endl;
    }
    else {
        std::cout << "No pair found." << std::endl;
    }

    return 0;
}
