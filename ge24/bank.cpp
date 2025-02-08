#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h> // ใช้ _kbhit() และ _getch() สำหรับตรวจจับการกดปุ่ม (Windows เท่านั้น)

using namespace std;
using namespace chrono;

int main() {
    const int rounds = 4;  // จำนวนรอบ
    const int maxTime = 120; // จำกัดเวลาแต่ละรอบ 120 วินาที
    int times[rounds]; // เก็บเวลาที่ใช้ในแต่ละรอบ

    for (int i = 0; i < rounds; i++) {
        cout << "\nRound " << i + 1 << ": Press Enter to start the timer..." << endl;
        
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

        cout << "Elapsed time for round " << i + 1 << ": " << times[i] << " seconds.\n";
    }

    // แสดงผลลัพธ์ทั้งหมดหลังจากครบ 4 รอบ
    cout << "\n=== Summary of all rounds ===\n";
    for (int i = 0; i < rounds; i++) {
        cout << "Round " << i + 1 << ": " << times[i] << " seconds\n";
    }

    return 0;
}
