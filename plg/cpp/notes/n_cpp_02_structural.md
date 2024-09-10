# C++ Structural Patterns

- [C++ Structural Patterns](#c-structural-patterns)
- [Decorator](#decorator)

---

# Decorator

```cpp
struct Component {
    Component();
    virtual void Action();
    virtual void AnotherAction();
};

struct Decorator : public Component {
    Decorator(Component*);
    virtual void Action();
    virtual void AnotherAction();
    private:
        Component* _component;
};

void Decorator::Action() {
    _component->Action();
};

void Decorator::AnotherAction() {
    _component->AnotherAction();
};


// Decorator's sublcasses define specific decorations
struct SpecificDecorator : public Decorator {
    SpecificDecorator(Component*, int val);
    virtual void Action();
    private:
        void SpecificAction(int);
        int _val;
};

void SpecificDecorator::Action() {
    Decorator::Action();
    SpecificAction(_val);
};
```