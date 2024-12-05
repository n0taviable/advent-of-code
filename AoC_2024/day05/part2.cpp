#include<bits/stdc++.h>

bool topologicalSort(const std::vector<int>& nodes,
                    const std::vector<std::pair<int, int>>& rules,
                    std::vector<int>& sorted_order) {
    // build adjacency list & computation of in-degrees
    std::unordered_map<int, std::vector<int>> adj;
    std::unordered_map<int, int> in_degree;

    for (const int& node : nodes) {
        adj[node] = std::vector<int>();
        in_degree[node];
    }

    for (const auto& rule : rules) {
        int X = rule.first;
        int Y = rule.second;
        if (in_degree.find(X) != in_degree.end() && in_degree.find(Y) != in_degree.end()) {
            adj[X].push_back(Y);
            in_degree[Y]++;
        }
    }

    // init. queue
    std::queue<int> q;
    for (const auto& node : nodes) {
        if (in_degree[node] == 0) {
            q.push(node);
        }
    }

    sorted_order.clear();

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        sorted_order.push_back(current);

        for (const int& neighbor : adj[current]) {
            in_degree[neighbor]--;
            if (in_degree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    // if all nodes in then done
    return sorted_order.size() == nodes.size();

}

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

    // read updates
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
            size_t start = page_str.find_first_not_of(" \t\n\r\f\v");
            size_t end = page_str.find_last_not_of(" \t\n\r\f\v");
            if (start != std::string::npos && end != std::string::npos) {
                page_str = page_str.substr(start, end - start + 1);
                if (!page_str.empty()) {
                    pages.push_back(std::stoi(page_str));
                }
            }
        }

        if (pages.empty()) {
            continue;
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

        if (!is_correct) {
            // re-order pages using the topological sort (kahn's variation)
            std::vector<int> relevant_rules;
            std::vector<std::pair<int, int>> applicable_rules;
            std::unordered_set<int> pages_set(pages.begin(), pages.end());

            // collect rules that can be applied
            for (const auto& rule : ordering_rules) {
                int X = rule.first;
                int Y = rule.second;
                if (pages_set.find(X) != pages_set.end() && pages_set.find(Y) != pages_set.end()) {
                    applicable_rules.emplace_back(X, Y);
                }
            }

           // sorting
            std::vector<int> sorted_order;
            bool success = topologicalSort(pages, applicable_rules, sorted_order);

            if (success) {
                size_t n = sorted_order.size();
                size_t middle_index = n / 2;
                int middle_page = sorted_order[middle_index];
                total_middle_sum += middle_page;
            } else {
                // if cycle occurs topological sort ! (just in case, should not happen)
                std::cerr << "error: eycle detected in ordering rules for update: ";
                for (const auto& p : pages) {
                    std::cerr << p << ",";
                }
                std::cerr << std::endl;
                return 1;
            }
        }
    }

    std::cout << total_middle_sum << std::endl;

    return 0;
}