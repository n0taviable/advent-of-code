#include<bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::vector<std::string> lab;
    {
        std::string line;
        while (std::getline(std::cin, line)) {
            lab.push_back(line);
        }
    }

    int rows = (int)lab.size();
    if (rows == 0) {
        std::cout << 0 << "\n";
        return 0;
    }
    int cols = (int)lab[0].size();

    // find guard initial position and facing direction
    // directions: Up=0, Right=1, Down=2, Left=3
    int guard_row = -1;
    int guard_col = -1;
    int dir = 0;

    bool found = false;
    for (int r = 0; r < rows && !found; r++) {
        for (int c = 0; c < cols && !found; c++) {
            char ch = lab[r][c];
            if (ch == '^') { guard_row = r; guard_col = c; dir = 0; found = true; }
            else if (ch == '>') { guard_row = r; guard_col = c; dir = 1; found = true; }
            else if (ch == 'v') { guard_row = r; guard_col = c; dir = 2; found = true; }
            else if (ch == '<') { guard_row = r; guard_col = c; dir = 3; found = true; }
        }
    }

    if (!found) {
        // no guard found !
        std::cout << 0 << "\n";
        return 0;
    }

    // set guard to '.'
    lab[guard_row][guard_col] = '.';

    // directions vectors: up, right, down, left
    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, 1, 0, -1};

    auto in_bounds = [&](int rr, int cc) {
        return rr >= 0 && rr < rows && cc >= 0 && cc < cols;
    };

    // visited array (2D)
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    int visited_count = 0;

    // mark initial position as visited
    if (!visited[guard_row][guard_col]) {
        visited[guard_row][guard_col] = true;
        visited_count++;
    }

    while (true) {
        int nr = guard_row + dr[dir];
        int nc = guard_col + dc[dir];

        // check if next cell is out of bounds || blocked
        bool blocked = false;
        if (!in_bounds(nr, nc)) {
            // out of bounds
            break;
        }
        if (lab[nr][nc] == '#') {
            // obstacle !
            blocked = true;
        }

        if (blocked) {
            // turn right 90 degrees (clockwise)
            dir = (dir + 1) % 4;
        } else {
            // step forward
            guard_row = nr;
            guard_col = nc;
            if (in_bounds(guard_row, guard_col) && !visited[guard_row][guard_col]) {
                visited[guard_row][guard_col] = true;
                visited_count++;
            }
            // out of bounds _after_ moving ?
            if (!in_bounds(guard_row, guard_col)) {
                break;
            }
        }

        if (!in_bounds(guard_row, guard_col)) {
            break;
        }
    }

    std::cout << visited_count << std::endl;

    return 0;
}
