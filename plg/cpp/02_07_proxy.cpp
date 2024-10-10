#include <iostream>
#include <string>
#include <windows.h>
// #include <unistd.h> // Linux

using namespace std;

struct BookInterface {
    virtual void display()=0;
};

struct Book : public BookInterface {
    const string _title;
    Book(const string title) : _title(title) {_load_from_disk();};

    void _load_from_disk() {
        cout << "Loading book " << _title << " from disk ... ";
        Sleep(1000);
        cout << "loaded!" << endl;
    };
    void display() override { cout << "\tDisplaying book '" << _title << "'" << endl; }
};

struct BookProxy : public BookInterface {
    const string _title;
    Book* _book;
    BookProxy(const string title) : _title(title),  _book(nullptr) {
        cout << "Proxy: book title '" << _title << "'" << endl;
    }

    void display() {
        if (!_book) { 
            _book = new Book(_title); 
        }
        cout << "Proxy: Logging access to the book '" << _title << "'" << endl;
        _book->display();
    }
};

int main() {
    // int* a=nullptr;
    // if (!a) { cout << "a nullptr" << endl; }
    Book b = Book("Fake Title");
    b.display();

    // Instantiating proxy
    BookProxy book1 = BookProxy("1984");
    BookProxy book2 = BookProxy("Some C++ Stuff");

    // Book not loaded yet
    cout << "Client: let's display the first book." << endl;
    book1.display();  // now loading the book
    cout << "Client: let's display the second book." << endl;
    book2.display();  // now loading the book
    
    // Books already loaded
    cout << "Client: let's display the first book again." << endl;
    book1.display();  // now loading the book
    cout << "Client: let's display the second book again." << endl;
    book2.display();  // now loading the book

    return 0;
}

