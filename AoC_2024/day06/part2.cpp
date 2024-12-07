#include <bits/stdc++.h>

// directions
enum Direction {
    Up = 0,
    Right = 1,
    Down = 2,
    Left = 3
};

const int dr[4] = {-1, 0, 1, 0}; // row deltas
const int dc[4] = {0, 1, 0, -1}; // col deltas

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::vector<std::string> grid;
    std::string line;
    while(std::getline(std::cin, line)){
        grid.push_back(line);
    }

    if(grid.empty()){
        // no grid
        std::cout << "0\n";
        return 0;
    }

    int num_rows = grid.size();
    int num_cols = 0;
    for(auto &s : grid){
        num_cols = std::max(num_cols, (int)s.size());
    }

    // find the guard's starting position and facing direction
    int start_row = -1, start_col = -1, direction = -1;
    for(int r = 0; r < num_rows; r++){
        for(int c = 0; c < grid[r].size(); c++){
            char ch = grid[r][c];
            if(ch == '^'){
                start_row = r;
                start_col = c;
                direction = Up;
                break;
            }
            else if(ch == '>'){
                start_row = r;
                start_col = c;
                direction = Right;
                break;
            }
            else if(ch == 'v'){
                start_row = r;
                start_col = c;
                direction = Down;
                break;
            }
            else if(ch == '<'){
                start_row = r;
                start_col = c;
                direction = Left;
                break;
            }
        }
        if(direction != -1){
            break;
        }
    }

    if(direction == -1){
        // no guard !
        std::cout << "0\n";
        return 0;
    }

    // replace w/ '.'
    grid[start_row][start_col] = '.';

    // init. hit directions tracking
    // each cell can be hit from Up (bit 0), Right (bit 1), Down (bit 2), Left (bit 3)
    // Initialize everything to 0 (no hits)
    std::vector<unsigned char> hit_dirs(num_rows * num_cols, 0);

    // helper lambda (mapping grid coordinates to idx)
    auto idx = [&](int r, int c) -> size_t {
        return static_cast<size_t>(r) * num_cols + c;
    };

    int loop_count = 0;

    // try placing obstacle
    for(int r = 0; r < num_rows; r++){
        for(int c = 0; c < grid[r].size(); c++){
            // skip if already obstacle or starting pos. of guard
            if(grid[r][c] == '#' || (r == start_row && c == start_col)){
                continue;
            }

            // tmp obstacle
            grid[r][c] = '#';

            // reset hit_dirs
            fill(hit_dirs.begin(), hit_dirs.end(), 0);

            int current_r = start_row;
            int current_c = start_col;
            int current_dir = direction;

            bool loop_found = false;

            while(true){
                int next_r = current_r + dr[current_dir];
                int next_c = current_c + dc[current_dir];

                // check if next pos. is out of bounds
                if(next_r < 0 || next_r >= num_rows || next_c < 0 || next_c >= num_cols || next_c >= (int)grid[next_r].size()){
                    // guard moves out of bounds
                    break;
                }

                if(grid[next_r][next_c] == '#'){
                    // obstacle !
                    size_t obstacle_idx = idx(next_r, next_c);

                    // check if the obstacle has been hit from _this_ direction before
                    if(hit_dirs[obstacle_idx] & (1 << current_dir)){
                        // then loop !
                        loop_found = true;
                        break;
                    }
                    else{
                        // mark this dir as hit
                        hit_dirs[obstacle_idx] |= (1 << current_dir);
                        // turn (clockwise/ right)
                        current_dir = (current_dir + 1) % 4;
                    }
                }
                else{
                    // step forward
                    current_r = next_r;
                    current_c = next_c;
                }
            }

            if(loop_found){
                loop_count++;
            }

            // remove tmp. obstacle
            grid[r][c] = '.';
        }
    }

    std::cout << loop_count << std::endl;

    return 0;
}
