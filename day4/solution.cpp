/* Link to problem: https://adventofcode.com/2020/day/4 */
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <unordered_set>
#include <unordered_map>
#include <regex>
using namespace std;

const unordered_map<string, int> expected_fields = { {"byr", 0}, {"iyr", 1}, {"eyr", 2}, {"hgt", 3}, {"hcl", 4}, {"ecl", 5}, {"pid", 6} };
const unordered_set<string> eye_color = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
const regex hair_color_regex("^#[0-9a-f]{6}$");
const regex height_regex_cm("^[0-9]{3}cm$");
const regex height_regex_in("^[0-9]{2}in$");

bool check_if_valid_passport(string &passport_data) {
    int current_fields[expected_fields.size()] = {0};
    char* field = strtok((char*) passport_data.c_str(), ":");
    while (field != NULL) {
        string field_str = field;
        if (expected_fields.find(field_str) != expected_fields.end()) {
            ++current_fields[expected_fields.find(field_str)->second];
        }
        field = strtok(NULL, " ");
        field = strtok(NULL, ":");
    }
    for (int elem : current_fields) {
        if (elem != 1) {
            return false;
        }
    }
    return true;
}

int part1() {
    ifstream reader("input.txt");
    string line;
    string data;
    int valid_passports = 0;
    while (getline(reader, line)) {
        if (line.length() < 3) {
            if (check_if_valid_passport(data)) {
                ++valid_passports;
            }
            data.clear();
        } else {
            data.append(line);
            data.append(" ");
        }
    }
    if (!data.empty()) {
        if (check_if_valid_passport(data)) {
            ++valid_passports;
        }
    }
    reader.close();
    return valid_passports;
}

bool is_number(char* s) {
    for (int i = 0; s[i] != '\0'; ++i) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

bool check_if_valid_passport_with_valid_fields(string &passport_data) {
    int current_fields[expected_fields.size()] = {0};
    char* field = strtok((char*) passport_data.c_str(), ":");
    while (field != NULL) {
        char* value = strtok(NULL, " ");
        string field_str = field;
        if (expected_fields.find(field_str) != expected_fields.end()) {
            ++current_fields[expected_fields.find(field_str)->second];

            if (field_str == "byr") {
                if (strlen(value) != 4 || !is_number(value)) {
                    return false;
                }
                int year = atoi(value);
                if (year < 1920 || year > 2002) {
                    return false;
                }
            } else if (field_str == "iyr") {
                if (strlen(value) != 4 || !is_number(value)) {
                    return false;
                }
                int year = atoi(value);
                if (year < 2010 || year > 2020) {
                    return false;
                }
            } else if (field_str == "eyr") {
                if (strlen(value) != 4 || !is_number(value)) {
                    return false;
                }
                int year = atoi(value);
                if (year < 2020 || year > 2030) {
                    return false;
                }
            } else if (field_str == "hgt") {
                if (regex_match(value, height_regex_in)) {
                    int height = atoi(value);
                    if (height < 59 || height > 76) {
                        return false;
                    }
                } else if (regex_match(value, height_regex_cm)) {
                    int height = atoi(value);
                    if (height < 150 || height > 193) {
                        return false;
                    }
                } else {
                    return false;
                }
            } else if (field_str == "hcl") {
                if (!regex_match(value, hair_color_regex)) {
                    return false;
                }
            } else if (field_str == "ecl") {
                if (eye_color.find(value) == eye_color.end()) {
                    return false;
                }
            } else if (field_str == "pid") {
                if (strlen(value) != 9 || !is_number(value)) {
                    return false;
                }
            }
        }
        field = strtok(NULL, ":");
    }
    for (int elem : current_fields) {
        if (elem != 1) {
            return false;
        }
    }
    return true;
}

int part2() {
    ifstream reader("input.txt");
    string line;
    string data;
    int valid_passports = 0;
    while (getline(reader, line)) {
        if (line.length() < 3) {
            if (check_if_valid_passport_with_valid_fields(data)) {
                ++valid_passports;
            }
            data.clear();
        } else {
            data.append(line);
            data.append(" ");
        }
    }
    if (!data.empty()) {
        if (check_if_valid_passport_with_valid_fields(data)) {
            ++valid_passports;
        }
    }
    reader.close();
    return valid_passports;
}

int main() {
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
    return 0;
}
