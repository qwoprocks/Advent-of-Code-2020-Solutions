/* Link to problem: https://adventofcode.com/2020/day/18 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

long long eval(string eqn) {
    long long result = 0;
    char curr_op = '+';
    int digit = 0;
    for (size_t i = 0; i < eqn.length(); ++i) {
        char c = eqn[i];
        if (isdigit(c)) {
            digit = digit * 10 + (c - '0');
        } else if (c == '+' || c == '*') {
            if (curr_op == '+') {
                result += digit;
            } else if (curr_op == '*') {
                result *= digit;
            }
            digit = 0;
            curr_op = c;
        } else if (c == '(') {
            int counter = 1;
            for (size_t j = i + 1; j < eqn.length(); ++j) {
                if (eqn[j] == '(') {
                    counter += 1;
                } else if (eqn[j] == ')') {
                    counter -= 1;
                }
                if (counter == 0) {
                    if (curr_op == '+') {
                        result += eval(eqn.substr(i + 1, j - (i + 1)));
                    } else if (curr_op == '*') {
                        result *= eval(eqn.substr(i + 1, j - (i + 1)));
                    }
                    i = j + 1;
                    break;
                }
            }
            digit = 0;
            curr_op = '+';
        }
    }
    if (curr_op == '+') {
        result += digit;
    } else if (curr_op == '*') {
        result *= digit;
    }
    return result;
}

long long part1(vector<string> &equations) {
    long long result = 0;
    for (string eqn : equations) {
        result += eval(eqn);
    }
    return result;
}

long long eval2(string eqn) {
    vector<long long> mult_stack;
    mult_stack.push_back(0);
    char curr_op = '+';
    int digit = 0;
    for (size_t i = 0; i < eqn.length(); ++i) {
        char c = eqn[i];
        if (isdigit(c)) {
            digit = digit * 10 + (c - '0');
        } else if (c == '+' || c == '*') {
            if (curr_op == '+') {
                mult_stack.back() += digit;
            } else if (curr_op == '*') {
                mult_stack.push_back(digit);
            }
            digit = 0;
            curr_op = c;
        } else if (c == '(') {
            int counter = 1;
            for (size_t j = i + 1; j < eqn.length(); ++j) {
                if (eqn[j] == '(') {
                    counter += 1;
                } else if (eqn[j] == ')') {
                    counter -= 1;
                }
                if (counter == 0) {
                    if (curr_op == '+') {
                        mult_stack.back() += eval2(eqn.substr(i + 1, j - (i + 1)));
                    } else if (curr_op == '*') {
                        mult_stack.push_back(eval2(eqn.substr(i + 1, j - (i + 1))));
                    }
                    i = j + 1;
                    break;
                }
            }
            digit = 0;
            curr_op = '+';
        }
    }
    long long result = 1;
    if (curr_op == '+') {
        mult_stack.back() += digit;
    } else if (curr_op == '*') {
        result = digit;
    }
    for (long long num : mult_stack) {
        result *= num;
    }
    return result;
}

long long part2(vector<string> &equations) {
    long long result = 0;
    for (string eqn : equations) {
        result += eval2(eqn);
    }
    return result;
}

int main() {
    ifstream reader("input.txt");
    string line;
    vector<string> equations;
    while(getline(reader, line)) {
        equations.push_back(line);
    }
    reader.close();
    cout << "Part 1: " << part1(equations) << endl;
    cout << "Part 2: " << part2(equations) << endl;
    return 0;
}
