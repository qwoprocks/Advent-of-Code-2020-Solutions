/* Link to problem: https://adventofcode.com/2020/day/19 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

bool check(string &s, unordered_map<string, vector<vector<string>>> &rules, vector<string> &rule, int s_index) {
    if (s_index == -1 || rule.size() == 0) {
        return s_index == -1 && rule.size() == 0;
    }
    if (rule.size() > s.length()) {
        return false;
    }

    vector<vector<string>> r = rules[rule.back()];
    if (r[0][0][1] == 'a' || r[0][0][1] == 'b') {
        if (s[s_index] == r[0][0][1]) {
            vector<string> t(rule.begin(), rule.end() - 1);
            return check(s, rules, t, s_index - 1);
        } else {
            return false;
        }
    } else {
        for (vector<string> r2 : r) {
            vector<string> t(rule.begin(), rule.end() - 1);
            t.insert(t.end(), r2.begin(), r2.end());
            if (check(s, rules, t, s_index)) {
                return true;
            }
        }
        return false;
    }
}

int part1(unordered_map<string, vector<vector<string>>> &rules, vector<string> &lines) {
    int num_lines = 0;
    for (string s : lines) {
        if (check(s, rules, rules["0"][0], s.length() - 1)) {
            ++num_lines;
        }
    }
    return num_lines;
}

int part2(unordered_map<string, vector<vector<string>>> &rules, vector<string> &lines) {
    rules["8"] = {{"42"}, {"42", "8"}};
    rules["11"] = {{"42", "31"}, {"42", "11", "31"}};
    return part1(rules, lines);
}

vector<string> split(string s, string delim) {
    vector<string> result;
    size_t delim_index = s.find(delim);
    size_t start_index = 0;
    while (true) {
        result.push_back(s.substr(start_index, delim_index - start_index));
        if (delim_index == string::npos) {
            break;
        }
        start_index = delim_index + delim.length();
        delim_index = s.find(start_index);
    }
    return result;
}

int main() {
    ifstream reader("input.txt");
    string line;
    unordered_map<string, vector<vector<string>>> rules;
    vector<string> lines;
    while(getline(reader, line)) {
        size_t i = line.find(": ");
        if (i != string::npos) {
            vector<vector<string>> curr_rules;
            for (string s : split(line.substr(i + 2), " | ")) {
                curr_rules.push_back(split(s, " "));
            }
            rules[line.substr(0, i)] = curr_rules;
        } else if (!line.empty()) {
            lines.push_back(line);
        }
    }
    reader.close();
    cout << "Part 1: " << part1(rules, lines) << endl;
    cout << "Part 2: " << part2(rules, lines) << endl;
    return 0;
}
