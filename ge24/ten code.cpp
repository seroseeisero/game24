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

    Game(int numPlayers) {  
        for (int i = 0; i < numPlayers; ++i) {
            string playerName;
            cout << "Enter name for Player " << (i + 1) << ": ";
            cin >> playerName;
            players.push_back(Player(playerName));
        }
    }

    void startGame() {
        cout << "\nGame Started!" << endl;
    }
};

int main() {
    string really;
    cout << " --  --*--ARE--*--  --" << endl;
    cout << " --  --*--YOU--*--  --  " << endl;
    cout << "--- --*--REALLY--*-- ---    " << endl;
    cout << "REALLY??? :";
    cin >> really;

    int numPlayers;
    cout << "Enter number of players (1-4): ";
    cin >> numPlayers;

    if (numPlayers < 1 || numPlayers > 4) {
        cout << "Invalid number of players. Please enter a number between 1 - 4." << endl;
        return 1;
    }

    Game game(numPlayers);  
    game.startGame();

  
    for (int i = 0; i < numPlayers; i++) {
        game.players[i].displayInfo();
    }

    return 0;
}

