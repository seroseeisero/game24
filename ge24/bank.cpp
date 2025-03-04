#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>
#include <vector>

using namespace std;
using namespace chrono;

int main() {
    int players;

    cout << "Enter number of players (1-4): ";
    cin >> players;

    if (players < 1 || players > 4) {
        cout << "Invalid number of players. Please enter a number between 1 and 4." << endl;
        return 1;
    }

    vector<string> playerNames(players); // เก็บชื่อผู้เล่น
    vector<int> times(players); // เก็บเวลาที่ใช้ในแต่ละรอบ

    // ให้ผู้เล่นกรอกชื่อ
    for (int i = 0; i < players; i++) {
        cout << "Enter name for Player " << i + 1 << ": ";
        cin >> playerNames[i];
    }

    for (int i = 0; i < players; i++) {
        cout << "\n" << playerNames[i] << ", Round 1: Press Spacebar to start the timer..." << endl;

        while (true) {
            if (_kbhit() && _getch() == 32) {  // 32 คือค่า ASCII ของ Spacebar
                break;
            }
        }

        auto start = high_resolution_clock::now();
        cout << "Timer started. Press Spacebar again to stop the timer..." << endl;

        while (true) {
            if (_kbhit() && _getch() == 32) {  // 32 คือค่า ASCII ของ Spacebar
                auto now = high_resolution_clock::now();
                times[i] = duration_cast<seconds>(now - start).count();
                break;
            }
        }

        cout << "Elapsed time for " << playerNames[i] << ": " << times[i] << " seconds.\n";
    }

    if (players > 1) { // แสดงอันดับเฉพาะถ้ามีมากกว่า 1 คน
        vector<int> rankedPlayers(times.begin(), times.end());
        sort(rankedPlayers.begin(), rankedPlayers.end());

        cout << "\n=== Ranking of players ===\n";
        for (int i = 0; i < players; i++) {
            cout << "Rank " << i + 1 << ": ";
            for (int j = 0; j < players; j++) {
                if (times[j] == rankedPlayers[i]) {
                    cout << playerNames[j] << " with time: " << rankedPlayers[i] << " seconds" << endl;
                    break;
                }
            }
        }
    }

    return 0;
}
