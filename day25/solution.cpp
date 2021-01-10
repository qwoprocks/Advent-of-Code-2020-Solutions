/* Link to problem: https://adventofcode.com/2020/day/25 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

long long part1(long long card_public_key, long long door_public_key) {
    long long mod = 20201227;
    long long subject_number = 7;
    long long card_loop_size = 0;
    long long start = 1;
    while (start != card_public_key) {
        start = (start * subject_number) % mod;
        ++card_loop_size;
    }
    long long encryption_key = 1;
    for (int i = 0; i < card_loop_size; ++i) {
         encryption_key = (encryption_key * door_public_key) % mod;
    }
    return encryption_key;
}

int main() {
    ifstream reader("input.txt");
    string line;
    getline(reader, line);
    long long card_public_key = stoll(line);
    getline(reader, line);
    long long door_public_key = stoll(line);
    cout << "Part 1: " << part1(card_public_key, door_public_key) << endl;
    return 0;
}
