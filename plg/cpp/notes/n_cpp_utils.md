# C++ Utils

- [C++ Utils](#c-utils)
  - [Clone an Object](#clone-an-object)
  - [Static Methods](#static-methods)
  - [Formatted Strings](#formatted-strings)
    - [An Interesting Case](#an-interesting-case)
  - [Sleep](#sleep)

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

## Formatted Strings

Using `stringstreams`:

```cpp
#include <string>
#include <sstream>

std::ostringstream oss;
oss << "sometext" << somevar << "sometext" << somevar;
std::string var = oss.str();
```

Using `std::to_string` if variables are declared as `char`:

```cpp
std::string var = "sometext" + std::to_string(somevar) + "sometext" + std::to_string(somevar);  
```

Using `+` operator:

```cpp
string var;
var = "sometext";
var += somevar;
var += "sometext";
var += somevar;
```

### An Interesting Case

```cpp
std::string var = "sometext" + somevar + "sometext" + somevar;
```

This doesn't work because the additions are performed left-to-right and "sometext" (the first one) is just a `const char *`. It has no operator+ to call. The simplest fix is this:

Now, the first parameter in the left-to-right list of + operations is a std::string, which has an operator+(const char *). That operator produces a string, which makes the rest of the chain work.

```cpp
std::string var = std::string("sometext") + somevar + "sometext" + somevar;
```

## Sleep

Function `Sleep` included into the headers `windows.h`|`unistd.h` (depending on the OS).

It requires time in `ms`.

```cpp
#include <windows.h>
// #include <unistd.h> // Linux

using namespace std;

int main() {
    ...
    Sleep(3e3);
    ...
}
```

Depending on the OS:

- Windows `#include <windows.h>` -> `Sleep()`
- UNIX/Linux `#include <unistd.h>` -> `sleep()`
