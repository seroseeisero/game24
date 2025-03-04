#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <conio.h>
#include <algorithm>
#include <random>
#include <string>
#include <cmath>
#include <sstream>
#include <stack>
#include <limits>

using namespace std;

// ✅ ประกาศ Prototype ฟังก์ชันที่จำเป็น
int generateInitialNumber();
void generateComponentNumbers(int targetNumber);
bool checkSolution(const string& expression, double target);
double evaluateExpression(const string& expression);

//--------------- คลาสผู้เล่น ---------------------
class Player {
public:
    string name;
    double number;
    double score;
    float time;
    bool correctAnswer;

    Player(string playerName) {
        name = playerName;
        time = 0;
        score = 0;
        correctAnswer = false;
    }

    void displayInfo() {
        cout << "Player: " << name << ", Time: " << time << endl;
    }
};

//--------------- คลาสเกม ---------------------
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

// Function to check if character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to get precedence of operator
int getPrecedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Function to perform operation
double applyOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : 0; // Avoid division by zero
    }
    return 0;
}

// Function เช็คคำตอบกับวงเล็บ
double evaluateExpression(const string& expression) {
    string expr = expression;
    // ลบช่องว่าง
    expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());
    
    stack<double> values;
    stack<char> ops;

    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == ' ') //ถ้าเป็นช่องว่าง
            continue; //ข้ามช่องว่าง

        //ถ้าเป็นอีกชระหรือทศยนิยม เก็บค่าใน stack 
        if (isdigit(expr[i]) || expr[i] == '.') {
            string numStr; //เก็บตัวเลขหรือทศนิยม
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.'))
                numStr += expr[i++];
            i--; // Move back one position
            values.push(stod(numStr)); //เปลงเป็นdouble 
        }
        else if (expr[i] == '(') {
            ops.push(expr[i]); //เจอ ( เก็บลง stack)
        }
        // If current character is closing bracket, solve the bracket
        else if (expr[i] == ')') { //เจอ ) จะคำนวณก่อน
            while (!ops.empty() && ops.top() != '(') {
                double val2 = values.top(); //ดึงค่ามาคำนวณ
                values.pop(); //เอาค่าออก
                
                double val1 = values.top();
                values.pop();
                
                char op = ops.top();
                ops.pop();
                
                values.push(applyOperation(val1, val2, op)); //คำนวณ เลขขจากoperator ,คืนค่า
            }
            
            if (!ops.empty())
                ops.pop(); //ถ้ามีวงเล็บจะลบออกและทำต่อ
        }
        // If current character is an operator
        else if (isOperator(expr[i])) {
            while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(expr[i])) { //ทำจนเจอสแตกว่างหรือตัวที่สำคัญกว่า
                if (ops.top() == '(') break; //เจอ ( หยุด
                
                double val2 = values.top();
                values.pop();
                
                double val1 = values.top();
                values.pop();
                
                char op = ops.top();
                ops.pop();
                
                values.push(applyOperation(val1, val2, op));
            }
            
            ops.push(expr[i]);
        }
    }
    
    while (!ops.empty()) { //เช็คจนจะว่าง
        double val2 = values.top();
        values.pop();
        
        double val1 = values.top();
        values.pop();
        
        char op = ops.top();
        ops.pop();
        
        values.push(applyOperation(val1, val2, op));
    }
    
    return values.top();
}

// Function to check if the expression evaluates to the target number
bool checkSolution(const string& expression, double target) {
    try {
        double result = evaluateExpression(expression);// จะคำนวณค่าของนิพจน์ที่รับเข้ามา
        return abs(result - target) < 1e-6; //เช็ว่าค่าใกล้กับค่าที่ต้องการโดยใช้ความคลาดเคลื่อนที่ยอมรับได้    
    } catch (...) { //เช็คข้อผิดพลาด
        return false;
    }
}

