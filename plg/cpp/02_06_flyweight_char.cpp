#include <iostream>
#include <string.h>

using namespace std;

const int FACTORY_SIZE = 10;

struct Circle {
    const char* m_color;
    Circle(const char* color) : m_color(color) {
        printf("Generated %s circle\n", m_color);
    };
    void draw(float x, float y, float radius) {
        printf("Drawing a %s circle at (%f, %f) with radius %f\n", m_color, x, y, radius);
    }
};

struct CircleP {
    const char* m_color;
    CircleP(const char* color) : m_color(color) {}
    void draw(float x, float y, float radius) {
        printf("Drawing a %s circleP at (%f, %f) with radius %f\n", m_color, x, y, radius);
    }
};

struct CircleFactory {
    Circle* circles[FACTORY_SIZE];
    const char* colors[FACTORY_SIZE];
    int counter = 0;

    Circle* get_circle(const char* color) { 
        printf("DBG: get_circle color %s\n", color);
        for (int i=0; i<FACTORY_SIZE; i++) {
            cout << "DBG: looking for " << color << endl; // DEBUG
            if (strcmp(color, colors[i])) 
        //     {
                printf("DBG: color %s yet created", color); // DEBUG
        // //         return circles[i];
        //     }
        }
        cout << "DBG: Creating " << color << endl; // DEBUG
        printf("DBG: Counter %d\n", counter);
        circles[counter] = new Circle(color);
        colors[counter] = color;
        counter++;
        return circles[counter-1];
    }
};

int main() {
    // This works!!
    // CircleP c = CircleP("white"); 
    // c.draw(2.3, 4.5, 6.789);

    const int N = 5;
    const char* colors[N] = {"red", "green", "blue", "red", "blue"};
    CircleFactory factory = CircleFactory();
    for (int i=0; i<N; i++) {
        cout << "DBG: " << colors[i] << endl; // DBG
        // CircleP c = CircleP(colors[i]); // This works!!
        // c.draw(2.3, 4.5, 6.789);
        Circle *circle = factory.get_circle(colors[i]);
        // circle->draw(12.3, 14.4, 1.2343);
    }
    cout << strcmp("red", "red") << endl;
    // Circle* circ = factory.circles[1];
    // cout << circ->m_color  << endl;
}

