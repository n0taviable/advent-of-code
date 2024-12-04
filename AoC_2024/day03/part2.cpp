#include<bits/stdc++.h>

int mul(const std::string& str) {
    int a;
    int b;
    sscanf(str.c_str(), "mul(%d,%d)", &a, &b);
    return a * b;
}

int main() {
    std::ostringstream oss;
    oss << std::cin.rdbuf();
    std::string input = oss.str();

    std::regex pattern("(do\\(\\)|don't\\(\\)|mul\\([0-9]{1,3},[0-9]{1,3}\\))");
    std::smatch match;

    int totalSum = 0;
    bool mult_enabled = true;

    auto matches_begin = std::sregex_iterator(input.begin(), input.end(), pattern);
    auto matches_end = std::sregex_iterator();

     for (std::sregex_iterator i = matches_begin; i != matches_end; ++i) {
        if (i->str() == "do()") {
            mult_enabled = true;
        } else if (i->str() == "don't()") {
            mult_enabled = false;
        } else if (mult_enabled) {
            totalSum += mul(i->str());
        }
    }

    std::cout << totalSum << std::endl;

    return 0;
}