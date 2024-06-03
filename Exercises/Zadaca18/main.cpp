#include <iostream>
#include <cstring>

using namespace std;

class ExistingPodcast {
private:

public:

    void message() {
        cout << "The podcast is already in the collection" << endl;
    }

};

class Podcast {

protected:
    char name[100];
    char url[1000];
    float streaming_cost;
    int discount;

public:
    Podcast() {
        strcpy(this->name, "NaN");
        strcpy(this->url, "NaN");
        this->streaming_cost = 0;
        this->discount = 0;
    }

    Podcast(char *name, char *url, float streaming_cost, int discount) {
        strcpy(this->name, name);
        strcpy(this->url, url);
        this->streaming_cost = streaming_cost;
        this->discount = discount;
    }

    Podcast(const Podcast &other) {
        strcpy(this->name, other.name);
        strcpy(this->url, other.url);
        this->streaming_cost = other.streaming_cost;
        this->discount = other.discount;
    }

    Podcast &operator=(const Podcast &other) {
        strcpy(this->name, other.name);
        strcpy(this->url, other.url);
        this->streaming_cost = other.streaming_cost;
        this->discount = other.discount;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Podcast &podcast) {


        os << "Podcast: " << podcast.name << endl;
        os << "URL: " << podcast.url << endl;
        if (podcast.discount > 0) {
            os << "regular price: $" << podcast.streaming_cost << ", bought on discount";
        } else {
            os << "regular price: $" << podcast.streaming_cost<<", ";
        }
        return os;
    }

    friend istream &operator>>(istream &is, Podcast &podcast) {

        is.get();
        is.getline(podcast.name, 100);
        is.getline(podcast.url, 1000);
        is >> podcast.streaming_cost >> podcast.discount;

        return is;
    }

    virtual bool operator==(const Podcast &other) {
        if (strcmp(this->url, other.url) == 0) {
            return true;
        }

        return false;
    }


    virtual float getPrice() {
        if (this->discount == 0) {
            return this->streaming_cost;
        } else {
            return (this->streaming_cost - ((this->streaming_cost / 100) * this->discount));
        }
    }
};


class StreamingPodcast : public Podcast {
private:
    float montly_fee;
    int month;
    int year;
public:

    float getPrice() override {
        float total_price = Podcast::getPrice();

        //todo - kolku meseci plakja pretplata
        return total_price;
    }

    StreamingPodcast() : Podcast() {
        this->montly_fee = 0;
        this->month = 0;
        this->year = 0;
    }

    StreamingPodcast(char *name, char *url, float streaming_cost, int discount, float montly_fee, int month, int year) : Podcast(name, url, streaming_cost, discount) {
        this->montly_fee = montly_fee;
        this->month = month;
        this->year = year;
    }

    StreamingPodcast(const StreamingPodcast &other) : Podcast(other) {
        this->montly_fee = other.montly_fee;
        this->month = other.month;
        this->year = other.year;
    }

    StreamingPodcast &operator=(const StreamingPodcast &other) {
        Podcast::operator=(other);

        this->montly_fee = other.montly_fee;
        this->month = other.month;
        this->year = other.year;

        return *this;
    }


    friend ostream &operator<<(ostream &os, StreamingPodcast &podcast) {

        os << *dynamic_cast<Podcast *>(&podcast);

        os << " monthly fee: $" << podcast.montly_fee << ", purchased: " << podcast.month << "-" << podcast.year << endl;

        return os;
    }


    friend istream &operator>>(istream &is, StreamingPodcast &podcast) {

        is.get();
        is.getline(podcast.name, 100);
        is.getline(podcast.url, 1000);
        is >> podcast.streaming_cost >> podcast.discount;

        is >> podcast.montly_fee >> podcast.month >> podcast.year;
        return is;
    }


};

class Playlist {
private:
    char playlist_name[100];
    Podcast **purchased_podcasts;
    int brojac;

public:

    Playlist(char *playlist_name) {
        strcpy(this->playlist_name, playlist_name);
        this->purchased_podcasts = nullptr;
        this->brojac = 0;
    }


