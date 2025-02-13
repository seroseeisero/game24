#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h> // ใช้ _kbhit() และ _getch() สำหรับตรวจจับการกดปุ่ม (Windows เท่านั้น)

using namespace std;
using namespace chrono;

int main() {
    int players; // จำนวนผู้เล่น
    const int maxTime = 120; // จำกัดเวลาแต่ละรอบ 120 วินาที

    // ให้ผู้เล่นเลือกจำนวนผู้เล่น
    cout << "Enter number of players (2-4): ";
    cin >> players;

    // ตรวจสอบจำนวนผู้เล่นที่ถูกต้อง
    if (players < 2 || players > 4) {
        cout << "Invalid number of players. Please enter a number between 2 and 4." << endl;
        return 1; // ออกจากโปรแกรมหากจำนวนผู้เล่นไม่ถูกต้อง
    }

    int times[players]; // เก็บเวลาที่ใช้ในแต่ละรอบ

    for (int i = 0; i < players; i++) {
        cout << "\nPlayer " << i + 1 << ", Round 1: Press Enter to start the timer..." << endl;
        
        while (true) {
            if (_kbhit() && _getch() == '\r') { // ตรวจจับการกด Enter
                break;
            }
        }

        auto start = high_resolution_clock::now(); // บันทึกเวลาเริ่มต้น
        cout << "Timer started. Press Enter again to stop the timer (or it will stop at 120 seconds)..." << endl;

        while (true) {
            auto now = high_resolution_clock::now();
            auto elapsed = duration_cast<seconds>(now - start).count();

            if (_kbhit() && _getch() == '\r') { // กด Enter เพื่อหยุดจับเวลา
                times[i] = elapsed;
                break;
            }
            if (elapsed >= maxTime) { // หยุดอัตโนมัติเมื่อครบ 120 วินาที
                cout << "\nTime is up! Auto-stopping at 120 seconds." << endl;
                times[i] = maxTime;
                break;
            }
        }

        cout << "Elapsed time for Player " << i + 1 << ": " << times[i] << " seconds.\n";
    }

    // แสดงผลลัพธ์ทั้งหมดหลังจากครบ 4 รอบ
    cout << "\n=== Summary of all players ===\n";
    for (int i = 0; i < players; i++) {
        cout << "Player " << i + 1 << ": " << times[i] << " seconds\n";
    }

    return 0;
}

