#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Image {
protected:

    char *ime_slika;
    char *ime_korisnik;
    int width;
    int height;
public:

    char *getImeSlika() const {
        return ime_slika;
    }

    char *getImeKorisnik() const {
        return ime_korisnik;
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    Image(char *ime_slika) {

        this->ime_slika = new char[strlen(ime_slika) + 1];
        strcpy(this->ime_slika, ime_slika);

        this->ime_korisnik = new char[8];
        strcpy(this->ime_korisnik, "unknown");

        this->width = 0;
        this->height = 0;
    }

    Image(char *ime_slika, char *ime_korisnik) {

        this->ime_slika = new char[strlen(ime_slika) + 1];
        strcpy(this->ime_slika, ime_slika);

        this->ime_korisnik = new char[strlen(ime_korisnik) + 1];
        strcpy(this->ime_korisnik, ime_korisnik);

        this->width = 0;
        this->height = 0;
    }


    Image() {
        this->ime_slika = new char[9];
        strcpy(this->ime_slika, "untitled");
        this->ime_korisnik = new char[8];
        strcpy(this->ime_korisnik, "unknown");
        this->width = 0;
        this->height = 0;
    }

    Image(char *ime_slika, char *ime_korisnik, int width, int height) {

        this->ime_slika = new char[strlen(ime_slika) + 1];
        strcpy(this->ime_slika, ime_slika);

        this->ime_korisnik = new char[strlen(ime_korisnik) + 1];
        strcpy(this->ime_korisnik, ime_korisnik);

        this->width = width;
        this->height = height;
    }

    Image(const Image &other) {

        this->ime_slika = new char[strlen(other.ime_slika) + 1];
        strcpy(this->ime_slika, other.ime_slika);

        this->ime_korisnik = new char[strlen(other.ime_korisnik) + 1];
        strcpy(this->ime_korisnik, other.ime_korisnik);

        this->width = other.width;
        this->height = other.height;
    }

    Image &operator=(const Image &other) {

        delete[]this->ime_slika;
        this->ime_slika = new char[strlen(other.ime_slika) + 1];
        strcpy(this->ime_slika, other.ime_slika);

        delete[]this->ime_korisnik;
        this->ime_korisnik = new char[strlen(other.ime_korisnik) + 1];
        strcpy(this->ime_korisnik, other.ime_korisnik);

        this->width = other.width;
        this->height = other.height;

        return *this;
    }

    virtual int fileSize() {
        int total = 0;
        total = this->width * this->height * 3;
        return total;
    }

    friend ostream &operator<<(ostream &os, Image &image) {
        os << image.ime_slika << " " << image.ime_korisnik << " " << image.fileSize();
        return os;
    }

    bool operator>(Image &other) {

        if (this->fileSize() > other.fileSize()) {
            return true;
        } else return false;
    }

};

class TransparentImage : public Image {
private:
    bool isTransparent;
public:

    TransparentImage() : Image() {
        this->isTransparent = true;
    }

    TransparentImage(char *ime_slika, char *ime_korisnik, int width, int height, bool isTransparent) : Image(ime_slika, ime_korisnik, width, height) {
        this->isTransparent = isTransparent;
    }

    TransparentImage(const TransparentImage &other) : Image(other) {
        this->isTransparent = other.isTransparent;
    }

    TransparentImage &operator=(const TransparentImage &other) {
        Image::operator=(other);
        this->isTransparent = other.isTransparent;

        return *this;
    }

    int fileSize() {
        int total = 0;
        if (this->isTransparent == true) {
            total = this->getWidth() * this->getHeight() * 4;
        } else {
            total = this->getWidth() * this->getHeight() + ((this->getWidth() * this->getHeight()) / 8);
        }

        return total;
    }


    friend ostream &operator<<(ostream &os, TransparentImage &image) {

        os << image.getImeSlika() << " " << image.getImeKorisnik() << " " << image.fileSize() << endl;
        return os;
    }


};

class Folder {
private:
    char folder_name[255];
    char folder_owner[50];
    Image **arr;
    int brojac; // maks =100
public:

    Folder(char *folder_name, char *folder_owner) {
        strcpy(this->folder_name, folder_name);
        strcpy(this->folder_owner, folder_owner);

        this->arr = nullptr;
        this->brojac = 0;
    }

