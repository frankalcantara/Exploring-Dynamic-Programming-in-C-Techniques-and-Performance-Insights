#include <vector>
#include <unordered_map>
#include <optional>
#include <utility>
#include <iostream>

// Helper function to create a unique key for memoization
std::string createKey(int start, int end) {
    return std::to_string(start) + "," + std::to_string(end);
}

// Recursive function with memoization to find a pair of numbers that add up to the target sum
std::optional<std::pair<int, int>> findPairRecursivelyMemo(
    const std::vector<int>& arr,
    int target,
    int start,
    int end,
    std::unordered_map<std::string, std::optional<std::pair<int, int>>>& memo
) {
    // Base case: If start index is greater than or equal to end index, no pair is found
    if (start >= end) {
        return std::nullopt; // Return no value (null optional)
    }

    // Create a unique key for memoization
    std::string key = createKey(start, end);

    // Check if the result is already in the memoization map
    if (memo.find(key) != memo.end()) {
        return memo[key]; // Return the memoized result
    }

    // Base case: If the sum of elements at start and end indices equals the target, pair is found
    if (arr[start] + arr[end] == target) {
        auto result = std::make_optional(std::make_pair(arr[start], arr[end]));
        memo[key] = result; // Store the result in the memoization map
        return result; // Return the pair
    }

    // Recursive call: Move the start index forward to check the next element
    auto result = findPairRecursivelyMemo(arr, target, start + 1, end, memo);
    if (result) {
        memo[key] = result; // Store the result in the memoization map
        return result; // If a pair is found in the recursive call, return it
    }

    // Recursive call: Move the end index backward to check the previous element
    result = findPairRecursivelyMemo(arr, target, start, end - 1, memo);
    memo[key] = result; // Store the result in the memoization map
    return result; // Return the result
}

// Function to find a pair of numbers that add up to the target sum using memoization
std::optional<std::pair<int, int>> ValuesMemo(const std::vector<int>& sequence, int targetSum) {
    // Memoization map to store results of subproblems
    std::unordered_map<std::string, std::optional<std::pair<int, int>>> memo;
    // Call the recursive function with initial indices (0 and size-1)
    return findPairRecursivelyMemo(sequence, targetSum, 0, sequence.size() - 1, memo);
}

int main() {
    // Example usage
    std::vector<int> sequence = { 8, 10, 2, 9, 7, 5 }; // Input array
    int targetSum = 11; // Target sum

    // Call the function to find the pair
    auto result = ValuesMemo(sequence, targetSum);

    // Print the result
    if (result) {
        std::cout << "Pair found: (" << result->first << ", " << result->second << ")\n";
    }
    else {
        std::cout << "No pair found.\n";
    }

    return 0;
}