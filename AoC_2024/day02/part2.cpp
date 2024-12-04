#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <string>

bool is_safe_report(const std::vector<int>& levels) {
    if (levels.size() < 2) {
        return true;    // report of size < 2 safe by default
    }

    bool is_decreasing = true;
    bool is_increasing = true;

    for (size_t i = 1; i < levels.size(); ++i) {
        int diff = levels[i] - levels[i - 1];
        
        // check for difference condition
        if (std::abs(diff) < 1 || std::abs(diff) > 3) {
            return false;
        }

        if (diff > 0) {
            is_decreasing = false;
        } else if (diff < 0) {
            is_increasing = false;
        } else {
            return false;   // diff at least one rule violated
        }
    }
    // levels either all increasing or all decreasing
    return is_increasing != is_decreasing;
}

bool is_safe_with_dampener(const std::vector<int>& levels) {
    if (is_safe_report(levels)) {
        return true;
    }

    // try removing each level one by one and see if report becomes safe
    for (size_t i = 0; i < levels.size(); ++i) {
        std::vector<int> modified_levels;
        modified_levels.reserve(levels.size() - 1);

        // copy all n - 1 levels
        for (size_t j = 0; j < levels.size(); ++j) {
            if (j != i) {
                modified_levels.push_back(levels[j]);
            }
        }

        if (is_safe_report(modified_levels)) {
            return true;
        }
    }
    return false;   // not such a level found that makes report safe
}

int main() {
    std::string line;
    int safe_reports = 0;

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        std::vector<int> levels;
        std::stringstream ss(line);
        int level;

        while (ss >> level) {
            levels.push_back(level);
        }

        if (is_safe_with_dampener(levels)) {
            safe_reports++;
        }
    }

    std::cout << safe_reports << std::endl;

    return 0;
}
