/* Link to problem: https://adventofcode.com/2020/day/12 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

int part1(vector<string> &lines) {
    int location[2] = {0, 0};
    char int_to_dir_map[4] = {'N', 'E', 'S', 'W'};
    int direction = 1;
    unordered_map<char, pair<size_t, int>> dir_to_move_map = {{'N', {1, 1}}, {'E', {0, 1}}, {'S', {1, -1}}, {'W', {0, -1}}};
    for (string line : lines) {
        int value = stoi(line.substr(1, string::npos));
        if (line[0] == 'R') {
            direction += value / 90;
            direction %= 4;
        } else if (line[0] == 'L') {
            direction -= value / 90;
            direction = (direction % 4 + 4) % 4;
        } else if (line[0] == 'F') {
            auto move = dir_to_move_map[int_to_dir_map[direction]];
            location[move.first] += move.second * value;
        } else {
            auto move = dir_to_move_map[line[0]];
            location[move.first] += move.second * value;
        }
    }
    return abs(location[0]) + abs(location[1]);
}

int part2(vector<string> &lines) {
    int ship_location[2] = {0, 0};
    int waypoint_location[2] = {10, 1};
    unordered_map<char, pair<size_t, int>> dir_to_move_map = {{'N', {1, 1}}, {'E', {0, 1}}, {'S', {1, -1}}, {'W', {0, -1}}};
    for (string line : lines) {
        int value = stoi(line.substr(1, string::npos));
        if (line[0] == 'R') {
            value /= 90;
            value %= 4;
            for (int i = 0; i < value; ++i) {
                int n0 = waypoint_location[0] - ship_location[0];
                int n1 = waypoint_location[1] - ship_location[1];
                waypoint_location[0] = ship_location[0] + n1;
                waypoint_location[1] = ship_location[1] - n0;
            }
        } else if (line[0] == 'L') {
            value /= 90;
            value %= 4;
            for (int i = 0; i < value; ++i) {
                int n0 = waypoint_location[0] - ship_location[0];
                int n1 = waypoint_location[1] - ship_location[1];
                waypoint_location[0] = ship_location[0] - n1;
                waypoint_location[1] = ship_location[1] + n0;
            }
        } else if (line[0] == 'F') {
            int r0 = waypoint_location[0] - ship_location[0];
            int r1 = waypoint_location[1] - ship_location[1];
            ship_location[0] += r0 * value;
            ship_location[1] += r1 * value;
            waypoint_location[0] = ship_location[0] + r0;
            waypoint_location[1] = ship_location[1] + r1;
        } else {
            auto move = dir_to_move_map[line[0]];
            waypoint_location[move.first] += move.second * value;
        }
    }
    return abs(ship_location[0]) + abs(ship_location[1]);
}

int main() {
    ifstream reader("input.txt");
    string line;
    vector<string> lines;
    while (getline(reader, line)) {
        lines.push_back(line);
    }
    cout << "Part 1: " << part1(lines) << endl;
    cout << "Part 2: " << part2(lines) << endl;
    return 0;
}
