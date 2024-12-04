#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <unordered_map>

int main() {
  std::vector<long> left_list;
  std::unordered_map<long, long> right_counts;
  std::string line;

  //readin input
  while (std::getline(std::cin, line)) {
    if (line.empty()) continue;

    long left_num, right_num;
    if (sscanf(line.c_str(), "%ld %ld", &left_num, &right_num) != 2) {
      continue;
    }

    left_list.push_back(left_num);
    right_counts[right_num]++;
  } 

  //get similarity scores
  long long similarity_score = 0;
  for (const int& num : left_list) {
    int count = right_counts[num];
    similarity_score += static_cast<long long>(num) * count;
  }
  std::cout << similarity_score << std::endl;

  return 0;
}