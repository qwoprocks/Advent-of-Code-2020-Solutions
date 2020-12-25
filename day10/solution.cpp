/* Link to problem: https://adventofcode.com/2020/day/10 */
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

int part1(vector<int> &sorted_adapters) {
    int jolt_diffs[3] = {0};
    for (size_t i = 1; i < sorted_adapters.size(); ++i) {
        ++jolt_diffs[sorted_adapters[i] - sorted_adapters[i - 1] - 1];
    }
    return jolt_diffs[0] * jolt_diffs[2];
}

long long part2(vector<int> &sorted_adapters) {
    int max_joltage = sorted_adapters[sorted_adapters.size() - 1];
    long long dp[max_joltage + 1] = {-1};
    dp[0] = 1;
    for (size_t i = 1; i < sorted_adapters.size(); ++i) {
        int joltage = sorted_adapters[i];
        long long num_ways = 0;
        for (int j = 1; j <= 3; ++j) {
            if (joltage - j >= 0 && dp[joltage - j] != -1) {
                num_ways += dp[joltage - j];
            }
        }
        dp[joltage] = num_ways;
    }
    return dp[max_joltage];
}

int main() {
    ifstream reader("input.txt");
    string line;
    vector<int> sorted_adapters;
    int max = 0;
    while (getline(reader, line)) {
        int joltage = stoi(line);
        sorted_adapters.push_back(joltage);
        if (joltage > max) {
            max = joltage;
        }
    }
    reader.close();

    // Add charging outlet with 0 joltage
    sorted_adapters.push_back(0);
    // Add built-in joltage adapter with max joltage + 3
    sorted_adapters.push_back(max + 3);
    sort(sorted_adapters.begin(), sorted_adapters.end());
    cout << "Part 1: " << part1(sorted_adapters) << endl;
    cout << "Part 2: " << part2(sorted_adapters) << endl;
    return 0;
}
