/* Link to problem: https://adventofcode.com/2020/day/16 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

int part1(vector<pair<pair<int, int>, pair<int, int>>> &ranges, vector<vector<int>> &nearby_tickets) {
    int error_rate = 0;
    for (auto ticket : nearby_tickets) {
        for (int field : ticket) {
            bool valid = false;
            for (auto range : ranges) {
                if ((field >= range.first.first && field <= range.first.second) || (field >= range.second.first && field <= range.second.second)) {
                    valid = true;
                    break;
                }
            }
            if (!valid) {
                error_rate += field;
            }
        }
    }
    return error_rate;
}

long long part2(vector<pair<pair<int, int>, pair<int, int>>> &ranges, vector<vector<int>> &nearby_tickets, vector<int> &my_ticket) {
    vector<set<size_t>> valid_order;
    for (size_t i = 0; i < ranges.size(); ++i) {
        set<size_t> possible_indices;
        for (size_t j = 0; j < my_ticket.size(); ++j) {
            possible_indices.insert(j);
        }
        valid_order.push_back(possible_indices);
    }
    for (auto ticket : nearby_tickets) {
        size_t i = 0;
        for (int field : ticket) {
            bool valid = false;
            for (auto range : ranges) {
                if ((field >= range.first.first && field <= range.first.second) || (field >= range.second.first && field <= range.second.second)) {
                    valid = true;
                    break;
                }
            }
            if (valid) {
                size_t j = 0;
                for (auto range : ranges) {
                    if (!((field >= range.first.first && field <= range.first.second) || (field >= range.second.first && field <= range.second.second))) {
                        valid_order[j].erase(i);
                    }
                    ++j;
                }
            }
            ++i;
        }
    }
    for (int i = 0; i < ranges.size(); ++i) {
        for (size_t j = 0; j < valid_order.size(); ++j) {
            if (valid_order[j].size() == 1) {
                int curr_index = *valid_order[j].begin();
                for (size_t k = 0; k < valid_order.size(); ++k) {
                    if (j == k) {
                        continue;
                    }
                    valid_order[k].erase(curr_index);
                }
            }
        }
    }
    long long result = 1;
    for (size_t i = 0; i < 6; ++i) {
        int curr_index = *valid_order[i].begin();
        result *= my_ticket[curr_index];
    }
    return result;
}

vector<int> read_ticket(string line) {
    vector<int> ticket;
    size_t start = 0;
    size_t delim_index = line.find(",");
    while (true) {
        ticket.push_back(stoi(line.substr(start, delim_index - start)));
        if (delim_index == string::npos) {
            break;
        }
        start = delim_index + 1;
        delim_index = line.find(",", start);
    }
    return ticket;
}

int main() {
    ifstream reader("input.txt");
    string line;
    // Get all the ranges
    vector<pair<pair<int, int>, pair<int, int>>> ranges;
    while (getline(reader, line)) {
        if (line.empty()) {
            break;
        }
        string range = line.substr(line.find(":") + 1);
        size_t delim_index = range.find(" or ");
        string left_range = range.substr(0, delim_index);
        string right_range = range.substr(delim_index + 4);
        delim_index = left_range.find("-");
        int left_range_lower_bound = stoi(left_range.substr(0, delim_index));
        int left_range_upper_bound = stoi(left_range.substr(delim_index + 1));
        delim_index = right_range.find("-");
        int right_range_lower_bound = stoi(right_range.substr(0, delim_index));
        int right_range_upper_bound = stoi(right_range.substr(delim_index + 1));
        ranges.push_back({{left_range_lower_bound, left_range_upper_bound}, {right_range_lower_bound, right_range_upper_bound}});
    }

    // Get own ticket
    getline(reader, line);
    getline(reader, line);
    vector<int> my_ticket = read_ticket(line);

    // Get nearby tickets
    getline(reader, line);
    getline(reader, line);
    vector<vector<int>> nearby_tickets;
    while (getline(reader, line)) {
        nearby_tickets.push_back(read_ticket(line));
    }
    reader.close();

    cout << "Part 1: " << part1(ranges, nearby_tickets) << endl;
    cout << "Part 2: " << part2(ranges, nearby_tickets, my_ticket) << endl;
    return 0;
}
