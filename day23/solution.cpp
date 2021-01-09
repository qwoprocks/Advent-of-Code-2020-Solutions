/* Link to problem: https://adventofcode.com/2020/day/23 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

string part1(unordered_map<int, int> linked_list, int first_cup, int max_cup) {
    int current_cup = first_cup;
    for (int i = 0; i < 100; ++i) {
        int c1 = linked_list[current_cup];
        int c2 = linked_list[c1];
        int c3 = linked_list[c2];
        int c4 = linked_list[c3];
        linked_list[current_cup] = c4;
        int dest = current_cup - 1;
        while (dest == c1 || dest == c2 || dest == c3 || dest == 0) {
            if (--dest < 1) {
                dest = max_cup;
            }
        }
        int destc1 = linked_list[dest];
        linked_list[dest] = c1;
        linked_list[c3] = destc1;
        current_cup = c4;
    }
    stringstream final_labels;
    int start_cup = linked_list[1];
    while (start_cup != 1) {
        final_labels << start_cup;
        start_cup = linked_list[start_cup];
    }
    return final_labels.str();
}

long long part2(unordered_map<int, int> linked_list, int first_cup, int max_cup, int last_cup) {
    for (int i = max_cup + 1; i < 1000000; ++i) {
        linked_list[i] = i + 1;
    }
    linked_list[last_cup] = max_cup + 1;
    linked_list[1000000] = first_cup;
    int current_cup = first_cup;
    for (int i = 0; i < 10000000; ++i) {
        int c1 = linked_list[current_cup];
        int c2 = linked_list[c1];
        int c3 = linked_list[c2];
        int c4 = linked_list[c3];
        linked_list[current_cup] = c4;
        int dest = current_cup - 1;
        while (dest == c1 || dest == c2 || dest == c3 || dest == 0) {
            if (--dest < 1) {
                dest = 1000000;
            }
        }
        int destc1 = linked_list[dest];
        linked_list[dest] = c1;
        linked_list[c3] = destc1;
        current_cup = c4;
    }
    long long result = linked_list[1];
    result *= linked_list[linked_list[1]];
    return result;
}

int main() {
    ifstream reader("input.txt");
    string line;
    getline(reader, line);
    unordered_map<int, int> linked_list;
    int max_cup = 0;
    for (int i = 0; i < line.length() - 1; ++i) {
        int current_cup = line[i] - '0';
        linked_list[current_cup] = line[i + 1] - '0';
        if (current_cup > max_cup) {
            max_cup = current_cup;
        }
    }
    int last_cup = line[line.length() - 1] - '0';
    linked_list[last_cup] = line[0] - '0';
    if (last_cup > max_cup) {
        max_cup = last_cup;
    }
    int first_cup = line[0] - '0';
    cout << "Part 1: " << part1(linked_list, first_cup, max_cup) << endl;
    cout << "Part 2: " << part2(linked_list, first_cup, max_cup, last_cup) << endl;
    return 0;
}
