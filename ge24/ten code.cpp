#include<iostream>
#include <string>
#include <vector>
using namespace std;

class Player {
public:
    string name;
    double number;
    double score;
    float time;

    Player(string playerName) {
        name = playerName;
        time = 0;
    }

    void displayInfo() {
        cout << "Player: " << name << ", Time: " << time << endl;
    }
};

class Game {
public:
    vector<Player> players;

    Game() {
        for (int i=0; i<4; ++i) {
            string playerName;
            cout <<"Enter name for Player " << (i + 1) << ": ";
            cin >> playerName;
            players.push_back(Player(playerName));
        }
    }
    void startGame() {
        cout << "\nGame Started!" << endl;
    }
};
int main() {
    Game game;
    game.startGame();

    return 0;
}
