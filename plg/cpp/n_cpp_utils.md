# C++ Utils

## Clone an Object

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


