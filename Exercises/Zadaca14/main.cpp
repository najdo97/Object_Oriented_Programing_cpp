#include<iostream>
#include<string.h>

using namespace std;

class RatingMissingException {
public:
    void message() {
        cout << "Druze, nema rejtinzi" << endl;
    }
};

class Person {
private:
    char name[20];
    int year;
public:
    Person(char *name, int year) {
        strcpy(this->name, name);
        this->year = year;
    }

    Person() {
        strcpy(this->name, "");
    }

    bool operator==(char *name) {
        return strcmp(this->name, name) == 0;
    }

    char const *getName() {
        return name;
    }

    void print() { cout << name << " (" << year << ")"; }
};

class Song {
private:
    Person performers[10];
    int numberPerformers;
    int *ratings;
    int numberRatings;

protected:
    char title[30];

public:
    int getNumRatings() {
        return this->numberRatings;
    }

    Song() {
        this->numberPerformers = 0;
        this->ratings = nullptr;
        this->numberRatings = 0;
    }

    Song(char *title, Person *performers, int numberPerformers, int *ratings, int numberRatings) {
        strcpy(this->title, title);
        this->numberPerformers = numberPerformers;
        for (int i = 0; i < numberPerformers; i++) this->performers[i] = performers[i];
        this->numberRatings = numberRatings;
        this->ratings = new int[numberRatings];
        for (int i = 0; i < numberRatings; i++) this->ratings[i] = ratings[i];

    }

    Song(const Song &k) {
        strcpy(this->title, k.title);
        this->numberPerformers = k.numberPerformers;
        for (int i = 0; i < k.numberPerformers; i++) this->performers[i] = k.performers[i];
        this->numberRatings = k.numberRatings;
        this->ratings = new int[k.numberRatings];
        for (int i = 0; i < k.numberRatings; i++) this->ratings[i] = k.ratings[i];

    }

    Song operator=(const Song &k) {
        if (&k == this) return *this;
        strcpy(this->title, k.title);
        this->numberPerformers = k.numberPerformers;
        for (int i = 0; i < k.numberPerformers; i++) this->performers[i] = k.performers[i];
        this->numberRatings = k.numberRatings;
        delete[] ratings;
        this->ratings = new int[k.numberRatings];
        for (int i = 0; i < k.numberRatings; i++) this->ratings[i] = k.ratings[i];
        return *this;
    }

    int getnumberPerformers() { return numberPerformers; }

    Person operator[](int i) {
        if (i < numberPerformers && i >= 0) {
            return performers[i];
        } else return Person();
    }

    virtual float getTotalRating() {

        if (this->numberRatings == 0) {
            throw RatingMissingException();
        } else {
            int min = 10000000, max = 0;
            float rating;
            for (int i = 0; i < this->numberRatings; i++) {
                if (this->ratings[i] > max) {
                    max = this->ratings[i];
                }
                if (this->ratings[i] < min) {
                    min = this->ratings[i];
                }
            }
            rating = ((float) max + (float) min) / 2;
            return rating;
        }
    }

    virtual void print() {

        for (int i = 0; i < this->numberPerformers; i++) {
            this->performers[i].print();
            if (i != this->numberPerformers - 1) {
                cout << ",";
            }
        }
cout<<":"<<Song::title<<endl;
    }


};

class Movie {
private:
    char *title;
protected:
    int popularity;
public:

    Movie() {
        this->title = nullptr;
        this->popularity = 0;
    }

    Movie(char *title, int popularity) {
        this->popularity = popularity;
        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);
    }

    Movie(const Movie &v) {
        this->popularity = v.popularity;
        this->title = new char[strlen(v.title) + 1];
        strcpy(this->title, v.title);
    }

    Movie operator=(const Movie &v) {
        if (this == &v) return *this;
        this->popularity = v.popularity;
        delete[] title;
        this->title = new char[strlen(v.title) + 1];
        strcpy(this->title, v.title);
        return *this;
    }

    void print() { cout << "Movie:" << title << endl; }

    virtual ~Movie() { delete[] title; }


};

class MovieSong : public Song, public Movie {

private:
    int popularity;
public:

    MovieSong() : Song(), Movie() {
        this->popularity = 0;
    };

    MovieSong(char *songTitle, Person *performers, int numberPerformers, int *ratings, int numberRatings,
              char *movieTitle, int moviePopularity, int songPopularity) :
            Song(songTitle, performers, numberPerformers, ratings, numberRatings), Movie(movieTitle, moviePopularity) {
        this->popularity = songPopularity;
    };

    MovieSong(const MovieSong &other) : Song(other), Movie(other) {
        this->popularity = other.popularity;
    };

    MovieSong &operator=(const MovieSong &other) {
        Song::operator=(other);
        Movie::operator=(other);

        this->popularity = other.popularity;

        return *this;
    };

    float getTotalRating() {
        return Song::getTotalRating() * ((float) this->popularity / (float) Movie::popularity);
    }

    void print() {

        Song::print();
        Movie::print();
    }

};

double averageRating(Song **songs, int n) {
    double average = 0.0;
    int brojac = 0;
    for (int i = 0; i < n; i++) {

        if (dynamic_cast<MovieSong *>(songs[i]) != nullptr) {
            if (dynamic_cast<MovieSong *>(songs[i])->getNumRatings() == 0) {
                average = average + 5.0;
                brojac++;
            } else {
                average = average + dynamic_cast<MovieSong *>(songs[i])->getTotalRating();
                brojac++;
            }
        }

    }
    return average / (double) brojac;

}

