/* Link to problem: https://adventofcode.com/2020/day/24 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

int part1(set<pair<int, int>> &black_tiles) {
    ifstream reader("input.txt");
    string line;
    while (getline(reader, line)) {
        if (line.empty()) {
            continue;
        }
        pair<int, int> coord = {0, 0};
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == 'e') {
                coord.first += 2;
            } else if (line[i] == 'w') {
                coord.first -= 2;
            } else {
                if (line[i] == 's') {
                    coord.second += 1;
                    if (line[i + 1] == 'e') {
                        coord.first += 1;
                    } else if (line[i + 1] == 'w') {
                        coord.first -= 1;
                    }
                } else if (line[i] == 'n') {
                    coord.second -= 1;
                    if (line[i + 1] == 'e') {
                        coord.first += 1;
                    } else if (line[i + 1] == 'w') {
                        coord.first -= 1;
                    }
                }
                ++i;
            }
        }
        if (black_tiles.find(coord) != black_tiles.end()) {
            black_tiles.erase(coord);
        } else {
            black_tiles.insert(coord);
        }
    }
    reader.close();
    return black_tiles.size();
}

int part2(set<pair<int, int>> &black_tiles) {
    set<pair<int, int>> black_tiles_buffer;
    vector<pair<int, int>> offsets = {{2, 0}, {-2, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for (int i = 0; i < 100; ++i) {
        for (auto tile : black_tiles) {
            int black_neighbour_count = 0;
            for (auto o : offsets) {
                pair<int, int> n = {tile.first + o.first, tile.second + o.second};
                if (black_tiles.find(n) != black_tiles.end()) {
                    ++black_neighbour_count;
                } else {
                    int neighbour_black_neighbour_count = 0;
                    for (auto o2 : offsets) {
                        pair<int, int> n2 = {n.first + o2.first, n.second + o2.second};
                        if (black_tiles.find(n2) != black_tiles.end()) {
                            ++neighbour_black_neighbour_count;
                        }
                    }
                    if (neighbour_black_neighbour_count == 2) {
                        black_tiles_buffer.insert(n);
                    } else {
                        black_tiles_buffer.erase(n);
                    }
                }
            }
            if (black_neighbour_count > 0 && black_neighbour_count <= 2) {
                black_tiles_buffer.insert(tile);
            } else {
                black_tiles_buffer.erase(tile);
            }
        }
        black_tiles = black_tiles_buffer;
    }
    return black_tiles.size();
}

int main() {
    set<pair<int, int>> black_tiles;
    cout << "Part 1: " << part1(black_tiles) << endl;
    cout << "Part 2: " << part2(black_tiles) << endl;
    return 0;
}
