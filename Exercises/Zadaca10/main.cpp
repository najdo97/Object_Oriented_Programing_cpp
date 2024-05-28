#include <iostream>
#include <cstring>

using namespace std;


class Goal {

private:
    char *goal_scorer;
    int minute_scored;
    char goalScored_teamName[50];

public:

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
        os << goal.minute_scored << goal.goal_scorer << endl;
        return os;
    }

    Goal operator++(int) {
        this->minute_scored++;

        return *this;
    }

    Goal operator--() {
        --this->minute_scored;
        return *this;
    }


};

class Game {
private:


public:
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
            cout << "Invalid team name: " << e.what() << endl;
        }
    }
    cout << n << endl;
    return 0;
}
