#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

struct Circle {
    const string m_color;
    Circle(const string color) : m_color(color) {
        printf("Generated %s circle\n", m_color.c_str());
    }
};

int main() {
    Circle c = Circle("red");
}