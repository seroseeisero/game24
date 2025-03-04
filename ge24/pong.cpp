#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

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

