/* Link to problem: https://adventofcode.com/2020/day/3 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int part1(int right_move, int down_move) {
    ifstream reader("input.txt");
    string line;
    int num_trees = 0;
    int right_pos = 0;
    int down_pos = 0;
    while (getline(reader, line)) {
        if (down_pos++ % down_move != 0)  {
            continue;
        }
        if (line[right_pos] == '#') {
            ++num_trees;
        }
        right_pos += right_move;
        if (right_pos >= line.length()) {
            right_pos -= line.length();
        }
    }
    reader.close();
    return num_trees;
}

long long part2() {
    return (long long) part1(1, 1) * part1(3, 1) * part1(5, 1) * part1(7, 1) * part1(1, 2);
}

int main() {
    cout << "Part 1: " << part1(3, 1) << endl;
    cout << "Part 2: " << part2() << endl;
    return 0;
}
