#include <iostream>
#include <cstring>

using namespace std;

class Book {
private:
    char ISBN[20];
    char naslov[50];
    char avtor[30];
    float osnovna_cena;

public:

    Book() {
        strcpy(this->ISBN, "NaN");
        strcpy(this->naslov, "NaN");
        strcpy(this->avtor, "NaN");

        this->osnovna_cena = 0.0;
    }

    Book(char *ISBN, char *naslov, char *avtor, float osnovna_cena) {
        strcpy(this->ISBN, ISBN);
        strcpy(this->naslov, naslov);
        strcpy(this->avtor, avtor);

        this->osnovna_cena = osnovna_cena;
    }

    Book(const Book &b) {
        strcpy(this->ISBN, b.ISBN);
        strcpy(this->naslov, b.naslov);
        strcpy(this->avtor, b.avtor);

        this->osnovna_cena = b.osnovna_cena;
    }

    ~ Book() {};

    Book &operator=(const Book &b) {
        strcpy(this->ISBN, b.ISBN);
        strcpy(this->naslov, b.naslov);
        strcpy(this->avtor, b.avtor);

        this->osnovna_cena = b.osnovna_cena;

        return *this;
    }

    void setISBN(char *isbn) {
        strcpy(this->ISBN, isbn);
    }

    void setNaslov(char *naslov) {
        strcpy(this->naslov, naslov);
    }

    void setAvtor(char *avtor) {
        strcpy(this->avtor, avtor);
    }

    void setOsnovnaCena(float osnovna_cena) {
        this->osnovna_cena = osnovna_cena;
    }


    const char *getIsbn() const {
        return ISBN;
    }

    const char *getNaslov() const {
        return naslov;
    }

    const char *getAvtor() const {
        return avtor;
    }

    float getOsnovnaCena() const {
        return osnovna_cena;
    }


    virtual float bookPrice() = 0;

    virtual bool operator>(const Book &b) {
        if (this->getOsnovnaCena() > b.getOsnovnaCena()) {
            return true;
        } else return false;
    };

    friend ostream &operator<<(ostream &os,  Book &book) {
        os << book.ISBN << ": " << book.naslov << ", " << book.avtor << " " << book.bookPrice() << endl;
        return os;
    }
};

class OnlineBook : public Book {
private:
    char *url;
    int golemina;

public:
    OnlineBook() : Book() {
        this->url = nullptr;
        this->golemina = 0;
    }

    OnlineBook(char *ISBN, char *naslov, char *avtor, float osnovna_cena, char *url, int golemina) : Book(ISBN, naslov,
                                                                                                          avtor,
                                                                                                          osnovna_cena) {

        this->url = new char[strlen(url) + 1];
        strcpy(this->url, url);
        this->golemina = golemina;
    }

    OnlineBook(const OnlineBook &o) : Book(o) {

        this->url = new char[strlen(o.url) + 1];
        strcpy(this->url, o.url);
        this->golemina = o.golemina;
    }

    ~OnlineBook() {
        delete[] this->url;
    }

    OnlineBook &operator=(const OnlineBook &o) {

        Book::operator=(o);

        delete[]this->url;
        this->url = new char[strlen(o.url) + 1];
        strcpy(this->url, o.url);
        this->golemina = o.golemina;

        return *this;
    }


    float bookPrice() override {

        float nova_cena = this->getOsnovnaCena();

        if (this->golemina > 20) {
            nova_cena = getOsnovnaCena() + (getOsnovnaCena() / 100 * 20);
        }
        return nova_cena;

    };

    bool operator>(const OnlineBook &b) {
        if (this->getOsnovnaCena() > b.getOsnovnaCena()) {
            return true;
        } else return false;
    };


};

class PrintBook : public Book {
private:
    float tezina;
    bool naLager;

public:

    PrintBook() : Book() {
        this->tezina = 0.0;
        this->naLager = false;
    };

    PrintBook(char *ISBN, char *naslov, char *avtor, float osnovna_cena, float tezina, bool naLager) :
            Book(ISBN, naslov, avtor, osnovna_cena) {
        this->tezina = tezina;
        this->naLager = naLager;
    };

    PrintBook(const PrintBook &p) : Book(p) {
        this->tezina = p.tezina;
        this->naLager = p.naLager;
    };

    //operator=
    PrintBook &operator=(const PrintBook &p) {

        Book::operator=(p);
        this->tezina = p.tezina;
        this->naLager = p.naLager;
        return *this;
    }

    float bookPrice() override {
        float nova_cena = this->getOsnovnaCena();

        if (this->tezina > 0.7) {
            nova_cena = getOsnovnaCena() + (getOsnovnaCena() / 100 * 15);
        }
        return nova_cena;
    }

    bool operator>(const PrintBook &b) {
        if (this->getOsnovnaCena() > b.getOsnovnaCena()) {
            return true;
        } else return false;
    }

};

void mostExpensiveBook(Book **books, int n) {

    int onlineBooks = 0, printBooks = 0, mostExpensive = 0, mostExpensiveBrojac = 0;


    for (int i = 0; i < n; i++) {
        if (dynamic_cast<OnlineBook *>(books[i])) {
            onlineBooks++;

        } else if (dynamic_cast<PrintBook *>(books[i])) {
            printBooks++;
        }

        if (books[i]->getOsnovnaCena() > mostExpensive) {
            mostExpensive = books[i]->getOsnovnaCena();
            mostExpensiveBrojac = i;
        }

    }
    cout << "FINKI-Education" << endl;

    cout << "Total number of online books: " << onlineBooks << endl;
    cout << "Total number of print books: " << printBooks << endl;


    cout << "The most expensive book is: \n" << (*books[mostExpensiveBrojac]) << endl;

}

int main() {

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2) {
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3) {
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4) {
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            } else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i < n; i++) delete books[i];
    delete[] books;
    return 0;
}
