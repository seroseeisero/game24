#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// ฟังก์ชันในการคำนวณผลลัพธ์ของสองตัวเลข
double applyOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b != 0) ? a / b : 1e9; // ตรวจสอบหารด้วย 0
        default: return 1e9;
    }
}

// ฟังก์ชันตรวจสอบว่าการเรียงลำดับตัวเลขและเครื่องหมายสามารถให้ผลลัพธ์ที่ต้องการได้หรือไม่
bool checkSolution(vector<double> nums, vector<char> ops, double target) {
    do { // ลองทุกการเรียงลำดับของตัวเลข
        do { // ลองทุกการจัดเรียงเครื่องหมาย
            double result1 = applyOperation(nums[0], nums[1], ops[0]);
            double result2 = applyOperation(result1, nums[2], ops[1]);
            double result3 = applyOperation(result2, nums[3], ops[2]);

            if (abs(result3 - target) < 1e-6) {
                return true; // ถ้าผลลัพธ์ตรงกับเป้าหมาย
            }
        } while (next_permutation(ops.begin(), ops.end()));
    } while (next_permutation(nums.begin(), nums.end()));

    return false;
}
