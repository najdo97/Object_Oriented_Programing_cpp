//  Да се напише програма која што од датотека со име "text.txt" ќе ги одреди и ќе ги испечати на стандарден излез:
//•	релативната фреквенција на сите мали букви
//•	релативната фреквенција на сите големи букви

//  Релативната фреквенција на даден(и) карактер(и) се пресметува како количник на вкупното појавување на тој/тие
//  карактер/и со вкупниот број на карактери во текстот (да се игнорираат празните места и специјалните знаци).


#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

void writeToFile() {
    std::ofstream outFile("text.txt");
    char c;
    while ((c = std::cin.get()) != '#') {
        outFile.put(c);
    }
    outFile.close();
}

int main() {
    writeToFile();

    ifstream textFile;
    textFile.open("text.txt");

    char c;
    int vkupnoBukvi = 0, golemiBukvi = 0, maliBukvi = 0;

    if (textFile.is_open()) {

        while (textFile.get(c)) {
            if (isalpha(c)) {
                vkupnoBukvi++;
            }
            if (isalpha(c) && isupper(c)) {
                golemiBukvi++;
            }
            if (isalpha(c) && islower(c)) {
                maliBukvi++;
            }
        }
    } else {
        cout << "Cant open file." << endl;
    }
    cout <<(float)golemiBukvi/(float)vkupnoBukvi<<endl;
    cout <<(float)maliBukvi/(float)vkupnoBukvi<<endl;

    return 0;
}
