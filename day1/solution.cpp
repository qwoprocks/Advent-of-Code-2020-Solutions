/* Link to problem: https://adventofcode.com/2020/day/1 */
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

int part1(vector<int> nums) {
    unordered_set<int> hash_set;
    for (int n : nums) {
        hash_set.insert(2020 - n);
    }
    for (int n : nums) {
        if (2020 - n != n && hash_set.find(n) != hash_set.end()) {
            return n * (2020 - n);
        }
    }
    return 0;
}

int part2(vector<int> nums) {
    unordered_map<int, pair<int, int>> hash_map;
    for (auto i = nums.begin(); i != nums.end(); ++i) {
        for (auto j = i; ++j != nums.end(); /**/) {
            hash_map[2020 - *i - *j] = { *i, *j };
        }
    }
    for (auto n = nums.begin(); n != nums.end(); ++n) {
        if (hash_map.find(*n) != hash_map.end()) {
            int i = hash_map[*n].first;
            int j = hash_map[*n].second;
            if (i != *n && j != *n) {
                return i * j * *n;
            }
        }
    }
    return 0;
}

int main() {
    vector<int> nums;
    ifstream reader("input.txt");
    int num = 0;
    while (reader >> num) {
        nums.push_back(num);
    }
    reader.close();
    cout << "Part 1: " << part1(nums) << endl;
    cout << "Part 2: " << part2(nums) << endl;
    return 0;
}