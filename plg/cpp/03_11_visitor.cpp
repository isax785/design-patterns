#include "dp_includes.h"

struct ShapeVisitor;

struct Shape {
    virtual void accept(ShapeVisitor* visitor)=0;
};
struct Circle : public Shape {
    void accept(ShapeVisitor* visitor);
    void draw() { cout << "Drawing Circle" << endl; }
    void resize() { cout << "Resizing Circle" << endl; }
};
struct Square : public Shape {
    void accept(ShapeVisitor* visitor);
    void draw() { cout << "Drawing Square" << endl; }
    void resize() { cout << "Resizing Square" << endl; }
};
struct Rectangle : public Shape {
    void accept(ShapeVisitor* visitor);
    void draw() { cout << "Drawing Square" << endl; }
    void resize() { cout << "Resizing Square" << endl; }
};

struct ShapeVisitor {
    virtual void visit_circle(Circle* circle)=0;
    virtual void visit_square(Square* square)=0;
    virtual void visit_rectangle(Rectangle* rectangle)=0;
};
struct DrawVisitor : public ShapeVisitor{
    void visit_circle(Circle * circle) override { circle->draw(); }
    void visit_square(Square * square) override { square->draw(); }
    void visit_rectangle(Rectangle * rectangle) override { rectangle->draw(); }
};
struct ResizeVisitor : public ShapeVisitor{
    void visit_circle(Circle * circle) override { circle->resize(); }
    void visit_square(Square * square) override { square->resize(); }
    void visit_rectangle(Rectangle * rectangle) override { rectangle->resize(); }
};

void Circle::accept(ShapeVisitor* visitor) { visitor -> visit_circle(this); }
void Square::accept(ShapeVisitor* visitor) { visitor -> visit_square(this); }
void Rectangle::accept(ShapeVisitor* visitor) { visitor -> visit_rectangle(this); }

int main() {
    vector<Shape*> shapes = {new Circle(), new Square(), new Rectangle()};
    ShapeVisitor* draw_visitor = new DrawVisitor();
    ShapeVisitor* resize_visitor = new ResizeVisitor();
    for (auto shape : shapes) {
        shape->accept(draw_visitor);
        shape->accept(resize_visitor);
    }
}