#include <iostream>
#include <vector>
#include <unordered_map>
#include <optional>

// Function to find a pair of numbers that add up to the target sum using tabulation
std::optional<std::pair<int, int>> ValuesTabulation(const std::vector<int>& sequence, int targetSum) {
    std::unordered_map<int, int> table; // Hash table to store elements and their indices

    for (int i = 0; i < sequence.size(); ++i) {
        int complement = targetSum - sequence[i];

        // Check if the complement exists in the hash table
        if (table.find(complement) != table.end()) {
            return std::make_optional(std::make_pair(sequence[i], complement)); // Pair found
        }

        // Store the current element in the hash table
        table[sequence[i]] = i;
    }

    // No pair found
    return std::nullopt;
}

int main() {
    // Example usage
    std::vector<int> sequence = { 8, 10, 2, 9, 7, 5 }; // Input array
    int targetSum = 11; // Target sum

    // Call the function to find the pair
    auto result = ValuesTabulation(sequence, targetSum);

    // Print the result
    if (result) {
        std::cout << "Pair found: (" << result->first << ", " << result->second << ")\n";
    }
    else {
        std::cout << "No pair found.\n";
    }

    return 0;
}