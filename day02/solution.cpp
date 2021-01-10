/* Link to problem: https://adventofcode.com/2020/day/2 */
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;

int part1() {
    ifstream reader("input.txt");
    string line;
    int valid_count = 0;
    while (getline(reader, line)) {
        const char* c_line = line.c_str();

        char* bounds = strtok((char*) c_line, " ");
        char letter = strtok(NULL, ":")[0];
        char* password = strtok(NULL, " ");

        int left_bound = atoi(strtok(bounds, "-"));
        int right_bound = atoi(strtok(NULL, "-"));
        int letter_count = 0;

        for (int i = 0; password[i] != '\0'; ++i) {
            if (password[i] == letter) {
                ++letter_count;
            }
        }
        if (letter_count >= left_bound && letter_count <= right_bound) {
            ++valid_count;
        }
    }
    reader.close();
    return valid_count;
}

int part2() {
    ifstream reader("input.txt");
    string line;
    int valid_count = 0;
    while (getline(reader, line)) {
        const char* c_line = line.c_str();

        char* bounds = strtok((char*) c_line, " ");
        char letter = strtok(NULL, ":")[0];
        char* password = strtok(NULL, " ");

        int first_pos = atoi(strtok(bounds, "-"));
        int second_pos = atoi(strtok(NULL, "-"));

        if (password[first_pos - 1] == letter ^ password[second_pos - 1] == letter) {
            ++valid_count;
        }
    }
    reader.close();
    return valid_count;
}

int main() {
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
    return 0;
}
