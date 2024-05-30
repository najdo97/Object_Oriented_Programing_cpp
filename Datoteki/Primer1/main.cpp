#include <iostream>
#include <fstream>

using namespace std;

bool eSamoglaska(char c) {

    char n = tolower(c);

    if (n == 'a' || n == 'e' || n == 'i' || n == 'o' || n == 'u') {
        return true;
    } else return false;
}

int main() {

    ifstream myFile;
    myFile.open("primer.txt");

    char c;
    int samoglaski = 0, br_redovi = 0, vkupno_samoglaski = 0;

    if (myFile.is_open()) {

        while (myFile.get(c)) {

            if (eSamoglaska(c)) {
                samoglaski++;
                vkupno_samoglaski++;
            }
            if (c == '\n') {
                if (samoglaski > 10) {
                    br_redovi++;
                }
                samoglaski = 0;
            }
        }
        if (samoglaski > 10) {
            br_redovi++;
            samoglaski = 0;
        }

    } else {
        cout << "ne se otvara datotekata " << endl;
    }

    cout << "Datotekata ima " << vkupno_samoglaski << " samoglaski" << endl;

    cout << "Vo " << br_redovi << " redovi ima poishe od 10 samoglaski" << endl;

    return 0;
}
