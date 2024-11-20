#include <iostream>
#include <string>
#include <algorithm> 

using namespace std;

struct TextFormatter {
    virtual string format(string& text)=0;
};

struct UpperCaseFormat : public TextFormatter {
    string format(string& text) override {
        for (auto & c: text) c = toupper(c);
        return text;
    }
};

struct LowerCaseFormat : public TextFormatter {
    string format(string& text) override {
        for (auto & c: text) c = tolower(c);
        return text;
    }
};

struct TitleCaseFormat : public TextFormatter {
    string format(string& text) override {
        bool newWord = true;

        for (size_t i = 0; text[i] != '\0'; ++i) {
            if (std::isspace(text[i])) {
                newWord = true;
            } else if (newWord) {
                text[i] = std::toupper(text[i]);
                newWord = false;
            } else {
                text[i] = std::tolower(text[i]);
            }
        }
        return text;
    }
};

struct TextEditor {
    private:
        TextFormatter* _formatter;
    public:
        TextEditor(TextFormatter* formatter) : _formatter(formatter) {}
        void set_formatter(TextFormatter* formatter) {_formatter = formatter;}
        string publish_text(string& text) {return _formatter->format(text);}    
};

int main() {
    TextFormatter* upper_formatter = new UpperCaseFormat();
    TextFormatter* lower_formatter = new LowerCaseFormat();
    TextFormatter* title_formatter = new TitleCaseFormat();

    string text = "this is the text to be formatted";
    TextEditor editor (upper_formatter);
    cout << editor.publish_text(text) << endl;

    editor.set_formatter(lower_formatter);
    cout << editor.publish_text(text) << endl;
    editor.set_formatter(title_formatter);
    cout << editor.publish_text(text) << endl;


    return 0;
}
