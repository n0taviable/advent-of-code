#include<bits/stdc++.h>

//  directions are N, NE, E, SE, S, SW, W, NW
int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

int main() {
  std::string word = "XMAS";
  int word_len = word.length();
  std::vector<std::string> grid;
  std::string line;

  while(getline(std::cin, line)) {
    if (line.empty()) continue;
    grid.push_back(line);
  }

  int n = grid.size();
  if (n == 0) {
    std::cerr << "Empty grid" << std::endl;
    return 1;
  }

  int m = grid[0].size(); // #cols
  int count = 0;

  // iterate over grid cells
  for (size_t i = 0; i < n; ++i) {    // rows
    for (size_t j = 0; j < m; ++j) {  // cols
      // check all directions:
      for (size_t dir = 0; dir < 8; ++dir) {
        size_t k;
        int x = i;
        int y = j;
        
        // try to match `word` from position (i,j) in `dir`:
        for (k = 0; k < word_len; ++k) {
          // boundary check
          if (x < 0 || x >= n || y < 0 || y >= m) {
            break;
          }
          // current char matching?
          if (grid[x][y] != word[k]) {
            break;
          }
          //move to next char in direction dir
          x += dx[dir];
          y += dy[dir];
        }
        // if whole word matched, increment count
        if (k == word_len) {
          count++;
        }
      }
    }
  }

  std::cout << "Total number of occurences of XMAS: " << count << std::endl;

  return 0;

}
