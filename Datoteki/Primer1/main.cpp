#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ifstream myFile;
    myFile.open("primer.txt");

    char c;

    if (myFile.is_open()) {
        while (myFile.get(c)) {
            myFile.get(c);
        }
    } else {
        cout << "ne se otvara datotekata " << endl;
    }

    return 0;
}
