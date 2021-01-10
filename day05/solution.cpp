/* Link to problem: https://adventofcode.com/2020/day/5 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int part1() {
    ifstream reader("input.txt");
    string line;
    int highest_seat_id = 0;
    while (getline(reader, line)) {
        int seat_id = 0;
        for (char c : line) {
            seat_id = seat_id << 1;
            if (c == 'B' || c == 'R') {
                ++seat_id;
            }
        }
        if (seat_id > highest_seat_id) {
            highest_seat_id = seat_id;
        }
    }
    reader.close();
    return highest_seat_id;
}

int part2() {
    ifstream reader("input.txt");
    string line;
    bool seats[2 << 10] = {false};
    while (getline(reader, line)) {
        int seat_id = 0;
        for (char c : line) {
            seat_id = seat_id << 1;
            if (c == 'B' || c == 'R') {
                ++seat_id;
            }
        }
        seats[seat_id] = true;
    }
    for (int i = 0; i < (2 << 10); ++i) {
        int row = i >> 3;
        if (row != 0 && row != 127) {
            if (!seats[i] && seats[i - 1] && seats[i + 1]) {
                return i;
            }
        }
    }
    reader.close();
    // Returns 0 if there is no answer found
    return 0;
}

int main() {
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
    return 0;
}
