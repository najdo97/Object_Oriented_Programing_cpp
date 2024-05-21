#include <iostream>
#include <cstring>

using namespace std;

class Image {

protected:
    char *ime_slika;
    char ime_korisnik[50];
    int sirina;
    int visina;

public:

    int getSirina() const {
        return sirina;
    }

    int getVisina() const {
        return visina;
    }

    char *getImeSlika() const {
        return ime_slika;
    }

    const char *getImeKorisnik() const {
        return ime_korisnik;
    }


    Image(char *ime) {
        this->ime_slika = new char[strlen(ime) + 1];
        strcpy(this->ime_slika, ime);

        strcpy(this->ime_korisnik, "unknown");
        this->sirina = 800;
        this->visina = 800;
    }

    Image(char *ime, char *ime_korisnik) {
        this->ime_slika = new char[strlen(ime) + 1];
        strcpy(this->ime_slika, ime);

        strcpy(this->ime_korisnik, ime_korisnik);
        this->sirina = 800;
        this->visina = 800;
    }

    Image() {
        this->ime_slika = new char[10];
        strcpy(this->ime_slika, "untitled");

        strcpy(this->ime_korisnik, "unknown");
        this->sirina = 800;
        this->visina = 800;
    }

    Image(char *ime_slika, char *ime_korisnik, int sirina, int visina) {
        this->ime_slika = new char[strlen(ime_slika) + 1];
        strcpy(this->ime_slika, ime_slika);

        strcpy(this->ime_korisnik, ime_korisnik);
        this->sirina = sirina;
        this->visina = visina;
    }

    Image(const Image &i) {
        this->ime_slika = new char[strlen(i.ime_slika) + 1];
        strcpy(this->ime_slika, i.ime_slika);

        strcpy(this->ime_korisnik, i.ime_korisnik);
        this->sirina = i.sirina;
        this->visina = i.visina;
    }

    Image &operator=(const Image &i) {
        delete[]this->ime_slika;
        this->ime_slika = new char[strlen(i.ime_slika) + 1];
        strcpy(this->ime_slika, i.ime_slika);

        strcpy(this->ime_korisnik, i.ime_korisnik);
        this->sirina = i.sirina;
        this->visina = i.visina;
        return *this;
    }

    virtual double fileSize() const {
        double picture_size;

        picture_size = this->visina * this->sirina * 3;

        return picture_size;
    }


    friend ostream &operator<<(ostream &os, const Image &image) {

        os << image.ime_slika << " " << image.ime_korisnik << " " << image.fileSize();

        return os;
    }

    bool operator>(Image &i) {     // neznam kako ide ako sporeduvame objekti od ista familija, ama razlicni klasi,primer transparaentna i netransparentna slika


        if (this->fileSize() > i.fileSize()) {
            return true;
        } else return false;
    }


};

class TransparentImage : public Image {

protected:
    bool isTransparent;
public:
    TransparentImage() : Image() {
        this->isTransparent = false;
    }

    TransparentImage(char *ime_slika, char *ime_korisnik, int sirina, int visina, bool isTransparent) : Image(ime_slika, ime_korisnik, sirina, visina) {
        this->isTransparent = isTransparent;
    }

    TransparentImage(const TransparentImage &t) : Image(t) {
        this->isTransparent = t.isTransparent;
    }

    TransparentImage &operator=(const TransparentImage &t) {
        Image::operator=(t);
        this->isTransparent = t.isTransparent;

        return *this;
    }


    double fileSize() const {
        double picture_size;

        if (this->isTransparent == true) {
            picture_size = this->getVisina() * this->getSirina() * 4;
        } else {
            picture_size = this->getVisina() * this->getSirina() + (this->getVisina() * this->getSirina()) / 8;
        }
        return picture_size;
    }

    friend ostream &operator<<(ostream &os, const TransparentImage &image) {

        os << image.getImeSlika() << " " << image.getImeKorisnik() << " " << image.fileSize();

        return os;
    }

    bool operator>(const TransparentImage &t) {     // neznam kako ide ako sporeduvame objekti od ista familija, ama razlicni klasi,primer transparaentna i netransparentna slika

        if (this->fileSize() > t.fileSize()) {
            return true;
        } else return false;
    }

};


