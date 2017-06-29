#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>
#include <utility>

using namespace std;

enum options {ROCK, PAPER, SCISSORS, SPOCK, LIZARD};

class Player {
    private:
    random_device rd;
    int id;

    public:
    Player(int);
    ~Player();
    //copy,move constructors and operators will be deleted
    int playTurn();
};

Player::Player(int id) {
    id = id;
};

Player::~Player() {
    ;
};

int Player::playTurn() {

    int a = rd() % 5;
    options output;
    switch (a) {
        case 0:
            output = ROCK;
            break;
        case 1:
            output = PAPER;
            break;
         case 2:
            output = SCISSORS;
            break;
        case 3:
            output = SPOCK;
            break;
        case 4:
            output = LIZARD;
            break;
        default:
            cout << "Something went wrong\n"; //this shouldn't happen
    }

    return output;
};


class Game {
    private:
    unordered_map<int,int> winners;
    unordered_map<int,int> losers;
    int totalgames;
    int ties;
    bool findWinner(int, int);
    void insertWinner(int);
    void insertLoser(int);

    public:
    Game();
    ~Game();
    void playGame(int, int);
    void printStats();
};

Game::Game() {
    totalgames = 0;
    ties = 0;
};

Game::~Game() {
    ;
};

void Game::insertWinner(int option) {
    if (winners.count(option) == 1) {
        winners[option] += 1;
    }
    else {
        winners.insert(make_pair(option,1));
    }
    return;
};

void Game::insertLoser(int option) {
    if (losers.count(option) == 1) {
        losers[option] += 1;
    }
    else {
        losers.insert(make_pair(option,1));
    }
    return;
};

void Game::playGame(int a, int b) {
    totalgames++;

    if (a == b) {
        ties++;
        return;
    }

    bool flag = findWinner(a, b);
    if (flag) {
        insertWinner(a);
        insertLoser(b);
    }
    else {
        insertWinner(b);
        insertLoser(a);
    }
    return;
};

bool Game::findWinner(int a, int b) { //find if a beats b
    if (a == ROCK) {
        if ((b == SCISSORS) || (b == LIZARD)) {
            return true;
        }
    }
    else if (a == PAPER) {
        if ((b == ROCK) || (b == SPOCK)) {
            return true;
        }
    }
    else if (a == SCISSORS) {
        if ((b == PAPER) || (b == LIZARD)) {
            return true;
        }
    }
    else if (a == SPOCK) {
        if ((b == SCISSORS) || (b == ROCK)) {
            return true;
        }
    }
    else if (a == LIZARD) {
        if ((b == SPOCK) || (b == PAPER)) {
            return true;
        }
    }
    else {
        return false;
    }
};

void Game::printStats() {
    for (auto it = winners.begin(); it != winners.end(); ++it) {
        switch (it->first) {
            case ROCK:
                cout << "ROCK: " << "Wins: " << it->second << " Losses: " << losers[it->first] << endl;
                break;
            case PAPER:
                cout << "PAPER: " << "Wins: " << it->second << " Losses: " << losers[it->first] << endl;
                break;
            case SCISSORS:
                cout << "SCISSORS: " << "Wins: " << it->second << " Losses: " << losers[it->first] << endl;
                break;
            case SPOCK:
                cout << "SPOCK: " << "Wins: " << it->second << " Losses: " << losers[it->first] << endl;
                break;
            case LIZARD:
                cout << "LIZARD: " << "Wins: " << it->second << " Losses: " << losers[it->first] << endl;
                break;
        }
    }

    cout << "Ties: " << ties << endl;
    cout << "Total games: " << totalgames << endl;
};

int main() {

    Player p1(1);
    Player p2(2);
    Game game;

    for (auto i = 0; i < 100000; ++i) {
        game.playGame(p1.playTurn(), p2.playTurn());
    }

    game.printStats();
    return 0;
};
