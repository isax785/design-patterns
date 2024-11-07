#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Command {
    void virtual execute()=0;
    void virtual undo()=0;
};

struct Document {
    string content;
    Document() : content("") {};
    void insert_text(string text, int position=0) {
        cout << "DBG: " << content.size() << endl; // DEBUG
        content = content.substr(0, position) + 
                  text + 
                  content.substr(position);
    }
    string delete_text(int position, int length) {
        string deleted_text = content.substr(position, length);
        content = content.substr(0, position) + deleted_text;
        return deleted_text;
    }
    friend ostream &operator << (ostream &o, const Document &doc) {
        o << doc.content;
        return o;
    }
};

struct InsertTextCommand : public Command {
    Document _doc;
    string _text;
    int _position;
    InsertTextCommand(Document &doc, string text, int position) :
        _doc(doc), _text(text), _position(position) {};
    void execute() override {
        _doc.insert_text(_text, _position);
    }
    void undo() override {
        _doc.delete_text(_position, _text.size());
    }
};

struct DeleteTextCommand : public Command {
    Document _doc;
    string _deleted_text;
    int _position;
    int _length;
    DeleteTextCommand(Document &doc, int position, int length) :
        _doc(doc), _position(position), _length(length), _deleted_text("") {};
    void execute() override {
        _deleted_text = _doc.delete_text(_position, _length);
    }
    void undo() override {
        _doc.insert_text(_deleted_text, _position);
    }
};


struct TextEditor {
    Document _doc;
    vector<Command*> history={};
    vector<Command*> undo_stack={};
    void execute_command(Command& command) {
        command.execute();
        history.push_back(&command);
        undo_stack.clear();
    }
    void undo() {
        if (history.size() == 0) return;
        Command* command = history.back();
        command->undo();
        history.pop_back();
        undo_stack.push_back(command);
    }
    void redo() {
        if (undo_stack.size() == 0) return;
        Command* command = undo_stack.back();
        command->execute();
        undo_stack.pop_back();
        history.push_back(command);
    }
    void show_document() {
        cout << _doc << endl;
    }
};

void display_editor_stacks(TextEditor *editor) {
    cout << "History:" << endl;
    for (auto c : editor->history) 
        cout << "  " << typeid(c).name() << " - " << &c << endl;
        
    cout << "Undo:" << endl;
    for (auto c : editor->undo_stack) 
        cout << "  " << typeid(c).name() << " - " << &c << endl;
};

int main() {
    Document doc = Document();
    TextEditor editor {};
    InsertTextCommand command0 = InsertTextCommand(editor._doc, "Hello", 0);
    editor.execute_command(command0);
    editor.show_document();
    // display_editor_stacks(&editor);
    // InsertTextCommand command1 = InsertTextCommand(editor._doc, " World", 4);
    // editor.execute_command(command1);
    // editor.show_document();
    // display_editor_stacks(&editor);
}