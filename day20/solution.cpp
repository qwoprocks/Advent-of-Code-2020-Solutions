/* Link to problem: https://adventofcode.com/2020/day/20 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

vector<char> getTop(vector<vector<char>> tile, bool rev=false) {
    vector<char> top = tile[0];
    if (rev) {
        reverse(top.begin(), top.end());
    }
    return top;
}

vector<char> getBottom(vector<vector<char>> tile, bool rev=false) {
    vector<char> bottom = tile[tile.size() - 1];
    if (rev) {
        reverse(bottom.begin(), bottom.end());
    }
    return bottom;
}

vector<char> getLeft(vector<vector<char>> tile, bool rev=false) {
    vector<char> left;
    for (int i = 0; i < tile[0].size(); ++i) {
        if (rev) {
            left.push_back(tile[tile.size() - 1 - i][0]);
        } else {
            left.push_back(tile[i][0]);
        }
    }
    return left;
}

vector<char> getRight(vector<vector<char>> tile, bool rev=false) {
    vector<char> right;
    for (int i = 0; i < tile[0].size(); ++i) {
        if (rev) {
            right.push_back(tile[tile.size() - 1 - i][tile[0].size() - 1]);
        } else {
            right.push_back(tile[i][tile[0].size() - 1]);
        }
    }
    return right;
}

long long part1(unordered_map<int, vector<vector<char>>> tiles, int *corner) {
    long long result = 1;
    unordered_map<int, vector<vector<char>>> tile_borders;
    for (auto tile : tiles) {
        tile_borders[tile.first] = {
            getTop(tile.second, false), getBottom(tile.second, false), getRight(tile.second, false), getLeft(tile.second, false),
            getTop(tile.second, true), getBottom(tile.second, true), getRight(tile.second, true), getLeft(tile.second, true)
        };
    }
    for (auto tile1 : tile_borders) {
        int count = 0;
        for (auto tile2 : tile_borders) {
            if (tile1.first == tile2.first) {
                continue;
            }
            for (int i = 0; i < 4; ++i) {
                for (vector<char> border2 : tile2.second) {
                    if (tile1.second[i] == border2) {
                        ++count;
                    }
                }
            }
        }
        if (count == 2) {
            result *= tile1.first;
            *corner = tile1.first;
        }
    }
    return result;
}

vector<vector<char>> rotateLeft(vector<vector<char>> tile) {
    vector<vector<char>> new_tile = tile;
    for (int i = 0; i < tile.size(); ++i) {
        for (int j = 0; j < tile[0].size(); ++j) {
            new_tile[tile.size() - 1 - j][i] = tile[i][j];
        }
    }
    return new_tile;
}

vector<vector<char>> rotateRight(vector<vector<char>> tile) {
    vector<vector<char>> new_tile = tile;
    for (int i = 0; i < tile.size(); ++i) {
        for (int j = 0; j < tile[0].size(); ++j) {
            new_tile[j][tile[0].size() - 1 - i] = tile[i][j];
        }
    }
    return new_tile;
}

vector<vector<char>> flip(vector<vector<char>> tile) {
    vector<vector<char>> new_tile = tile;
    for (int i = 0; i < tile.size(); ++i) {
        new_tile[tile.size() - 1 - i] = tile[i];
    }
    return new_tile;
}

int part2(unordered_map<int, vector<vector<char>>> &tiles, int corner) {
    unordered_map<int, vector<vector<char>>> tile_borders;
    for (auto tile : tiles) {
        tile_borders[tile.first] = {
            getTop(tile.second, false), getBottom(tile.second, false), getRight(tile.second, false), getLeft(tile.second, false),
            getTop(tile.second, true), getBottom(tile.second, true), getRight(tile.second, true), getLeft(tile.second, true)
        };
    }
    unordered_set<int> not_visited;
    for (auto t : tiles) {
        not_visited.insert(t.first);
    }
    auto starting_tile = tiles[corner];
    bool found = false;
    while (!found) {
        int r = rand() % 2;
        if (r == 0) {
            starting_tile = rotateRight(starting_tile);
        } else {
            starting_tile = flip(starting_tile);
        }
        auto right_border = getRight(starting_tile, false);
        for (int tile_no : not_visited) {
            for (auto border : tile_borders[tile_no]) {
                if (right_border == border) {
                    found = true;
                    break;
                }
            }
        }
    }

    // Put together starting row
    vector<vector<vector<char>>> starting_row;
    starting_row.push_back(starting_tile);
    not_visited.erase(corner);
    while (true) {
        auto right_border = getRight(starting_row.back(), false);
        int found_tile = -1;
        for (int t : not_visited) {
            auto tile = tiles[t];
            auto borders = tile_borders[t];
            if (borders[0] == right_border) {
                starting_row.push_back(flip(rotateLeft(tile)));
                found_tile = t;
            } else if (borders[1] == right_border) {
                starting_row.push_back(rotateRight(tile));
                found_tile = t;
            } else if (borders[2] == right_border) {
                starting_row.push_back(flip(rotateLeft(rotateLeft(tile))));
                found_tile = t;
            } else if (borders[3] == right_border) {
                starting_row.push_back(tile);
                found_tile = t;
            } else if (borders[4] == right_border) {
                starting_row.push_back(rotateLeft(tile));
                found_tile = t;
            } else if (borders[5] == right_border) {
                starting_row.push_back(flip(rotateRight(tile)));
                found_tile = t;
            } else if (borders[6] == right_border) {
                starting_row.push_back(rotateLeft(rotateLeft(tile)));
                found_tile = t;
            } else if (borders[7] == right_border) {
                starting_row.push_back(flip(tile));
                found_tile = t;
            }
            if (found_tile != -1) {
                break;
            }
        }
        if (found_tile == -1) {
            break;
        } else {
            not_visited.erase(found_tile);
        }
    }

    for (int i = 0; i < starting_row.size(); ++i) {
        starting_row[i] = flip(starting_row[i]);
    }

    // Put together the rest of the rows
    vector<vector<vector<vector<char>>>> arranged_tiles;
    arranged_tiles.push_back(starting_row);
    while (not_visited.size() > 0) {
        auto curr_row = arranged_tiles.back();
        vector<vector<vector<char>>> next_row;
        for (auto tile : curr_row) {
            auto bottom_border = getBottom(tile, false);
            int found_tile = -1;
            for (int t : not_visited) {
                auto tile = tiles[t];
                auto borders = tile_borders[t];
                if (borders[0] == bottom_border) {
                    next_row.push_back(tile);
                    found_tile = t;
                } else if (borders[1] == bottom_border) {
                    next_row.push_back(flip(rotateLeft(rotateLeft(tile))));
                    found_tile = t;
                } else if (borders[2] == bottom_border) {
                    next_row.push_back(rotateLeft(tile));
                    found_tile = t;
                } else if (borders[3] == bottom_border) {
                    next_row.push_back(rotateRight(flip(tile)));
                    found_tile = t;
                } else if (borders[4] == bottom_border) {
                    next_row.push_back(rotateRight(flip(rotateLeft(tile))));
                    found_tile = t;
                } else if (borders[5] == bottom_border) {
                    next_row.push_back(rotateRight(rotateRight(tile)));
                    found_tile = t;
                } else if (borders[6] == bottom_border) {
                    next_row.push_back(rotateLeft(flip(tile)));
                    found_tile = t;
                } else if (borders[7] == bottom_border) {
                    next_row.push_back(rotateRight(tile));
                    found_tile = t;
                }
                if (found_tile != -1) {
                    break;
                }
            }
            not_visited.erase(found_tile);
        }
        arranged_tiles.push_back(next_row);
    }

    // Construct the full picture
    vector<vector<char>> full_picture;
    for (auto row_of_tiles : arranged_tiles) {
        for (int i = 1; i < row_of_tiles[0].size() - 1; ++i) {
            vector<char> row;
            for (auto tile : row_of_tiles) {
                row.insert(row.end(), tile[i].begin() + 1, tile[i].end() - 1);
            }
            full_picture.push_back(row);
        }
    }

    // Find the roughness
    int roughness = 0;
    vector<pair<int, int>> offsets = {
        {18, 0}, {0, 1}, {5, 1}, {6, 1}, {11, 1}, {12, 1}, {17, 1}, {18, 1},
        {19, 1}, {1, 2}, {4, 2}, {7, 2}, {10, 2}, {13, 2}, {16, 2}
    };
    unordered_set<int> monster_coords;
    while (true) {
        int total_hash = 0;
        for (int i = 0; i < full_picture.size(); ++i) {
            for (int j = 0; j < full_picture[0].size(); ++j) {
                if (full_picture[i][j] == '#') {
                    ++total_hash;
                }
                if (i < full_picture.size() - 2 && j < full_picture[0].size() - 19) {
                    bool monster_present = true;
                    for (auto p : offsets) {
                        monster_present &= full_picture[i + p.second][j + p.first] == '#';
                    }
                    if (monster_present) {
                        for (auto p : offsets) {
                            monster_coords.insert((i + p.second) * full_picture.size() + j + p.first);
                        }
                    }
                }
            }
        }
        if (monster_coords.size() > 0) {
            roughness = total_hash - monster_coords.size();
            break;
        }
        int r = rand() % 2;
        if (r == 0) {
            full_picture = rotateRight(full_picture);
        } else {
            full_picture = flip(full_picture);
        }
    }
    return roughness;
}

int main() {
    ifstream reader("input.txt");
    string line;
    unordered_map<int, vector<vector<char>>> tiles;
    int curr_tile_no;
    vector<vector<char>> curr_tile;
    while(getline(reader, line)) {
        if (line.find(":") != string::npos) {
            curr_tile_no = stoi(line.substr(line.find(" "), line.find(":") - line.find(" ")));
        } else if (line.empty() && curr_tile.size() != 0) {
            tiles[curr_tile_no] = curr_tile;
            curr_tile.clear();
        } else {
            vector<char> tile_row(line.begin(), line.end());
            curr_tile.push_back(tile_row);
        }
    }
    reader.close();
    int corner = 0;
    cout << "Part 1: " << part1(tiles, &corner) << endl;
    cout << "Part 2: " << part2(tiles, corner) << endl;
    return 0;
}
