#include<bits/stdc++.h>

int main() {
    std::vector<std::string> grid;
    std::string line;

    while (getline(std::cin, line)) {
        if (line.empty()) continue;
        grid.push_back(line);
    }

    int n = grid.size();    // # rows
    if (n == 0) {
        std::cerr << "empty grid" << std::endl;
        return 1;
    }
    int m = grid[0].size(); // # columns
    int count = 0;

    // iterate over grid
    for (int i = 0; i < n; ++i) {   // rows
        for (int j = 0; j < m; ++j) {   // cols
            if (grid[i][j] == 'A') {
                bool match = true;

                // check '\' diagonal positions (i-1,j-1), (i,j), (i+1,j+1)
                if (i - 1 >= 0 && i + 1 < n && j - 1 >= 0 && j + 1 < m) {
                    char c1 = grid[i - 1][j - 1];
                    char c2 = grid[i][j];     // 'A'
                    char c3 = grid[i + 1][j + 1];

                    std::string seq1 = "";
                    seq1 += c1;
                    seq1 += c2;
                    seq1 += c3;

                    // check seq1 'MAS' or 'SAM'
                    if (seq1 != "MAS" && seq1 != "SAM") {
                        match = false;
                    }
                } else {
                    match = false;
                }

                // check '/' diagonal positions (i-1,j+1), (i,j), (i+1,j-1)
                if (i - 1 >= 0 && i + 1 < n && j + 1 < m && j - 1 >= 0) {
                    char d1 = grid[i - 1][j + 1];
                    char d2 = grid[i][j];     // 'A'
                    char d3 = grid[i + 1][j - 1];

                    std::string seq2 = "";
                    seq2 += d1;
                    seq2 += d2;
                    seq2 += d3;

                    // check seq2 'MAS' or 'SAM'
                    if (seq2 != "MAS" && seq2 != "SAM") {
                        match = false;
                    }
                } else {
                    match = false;
                }

                // if both diagonals match increment count
                if (match) {
                    count++;
                }
            }
        }
    }

    std::cout << "Total occurences of X-MAS: " << count << std::endl;
    return 0;
}
