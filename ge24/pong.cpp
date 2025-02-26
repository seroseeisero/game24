#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

// ฟังก์ชันเพื่อดำเนินการคำนวณตามเครื่องหมายที่กำหนด
double applyOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b; // บวก
        case '-': return a - b; // ลบ
        case '*': return a * b; // คูณ
        case '/': return (b != 0) ? a / b : 1e9; // หาร (ตรวจสอบหารด้วย 0)
        default: return 1e9;
    }
}

// ตรวจสอบว่ามีการเรียงลำดับตัวเลขและเครื่องหมายแล้วให้ผลลัพธ์ที่ต้องการหรือไม่
bool checkSolution(vector<double> nums, vector<char> ops, double target) {
    do {
        for (int i = 0; i < 4; i++) { // ลูปผ่านเครื่องหมายตัวที่ 1
            for (int j = 0; j < 4; j++) { // ลูปผ่านเครื่องหมายตัวที่ 2
                for (int k = 0; k < 4; k++) { // ลูปผ่านเครื่องหมายตัวที่ 3
                    double res1 = applyOperation(nums[0], nums[1], ops[i]); // คำนวณคู่แรก
                    double res2 = applyOperation(res1, nums[2], ops[j]); // คำนวณกับตัวที่สาม
                    double res3 = applyOperation(res2, nums[3], ops[k]); // คำนวณกับตัวที่สี่
                    if (abs(res3 - target) < 1e-6) return true; // ตรวจสอบว่าตรงกับเป้าหมายหรือไม่
                }
            }
        }
    } while (next_permutation(nums.begin(), nums.end())); // ลองทุกการเรียงลำดับตัวเลข
    return false;
}

int main() {
    random_device rd;
    mt19937 gen(rd()); // กำหนดตัวสร้างเลขสุ่ม
    uniform_int_distribution<int> dist(1, 9); // ช่วงสุ่มตัวเลข 1-9
    uniform_int_distribution<int> target_dist(24, 50);
    
    vector<double> nums(4);
    for (int i = 0; i < 4; i++) nums[i] = dist(gen); // สุ่มเลข 4 ตัว
    double target = target_dist(gen); // สุ่มค่าผลลัพธ์ที่ต้องหา
    
    vector<char> ops = {'+', '-', '*', '/'}; // เครื่องหมายที่ใช้ได้
    
    cout << "Numbers: ";
    for (double num : nums) cout << num << " "; // แสดงตัวเลขที่สุ่มได้
    cout << "\nTarget: " << target << endl; // แสดงค่าผลลัพธ์ที่ต้องหา
    
    if (checkSolution(nums, ops, target)) { // ตรวจสอบว่ามีวิธีทำให้ได้ผลลัพธ์หรือไม่
        cout << "Solution exists!" << endl; // มีคำตอบ
    } else {
        cout << "No solution found." << endl; // ไม่มีคำตอบ
    }
    
    return 0;
}
