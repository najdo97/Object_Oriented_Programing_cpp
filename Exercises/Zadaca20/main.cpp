#include <iostream>
#include <cstring>

using namespace std;

class Word {
private:
    char *word;
public:
    const char *getWord() const {
        return this->word;
    }

    Word() {
        this->word = new char[10];
        strcpy(this->word, "UNDEFINED");
    }

    Word(char *word) {
        this->word = new char[strlen(word) + 1];
        strcpy(this->word, word);
    }

    Word(const Word &other) {
        this->word = new char[strlen(other.word) + 1];
        strcpy(this->word, other.word);
    }

    Word &operator=(const Word &other) {

        delete this->word;

        this->word = new char[strlen(other.word) + 1];
        strcpy(this->word, other.word);

        return *this;
    }

    ~Word() {
        delete this->word;
    }
};

class Sentence {

private:
    Word *arr_words;
    int num_words;
    int max_words;

public:

    Sentence() {
        this->arr_words = nullptr;
        this->num_words = 0;
        this->max_words = 10;
    }

    Sentence(Word *arr_words, int num_words) {
        for (int i = 0; i < num_words; i++) {
            this->arr_words[i] = arr_words[i];
        }
        this->num_words = num_words;
        this->max_words = 10;
    }

    Sentence(Word *arr_words, int num_words, int max_words) {
        this->arr_words = new Word[num_words];
        for (int i = 0; i < num_words; i++) {
            this->arr_words[i] = arr_words[i];
        }
        this->num_words = num_words;
        this->max_words = max_words;
    }

    Sentence(const Sentence &other) {
        this->arr_words = new Word[other.num_words];
        for (int i = 0; i < other.num_words; i++) {
            this->arr_words[i] = other.arr_words[i];
        }
        this->num_words = other.num_words;
        this->max_words = other.max_words;
    }

    Sentence &operator=(const Sentence &other) {
        delete[]this->arr_words;
        this->arr_words = new Word[other.num_words];
        for (int i = 0; i < other.num_words; i++) {
            this->arr_words[i] = other.arr_words[i];
        }
        this->num_words = other.num_words;
        this->max_words = other.max_words;

        return *this;
    }

    void add(Word w) {

        Word *tmp = new Word[this->num_words + 1];

        for (int i = 0; i < this->num_words; i++) {
            tmp[i] = this->arr_words[i];
        }
        tmp[this->num_words] = w;
        this->num_words++;

        delete[] this->arr_words;
        this->arr_words = tmp;

        if (this->num_words == this->max_words) {
            this->max_words += 10;
        }






//        if (this->num_words == 0) {
//            this->arr_words = new Word[this->max_words];
//
//            this->arr_words[this->num_words] = w;
//            this->num_words++;
//        }
//
//        if (this->num_words == max_words) {
//            this->max_words = max_words + 10;
//            Word *tmp = new Word[max_words];
//            for (int i = 0; i < this->num_words; i++) {
//                tmp[i] = this->arr_words[i];
//            }
//
//            delete[]this->arr_words;
//            this->arr_words = tmp;
//        }
//
//        this->arr_words[this->num_words] = w;
//        this->num_words++;
    }

    void print() {
        for (int i = 0; i < this->num_words; i++) {
            cout << this->arr_words[i].getWord() << " ";
        }
        cout << endl;
    }

    void swap(int i, int j) {
        Word tmp;
        tmp = this->arr_words[i];
        this->arr_words[i] = this->arr_words[j];
        this->arr_words[j] = tmp;
    }

};

int main() {
    int n;
    cin >> n;
    cin.get();
    cout << "CONSTRUCTOR" << endl;
    Sentence s;
    cout << "ADD WORD" << endl;
    for (int i = 0; i < n; ++i) {
        char w[100];
        cin.getline(w, 100);
        Word word(w);
        s.add(word);
    }
    cout << "PRINT SENTENCE" << endl;
    s.print();
    cout << "COPY" << endl;
    Sentence x = s;
    cout << "SWAP" << endl;
    x.swap(n / 2, n / 3);
    x.print();
    cout << "ORIGINAL" << endl;
    s.print();
    return 0;
}
