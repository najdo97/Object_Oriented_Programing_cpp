#include<iostream>
#include<cstdio>
#include <cstring>

using namespace std;

class Camera {
private:
    char manufacturer[20];
    char model[20];
    int production_year;
    float resolution;

    void copy_camera(const Camera &other) {
        strcpy(this->manufacturer, other.manufacturer);
        strcpy(this->model, other.model);
        this->production_year = other.production_year;
        this->resolution = other.resolution;
    }

public:
    const char *getManufacturer() const {
        return manufacturer;
    }

    const char *getModel() const {
        return model;
    }

    int getProductionYear() const {
        return production_year;
    }

    float getResolution() const {
        return resolution;
    }

    Camera() {
        strcpy(this->manufacturer, "NaN");
        strcpy(this->model, "NaN");
        this->production_year = 0;
        this->resolution = 0;
    }

    Camera(char *manufacturer, char *model, int production_year, float resolution) {
        strcpy(this->manufacturer, manufacturer);
        strcpy(this->model, model);
        this->production_year = production_year;
        this->resolution = resolution;
    }

    Camera(const Camera &other) {
        copy_camera(other);
    }

    Camera &operator=(const Camera &other) {
        copy_camera(other);
        return *this;
    }

    friend ostream &operator<<(ostream &os, Camera &camera) {
        os << camera.model << endl;
        return os;
    }

    virtual float price() = 0;

    virtual float rentalPrice(int days) = 0;

    bool operator<(Camera &other) {
        if (this->price() < other.price()) {
            return true;
        } else return false;
    }

};

class PhotoCamera : public Camera {
private:
    bool isRaw;
public:
    PhotoCamera() : Camera() {
        this->isRaw = false;
    }

    PhotoCamera(char *manufacturer, char *model, int production_year, float resolution, bool isRaw) : Camera(manufacturer, model, production_year, resolution) {
        this->isRaw = isRaw;
    }

    PhotoCamera(const PhotoCamera &other) : Camera(other) {
        this->isRaw = other.isRaw;
    }

    PhotoCamera &operator=(const PhotoCamera &other) {
        Camera::operator=(other);
        this->isRaw = other.isRaw;
        return *this;
    }

    float price() override {
        float total = 0;
        if (this->isRaw) {
            total = (100 + (int) this->getResolution() * 20) + 50;
        } else total = (100 + (int) this->getResolution() * 20);

        return total;
    }

    float rentalPrice(int days) override {
        float total = 0;
        if (days <= 7) {
            total = (this->price() / 100) * days;
        } else if (days > 7) {
            total = (this->price() / 100) * days;
            total = total - (total * 0.2);
        }
        return total;
    }
};


class VideoCamera : public Camera {
private:
    int length;
public:
    VideoCamera() : Camera() {
        this->length = 0;
    }

    VideoCamera(char *manufacturer, char *model, int production_year, float resolution, int length) : Camera(manufacturer, model, production_year, resolution) {
        this->length = length;
    }

    VideoCamera(const VideoCamera &other) : Camera(other) {
        this->length = other.length;
    }

    VideoCamera &operator=(const VideoCamera &other) {
        Camera::operator=(other);
        this->length = other.length;
        return *this;
    }

    float price() override {
        float total = 0;
        if (this->length <= 60) {
            total = this->getResolution() * 80;
        } else {
            total = this->getResolution() * 80;

            total = total + (total * 0.4);
        }
        return total;
    }

    float rentalPrice(int days) override {
        float total = 0;
        if (days <= 7) {
            total = (this->price() / 100) * days;
        } else if (days > 7) {
            total = (this->price() / 100) * days;
            total = total - (total * 0.2);
        }
        return total;
    }

};


class FilmCamera : public Camera {
private:
    int fps;
public:
    FilmCamera() : Camera() {
        this->fps = 0;
    }

    FilmCamera(char *manufacturer, char *model, int production_year, float resolution, int fps) : Camera(manufacturer, model, production_year, resolution) {
        this->fps = fps;
    }

    FilmCamera(const FilmCamera &other) : Camera(other) {
        this->fps = other.fps;
    }

    FilmCamera &operator=(const FilmCamera &other) {
        Camera::operator=(other);
        this->fps = other.fps;
        return *this;
    }

    float price() override {
        float total = 50000;
        int pom = fps;

        if (this->fps > 30) {
            while (pom > 30) {
                total = total + 5000;
                pom--;
            }
        }
        return total;
    }

    float rentalPrice(int days) override {
        float total = 500;

        if (this->fps > 60) {
            total = total * 2;
        }

        return total * days;
    }
};


Camera &mostExpensiveCamera(Camera **kameri, int n) {

    int idx = 0;

    for (int i = 0; i < n; i++) {
        if (kameri[idx]->price() < kameri[i]->price())
            idx = i;
    }

    return *kameri[idx];
}

float production(Camera **kameri, int n, int days) {

    int total = 0;

    for (int i = 0; i < n; i++) {
        total = total + kameri[i]->rentalPrice(days);
    }
    return total;
}

int main(int argc, char *argv[]) {
    // Variables for reading input
    char model[20], producer[20];
    int year, length, fps, n;
    float resolution;
    bool raw;

    int t;

    // Array of cameras
    Camera *c[10];

    // Read number of cameras
    cin >> n;

    for (int i = 0; i < n; ++i) {

        // Camera type: 1 - Photo, 2 - Video, 3 - Film
        cin >> t;

        if (t == 1) {
            cin >> producer >> model >> year >> resolution;
            cin >> raw;
            c[i] = new PhotoCamera(producer, model, year, resolution, raw);
        } else if (t == 2) {
            cin >> producer >> model >> year >> resolution;
            cin >> length;
            c[i] = new VideoCamera(producer, model, year, resolution, length);
        } else if (t == 3) {
            cin >> producer >> model >> year >> resolution;
            cin >> fps;
            c[i] = new FilmCamera(producer, model, year, resolution, fps);
        }
    }


    // Production days
    int days;
    cin >> days;


    cout << "Price of production is: " << production(c, n, days) << endl;
    cout << "Most expensive camera used in production is: " << mostExpensiveCamera(c, n) << endl;


    return 0;
}