    Playlist() {
        strcpy(this->playlist_name, "NaN");
        this->purchased_podcasts = nullptr;
        this->brojac = 0;
    }


    Playlist(char *playlist_name, Podcast **purchased_podcasts, int brojac) {

        strcpy(this->playlist_name, playlist_name);

        this->purchased_podcasts = new Podcast *[brojac];
        for (int i = 0; i < brojac; i++) {
            this->purchased_podcasts[i] = purchased_podcasts[i];
        }

        this->brojac = brojac;
    }

    Playlist(const Playlist &other) {

        strcpy(this->playlist_name, other.playlist_name);

        this->purchased_podcasts = new Podcast *[other.brojac];
        for (int i = 0; i < other.brojac; i++) {
            this->purchased_podcasts[i] = other.purchased_podcasts[i];
        }

        this->brojac = other.brojac;
    }

    Playlist &operator=(const Playlist &other) {

        strcpy(this->playlist_name, other.playlist_name);

        for (int i = 0; i < this->brojac; i++) {
            delete this->purchased_podcasts[i];
        }
        delete[]this->purchased_podcasts;

        this->purchased_podcasts = new Podcast *[other.brojac];
        for (int i = 0; i < other.brojac; i++) {
            this->purchased_podcasts[i] = other.purchased_podcasts[i];
        }

        this->brojac = other.brojac;

        return *this;
    }

    ~Playlist() {
        for (int i = 0; i < this->brojac; i++) {
            delete this->purchased_podcasts[i];
        }
        delete[]this->purchased_podcasts;
    }

    Playlist &operator+=(Podcast &other) {

        for (int i = 0; i < this->brojac; i++) {
            if (this->purchased_podcasts[i]->operator==(other) == true) {
                throw ExistingPodcast();
            }
        }

        Podcast **tmp = new Podcast *[this->brojac + 1];

        for (int i = 0; i < this->brojac; i++) {
            tmp[i] = this->purchased_podcasts[i];
        }

        StreamingPodcast *pom = dynamic_cast<StreamingPodcast *>(&other);

        if (pom == nullptr) {
            tmp[this->brojac] = new Podcast(other);
        } else {
            tmp[this->brojac] = new StreamingPodcast(*pom);
        }

        this->brojac++;

        delete[] this->purchased_podcasts;
        this->purchased_podcasts = tmp;

        return *this;
    }

    float total_spent() {

        float total_spent = 0;

        for (int i = 0; i < this->brojac; i++) {
            total_spent = total_spent + this->purchased_podcasts[i]->getPrice();
        }
        return total_spent;
    }

    friend ostream &operator<<(ostream &os, const Playlist &playlist) {
        cout << "Playlist: " << playlist.playlist_name << endl;
        for (int i = 0; i < playlist.brojac; i++) {
            if (dynamic_cast<StreamingPodcast *>(playlist.purchased_podcasts[i]) != nullptr) {
                cout << *dynamic_cast<StreamingPodcast *>(playlist.purchased_podcasts[i])<< endl;
            }else
            {
                cout <<*playlist.purchased_podcasts[i]<< endl;
            }
        }
        return os;
    }

};

