#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>  // เพิ่มมาสำหรับ std::shuffle
using namespace std;

// ฟังก์ชันสำหรับสร้างเลขเริ่มต้นระหว่าง 24-30
int generateInitialNumber() {
    return rand() % 7 + 24;  // สร้างเลขสุ่มได้ 7 ค่า: 24, 25, 26, 27, 28, 29, 30
}

// ฟังก์ชันสำหรับสร้างตัวเลของค์ประกอบที่สามารถคำนวณให้ได้เลขเป้าหมาย
void generateComponentNumbers(int targetNumber) {
    vector<int> components;  // เวกเตอร์สำหรับเก็บตัวเลของค์ประกอบ
    int sum = 0;  // ผลบวกชั่วคราวของตัวเลของค์ประกอบ
    
    // สร้างตัวเลข 3 ตัวแรกที่รวมกันแล้วไม่เกินเลขเป้าหมาย
    for (int i = 0; i < 3; i++) {
        int max_value = min(15, targetNumber - sum - 1);  // กำหนดค่าสูงสุดที่จะสุ่มได้
        if (max_value < 1) max_value = 1;  // ป้องกันกรณีค่าต่ำกว่า 1
        
        int num = rand() % max_value + 1;  // สุ่มเลขระหว่าง 1 ถึง max_value
        components.push_back(num);  // เพิ่มเลขสุ่มเข้าไปในเวกเตอร์
        sum += num;  // รวมผลบวก
    }
    
    // ตัวเลขที่ 4 ควรทำให้สามารถไปถึงเลขเป้าหมายได้โดยการบวก
    int lastNumber = targetNumber - sum;  // คำนวณตัวเลขสุดท้ายที่ต้องการ
    
    // ตรวจสอบว่าตัวเลขสุดท้ายอยู่ในช่วง 1-15 หรือไม่
    if (lastNumber < 1 || lastNumber > 15) {
        // ถ้าไม่สามารถใช้การบวกได้ ลองใช้การลบหรือดำเนินการอื่นๆ
        components.clear();  // ล้างเวกเตอร์เดิม
        
        // เลือกตัวเลขแรกที่ใกล้เคียงกับเป้าหมายแต่ไม่เกิน 15
        int first = min(15, targetNumber / 2);  // หารครึ่งเลขเป้าหมาย แต่ไม่เกิน 15
        components.push_back(first);  // เพิ่มเข้าในเวกเตอร์
        
        // เลือกตัวเลขที่สองที่สามารถช่วยให้ถึงเป้าหมายเมื่อรวมกับตัวแรก
        int second = min(15, abs(targetNumber - first));  // ค่าต่างจากเป้าหมาย แต่ไม่เกิน 15
        components.push_back(second);  // เพิ่มเข้าในเวกเตอร์
        
        // เลือกตัวเลขอีกสองตัวที่มีค่าน้อยพอ
        components.push_back(rand() % 5 + 1);  // สุ่มเลข 1-5
        components.push_back(rand() % 5 + 1);  // สุ่มเลข 1-5
    } else {
        // ถ้าตัวเลขสุดท้ายอยู่ในช่วง 1-15 ก็เพิ่มเข้าไปได้เลย
        components.push_back(lastNumber);
    }
    
    // สลับตำแหน่งตัวเลขเพื่อไม่ให้เห็นชัดเจนว่าใช้ตัวไหนอย่างไร
    random_device rd;  // สร้างตัวสร้างเลขสุ่มจากฮาร์ดแวร์
    mt19937 g(rd());   // ใช้ Mersenne Twister สำหรับสร้างเลขสุ่มคุณภาพสูง
    shuffle(components.begin(), components.end(), g);  // สลับเวกเตอร์
    
    // แสดงตัวเลของค์ประกอบ
    for (int num : components) {
        cout << num << " ";  // แสดงแต่ละตัวเลข
    }
    cout << endl;  // ขึ้นบรรทัดใหม่
    
    // แสดงคำใบ้สำหรับวิธีการแก้ปัญหา
    cout << "Hint (one possible solution): ";
    if (components.size() == 4) {  // ตรวจสอบว่ามีตัวเลขครบ 4 ตัว
        if (lastNumber <= 15) {
            // ถ้าวิธีการบวกใช้ได้ แนะนำให้ลองบวกหรือลบ
            cout << "Try addition or subtraction between some numbers" << endl;
        } else {
            // ถ้าวิธีการบวกใช้ไม่ได้ แนะนำให้ลองคูณหรือหาร
            cout << "Try multiplication and/or division with some numbers" << endl;
        }
    }
}

// ฟังก์ชันหลัก
int main() {
    srand(time(0));  // กำหนดค่าเริ่มต้นของการสุ่มโดยใช้เวลาปัจจุบัน
    int initialNumber = generateInitialNumber();  // สร้างเลขเป้าหมาย
    cout << "Initial Number: " << initialNumber << endl;  // แสดงเลขเป้าหมาย
    cout << "Component Numbers: ";  // แสดงข้อความ
    generateComponentNumbers(initialNumber);  // สร้างและแสดงตัวเลของค์ประกอบ
    
    return 0;  // จบการทำงานของโปรแกรม
}
