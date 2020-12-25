/* Link to problem: https://adventofcode.com/2020/day/11 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool areSeatsEqual(vector<vector<char>> &a, vector<vector<char>> &b) {
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < a[0].size(); ++j) {
            if (a[i][j] != b[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void fill_neighbours(pair<int, int> *neighbours, int i, int j, bool isPart2, vector<vector<char>> &seats) {
    pair<int, int> directions[8] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    for (size_t k = 0; k < 8; ++k) {
        auto p = directions[k];
        int curr_i = i;
        int curr_j = j;
        while (true) {
            int new_i = curr_i + p.first;
            int new_j = curr_j + p.second;
            if (new_i >= 0 && new_i < seats.size() && new_j >= 0 && new_j < seats[0].size()) {
                if (isPart2 && seats[new_i][new_j] == '.') {
                    curr_i = new_i;
                    curr_j = new_j;
                    continue;
                }
                neighbours[k] = {new_i, new_j};
            }
            break;
        }
    }
}

int part1(vector<vector<char>> seats) {
    vector<vector<char>> buffer_seats(seats.size(), vector<char>(seats[0].size(), '.'));
    while (true) {
        for (size_t i = 0; i < seats.size(); ++i) {
            for (size_t j = 0; j < seats[0].size(); ++j) {
                pair<int, int> neighbours[8] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
                fill_neighbours(neighbours, i, j, false, seats);
                int occupied_count = 0;
                for (auto p : neighbours) {
                    if (p.first == -1) {
                        continue;
                    }
                    if (seats[p.first][p.second] == '#') {
                        ++occupied_count;
                    }
                }
                if (seats[i][j] == 'L') {
                    if (occupied_count == 0) {
                        buffer_seats[i][j] = '#';
                    } else {
                        buffer_seats[i][j] = 'L';
                    }
                } else if (seats[i][j] == '#') {
                    if (occupied_count >= 4) {
                        buffer_seats[i][j] = 'L';
                    } else {
                        buffer_seats[i][j] = '#';
                    }
                }
            }
        }
        if (areSeatsEqual(buffer_seats, seats)) {
            break;
        }
        seats = buffer_seats;
    }
    int occupied_count = 0;
    for (auto row : seats) {
        for (char c : row) {
            if (c == '#') {
                ++occupied_count;
            }
        }
    }
    return occupied_count;
}

int part2(vector<vector<char>> seats) {
    vector<vector<char>> buffer_seats(seats.size(), vector<char>(seats[0].size(), '.'));
    while (true) {
        for (size_t i = 0; i < seats.size(); ++i) {
            for (size_t j = 0; j < seats[0].size(); ++j) {
                pair<int, int> neighbours[8] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};
                fill_neighbours(neighbours, i, j, true, seats);
                int occupied_count = 0;
                for (auto p : neighbours) {
                    if (p.first == -1) {
                        continue;
                    }
                    if (seats[p.first][p.second] == '#') {
                        ++occupied_count;
                    }
                }
                if (seats[i][j] == 'L') {
                    if (occupied_count == 0) {
                        buffer_seats[i][j] = '#';
                    } else {
                        buffer_seats[i][j] = 'L';
                    }
                } else if (seats[i][j] == '#') {
                    if (occupied_count >= 5) {
                        buffer_seats[i][j] = 'L';
                    } else {
                        buffer_seats[i][j] = '#';
                    }
                }
            }
        }
        if (areSeatsEqual(buffer_seats, seats)) {
            break;
        }
        seats = buffer_seats;
    }
    int occupied_count = 0;
    for (auto row : seats) {
        for (char c : row) {
            if (c == '#') {
                ++occupied_count;
            }
        }
    }
    return occupied_count;
}

int main() {
    ifstream reader("input.txt");
    string line;
    vector<vector<char>> seats;
    while (getline(reader, line)) {
        vector<char> row;
        for (char c : line) {
            row.push_back(c);
        }
        seats.push_back(row);
    }
    cout << "Part 1: " << part1(seats) << endl;
    cout << "Part 2: " << part2(seats) << endl;
    return 0;
}
