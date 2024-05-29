#include <iostream>
#include <cstring>

using namespace std;

class InvalidTeamName {
private:
public:
    void message(char *team) {
        cout << "Invalid team name: " << team << endl;
    }
};

class Goal {

private:
    char *goal_scorer;
    int minute_scored;
    char goalScored_teamName[50];

public:
    char *getGoalScorer() const {
        return goal_scorer;
    }

    int getMinuteScored() const {
        return minute_scored;
    }

    const char *getTeamName() const {
        return goalScored_teamName;
    }

    Goal() {
        this->goal_scorer = nullptr;
        this->minute_scored = 0;
        strcpy(this->goalScored_teamName, "NaN");
    }

    Goal(char *goal_scorer, int minute_scored, char *goalScored_teamName) {
        this->goal_scorer = new char[strlen(goal_scorer) + 1];
        strcpy(this->goal_scorer, goal_scorer);

        this->minute_scored = minute_scored;
        strcpy(this->goalScored_teamName, goalScored_teamName);
    }

    Goal(const Goal &other) {
        this->goal_scorer = new char[strlen(other.goal_scorer) + 1];
        strcpy(this->goal_scorer, other.goal_scorer);

        this->minute_scored = other.minute_scored;
        strcpy(this->goalScored_teamName, other.goalScored_teamName);
    }

    Goal &operator=(const Goal &other) {
        delete[]this->goal_scorer;
        this->goal_scorer = new char[strlen(other.goal_scorer) + 1];
        strcpy(this->goal_scorer, other.goal_scorer);

        this->minute_scored = other.minute_scored;
        strcpy(this->goalScored_teamName, other.goalScored_teamName);

        return *this;
    }

    friend ostream &operator<<(ostream &os, const Goal &goal) {
        os << goal.minute_scored << " " <<goal.goal_scorer << endl;
        return os;
    }

    Goal operator++(int) {
        this->minute_scored++;

        return *this;
    }

    Goal operator--() {
        this->minute_scored;
        return *this;
    }

};

class Game {
private:
    Goal *golovi;
    int num;
    char home_team[50];
    char away_team[50];

public:

    Game() {
        this->golovi = nullptr;
        this->num = 0;
        strcpy(this->home_team, "NoName");
        strcpy(this->away_team, "NoName");
    }

    Game(char *home_team, char *away_team) {
        this->golovi = nullptr;
        this->num = 0;
        strcpy(this->home_team, home_team);
        strcpy(this->away_team, away_team);
    }

    Game(const Game &other) {
        if (other.num != 0) {
            this->golovi = new Goal[other.num];
            for (int i = 0; i < other.num; i++) {
                this->golovi[i] = other.golovi[i];
            }
        } else this->golovi = nullptr;
        this->num = other.num;
        strcpy(this->home_team, other.home_team);
        strcpy(this->away_team, other.away_team);
    }

    Game &operator=(const Game &other) {
        delete[] this->golovi;
        if (other.num != 0) {
            this->golovi = new Goal[other.num];
            for (int i = 0; i < other.num; i++) {
                this->golovi[i] = other.golovi[i];
            }
        } else this->golovi = nullptr;
        this->num = other.num;
        strcpy(this->home_team, other.home_team);
        strcpy(this->away_team, other.away_team);

        return *this;
    }


    Game &operator+=(const Goal &new_goal_scored) {

        if (strcmp(this->home_team, new_goal_scored.getTeamName()) == 0 || strcmp(this->away_team, new_goal_scored.getTeamName()) == 0) {
            Goal *tmp = new Goal[this->num + 1];
            for (int i = 0; i < this->num; i++) {
                tmp[i] = this->golovi[i];
            }
            tmp[this->num] = new_goal_scored;
            this->num++;

            delete[] this->golovi;
            this->golovi = tmp;

        } else {
            throw InvalidTeamName();
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Game &game) {
        os << game.home_team << " - " << game.away_team << endl;
        for (int i = 0; i < game.num; i++) {
            os << game.golovi[i];
        }

        return os;
    }

};

int main() {
    char team1[50];
    char team2[50];
    cin >> team1;
    cin >> team2;
    Game n(team1, team2);
    int x;
    cin >> x;
    char player[100];
    int m;
    for (int i = 0; i < x; ++i) {
        cin >> player;
        cin >> m;
        cin >> team1;
        Goal g(player, m, team1);
        try {
            n += g;
        } catch (InvalidTeamName &e) {
            e.message(team1);
        }
    }
    cout << n << endl;
    return 0;
}
