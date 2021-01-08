/* Link to problem: https://adventofcode.com/2020/day/21 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

vector<string> split(string s, string delim) {
    vector<string> parts;
    size_t delim_index = s.find(delim);
    size_t start_index = 0;
    while(true) {
        parts.push_back(s.substr(start_index, delim_index - start_index));
        if (delim_index == string::npos) {
            break;
        }
        start_index = delim_index + delim.length();
        delim_index = s.find(delim, start_index);
    }
    return parts;
}

int part1(map<string, set<string>> &allergen_to_ingredients_map, vector<string> &ingredients) {
    ifstream reader("input.txt");
    string line;
    while(getline(reader, line)) {
        if (!line.empty()) {
            string delim = " (contains ";
            // Get set of ingredients
            vector<string> curr_ingredients = split(line.substr(0, line.find(delim)), " ");
            ingredients.insert(ingredients.end(), curr_ingredients.begin(), curr_ingredients.end());
            set<string> curr_ingredients_set(curr_ingredients.begin(), curr_ingredients.end());

            // allergens
            string allergens_string = line.substr(line.find(delim) + delim.length());
            allergens_string = allergens_string.substr(0, allergens_string.length() - 1);
            vector<string> curr_allergens = split(allergens_string, ", ");

            for (string allergen : curr_allergens) {
                if (allergen_to_ingredients_map.find(allergen) != allergen_to_ingredients_map.end()) {
                    vector<string> to_remove;
                    for (string prev_allergen : allergen_to_ingredients_map[allergen]) {
                        if (curr_ingredients_set.find(prev_allergen) == curr_ingredients_set.end()) {
                            to_remove.push_back(prev_allergen);
                        }
                    }
                    for (string r : to_remove) {
                        allergen_to_ingredients_map[allergen].erase(r);
                    }
                } else {
                    allergen_to_ingredients_map[allergen] = curr_ingredients_set;
                }
            }
        }
    }
    reader.close();
    for (auto entry : allergen_to_ingredients_map) {
        for (string i : entry.second) {
            ingredients.erase(remove(ingredients.begin(), ingredients.end(), i), ingredients.end());
        }
    }
    return ingredients.size();
}

string part2(map<string, set<string>> &allergen_to_ingredients_map, vector<string> &ingredients) {
    set<string> ingredients_set(ingredients.begin(), ingredients.end());
    for (string i : ingredients_set) {
        for (auto entry : allergen_to_ingredients_map) {
            allergen_to_ingredients_map[entry.first].erase(i);
        }
    }
    for (int i = 0; i < allergen_to_ingredients_map.size(); ++i) {
        for (auto entry : allergen_to_ingredients_map) {
            if (entry.second.size() == 1) {
                for (auto other_entry : allergen_to_ingredients_map) {
                    if (other_entry.first == entry.first) {
                        continue;
                    }
                    allergen_to_ingredients_map[other_entry.first].erase(*entry.second.begin());
                }
            }
        }
    }
    string result = "";
    for (auto entry : allergen_to_ingredients_map) {
        result += *entry.second.begin() + ",";
    }
    return result.substr(0, result.length() - 1);
}

int main() {
    map<string, set<string>> allergen_to_ingredients_map;
    vector<string> ingredients;
    cout << "Part 1: " << part1(allergen_to_ingredients_map, ingredients) << endl;
    cout << "Part 2: " << part2(allergen_to_ingredients_map, ingredients) << endl;
    return 0;
}
