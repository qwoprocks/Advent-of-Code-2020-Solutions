/* Link to problem: https://adventofcode.com/2020/day/13 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int part1(vector<string> &bus_ids, int earliest_timestamp) {
    int current_timestamp = earliest_timestamp;
    while (true) {
        for (string id : bus_ids){
            if (all_of(id.begin(), id.end(), ::isdigit)) {
                if (current_timestamp % stoi(id) == 0) {
                    return (current_timestamp - earliest_timestamp) * stoi(id);
                }
            }
        }
        ++current_timestamp;
    }
    // If no answer is found, return 0
    return 0;
}

long long part2(vector<string> &bus_ids) {
    vector<pair<int, size_t>> bus_ids_index_pair;
    for (size_t i = 0; i < bus_ids.size(); ++i) {
        string id = bus_ids[i];
        if (all_of(id.begin(), id.end(), ::isdigit)) {
            bus_ids_index_pair.push_back({i, stoi(id)});
        }
    }
    // Sieve method
    long long answer = bus_ids_index_pair[0].first;
    long long product = 1;
    for (size_t i = 0; i < bus_ids_index_pair.size() - 1; ++i) {
        auto p = bus_ids_index_pair[i];
        product *= p.second;
        auto p2 = bus_ids_index_pair[i + 1];
        while ((answer + p2.first) % p2.second != 0) {
            answer += product;
        }
    }
    return answer;
}

int main() {
    ifstream reader("input.txt");
    string line;
    getline(reader, line);
    int earliest_timestamp = stoi(line);

    // Read bus ids into a vector
    getline(reader, line);
    vector<string> bus_ids;
    size_t start_index = 0;
    size_t delim_index = line.find(",", start_index);
    while (delim_index != string::npos) {
        bus_ids.push_back(line.substr(start_index, delim_index - start_index));
        start_index = delim_index + 1;
        delim_index = line.find(",", start_index);
    }
    bus_ids.push_back(line.substr(start_index, delim_index - start_index));

    cout << "Part 1: " << part1(bus_ids, earliest_timestamp) << endl;
    cout << "Part 2: " << part2(bus_ids) << endl;
    return 0;
}
