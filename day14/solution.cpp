/* Link to problem: https://adventofcode.com/2020/day/14 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <list>
using namespace std;

long long part1() {
    ifstream reader("input.txt");
    string line;
    map<long long, long long> memory;
    long long andmask = 0;
    long long ormask = 0;
    while (getline(reader, line)) {
        if (line.substr(0, 4) == "mask") {
            andmask = 0;
            ormask = 0;
            for (char c : line.substr(7)) {
                andmask <<= 1;
                ormask <<= 1;
                if (c == 'X') {
                    andmask += 1;
                } else {
                    int bit = c - '0';
                    ormask += bit;
                    andmask += bit;
                }
            }
        } else if (!line.empty()) {
            size_t left_brack_index = line.find('[');
            size_t right_bracket_index = line.find(']');
            long long mem_loc = stoll(line.substr(left_brack_index + 1, right_bracket_index - left_brack_index - 1));
            long long mem_value = stoll(line.substr(right_bracket_index + 4)) & andmask | ormask;
            memory[mem_loc] = mem_value;
        }
    }
    reader.close();

    long long result = 0;
    for (auto mem_entry : memory) {
        result += mem_entry.second;
    }
    return result;
}

long long part2() {
    ifstream reader("input.txt");
    string line;
    map<long long, long long> memory;
    string mask;
    long long ormask = 0;
    while (getline(reader, line)) {
        if (line.substr(0, 4) == "mask") {
            ormask = 0;
            mask = line.substr(7);
            for (char c : mask) {
                ormask <<= 1;
                if (c == '1') {
                    ormask += 1;
                }
            }
        } else if (!line.empty()) {
            size_t left_brack_index = line.find('[');
            size_t right_bracket_index = line.find(']');
            long long mem_loc = stoll(line.substr(left_brack_index + 1, right_bracket_index - left_brack_index - 1)) | ormask;
            long long mem_value = stoll(line.substr(right_bracket_index + 4));
            list<long long> queue;
            queue.push_back(0);
            for (size_t i = 0; i < mask.length(); ++i) {
                if (mask[i] == 'X') {
                    size_t size = queue.size();
                    for (size_t j = 0; j < size; j++) {
                        long long curr = queue.front();
                        queue.pop_front();
                        queue.push_back((curr << 1));
                        queue.push_back((curr << 1) + 1);
                    }
                } else {
                    size_t size = queue.size();
                    int bit = (mem_loc >> (35 - i)) & 1;
                    for (size_t j = 0; j < size; j++) {
                        long long curr = queue.front();
                        queue.pop_front();
                        queue.push_back((curr << 1) + bit);
                    }
                }
            }
            for (long long locs : queue) {
                memory[locs] = mem_value;
            }
        }
    }
    reader.close();

    long long result = 0;
    for (auto mem_entry : memory) {
        result += mem_entry.second;
    }
    return result;
}

int main() {
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
    return 0;
}
