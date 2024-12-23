#include "dp_includes.h"

struct Memento {
    string _state;
    Memento(string state) : _state(state) {}
    string get_state() {return _state;}
};

struct Editor {
    string _content;
    void type(string s) {_content += s;}
    string get_content() {return _content;}
    Memento save() {return Memento(_content);}
    void restore(Memento &mem) {_content = mem.get_state();};
};

struct History {
    vector<Memento> _mementos;
    History() {_mementos={};}
    void push(Memento mem) {_mementos.push_back(mem);}
    Memento pop(){
        if (_mementos.size()==0) return Memento("");
        Memento mem = _mementos.back();
        _mementos.pop_back();
        return mem;
    };
};

void display_content(string con) {
    cout << "Current content: " << con << endl;
};

int main() {
    Editor editor;
    History history;
    editor.type("This is the FIRST sentence. ");
    history.push(editor.save());
    editor.type("This is the SECOND sentence. ");
    history.push(editor.save());
    editor.type("This is the THIRD sentence. ");
    display_content(editor.get_content());
    // history.push(editor.save());
    history.push(editor.get_content());
    Memento mem = history.pop();
    editor.restore(mem);
    display_content(editor.get_content());
}