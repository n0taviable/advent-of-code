#include<bits/stdc++.h>

int main() {
    std::vector<std::pair<int, int>> ordering_rules;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            break;
        }
        size_t delimiter_pos = line.find('|');
        if (delimiter_pos != std::string::npos) {
            int X = std::stoi(line.substr(0, delimiter_pos));
            int Y = std::stoi(line.substr(delimiter_pos + 1));
            ordering_rules.emplace_back(X, Y);
        }
    }

    long long total_middle_sum = 0;
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }
        std::vector<int> pages;
        std::stringstream ss(line);
        std::string page_str;
        while (std::getline(ss, page_str, ',')) {
            // trim leadin_trailing whitespaces just in case
            page_str.erase(0, page_str.find_first_not_of(" \t\n\r\f\v"));
            page_str.erase(page_str.find_last_not_of(" \t\n\r\f\v") + 1);
            if (!page_str.empty()) {
                pages.push_back(std::stoi(page_str));
            }
        }

        // map from page number to index in update
        std::unordered_map<int, int> page_position;
        for (size_t i = 0; i < pages.size(); ++i) {
            page_position[pages[i]] = i;
        }

        bool is_correct = true;
        // check ordering rules
        for (const auto& rule : ordering_rules) {
            int X = rule.first;
            int Y = rule.second;
            // both X and Y in update?
            if (page_position.find(X) != page_position.end() && page_position.find(Y) != page_position.end()) {
                if (page_position[X] >= page_position[Y]) {
                    is_correct = false;
                    break;
                }
            }
        }

        if (is_correct) {
            size_t n = pages.size();
            if (n == 0) {
                continue;
            }
            size_t middle_index = n / 2;
            int middle_page = pages[middle_index];
            total_middle_sum += middle_page;
        }
    }

    std::cout << total_middle_sum << std::endl;

    return 0;
}
