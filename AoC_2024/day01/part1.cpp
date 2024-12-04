#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

int main() {
  std::vector<long> left_list;
  std::vector<long> right_list;
  std::string line;

  //readin input
  while (std::getline(std::cin, line)) {
    if (line.empty()) continue;

    long left_num, right_num;
    if (sscanf(line.c_str(), "%ld %ld", &left_num, &right_num) != 2) {
      continue;
    }

    left_list.push_back(left_num);
    right_list.push_back(right_num);
  } 

  //sorting
  std::sort(left_list.begin(), left_list.end());
  std::sort(right_list.begin(), right_list.end());
  
  //get dists
  long long total_distance = 0;
  for (size_t i = 0; i < left_list.size(); ++i) {
    total_distance += std::abs(left_list[i] - right_list[i]);
  }
  std::cout << total_distance << std::endl;

  return 0;
}
