/* Link to problem: https://adventofcode.com/2020/day/9 */
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <list>
using namespace std;

long part1(vector<long> &numbers) {
    unordered_set<long> hashset;
    list<long> running_list;
    for (size_t i = 0; i < numbers.size(); ++i) {
        if (i < 25) {
            running_list.push_back(numbers[i]);
            hashset.insert(numbers[i]);
        } else {
            long current = numbers[i];
            bool found = false;
            for (long n : running_list) {
                found |= hashset.find(current - n) != hashset.end();
            }
            if (!found) {
                return current;
            }
            hashset.erase(running_list.front());
            running_list.pop_front();
            hashset.insert(numbers[i]);
            running_list.push_back(numbers[i]);
        }
    }
    // If no answer is found, return 0
    return 0;
}

long part2(vector<long> &numbers, long part1_ans) {
    unordered_map<long, size_t> hashmap;
    long running_sum = numbers[0];
    hashmap[running_sum] =  0;
    for (size_t i = 1; i < numbers.size(); ++i) {
        running_sum += numbers[i];
        long difference = running_sum - part1_ans;
        if (hashmap.find(difference) != hashmap.end()) {
            size_t j = hashmap[difference] + 1;
            long smallest = numbers[j];
            long largest = numbers[j];
            for (; j <= i; ++j) {
                smallest = min((long) numbers[j], smallest);
                largest = max((long) numbers[j], largest);
            }
            return smallest + largest;
        }
        hashmap[running_sum] = i;
    }
    // If answer not found, return 0
    return 0;
}

int main() {
    ifstream reader("input.txt");
    string line;
    vector<long> numbers;
    while (getline(reader, line)) {
        numbers.push_back(stol(line));
    }
    reader.close();
    long part1_ans = part1(numbers);
    cout << "Part 1: " << part1_ans << endl;
    cout << "Part 2: " << part2(numbers, part1_ans) << endl;
    return 0;
}
