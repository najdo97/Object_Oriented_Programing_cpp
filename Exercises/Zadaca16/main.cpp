#include <iostream>
#include <cstring>

using namespace std;

class Pair {
private:

    char *key;
    float value;
public:


    char *getKey() const {
        return key;
    }

    Pair() {
        this->key = nullptr;
        this->value = 0.0;
    }

    Pair(char *key, float value) {
        this->key = new char[strlen(key) + 1];
        strcpy(this->key, key);

        this->value = value;
    }

    Pair(const Pair &other) {
        this->key = new char[strlen(other.key) + 1];
        strcpy(this->key, other.key);

        this->value = other.value;
    }

    Pair &operator=(const Pair &other) {
        delete[] this->key;
        this->key = new char[strlen(other.key) + 1];
        strcpy(this->key, other.key);

        this->value = other.value;
        return *this;
    }

    ~Pair() {
        delete[]this->key;
    }

    friend ostream &operator<<(ostream &os, const Pair &pair1) {
        os << "('" << pair1.key << "', " << pair1.value <<")"<< endl;
        return os;
    }

    Pair &operator++() {

        this->value++;
        return *this;
    }

    Pair operator++(int) {
        Pair *tmp = new Pair(this->key, this->value);
        this->value++;
        return *tmp;
    }

    Pair operator+(const Pair &other) {
        Pair tmp;

        if (this->key == nullptr) {
            tmp.key = other.key;
            tmp.value = other.value;
            return tmp;
        }

        if (strlen(this->key) >= strlen(other.key)) {
            tmp.key = this->key;
        } else {
            tmp.key = other.key;
        }
        tmp.value = this->value + other.value;

        return tmp;
    }

};

class Collection {
private:
    Pair *arr;
    int arr_size;
public:
    Collection() {
        this->arr = nullptr;
        this->arr_size = 0;
    }

    Collection(Pair *arr, int arr_size) {
        this->arr = new Pair[arr_size];
        for (int i = 0; i < arr_size; i++) {
            this->arr[i] = arr[i];
        }

        this->arr_size = arr_size;
    }

    Collection(const Collection &other) {
        this->arr = new Pair[other.arr_size];
        for (int i = 0; i < other.arr_size; i++) {
            this->arr[i] = other.arr[i];
        }

        this->arr_size = other.arr_size;
    }

    Collection &operator=(const Collection &other) {
        delete[]this->arr;
        this->arr = new Pair[other.arr_size];
        for (int i = 0; i < other.arr_size; i++) {
            this->arr[i] = other.arr[i];
        }

        this->arr_size = other.arr_size;
        return *this;
    }

    ~Collection() {
        delete[]this->arr;
    }

    Collection &operator+=(const Pair &other) {

        Pair *tmp = new Pair[this->arr_size + 1];
        for (int i = 0; i < this->arr_size; i++) {
            tmp[i] = this->arr[i];
        }

        tmp[this->arr_size] = other;
        this->arr_size++;

        delete[]this->arr;
        this->arr = tmp;

        return *this;
    }


    friend ostream &operator<<(ostream &os, const Collection &collection) {

        os << "Size: " << collection.arr_size << endl;

        for (int i = 0; i < collection.arr_size; i++) {
            os << collection.arr[i];
        }
        return os;
    }

    bool operator==(const Collection &other) {

        if (this->arr_size != other.arr_size) {
            return false;
        }
        for (int i = 0; i < this->arr_size; i++) {
            if (strcmp(this->arr[i].getKey(), other.arr[i].getKey()) != 0) {
                return false;
            }
        }

        return true;
    }


    Pair *find(const char *key) {

        for (int i = 0; i < this->arr_size; i++) {
            if (strcmp(this->arr[i].getKey(), key) == 0) {
                return &this->arr[i];
            }
        }
        return nullptr;
    }
};

void read(char *k, float *v) {
    cin >> k;
    cin >> *v;
}

int main() {
    char key[50];
    float value;
    cout << "----- class Pair -----" << endl;
    read(key, &value);
    cout << "----- constructor -----" << endl;
    Pair p1(key, value);
    read(key, &value);
    Pair p2(key, value);
    Pair p3(p1);
    cout << "----- operator << -----" << endl;
    cout << p1;
    cout << p2;
    cout << "----- operator ++(int) -----" << endl;
    cout << p1++;
    cout << p1;
    cout << "----- operator ++ -----" << endl;
    cout << ++p2;
    cout << "----- operator + -----" << endl;
    Pair p = p1 + p2;
    cout << "----- operator = -----" << endl;
    p3 = p;
    cout << p3;

    cout << "----- class Collection -----" << endl;
    cout << "----- constructor -----" << endl;
    Collection k;
    cout << "----- operator += -----" << endl;
    k += p1;
    k += p2;
    k += p3;
    cout << "----- operator << -----" << endl;
    cout << k;
    cout << "----- copy constructor -----" << endl;
    Collection k2(k);
    cout << "----- operator == -----" << endl;
    if (k == k2) {
        cout << "k == k2" << endl;
    }
    k2 += p1;
    if (k == k2) {
        // not equal
        cout << "k == k2" << endl;
    }
    cout << "----- find -----" << endl;
    Pair *f = k.find(key);
    cout << *f;
    strcat(key, "other");
    f = k.find(key);
    if (f == NULL) {
        cout << key << " not found" << endl;
    }
    return 0;
}
