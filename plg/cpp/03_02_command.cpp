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
        // cout << "DBG: " << content.size() << endl; // DEBUG
        content = content.substr(0, position) + 
                  text + 
                  content.substr(position);
        
        // cout << "DBG: " << content.size() << endl; // DEBUG
        // cout << "DBG: " << &content << " " << content << endl; // DEBUG
    }
    string delete_text(int position, int length) {
        string deleted_text = content.substr(position, length);
        cout << "Del txt " << deleted_text << endl;
        content = content.substr(0, position) + content.substr(position+length);
        return deleted_text;
    }
    friend ostream &operator << (ostream &o, const Document &doc) {
        o << doc.content;
        return o;
    }
};

struct InsertTextCommand : public Command {
    Document *_doc;
    string _text;
    int _position;
    InsertTextCommand(Document &doc, string text, int position) :
        _doc(&doc), _text(text), _position(position) {
            // cout << "DBG: doc ptr " << &doc << " " << &_doc << endl; // DEBUG
        };
    void execute() override {
        _doc->insert_text(_text, _position);
        // cout << "DBG-ITex: " << &_doc << " " << _doc->content << endl; // DEBUG
    }
    void undo() override {
        cout << "DBG: undo insert " << _position << endl;
        _doc->delete_text(_position, _text.size());
    }
};

struct DeleteTextCommand : public Command {
    Document *_doc;
    string _deleted_text;
    int _position;
    int _length;
    DeleteTextCommand(Document &doc, int position, int length) :
        _doc(&doc), _position(position), _length(length), _deleted_text("") {
            // cout << "DBG: doc ptr " << &doc << " " << &_doc << endl; // DEBUG
        };
    void execute() override {
        _deleted_text = _doc->delete_text(_position, _length);
        // cout << "DBG-DTex: " << &_doc << " " << _doc->content << endl; // DEBUG
    }
    void undo() override {
        _doc->insert_text(_deleted_text, _position);
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
        // cout << "DBG-SH: " << &_doc << " " << _doc.content << endl; // DEBUG
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
    TextEditor editor;
    
    InsertTextCommand command0 = InsertTextCommand(editor._doc, "Hello", 0);
    editor.execute_command(command0);
    editor.show_document();

    InsertTextCommand command1 = InsertTextCommand(editor._doc, " World", 5);
    editor.execute_command(command1);
    editor.show_document();

    display_editor_stacks(&editor);

    editor.undo();
    editor.show_document();
    display_editor_stacks(&editor);

}