int main() {
    int test_case_num;

    cin >> test_case_num;

    // for Podcast
    char podcast_name[100];
    char podcast_url[1000];
    float podcast_price;
    int podcast_discount;

    // for StreamingPodcast
    float sub_podcast_monthly_fee;
    int sub_podcast_month, sub_podcast_year;

    // for Playlist
    char name[100];
    int num_podcasts_in_playlist;

    if (test_case_num == 1) {
        cout << "Testing class Podcast and operator&lt;&lt; for Podcast" << std::endl;
        cin.get();
        cin.getline(podcast_name, 100);
        cin.getline(podcast_url, 1000);
        //cin.get();
        cin >> podcast_price >> podcast_discount;

        Podcast p(podcast_name, podcast_url, podcast_price, podcast_discount);

        cout << p;
    } else if (test_case_num == 2) {
        cout << "Testing class StreamingPodcast and operator&lt;&lt; for StreamingPodcast" << std::endl;
        cin.get();
        cin.getline(podcast_name, 100);
        cin.getline(podcast_url, 1000);
        //cin.get();
        cin >> podcast_price >> podcast_discount;

        cin >> sub_podcast_monthly_fee;
        cin >> sub_podcast_month >> sub_podcast_year;

        StreamingPodcast sp(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
        cout << sp;
    } else if (test_case_num == 3) {
        cout << "Testing operator&gt;&gt; for Podcast" << std::endl;
        Podcast p;

        cin >> p;

        cout << p;
    } else if (test_case_num == 4) {
        cout << "Testing operator&gt;&gt; for StreamingPodcast" << std::endl;
        StreamingPodcast sp;

        cin >> sp;

        cout << sp;
    } else if (test_case_num == 5) {
        cout << "Testing class Playlist and operator+= for Playlist" << std::endl;
        cout << endl;
        cin.get();
        cin.getline(name, 100);
        Playlist u(name);

        int num_user_podcasts;
        int podcast_type;
        cin >> num_user_podcasts;

        try {

            for (int i = 0; i < num_user_podcasts; ++i) {

                cin >> podcast_type;

                Podcast *g;
                // 1 - Game, 2 - SubscriptionGame
                if (podcast_type == 1) {
                    cin.get();
                    cin.getline(podcast_name, 100);
                    cin.getline(podcast_url, 1000);

                    cin >> podcast_price >> podcast_discount;
                    g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
                } else if (podcast_type == 2) {
                    cin.get();
                    cin.getline(podcast_name, 100);
                    cin.getline(podcast_url, 1000);

                    cin >> podcast_price >> podcast_discount;

                    cin >> sub_podcast_monthly_fee;
                    cin >> sub_podcast_month >> sub_podcast_year;
                    g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
                }

                //cout<<(*g);


                u += (*g);
            }
        } catch (ExistingPodcast &ex) {
            ex.message();
        }

        cout << u << endl;

    } else if (test_case_num == 6) {
        cout << "Testing exception ExistingPodcast for Playlist" << std::endl;

        cin.get();
        cin.getline(name, 100);
        Playlist u(name);

        int num_podcasts_in_playlist;
        int podcast_type;
        cin >> num_podcasts_in_playlist;

        for (int i = 0; i < num_podcasts_in_playlist; ++i) {

            cin >> podcast_type;

            Podcast *g;
            // 1 - Game, 2 - SubscriptionGame
            if (podcast_type == 1) {
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin >> podcast_price >> podcast_discount;
                g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
            } else if (podcast_type == 2) {
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin >> podcast_price >> podcast_discount;

                cin >> sub_podcast_monthly_fee;
                cin >> sub_podcast_month >> sub_podcast_year;
                g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
            }

            //cout<<(*g);

            try {
                u += (*g);
            }
            catch (ExistingPodcast &ex) {
                ex.message();
            }
        }
        cout << endl;
        cout << u;
    } else if (test_case_num == 7) {
        cout << "Testing total_spent method() for Playlist" << std::endl;
        cout << endl;
        cin.get();
        cin.getline(name, 100);
        Playlist u(name);

        int num_podcasts_in_playlist;
        int podcast_type;
        cin >> num_podcasts_in_playlist;

        for (int i = 0; i < num_podcasts_in_playlist; ++i) {

            cin >> podcast_type;

            Podcast *g;
            // 1 - Game, 2 - SubscriptionGame
            if (podcast_type == 1) {
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin >> podcast_price >> podcast_discount;
                g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
            } else if (podcast_type == 2) {
                cin.get();
                cin.getline(podcast_name, 100);
                cin.getline(podcast_url, 1000);

                cin >> podcast_price >> podcast_discount;

                cin >> sub_podcast_monthly_fee;
                cin >> sub_podcast_month >> sub_podcast_year;
                g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
            }

            //cout<<(*g);

            try {
                u += (*g);
            }
            catch (ExistingPodcast &ex) {
                ex.message();
            }
        }

        cout << u << endl;

        cout << "Total money spent: $" << u.total_spent() << endl;
    }
}