void printSongs(char *performer, Song **songs, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < songs[i]->getnumberPerformers(); j++) {

            if (songs[i]->operator[](j).operator==(performer)) {
                songs[i]->print();
            };

        }
    }
}


int main() {

    Person performers[10];
    int year, numberOfPerformers, ratings[20], rating, numberOfRatings, type, popularity, songPopularity;
    char name[40], title[30], perfomer[30];

    char movieTitle[50];
    cin >> type;

    if (type == 1) //test class MovieSong
    {
        cout << "-----TEST MovieSong-----" << endl;
        cin >> title >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++) {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++) {
            cin >> rating;
            ratings[i] = rating;
        }
        cin >> title >> popularity >> songPopularity;


        MovieSong ok(title, performers, numberOfPerformers, ratings, numberOfRatings, title, popularity,
                     songPopularity);
        cout << "Object of class MovieSong is created";

    } else if (type == 2) // function print in song
    {
        cout << "-----TEST print-----" << endl;
        cin >> title >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++) {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++) {
            cin >> rating;
            ratings[i] = rating;
        }

        Song k(title, performers, numberOfPerformers, ratings, numberOfRatings);
        k.print();

    } else if (type == 3) // function getTotalRating
    {
        cout << "-----TEST getTotalRating-----" << endl;
        cin >> title >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++) {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++) {
            cin >> rating;
            ratings[i] = rating;
        }

        Song k(title, performers, numberOfPerformers, ratings, numberOfRatings);
        cout << "Total rating: " << k.getTotalRating() << endl;

    } else if (type == 4) //funkcija getTotalRating vo MovieSong
    {
        cout << "-----TEST getTotalRating-----" << endl;
        cin >> title >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++) {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++) {
            cin >> rating;
            ratings[i] = rating;
        }
        cin >> title >> popularity >> songPopularity;

        MovieSong fp(title, performers, numberOfPerformers, ratings, numberOfRatings, title, popularity,
                     songPopularity);
        cout << "Total rating: " << fp.getTotalRating() << endl;

    } else if (type == 5) //funkcija print vo MovieSong
    {
        cout << "-----TEST print -----" << endl;
        cin >> title >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++) {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++) {
            cin >> rating;
            ratings[i] = rating;
        }
        cin >> movieTitle >> popularity >> songPopularity;

        MovieSong fp(title, performers, numberOfPerformers, ratings, numberOfRatings, movieTitle, popularity,
                     songPopularity);
        fp.print();

    } else if (type == 6) //all classes
    {
        cout << "-----TEST Song and MovieSong-----" << endl;
        cin >> title >> numberOfPerformers;
        for (int i = 0; i < numberOfPerformers; i++) {
            cin >> name >> year;
            performers[i] = Person(name, year);
        }
        cin >> numberOfRatings;
        for (int i = 0; i < numberOfRatings; i++) {
            cin >> rating;
            ratings[i] = rating;
        }
        cin >> title >> popularity >> songPopularity;

        Song *p = new MovieSong(title, performers, numberOfPerformers, ratings, numberOfRatings, title, popularity,
                                songPopularity);
        p->print();
        cout << "Total rating: " << p->getTotalRating() << endl;
        delete p;


    } else if (type == 7) // function average rating
    {
        cout << "-----TEST average rating-----" << endl;
        int k, opt;
        cin >> k;
        Song **pesni = new Song *[k];
        for (int j = 0; j < k; j++) {
            cin >> opt; //1 Song 2 MovieSong
            cin >> title >> numberOfPerformers;
            for (int i = 0; i < numberOfPerformers; i++) {
                cin >> name >> year;
                performers[i] = Person(name, year);
            }
            cin >> numberOfRatings;
            for (int i = 0; i < numberOfRatings; i++) {
                cin >> rating;
                ratings[i] = rating;
            }
            if (opt == 1) {
                pesni[j] = new Song(title, performers, numberOfPerformers, ratings, numberOfRatings);
            } else {
                cin >> title >> popularity >> songPopularity;
                pesni[j] = new MovieSong(title, performers, numberOfPerformers, ratings, numberOfRatings, title,
                                         popularity, songPopularity);
            }
        }

        cout << "Average rating of the songs is " << averageRating(pesni, k);
        for (int j = 0; j < k; j++) delete pesni[j];
        delete[] pesni;

    } else if (type == 8) // function print songs
    {
        cout << "-----TEST print songs-----" << endl;
        int k, opt;
        cin >> k;
        Song **pesni = new Song *[k];
        for (int j = 0; j < k; j++) {
            cin >> opt; //1 Song 2 MovieSong
            cin >> title >> numberOfPerformers;
            for (int i = 0; i < numberOfPerformers; i++) {
                cin >> name >> year;
                performers[i] = Person(name, year);
            }
            cin >> numberOfRatings;
            for (int i = 0; i < numberOfRatings; i++) {
                cin >> rating;
                ratings[i] = rating;
            }
            if (opt == 1) {
                pesni[j] = new Song(title, performers, numberOfPerformers, ratings, numberOfRatings);
            } else {
                cin >> movieTitle >> popularity >> songPopularity;
                pesni[j] = new MovieSong(title, performers, numberOfPerformers, ratings, numberOfRatings, movieTitle,
                                         popularity, songPopularity);
            }
        }
        cin >> perfomer;
        cout << "Songs of " << perfomer << " are:" << endl;
        printSongs(perfomer, pesni, k);
        for (int j = 0; j < k; j++) delete pesni[j];
        delete[] pesni;

    }


    return 0;
}

