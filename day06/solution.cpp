/* Link to problem: https://adventofcode.com/2020/day/6 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int part1() {
    ifstream reader("input.txt");
    string line;
    int total_count = 0;
    bool question_answered[26] = {false};
    while (getline(reader, line)) {
        if (line.empty()) {
            for (int i = 0; i < 26; ++i) {
                question_answered[i] = false;
            }
        } else {
            for (char c : line) {
                int index = c - 'a';
                if (!question_answered[index]) {
                    ++total_count;
                    question_answered[index] = true;
                }
            }
        }
    }
    reader.close();
    return total_count;
}

int part2() {
    ifstream reader("input.txt");
    string line;
    int total_count = 0;
    bool start = true;
    bool question_answered[26] = {false};
    while (getline(reader, line)) {
        if (line.empty()) {
            for (int i = 0; i < 26; ++i) {
                if (question_answered[i]) {
                    ++total_count;
                }
                question_answered[i] = false;
            }
            start = true;
        } else {
            if (start) {
                for (char c : line) {
                    int index = c - 'a';
                    question_answered[index] = true;
                }
                start = false;
            } else {
                bool curr_question_answered[26] = {false};
                for (char c : line) {
                    int index = c - 'a';
                    curr_question_answered[index] = true;
                }
                for (int i = 0; i < 26; i++) {
                    question_answered[i] = question_answered[i] && curr_question_answered[i];
                }
            }
        }
    }
    // Account for last block which doesn't have empty line after it
    for (int i = 0; i < 26; ++i) {
        if (question_answered[i]) {
            ++total_count;
        }
    }
    reader.close();
    return total_count;
}

int main() {
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
    return 0;
}
