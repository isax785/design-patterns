#include <iostream>
using namespace std;

struct Button {
    virtual void click()=0;
    // virtual void optional_method();
};

struct Checkbox {
    virtual void check()=0;
};

struct WindowsButton: public Button {
    void click() override{cout << "Windows Button clicked" << endl;}
    };
struct LinuxButton: public Button {
    void click() override{cout << "Linux Button clicked" << endl;}
    };
struct MacButton: public Button {
    void click() override{cout << "Mac Button clicked" << endl;}
    };
struct WindowsCheckbox: public Checkbox {
    void check() override {cout << "Windows Checkbox checked" << endl;}
    };
struct LinuxCheckbox: public Checkbox {
    void check() override {cout << "Linux Checkbox checked" << endl;}
    };
struct MacCheckbox: public Checkbox {
    void check() override {cout << "Mac Checkbox checked" << endl;}
    };

struct GUIFactory {
    virtual Button* create_button()=0;
    virtual Checkbox* create_checkbox()=0;
};

struct WindowsFactory : public GUIFactory {
    Button* create_button() override{return new WindowsButton;};
    Checkbox* create_checkbox() override{return new WindowsCheckbox;};
};

struct LinuxFactory : public GUIFactory {
    Button* create_button() override{return new LinuxButton;};
    Checkbox* create_checkbox() override{return new LinuxCheckbox;};
};

struct MacFactory : public GUIFactory {
    Button* create_button() override{return new MacButton;};
    Checkbox* create_checkbox() override{return new MacCheckbox;};
};

// Client code
void create_ui(GUIFactory* factory) {
    Button* button = factory->create_button();
    Checkbox* checkbox = factory->create_checkbox();
    button->click();
    checkbox->check();
}

enum OS {WINDOWS, LINUX, MAC};

int main() {
    OS os = MAC;
    GUIFactory* factory;
    switch (os){
        case WINDOWS:
            factory = new WindowsFactory();
            break;
        case LINUX:
            factory = new LinuxFactory();
            break;
        case MAC:
            factory = new MacFactory();
            break;        
    }
    create_ui(factory);

    return 0;
}
