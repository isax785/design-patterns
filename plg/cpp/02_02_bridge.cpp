#include <iostream>
#include <vector>

using namespace std;

// **Intent**: decouple an ABSTRACTION from its IMPLEMENTATION so that the two can vary independently.

struct Renderer { // IMPLEMENTATION abstract class
    virtual void render_circle(float radius)=0;
    virtual void render_square(float side)=0;
};

struct VectorRenderer : public Renderer {
    void render_circle(float radius) override {
        cout <<  "Drawing a circle with radius " << radius << " using Vector Renderer" << endl;
    };
    void render_square(float side) override {
         cout <<  "Drawing a square with side " << side << " using Vector Renderer" << endl;
    };
};

struct RasterRenderer : public Renderer {
    void render_circle(float radius) override {
        cout <<  "Drawing a circle with radius " << radius << " using Raster Renderer" << endl;
    };
    void render_square(float side) override {
         cout <<  "Drawing a square with side " << side << " using Raster Renderer" << endl;
    };
};

struct Shape { // ABSTRACTION
    Renderer* _renderer;
    Shape(Renderer* renderer) : _renderer(renderer) {};
    virtual void draw() {};
    virtual void resize(float factor) {};
};

struct Circle : public Shape {
    float _radius;
    Circle(Renderer* renderer, float radius) : Shape(renderer), _radius(radius) {
        cout << "Circle with radius " << radius << " instantiated!" <<endl;
    }
    void draw() override {_renderer->render_circle(_radius);}
    void resize(float factor) override {_radius *= factor;}
};

struct Square : public Shape {
    float _side;
    Square(Renderer* renderer, float side) : Shape(renderer), _side(side) {
        cout << "Square with side " << side << " instantiated!" <<endl;
    }
    void draw() override {_renderer->render_circle(_side);}
    void resize(float factor) override {_side *= factor;}
};

int main() {
    Renderer* vector_renderer = new VectorRenderer();
    Renderer* raster_renderer = new RasterRenderer();

    vector<Shape*> shapes;
    shapes.push_back(new Circle(vector_renderer, 12));
    shapes.push_back(new Circle(raster_renderer, 12));
    shapes.push_back(new Circle(vector_renderer, 100));
    shapes.push_back(new Square(vector_renderer, 1.56));
    shapes.push_back(new Square(raster_renderer, 100000));
    shapes.push_back(new Square(vector_renderer, 23.7));

    for (int i=0; i<shapes.size(); i++) {
        cout << i << " - " << typeid(shapes[i]).name() << endl;
        shapes[i]->draw();
        cout << "Now resizing by the factor: " << i << endl;
        shapes[i]->resize(i);
        shapes[i]->draw();
    }
    
    return 0;
}