class Folder {

protected:
    char ime_folder[255];
    char sopstevenik_folder[50];
    Image *sliki[100];
    int br_sliki;

public:

    Folder() {
        strcpy(this->ime_folder, "unknown");
        strcpy(this->sopstevenik_folder, "unknown");
//
//        for (int i = 0; i < 100; i++) {
//            this->sliki[i] = nullptr;
//        }
        this->br_sliki = 0;
    }

    Folder(char *ime_folder, char *sopstevenik_folder) {
        strcpy(this->ime_folder, ime_folder);
        strcpy(this->sopstevenik_folder, sopstevenik_folder);

        for (int i = 0; i < 100; i++) {
            this->sliki[i] = nullptr;
        }
        this->br_sliki = 0;
    }


    Folder(char *ime_folder, char *sopstevenik_folder, Image **sliki, int br_sliki) {
        strcpy(this->ime_folder, ime_folder);
        strcpy(this->sopstevenik_folder, sopstevenik_folder);

        for (int i = 0; i < 100; i++) {
            this->sliki[i] = sliki[i];
        }
        this->br_sliki = br_sliki;
    }

    Folder(const Folder &f) {
        strcpy(this->ime_folder, f.ime_folder);
        strcpy(this->sopstevenik_folder, f.sopstevenik_folder);

        for (int i = 0; i < 100; i++) {
            this->sliki[i] = f.sliki[i];
        }
        this->br_sliki = f.br_sliki;

    }

    Folder &operator=(const Folder &f) {
        strcpy(this->ime_folder, f.ime_folder);
        strcpy(this->sopstevenik_folder, f.sopstevenik_folder);

        for (int i = 0; i < 100; i++) {
            delete[]this->sliki[i];
        }

        for (int i = 0; i < 100; i++) {
            this->sliki[i] = f.sliki[i];
        }

        this->br_sliki = f.br_sliki;

        return *this;
    }

    Folder &operator+=(Image &i) {

        if (this->br_sliki >= 100) {
            return *this;
        } else {
            this->sliki[br_sliki++] = &i;
            br_sliki++;
        }
        return *this;
    }


    double folderSize() {

        double total_size = 0.0;

        for (int i = 0; i < this->br_sliki; i++) {
            if (dynamic_cast<TransparentImage *>(this->sliki[i]) != nullptr) {
                total_size = total_size + dynamic_cast<TransparentImage *>(this->sliki[i])->fileSize();
            } else {
                total_size = total_size + this->sliki[i]->fileSize();
            }
        }
        return total_size;
    }

    Image *getMaxFile() {

        Image *max_file = sliki[0];
        int max_index = 0;
        for (int i = 0; i < this->br_sliki; i++) {
            if (dynamic_cast<TransparentImage *>(this->sliki[i]) == nullptr) {
                if (this->sliki[i] > max_file) {
                    max_file = this->sliki[i];
                    max_index=i;
                }
            } else {
                if (dynamic_cast<TransparentImage *>(this->sliki[i]) >max_file) {
                    max_file = dynamic_cast<TransparentImage *>(this->sliki[i]);
                    max_index = i;
                }
            }
        }

        return this->sliki[max_index];
    }

    friend ostream &operator<<(ostream &os, Folder &folder) {
        os << folder.ime_folder << " " << folder.sopstevenik_folder << endl;
        for (int i = 0; i < folder.br_sliki; i++) {
            os << folder.sliki[i]->getImeSlika() << folder.sliki[i]->getImeKorisnik() << folder.sliki[i]->fileSize() << endl;
        }
        os << "Folder size: " << folder.folderSize() << endl;


        return os;
    }

    Image *operator[](int pom) {

        if (pom > this->br_sliki) {
            return nullptr;
        } else return this->sliki[pom];

    }

};


Folder &max_folder_size(Folder *niza, int br_folderi) {

    double max_size = 0.0;
    int max_index = 0;
    for (int i = 0; i < br_folderi; i++) {
        if (niza[i].folderSize() > max_size) {
            max_size = niza[i].folderSize();
            max_index = i;
        }
    }

    return niza[max_index];
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
