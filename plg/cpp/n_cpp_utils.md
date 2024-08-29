# C++ Utils

- [C++ Utils](#c-utils)
  - [Clone an Object](#clone-an-object)
  - [Static Methods](#static-methods)

---

## Clone an Object

> See also the [Prototype (C++) implementation](../cpp/01_05_prototype.cpp) for a more detailed example.

Implement a dedicated `clone` method (`Interface* clone() const { return new Foo(*this); }`):

```cpp
class Interface
{
public:
  virtual Interface* clone() const = 0;
};

class Foo : public Interface
{
public:
  Interface* clone() const { return new Foo(*this); }
};

class Bar : public Interface
{
public:
  Interface* clone() const { return new Bar(*this); }
};

Interface* my_foo = /* somehow construct either a Foo or a Bar */;
Interface* copy = my_foo->clone();
```

## Static Methods

```cpp
//declaration
class Singleton {
    public:
        static Singleton* Instance();
    ...
}

// call
int main(){
    ...
    Singleton* sing = Singleton::Instance();
    ...
}
```