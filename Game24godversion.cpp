#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <chrono>
#include <conio.h>
#include <sstream>
#include <cmath>

using namespace std;
using namespace chrono;

class Player {
public:
    string name;
    int time;
    string answer;
    bool isCorrect; // เช็คคำตอบถูกหรือไม่

    Player(string playerName) {
        name = playerName;
        time = 0;
        isCorrect = false; // เริ่มต้นเป็นคำตอบไม่ถูก
    }

    void displayInfo() {
        cout << "Player: " << name << ", Time: " << time << " seconds" << endl;
    }
};

class Game {
public:
    vector<Player> players;
    int targetNumber;
    vector<int> componentNumbers;

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
        generateNumbers();
        // แสดงตัวเลขก่อนให้เลือกว่าจะสุ่มใหม่หรือไม่
        displayNumbers();
        askForNewNumbers();
    }

    void generateNumbers() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> componentDist(1, 9);

        // สุ่มตัวเลขที่ใช้ในการคำนวณ
        componentNumbers.clear(); // ลบเลขเดิมออกก่อน
        for (int i = 0; i < 4; i++) {
            componentNumbers.push_back(componentDist(gen));
        }

        // สร้าง targetNumber โดยใช้ตัวเลขที่สุ่ม
        targetNumber = generateTargetNumber();
    }

    int generateTargetNumber() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> operatorDist(0, 3);  // 0 = +, 1 = -, 2 = *, 3 = /

        // คำนวณผลลัพธ์จากตัวเลขที่สุ่มมา
        int result = componentNumbers[0];
        for (int i = 1; i < componentNumbers.size(); i++) {
            int op = operatorDist(gen);
            switch (op) {
                case 0: // +
                    result += componentNumbers[i];
                    break;
                case 1: // -
                    result -= componentNumbers[i];
                    break;
                case 2: // *
                    result *= componentNumbers[i];
                    break;
                case 3: // /
                    if (componentNumbers[i] != 0) { // ตรวจสอบหารด้วย 0
                        result /= componentNumbers[i];
                    }
                    break;
            }
        }

        // ใช้ abs() เพื่อให้ผลลัพธ์ไม่เป็นลบ
        return abs(result);  // ใช้ abs() เพื่อป้องกันผลลัพธ์ลบ
    }

    void displayNumbers() {
        cout << "Target Number: " << targetNumber << endl;
        cout << "Component Numbers: ";
        for (int num : componentNumbers) cout << num << " ";
        cout << endl;
    }

    void askForNewNumbers() {
        char choice;
        while (true) {
            cout << "\nDo you want to generate new numbers? (y/n): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y') {
                generateNumbers(); // สุ่มใหม่
                displayNumbers();  // แสดงตัวเลขใหม่
            } else if (choice == 'n' || choice == 'N') {
                break; // ไม่สุ่มใหม่เริ่มเกม
            } else {
                cout << "Invalid choice. Please enter 'y' or 'n'.\n";
            }
        }
    }
};

double applyOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b != 0) ? a / b : 1e9;
        default: return 1e9;
    }
}

bool checkSolution(const vector<int>& nums, int target, const string& expression) {
    stringstream ss(expression);
    vector<int> usedNumbers;
    int num;
    char op;

    while (ss >> num) {
        usedNumbers.push_back(num);
        if (!(ss >> op)) break;
    }

    sort(usedNumbers.begin(), usedNumbers.end());
    vector<int> sortedNums = nums;
    sort(sortedNums.begin(), sortedNums.end());

    if (usedNumbers != sortedNums) {
        return false;
    }

    return true; // Placeholder, actual evaluation logic needs to be implemented.
}

int main() {
    int numPlayers;
    cout << "Enter number of players (2-4): ";
    cin >> numPlayers;

    if (numPlayers < 2 || numPlayers > 4) {
        cout << "Invalid number of players. Please enter a number between 2 and 4." << endl;
        return 1;
    }

    Game game(numPlayers);
    game.startGame();

    for (int i = 0; i < numPlayers; i++) {
        cout << "\n" << game.players[i].name << ", Press Spacebar to start the timer..." << endl;
        while (true) {
            if (_kbhit() && _getch() == 32) break;
        }

        auto start = high_resolution_clock::now();
        cout << "Timer started. Enter your answer: ";
        cin.ignore();
        getline(cin, game.players[i].answer);

        auto end = high_resolution_clock::now();
        game.players[i].time = duration_cast<seconds>(end - start).count();

        cout << "\nTime taken: " << game.players[i].time << " seconds." << endl;

        // เก็บผลว่าเป็นคำตอบถูกหรือไม่
        game.players[i].isCorrect = checkSolution(game.componentNumbers, game.targetNumber, game.players[i].answer);
    }

    // แสดงผลลัพธ์หลังจากทุกคนเล่นเสร็จ
    cout << "\nGame Over!" << endl;

    // ค้นหาผู้เล่นที่ชนะ
    Player* winner = nullptr;
    for (int i = 0; i < numPlayers; i++) {
        if (game.players[i].isCorrect) {
            if (winner == nullptr || game.players[i].time < winner->time) {
                winner = &game.players[i];
            }
        }
    }

    // แสดงผลลัพธ์สำหรับผู้ชนะ
    if (winner != nullptr) {
        cout << "The winner is " << winner->name << "!" << endl;
        cout << "Time: " << winner->time << " seconds" << endl;
    } else {
        cout << "No one won the game." << endl;
    }

    return 0;
}
