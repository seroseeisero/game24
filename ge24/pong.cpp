#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// ฟังก์ชันในการคำนวณผลลัพธ์ของสองตัวเลข
double applyOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b != 0) ? a / b : 1e9; // ตรวจสอบการหารด้วย 0
        default: return 1e9;
    }
}

// ฟังก์ชันในการตรวจสอบว่าการจัดการตัวเลขและเครื่องหมายทำให้ได้ผลลัพธ์ 24 หรือไม่
bool checkSolution(vector<double> nums, vector<char> ops) {
    // ลองทุกการเรียงลำดับของตัวเลข
    do {
        // ลองทุกการจัดเรียงเครื่องหมาย
        do {
            double result1 = applyOperation(nums[0], nums[1], ops[0]);
            double result2 = applyOperation(result1, nums[2], ops[1]);
            double result3 = applyOperation(result2, nums[3], ops[2]);

            if (abs(result3 - 24) < 1e-6) {
                return true; // ถ้าผลลัพธ์เท่ากับ 24
            }
        } while (next_permutation(ops.begin(), ops.end())); // ลองทุกการจัดเรียงเครื่องหมาย
    } while (next_permutation(nums.begin(), nums.end())); // ลองทุกการจัดเรียงตัวเลข
    return false;
}

// ฟังก์ชันสุ่มตัวเลข
vector<int> generateRandomNumbers() {
    vector<int> numbers(4);
    for (int i = 0; i < 4; i++) {
        numbers[i] = rand() % 15 + 1; // สุ่มเลข 1-15
    }
    return numbers;
}

