#include<bits/stdc++.h>

int main() {
    std::ostringstream oss;
    oss << std::cin.rdbuf();
    std::string input = oss.str();

    std::regex pattern(R"(mul\(([0-9]{1,3}),([0-9]{1,3})\))");
    std::smatch match;

    int totalSum = 0;

    auto matches_begin = std::sregex_iterator(input.begin(), input.end(), pattern);
    auto matches_end = std::sregex_iterator();

    for (std::sregex_iterator i = matches_begin; i != matches_end; ++i) {
        match = *i;

        int X = std::stoi(match[1].str());
        int Y = std::stoi(match[2].str());

        totalSum += X * Y;
    }

    std::cout << totalSum << std::endl;

    return 0;
}