#include <iostream>
#include <cstring>

using namespace std;


class Character {
private:
    char ch;
public:

    char getCh() const {
        return ch;
    }

    void setCh(char ch) {
        Character::ch = ch;
    }


    Character() {
        this->ch = '0';
    }

    Character(char c) {
        this->ch = c;
    }

    Character(const Character &c) {
        this->ch = c.ch;
    }

    Character &operator=(const Character &c) {
        this->ch = c.ch;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Character &character) {
        os << character.ch << endl;
        return os;
    }
};

class CharSequence {

private:
    Character *charArray;
    int arraySize;
public:

    CharSequence() {
        this->charArray = nullptr;
    }

    CharSequence(char *charArray) {

        this->charArray = new Character[strlen(charArray) + 1];
        for (int i = 0; i < strlen(charArray); i++) {
            this->charArray[i].setCh(charArray[i]);
        }
        this->arraySize = strlen(charArray);
    }

    CharSequence(Character *charArray, int arraySize) {
        this->charArray = new Character[arraySize];
        for (int i = 0; i < arraySize; i++) {
            this->charArray[i] = charArray[i];
        }
    }

    CharSequence(const CharSequence &cs) {
        this->charArray = new Character[cs.arraySize];
        for (int i = 0; i < cs.arraySize; i++) {
            this->charArray[i] = cs.charArray[i];
        }
    }

    CharSequence &operator=(const CharSequence &cs) {
        delete this->charArray;
        this->charArray = new Character[cs.arraySize];
        for (int i = 0; i < cs.arraySize; i++) {
            this->charArray[i] = cs.charArray[i];
        }
        return *this;
    }

    ~CharSequence() {
        delete this->charArray;
    }

    CharSequence &operator+=(const Character &c) {

        Character *tmp = new Character[this->arraySize + 1];

        for (int i = 0; i < arraySize; i++) {
            tmp[i] = this->charArray[i];
        }
        tmp[arraySize] = c;
        this->arraySize++;
        delete this->charArray;
        this->charArray = tmp;

        return *this;
    }


    Character &operator[](int i) {

        return this->charArray[i];
    }


    bool operator==(const CharSequence &cs) {
        if (this->arraySize != cs.arraySize) {
            return false;
        }
        for (int i = 0; i < this->arraySize; i++) {
            if (this->charArray[i].getCh() != cs.charArray[i].getCh()) {
                return false;
            }
        }
        return true;
    }

    int operator[](char c) {
        int brojac = 0;
        for (int i = 0; i < this->arraySize; i++) {
            if (this->charArray[i].getCh() == c) {
                brojac++;
            }
        }
        return brojac;
    }

    CharSequence toUpperCase() {
        CharSequence lowCase;
        lowCase.charArray = new Character[this->arraySize];
        lowCase.arraySize = this->arraySize;
        for (int i = 0; i < this->arraySize; i++) {

            lowCase.charArray[i].setCh((char) toupper(this->charArray[i].getCh()));

        }
        return lowCase;
    }


    friend ostream &operator<<(ostream &os, const CharSequence &sequence) {

        return os;
    }
};


int main() {
    int n;
    cin >> n;

    if (n == 1) {
        cout << "Testing Character class" << endl;
        cout << "Character constructor" << endl;
        char c;
        cin >> c;
        Character cc(c);
        cout << "OK" << endl;
        cout << "Character operator <<" << endl;
        cout << cc << endl;
    } else if (n == 2) {
        cout << "Testing CharSequence constructors" << endl;
        char word[100];
        cin >> word;
        CharSequence cs1(word);
        cout << cs1 << endl;
    } else if (n == 3) {
        cout << "Testing CharSequence copy constructor and operator[int]" << endl;
        CharSequence cs("Some sequence");
        CharSequence copy(cs);
        cs[0] = 'X';
        cout << "Original: " << cs << endl;
        cout << "Copy: " << copy << endl;
    } else if (n == 4) {
        cout << "Testing CharSequence =operator and operator[int]" << endl;
        CharSequence cs("Some sequence");
        CharSequence copy;
        copy = cs;
        cs[0] = 'X';
        cout << "Original: " << cs << endl;
        cout << "Copy: " << copy << endl;
    } else if (n == 5) {
        cout << "Testing CharSequence operator+=" << endl;
        CharSequence cs;
        char word[100];
        cin >> word;
        int len = strlen(word);
        for (int i = 0; i < len; ++i) {
            cs += Character(word[i]);
        }
        cout << cs << endl;
    } else if (n == 6) {
        cout << "Testing CharSequence operator[char]" << endl;
        CharSequence cs("If you don't read the newspaper, you're uninformed. If you read the newspaper, you're mis-informed.");
        cout << cs['e'] << endl;
    } else if (n == 7) {
        cout << "Testing CharSequence toUpperCase" << endl;
        CharSequence cs("If you tell the truth, you don't have to remember anything");
        cout << cs.toUpperCase() << endl;
    } else if (n == 8) {
        cout << "Testing CharSequence operator ==" << endl;
        CharSequence cs1("abc");
        CharSequence cs2("abc");
        CharSequence cs3("abcd");
        CharSequence cs4("xyz");
        cout << (cs1 == cs2) << endl;
        cout << (cs1 == cs3) << endl;
        cout << (cs2 == cs4) << endl;
    }

    return 0;
}

