/* Link to problem: https://adventofcode.com/2020/day/8 */
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
using namespace std;

int part1(vector<string> &instructions) {
    set<int> visited;
    size_t i = 0;
    int acculumator = 0;
    while (true) {
        if (visited.find(i) != visited.end()) {
            break;
        }
        visited.insert(i);
        string curr_instruction = instructions[i];
        size_t delimIndex = curr_instruction.find(" ");
        string command = curr_instruction.substr(0, delimIndex);
        int value = stoi(curr_instruction.substr(delimIndex + 1, string::npos));
        if (command == "acc") {
            acculumator += value;
        } else if (command == "jmp") {
            i += value - 1;
        }
        ++i;
    }
    return acculumator;
}

int part2(vector<string> &instructions) {
    for (int i = 1; i <= instructions.size(); ++i) {
        set<int> visited;
        size_t j = 0;
        int numNopsOrJmps = 0;
        int acculumator = 0;
        while (true) {
            if (j == instructions.size()) {
                return acculumator;
            }
            if (visited.find(j) != visited.end()) {
                break;
            }
            visited.insert(j);
            string curr_instruction = instructions[j];
            size_t delimIndex = curr_instruction.find(" ");
            string command = curr_instruction.substr(0, delimIndex);
            int value = stoi(curr_instruction.substr(delimIndex + 1, string::npos));
            if (command == "acc") {
                acculumator += value;
            } else if (command == "jmp") {
                ++numNopsOrJmps;
                if (numNopsOrJmps != i) {
                    j += value - 1;
                }
            } else if (command == "nop") {
                ++numNopsOrJmps;
                if (numNopsOrJmps == i) {
                    j += value - 1;
                }
            }
            ++j;
        }
    }
    // If answer not found, return 0
    return 0;
}

int main() {
    ifstream reader("input.txt");
    string line;
    vector<string> instructions;
    while (getline(reader, line)) {
        instructions.push_back(line);
    }
    reader.close();
    cout << "Part 1: " << part1(instructions) << endl;
    cout << "Part 2: " << part2(instructions) << endl;
    return 0;
}
