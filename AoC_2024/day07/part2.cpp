#include<bits/stdc++.h>

// concatenate two numbers
int64_t concatenate(int64_t a, int64_t b) {
    int64_t multiplier = 1;
    while (multiplier <= b) {
        multiplier *= 10;
    }
    return a * multiplier + b;
}

// recursive eval. all possible operator combinations
bool evaluateOperators(const std::vector<int64_t>& numbers, int index, int64_t current_value, int64_t target) {
    if (index == numbers.size()) {
        return current_value == target;
    }

    // addition
    if (evaluateOperators(numbers, index + 1, current_value + numbers[index], target)) {
        return true;
    }

    // multiplication
    if (evaluateOperators(numbers, index + 1, current_value * numbers[index], target)) {
        return true;
    }

    // concatenation
    int64_t concatenated = concatenate(current_value, numbers[index]);
    if (evaluateOperators(numbers, index + 1, concatenated, target)) {
        return true;
    }

    return false;
}

// check if any operator combination can produce test value
bool canProduce(const std::vector<int64_t> &numbers, int64_t target) {
    if (numbers.empty())
        return false;
    if (numbers.size() == 1)
        return numbers[0] == target;
    
    return evaluateOperators(numbers, 1, numbers[0], target);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string line;
    int64_t total_sum = 0;
    
    while (std::getline(std::cin, line)) {
        if (line.empty())
            continue;
        
        // split
        size_t colon_pos = line.find(':');
        if (colon_pos == std::string::npos) {
            continue;
        }
        
        std::string test_value_str = line.substr(0, colon_pos);
        int64_t test_value = 0;
        std::stringstream ss_test(test_value_str);
        ss_test >> test_value;
        
        std::string numbers_str = line.substr(colon_pos + 1);
        std::stringstream ss_numbers(numbers_str);
        std::vector<int64_t> numbers;
        int64_t num;
        while (ss_numbers >> num) {
            numbers.push_back(num);
        }
        
        if (canProduce(numbers, test_value)) {
            total_sum += test_value;
        }
    }
    
    std::cout << total_sum << std::endl;
    
    return 0;
}
