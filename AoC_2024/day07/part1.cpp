#include<bits/stdc++.h>

// function to check if any operator combination can produce target value
bool canProduce(const std::vector<int64_t>& numbers, int64_t target) {
    int n = numbers.size();
    if (n == 0)
        return false;
    if (n == 1)
        return numbers[0] == target;
    
    // 2^(n-1) possible operator combinations
    // each bit in mask represents an operator: 0 for '+', 1 for '*'
    int64_t total_combinations = 1LL << (n - 1);
    for (int64_t mask = 0; mask < total_combinations; ++mask) {
        int64_t result = numbers[0];
        for (int i = 0; i < n - 1; ++i) {
            if (mask & (1LL << i)) {
                result *= numbers[i + 1];
            } else {
                result += numbers[i + 1];
            }
        }
        if (result == target)
            return true;
    }
    return false;
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
            continue;   // not necessary if input is well-formatted
        }
        
        // get and convert test value
        std::string test_value_str = line.substr(0, colon_pos);
        int64_t test_value = 0;
        std::stringstream ss_test(test_value_str);
        ss_test >> test_value;
        
        // get numbers
        std::string numbers_str = line.substr(colon_pos + 1);
        std::stringstream ss_numbers(numbers_str);
        std::vector<int64_t> numbers;
        int64_t num;
        while (ss_numbers >> num) {
            numbers.push_back(num);
        }
        
        // check if any operator combination can produce test value
        if (canProduce(numbers, test_value)) {
            total_sum += test_value;
        }
    }
    
    std::cout << total_sum << std::endl;
    
    return 0;
}
