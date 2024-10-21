#include <iostream>

using namespace std;

const int FACTORY_SIZE = 100;

struct Circle {
    const char* m_color;
    Circle(const char* color) : m_color(color) {
        printf("Generated &s circle\n", m_color);
    };
    void draw(float x, float y, float radius) {
        printf("Drawing a %s circle at (%f, %f) with radius %f\n", m_color, x, y, radius);
    }
};

struct CircleFactory {
    Circle* circles[FACTORY_SIZE];
    const char* colors[FACTORY_SIZE];
    int counter = 0;
    Circle* get_circle(const char* color) { 
        for (int i=0; i<FACTORY_SIZE; i++) {
            cout << color << endl; // DEBUG
            if (color = colors[i]) 
            {
                return circles[i];
            }
        }
        circles[counter] = new Circle(color);
        colors[counter] = color;
        counter++;
        return circles[counter-1];
    }
};

int main() {
    // Circle c {"white"}; // This worked also without defining a constructor ???
    // c.draw(2.3, 4.5, 6.789);
    const char* colors[3] = {"red", "green", "blue"};
    CircleFactory factory = CircleFactory();
    for (auto color : colors) {
        Circle *circle = factory.get_circle(color);
        circle->draw(12.3, 14.4, 1.2343);
    }
    Circle* circ = factory.circles[1];
    cout << circ->m_color  << endl;
}

