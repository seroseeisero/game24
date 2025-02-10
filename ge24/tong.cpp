#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int generateInitialNumber() {
    return rand() % 27 + 24;
}

void generateComponentNumbers() {
    for (int i = 0; i < 4; i++) {
        cout << rand() % 15 + 1 << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));

    int initialNumber = generateInitialNumber();
    cout << "Initial Number: " << initialNumber << endl;

    cout << "Component Numbers: ";
    generateComponentNumbers();

    return 0;
}
