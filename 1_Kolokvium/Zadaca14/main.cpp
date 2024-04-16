#include<iostream>
#include<cstring>

using namespace std;

enum Extension {
    pdf, txt, exe
};

class File {

private:
    char *ime_datoteka;
    Extension ext;
    char *ime_sopstvenik;
    int golemina;

public:


    File() {
        this->ime_datoteka = nullptr;
        this->ext = txt;
        this->ime_sopstvenik = nullptr;
        this->golemina = 0;
    };

    File(char *ime_datoteka, char *ime_sopstvenik, int golemina, Extension ext) {
        this->ime_datoteka = new char[strlen(ime_datoteka) + 1];
        strcpy(this->ime_datoteka, ime_datoteka);

        this->ext = ext;

        this->ime_sopstvenik = new char[strlen(ime_sopstvenik) + 1];
        strcpy(this->ime_sopstvenik, ime_sopstvenik);

        this->golemina = golemina;
    };


    File(const File &f) {
        this->ime_datoteka = new char[strlen(f.ime_datoteka) + 1];
        strcpy(this->ime_datoteka, f.ime_datoteka);

        this->ext = f.ext;

        this->ime_sopstvenik = new char[strlen(f.ime_sopstvenik) + 1];
        strcpy(this->ime_sopstvenik, f.ime_sopstvenik);

        this->golemina = f.golemina;
    };


    ~File() {
        delete[] this->ime_datoteka;
        delete[] this->ime_sopstvenik;

    };


    File &operator=(const File &f) {
        if (this == &f) {
            return *this;
        }

        delete[]this->ime_datoteka;
        this->ime_datoteka = new char[strlen(f.ime_datoteka) + 1];
        strcpy(this->ime_datoteka, f.ime_datoteka);

        this->ext = f.ext;

        delete[]this->ime_sopstvenik;
        this->ime_sopstvenik = new char[strlen(f.ime_sopstvenik) + 1];
        strcpy(this->ime_sopstvenik, f.ime_sopstvenik);

        this->golemina = f.golemina;


        return *this;
    }

//txt, pdf, exe
    void print() {
        if (this->ext == txt) {
            cout << "File name: " << this->ime_datoteka << ".txt" << endl;
        } else if (this->ext == pdf) {
            cout << "File name: " << this->ime_datoteka << ".pdf" << endl;
        } else if (this->ext == exe) {
            cout << "File name: " << this->ime_datoteka << ".exe" << endl;
        }

        cout << "File owner: " << this->ime_sopstvenik << endl;
        cout << "File size: " << this->golemina << endl;
    }

    bool equals(const File &that) {
        if ((strcmp(this->ime_datoteka, that.ime_datoteka) == 0) &&
            (strcmp(this->ime_sopstvenik, that.ime_sopstvenik) == 0) &&
            (this->ext == that.ext)) {
            return true;
        } else return false;
    }

    bool equalsType(const File &that) {
        if (this->ext == that.ext) {
            return true;
        } else return false;
    }

};

class Folder {
private:
    char *ime_folder;
    int br_datoteki;
    File *niza_datoteki;

public:

    Folder() {
        this->ime_folder = nullptr;
        this->br_datoteki = 0;
        this->niza_datoteki = nullptr;
    };

    Folder(const char *name) {
        this->ime_folder = new char[strlen(name) + 1];
        this->ime_folder = strcpy(this->ime_folder, name);

        this->br_datoteki = 0;
        this->niza_datoteki = nullptr;

    };

    Folder(const Folder &f) {
        this->ime_folder = new char[strlen(f.ime_folder) + 1];
        strcpy(this->ime_folder, f.ime_folder);

        this->br_datoteki = f.br_datoteki;

        if (f.niza_datoteki != nullptr) {
            this->niza_datoteki = new File[f.br_datoteki];
            for (int i = 0; i < f.br_datoteki; i++) {
                this->niza_datoteki[i] = f.niza_datoteki[i];
            }
        } else this->niza_datoteki = nullptr;
    };

    ~Folder() {
        delete[] this->niza_datoteki;
    };


    Folder &operator=(const Folder &f) {
        this->ime_folder = new char[strlen(f.ime_folder) + 1];
        strcpy(this->ime_folder, f.ime_folder);

        this->br_datoteki = f.br_datoteki;

        if (f.niza_datoteki != nullptr) {
            delete[] this->niza_datoteki;
            this->niza_datoteki = new File[f.br_datoteki];
            for (int i = 0; i < f.br_datoteki; i++) {
                this->niza_datoteki[i] = f.niza_datoteki[i];
            }
        } else this->niza_datoteki = nullptr;

        return *this;
    }

    void print() {


        cout << "Folder name: " << this->ime_folder << endl;

        for (int i = 0; i < this->br_datoteki; i++) {
            this->niza_datoteki[i].print();
        }
    }

    void remove(const File &file) {
        //кој ќе ја избрише првата датотека од директориумот која е еднаква според equals методот

        File *pom = new File[this->br_datoteki];
        int brojac = 0;
        for (int i = 0; i < this->br_datoteki; i++) {
            if (!this->niza_datoteki[i].equals(file)) {
                pom[i] = this->niza_datoteki[i];
            } else brojac++;
        }

        delete[]this->niza_datoteki;
        this->niza_datoteki = pom;
        this->br_datoteki = this->br_datoteki - brojac;

    }

    void add(const File &file) {

        File *pom = new File[this->br_datoteki + 1];

        for (int i = 0; i < this->br_datoteki; i++) {
            pom[i] = this->niza_datoteki[i];
        }

        pom[this->br_datoteki] = file;
        this->br_datoteki++;

        delete[]this->niza_datoteki;
        this->niza_datoteki = pom;
    }


};


int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    } else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    } else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    } else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    } else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}