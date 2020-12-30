/* Link to problem: https://adventofcode.com/2020/day/15 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int part1(vector<size_t> memory, size_t number, size_t start, size_t end) {
    size_t i = start;
    size_t prev_number = number;
    size_t next_number;
    while (i < end) {
        if (memory[prev_number] == 0) {
            next_number = 0;
        } else {
            next_number = i - memory[prev_number];
        }
        memory[prev_number] = i;
        prev_number = next_number;
        ++i;
    }
    return prev_number;
}

int main() {
    ifstream reader("input.txt");
    string line;
    getline(reader, line);
    reader.close();

    vector<size_t> memory(30000001, 0);
    size_t number = 0;
    size_t i = 1;
    size_t start_index = 0;
    size_t delim_index = line.find(",");
    while (delim_index != string::npos) {
        number = stoi(line.substr(start_index, delim_index - start_index));
        start_index = delim_index + 1;
        delim_index = line.find(",", start_index);
        memory[number] = i;
        ++i;
    }
    number = stoi(line.substr(start_index, delim_index - start_index));
    memory[number] = i;
    cout << "Part 1: " << part1(memory, number, i, 2020) << endl;
    cout << "Part 2: " << part1(memory, number, i, 30000000) << endl;
    return 0;
}
