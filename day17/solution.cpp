/* Link to problem: https://adventofcode.com/2020/day/17 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int part1() {
    size_t size = 26;
    ifstream reader("input.txt");
    string line;
    vector<vector<vector<bool>>> grid(size, vector<vector<bool>>(size, vector<bool>(size)));
    size_t k = 8;
    while (getline(reader, line)) {
        size_t j = 8;
        for (char c : line) {
            if (c == '#') {
                grid[12][j][k] = true;
            }
            ++j;
        }
        ++k;
    }
    vector<vector<vector<bool>>> buffer_grid(size, vector<vector<bool>>(size, vector<bool>(size)));
    vector<int> offsets = {-1, 0, 1};
    for (int cycle = 0; cycle < 6; ++cycle) {
        for (size_t a = 1; a < size - 1; ++a) {
            for (size_t b = 1; b < size - 1; ++b) {
                for (size_t c = 1; c < size - 1; c++) {
                    int num_active = 0;
                    for (int d : offsets) {
                        for (int e : offsets) {
                            for (int f : offsets) {
                                if (d == 0 && e == 0 && f == 0) {
                                    continue;
                                }
                                if (grid[a + d][b + e][c + f]) {
                                    ++num_active;
                                }
                            }
                        }
                    }
                    if (grid[a][b][c]) {
                        if (num_active == 2 || num_active == 3) {
                            buffer_grid[a][b][c] = true;
                        } else {
                            buffer_grid[a][b][c] = false;
                        }
                    } else {
                        if (num_active == 3) {
                            buffer_grid[a][b][c] = true;
                        } else {
                            buffer_grid[a][b][c] = false;
                        }
                    }
                }
            }
        }
        grid = buffer_grid;
    }
    int final_num_active = 0;
    for (size_t a = 1; a < size - 1; ++a) {
        for (size_t b = 1; b < size - 1; ++b) {
            for (size_t c = 1; c < size - 1; c++) {
                if (buffer_grid[a][b][c]) {
                    ++final_num_active;
                }
            }
        }
    }
    return final_num_active;
}

int part2() {
    size_t size = 26;
    ifstream reader("input.txt");
    string line;
    vector<vector<vector<vector<bool>>>> grid(size, vector<vector<vector<bool>>>(size, vector<vector<bool>>(size, vector<bool>(size))));
    size_t k = 8;
    while (getline(reader, line)) {
        size_t j = 8;
        for (char c : line) {
            if (c == '#') {
                grid[12][12][j][k] = true;
            }
            ++j;
        }
        ++k;
    }
    vector<vector<vector<vector<bool>>>> buffer_grid(size, vector<vector<vector<bool>>>(size, vector<vector<bool>>(size, vector<bool>(size))));
    vector<int> offsets = {-1, 0, 1};
    for (int cycle = 0; cycle < 6; ++cycle) {
        for (size_t a = 1; a < size - 1; ++a) {
            for (size_t b = 1; b < size - 1; ++b) {
                for (size_t c = 1; c < size - 1; c++) {
                    for (size_t d = 1; d < size - 1; d++) {
                        int num_active = 0;
                        for (int e : offsets) {
                            for (int f : offsets) {
                                for (int g : offsets) {
                                    for (int h : offsets) {
                                        if (e == 0 && f == 0 && g == 0 && h == 0) {
                                            continue;
                                        }
                                        if (grid[a + e][b + f][c + g][d + h]) {
                                            ++num_active;
                                        }
                                    }
                                }
                            }
                        }
                        if (grid[a][b][c][d]) {
                            if (num_active == 2 || num_active == 3) {
                                buffer_grid[a][b][c][d] = true;
                            } else {
                                buffer_grid[a][b][c][d] = false;
                            }
                        } else {
                            if (num_active == 3) {
                                buffer_grid[a][b][c][d] = true;
                            } else {
                                buffer_grid[a][b][c][d] = false;
                            }
                        }
                    }
                }
            }
        }
        grid = buffer_grid;
    }
    int final_num_active = 0;
    for (size_t a = 1; a < size - 1; ++a) {
        for (size_t b = 1; b < size - 1; ++b) {
            for (size_t c = 1; c < size - 1; c++) {
                for (size_t d = 1; d < size - 1; d++) {
                    if (buffer_grid[a][b][c][d]) {
                        ++final_num_active;
                    }
                }
            }
        }
    }
    return final_num_active;
}

int main() {
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
    return 0;
}
