#include <iostream>
using namespace std;

// `static`: members (attributes and methodx) that are not 
//           bounded to class instances,
//           they are bounded to the class definition

class Singleton {
    public:
        static Singleton* Instance();
    protected:
        Singleton();
    private:
        static Singleton* _instance;
        static int _counter;
};

int main() {
    Singleton* sing = Singleton::Instance();
    Singleton* sing2 = Singleton::Instance();
    Singleton* sing3 = Singleton::Instance();
    Singleton* sing4 = Singleton::Instance();
    return 0;
}

// Definitions

Singleton* Singleton::_instance = 0;
int Singleton::_counter = 0;
Singleton::Singleton() {
    cout << "Creating Singleton Object ... Done!" << endl;
};
Singleton* Singleton::Instance() {
    if (_instance == 0) {
        _instance = new Singleton;
        cout << "Created FIRST Singleton Object" << endl;
        _counter++;
    }
    else {
        _counter++;
        cout << "Singleton Object creation call: " << _counter << endl;
    }
    return _instance;
};