// ✅ playTimerGame() อยู่หลัง checkSolution()
void playTimerGame(vector<Player> &players, int targetNumber) {
    const int maxTime = 120;

    // Clear input buffer before starting
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < players.size(); i++) {
        cout << "\n" << players[i].name << ", press Spacebar to start the timer..." << endl;

        while (true) {
            if (_kbhit() && _getch() == 32) {
                break;
            }
        }

        auto start = chrono::high_resolution_clock::now();
        cout << "Timer started. Enter your answer (e.g., 5+1+6+15 or (5+1)*(6-2)): ";

        string input;
        getline(cin, input);

        auto stop = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::seconds>(stop - start).count();
        players[i].time = elapsed;

        players[i].correctAnswer = checkSolution(input, targetNumber);
        if (players[i].correctAnswer) {
            cout << "!Correct answer!" << endl;
        } else {
            cout << "!Wrong answer!" << endl;
        }
        cout << "Elapsed time for " << players[i].name << ": " << players[i].time << " sec.\n";
    }

    // First group: correct answers sorted by time
    vector<Player> correctPlayers;
    vector<Player> wrongPlayers;
    
    for (const auto& player : players) {
        if (player.correctAnswer) {
            correctPlayers.push_back(player);
        } else {
            wrongPlayers.push_back(player);
        }
    }
    
    // Sort both groups by time
    sort(correctPlayers.begin(), correctPlayers.end(), [](const Player &a, const Player &b) {
        return a.time < b.time;
    });
    
    sort(wrongPlayers.begin(), wrongPlayers.end(), [](const Player &a, const Player &b) {
        return a.time < b.time;
    });
    
    // Combine the groups: correct players first, then incorrect players
    vector<Player> rankedPlayers;
    rankedPlayers.insert(rankedPlayers.end(), correctPlayers.begin(), correctPlayers.end());
    rankedPlayers.insert(rankedPlayers.end(), wrongPlayers.begin(), wrongPlayers.end());

    cout << "\n=== Ranking of players ===\n";
    for (int i = 0; i < rankedPlayers.size(); i++) {
        cout << "Rank " << i + 1 << ": " << rankedPlayers[i].name << " - " << rankedPlayers[i].time << " sec";
        if (!rankedPlayers[i].correctAnswer) {
            cout << " (Wrong answer)";
        }
        cout << endl;
    }
    
    if (!correctPlayers.empty()) {
        cout << "\nWinner is: " << correctPlayers[0].name << " with " << correctPlayers[0].time << " sec!" << endl;
    } else {
        cout << "\nNo winner - all players gave incorrect answers!" << endl;
    }
}

// ✅ ฟังก์ชันที่ใช้สุ่มตัวเลข
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
    mt19937 g(rd());   //  mtเป็นเครื่องมือที่มีความเร็วในการสุ่มสูง และกระจายตัวดี  g(rd()) คือ generateสุ่มเลขที่ไม่มีความซ้ำซากในแต่ละรอบที่รัน
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

// ✅ main() อยู่ล่างสุด
int main() {
    srand(time(0));

    // 🎬 แสดง Intro ก่อนเริ่มเกม
    cout << "\n--  --*--ARE--*--  --" << endl;
    cout << " --  --*--YOU--*--  --" << endl;
    cout << "--- --*--READY--*-- ---" << endl;

    string ready;
    cout << "READY??? :";
    cin >> ready;

    // ตรวจสอบว่าผู้ใช้พิมพ์ "yes" เท่านั้น
    if (ready != "yes") {
        cout << "Please type 'yes' to proceed." << endl;
        return 1;
    }

    int numPlayers;
    cout << "Enter number of players (1-4): ";
    cin >> numPlayers;

    if (numPlayers < 1 || numPlayers > 4) {
        cout << "Invalid number of players. Please enter a number between 1 and 4." << endl;
        return 1;
    }

    Game game(numPlayers);
    game.startGame();

    int initialNumber = generateInitialNumber();
    cout << "Initial Number: " << initialNumber << endl;
    cout << "Component Numbers: ";
    generateComponentNumbers(initialNumber);

    playTimerGame(game.players, initialNumber);

    return 0;
}
