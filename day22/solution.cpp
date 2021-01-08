/* Link to problem: https://adventofcode.com/2020/day/22 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <deque>
using namespace std;

int part1(deque<int> player1, deque<int> player2) {
    while (player1.size() != 0 && player2.size() != 0) {
        int c1 = player1.front();
        int c2 = player2.front();
        player1.pop_front();
        player2.pop_front();
        if (c1 > c2) {
            player1.push_back(c1);
            player1.push_back(c2);
        } else {
            player2.push_back(c2);
            player2.push_back(c1);
        }
    }
    deque<int> *winning_player = player1.size() != 0 ? &player1 : &player2;
    int result = 0;
    int i = winning_player->size();
    for (auto p = winning_player->begin(); p != winning_player->end(); ++p) {
        result += i * (*p);
        --i;
    }
    return result;
}

bool recursive_game(deque<int> &player1, deque<int> &player2) {
    set<vector<deque<int>>> past_rounds;
    while (player1.size() != 0 && player2.size() != 0) {
        vector<deque<int>> curr_round = {player1, player2};
        if (past_rounds.find(curr_round) != past_rounds.end()) {
            return true;
        }
        past_rounds.insert(curr_round);
        int c1 = player1.front();
        int c2 = player2.front();
        player1.pop_front();
        player2.pop_front();
        if (player1.size() >= c1 && player2.size() >= c2) {
            deque<int> new_player1(player1.begin(), player1.begin() + c1);
            deque<int> new_player2(player2.begin(), player2.begin() + c2);
            if (recursive_game(new_player1, new_player2)) {
                player1.push_back(c1);
                player1.push_back(c2);
            } else {
                player2.push_back(c2);
                player2.push_back(c1);
            }
        } else {
            if (c1 > c2) {
                player1.push_back(c1);
                player1.push_back(c2);
            } else {
                player2.push_back(c2);
                player2.push_back(c1);
            }
        }
    }
    return player1.size() != 0;
}

int part2(deque<int> player1, deque<int> player2) {
    recursive_game(player1, player2);
    deque<int> *winning_player = player1.size() != 0 ? &player1 : &player2;
    int result = 0;
    int i = winning_player->size();
    for (auto p = winning_player->begin(); p != winning_player->end(); ++p) {
        result += i * (*p);
        --i;
    }
    return result;
}

int main() {
    ifstream reader("input.txt");
    string line;
    deque<int> player1;
    deque<int> player2;
    deque<int> *curr_player = &player1;
    while(getline(reader, line)) {
        if (line.empty()) {
            curr_player = &player2;
        } else if (line.find(":") == string::npos) {
            curr_player->push_back(stoi(line));
        }
    }
    cout << "Part 1: " << part1(player1, player2) << endl;
    cout << "Part 2: " << part2(player1, player2) << endl;
    return 0;
}
