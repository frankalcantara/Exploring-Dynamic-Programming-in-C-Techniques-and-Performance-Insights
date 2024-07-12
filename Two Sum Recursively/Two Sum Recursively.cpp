#include <vector>
#include <optional>
#include <iostream>

// Recursive function to find a pair of numbers that add up to the target sum
std::optional<std::pair<int, int>> findPairRecursively(const std::vector<int>& arr, int target, int start, int end) {
    // Base case: If start index is greater than or equal to end index, no pair is found
    if (start >= end) {
        return std::nullopt; // Return no value (null optional)
    }
    // Base case: If the sum of elements at start and end indices equals the target, pair is found
    if (arr[start] + arr[end] == target) {
        return std::make_optional(std::make_pair(arr[start], arr[end])); // Return the pair
    }
    // Recursive call: Move the start index forward to check the next element
    auto result = findPairRecursively(arr, target, start + 1, end);
    if (result) {
        return result; // If a pair is found in the recursive call, return it
    }
    // Recursive call: Move the end index backward to check the previous element
    return findPairRecursively(arr, target, start, end - 1);
}

// Function to find a pair of numbers that add up to the target sum
std::optional<std::pair<int, int>> Values(const std::vector<int>& sequence, int targetSum) {
    // Call the recursive function with initial indices (0 and size-1)
    return findPairRecursively(sequence, targetSum, 0, sequence.size() - 1);
}

int main() {
    // Example usage
    std::vector<int> sequence = { 8, 10, 2, 9, 7, 5 }; // Input array
    int targetSum = 11; // Target sum

    // Call the function to find the pair
    auto result = Values(sequence, targetSum);

    // Print the result
    if (result) {
        std::cout << "Pair found: (" << result->first << ", " << result->second << ")\n";
    }
    else {
        std::cout << "No pair found.\n";
    }

    return 0;
}
