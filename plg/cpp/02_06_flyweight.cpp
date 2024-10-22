#include <iostream>
#include <string>
#include <map>
#include <stdio.h>

using namespace std;

const int FS = 10;  // Factory Size

struct Circle {
    const string m_color;
    Circle(const string color) : m_color(color) {
        printf("Generated %s circle\n", m_color.c_str());
    }

    void draw(float x, float y, float radius) {
        printf("Drawing a %s circle at (%f, %f) with radius %f", m_color.c_str(), x, y, radius);
    }
};

bool compare_strings(string& s1, string& s2) {
    if (s1.size() != s2.size()) return false;
    for(int i=0; i<s1.size(); i++) {
        if (s1[i] != s2[i]) return false;
    }
    return true;
};

struct CircleFactory {
    map<string, Circle*> circles;

    Circle* get_circle(const string color) {
        if (circles.find(color) != circles.end()) {
            cout << color << " circle yet created" << endl;
            return circles[color];
        }
        else {
            circles[color] = new Circle(color);
            return circles[color];
        }
    }
};


int main() {
    const int N=5;
    CircleFactory factory = CircleFactory();
    const string colors[N] = {"red", "green", "blue", "red", "blue"};
    for (int i=0; i<N; i++) {
        cout << "DBG-m: " << colors[i] << endl; // DBG
        Circle *circle = factory.get_circle(colors[i]);
        circle->draw(12.3, 14.4, 1.2343);
    }
}