    Folder() {
        strcpy(this->folder_name, "NaN");
        strcpy(this->folder_owner, "NaN");

        this->arr = nullptr;
        this->brojac = 0;
    }

    Folder(char *folder_name, char *folder_owner, Image **arr, int brojac) {
        strcpy(this->folder_name, folder_name);
        strcpy(this->folder_owner, folder_owner);

        this->arr = new Image *[brojac];
        for (int i = 0; i < brojac; i++) {
            this->arr[i] = arr[i];
        }

        this->brojac = brojac;
    }

    Folder(const Folder &other) {
        strcpy(this->folder_name, other.folder_name);
        strcpy(this->folder_owner, other.folder_owner);

        this->arr = new Image *[other.brojac];
        for (int i = 0; i < other.brojac; i++) {
            this->arr[i] = other.arr[i];
        }

        this->brojac = other.brojac;
    }

    Folder &operator=(const Folder &other) {
        strcpy(this->folder_name, other.folder_name);
        strcpy(this->folder_owner, other.folder_owner);

//        for (int i = 0; i < this->brojac; i++) {
//            delete this->arr[i];
//        }
        delete[]this->arr;

        this->arr = new Image *[other.brojac];
        for (int i = 0; i < other.brojac; i++) {
            this->arr[i] = other.arr[i];
        }

        this->brojac = other.brojac;
        return *this;
    }


    int folderSize() {
        int total = 0;
        for (int i = 0; i < this->brojac; i++) {
            total = total + this->arr[i]->fileSize();
        }

        return total;
    }

    Image *getMaxFile() {
        int max_idx = 0, max_size = 0;
        for (int i = 0; i < this->brojac; i++) {
            if (this->arr[i]->fileSize() > max_size) {
                max_size = this->arr[i]->fileSize();
                max_idx = i;
            }
        }
        return this->arr[max_idx];
    }

    Folder &operator+=(Image &other) {

        if (this->brojac >= 100) {
            return *this;
        }
        Image **tmp = new Image *[this->brojac + 1];

        for (int i = 0; i < this->brojac; i++) {
            tmp[i] = this->arr[i];
        }

        if (dynamic_cast<TransparentImage *>(&other) != nullptr) {
            tmp[this->brojac] = new TransparentImage(*dynamic_cast<TransparentImage *>(&other));
        } else {
            tmp[this->brojac] = new Image(other);
        }

        this->brojac++;

        delete[]this->arr;
        this->arr = tmp;

        return *this;

    }

    friend ostream &operator<<(ostream &os, const Folder &folder) {

        os << folder.folder_name << " " << folder.folder_owner << endl;
        for (int i = 0; i < folder.brojac; i++) {
            os << *folder.arr[i] << endl;
        }

        return os;
    }

    Image *operator[](const int i) {
        if (this->arr[i] == nullptr) {
            return NULL;
        } else return this->arr[i];
    };

};

Folder *max_folder_size(Folder *folder_list, int num_folders) {

    int max_idx = 0, max_value = 0;
    for (int i = 0; i < num_folders; i++) {
        if (folder_list[i].folderSize() > max_value) {
            max_value = folder_list[i].folderSize();
            max_idx = i;
        }
    }
    return &folder_list[max_idx];
}


int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc == 1) {
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout << f1;

        Image f2(name);
        cout << f2;

        Image f3(name, user_name);
        cout << f3;

        Image f4(name, user_name, w, h);
        cout << f4;
    } else if (tc == 2) {
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout << tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout << tf4;
    } else if (tc == 3) {
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout << f3;
    } else if (tc == 4) {
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout << dir;
    } else if (tc == 5) {
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout << *(dir.getMaxFile());
    } else if (tc == 6) {
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout << *dir[sub];
    } else if (tc == 7) {
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i = 0; i < folders_num; ++i) {
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image *f;
            TransparentImage *tf;

            int sub, fileType;

            while (1) {
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >> fileType;
                if (fileType == 1) { // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name, user_name, w, h);
                    dir += *f;
                } else if (fileType == 2) {
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name, user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout << max_folder_size(dir_list, folders_num);
    }
    return 0;
};
