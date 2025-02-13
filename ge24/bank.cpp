#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>
#include <algorithm>
#include <vector>

using namespace std;
using namespace chrono;

int main() {
    int players;
    const int maxTime = 120;

    cout << "Enter number of players (2-4): ";
    cin >> players;

    if (players < 2 || players > 4) {
        cout << "Invalid number of players. Please enter a number between 2 and 4." << endl;
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
        cout << "\n" << playerNames[i] << ", Round 1: Press Enter to start the timer..." << endl;
        
        while (true) {
            if (_kbhit() && _getch() == '\r') {
                break;
            }
        }

        auto start = high_resolution_clock::now();
        cout << "Timer started. Press Enter again to stop the timer (or it will stop at 120 seconds)..." << endl;

        while (true) {
            auto now = high_resolution_clock::now();
            auto elapsed = duration_cast<seconds>(now - start).count();

            if (_kbhit() && _getch() == '\r') {
                times[i] = elapsed;
                break;
            }
            if (elapsed >= maxTime) {
                cout << "\nTime is up! Auto-stopping at 120 seconds." << endl;
                times[i] = maxTime;
                break;
            }
        }

        cout << "Elapsed time for " << playerNames[i] << ": " << times[i] << " seconds.\n";
    }

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

    return 0;
}

