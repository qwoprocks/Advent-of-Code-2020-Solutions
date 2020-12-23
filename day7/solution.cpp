/* Link to problem: https://adventofcode.com/2020/day/7 */
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <list>
#include <vector>
using namespace std;

vector<string> split(string s, string delim) {
    vector<string> parts;
    size_t start = 0;
    size_t delimIndex = s.find(delim);
    while (delimIndex != string::npos) {
        string part = s.substr(start, delimIndex - start);
        parts.push_back(part);
        start = delimIndex + delim.length();
        delimIndex = s.find(delim, start);
    }
    parts.push_back(s.substr(start, string::npos));
    return parts;
}

int part1() {
    ifstream reader("input.txt");
    string line;
    map<string, set<string>> graph;
    while (getline(reader, line)) {
        vector<string> innerOuterBagSplit = split(line, " bags contain ");
        string outerBag = innerOuterBagSplit[0];
        vector<string> innerBags = split(innerOuterBagSplit[1], ", ");
        for (string bag : innerBags) {
            if (bag == "no other bags.") {
                continue;
            }
            vector<string> innerBagSplit = split(bag, " ");
            string innerBag = innerBagSplit[1] + " " + innerBagSplit[2];
            if (graph.find(innerBag) != graph.end()) {
                graph[innerBag].insert(outerBag);
            } else {
                set<string> tempSet;
                tempSet.insert(outerBag);
                graph[innerBag] = tempSet;
            }
        }
    }
    list<string> queue;
    set<string> visited;
    visited.insert("shiny gold");
    queue.push_back("shiny gold");
    while (queue.size() > 0) {
        string currentBag = queue.front();
        visited.insert(currentBag);
        queue.pop_front();
        for (string bag : graph[currentBag]) {
            if (visited.find(bag) == visited.end()) {
                queue.push_back(bag);
            }
        }
    }
    reader.close();
    return visited.size() - 1; // minus one since we don't count the shiny gold bag.
}

long long countTotalBagsInside(string bag, map<string, set<pair<int, string>>> &graph) {
    if (graph.find(bag) == graph.end() || graph[bag].size() == 0) {
        return 0;
    }
    long long numBags = 0;
    for (auto innerBags : graph[bag]) {
        numBags += innerBags.first * (countTotalBagsInside(innerBags.second, graph) + 1);
    }
    return numBags;
}

int part2() {
    ifstream reader("input.txt");
    string line;
    map<string, set<pair<int, string>>> graph;
    while (getline(reader, line)) {
        vector<string> innerOuterBagSplit = split(line, " bags contain ");
        string outerBag = innerOuterBagSplit[0];
        vector<string> innerBags = split(innerOuterBagSplit[1], ", ");
        for (string bag : innerBags) {
            if (bag == "no other bags.") {
                continue;
            }
            vector<string> innerBagSplit = split(bag, " ");
            int numBags = stoi(innerBagSplit[0]);
            string innerBag = innerBagSplit[1] + " " + innerBagSplit[2];
            if (graph.find(outerBag) != graph.end()) {
                graph[outerBag].insert({numBags, innerBag});
            } else {
                set<pair<int, string>> tempSet;
                tempSet.insert({numBags, innerBag});
                graph[outerBag] = tempSet;
            }
        }
    }
    reader.close();
    return countTotalBagsInside("shiny gold", graph);
}

int main() {
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
    return 0;
}
