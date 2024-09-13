#include <iostream>
#include <string>

using namespace std;

struct TextFormatter {
    virtual string format(string& text)=0;
};

struct UpperCaseFormat : public TextFormatter {
    string format(string& text) override {
        string text_upper = toupper(text.c_str(), locale());
        return text;
    }
};

struct LowerCaseFormat : public TextFormatter {
    string format(string& text) override {
        string text_upper = toupper(text.c_str(), locale());

        return text;
    }
};
// struct TitleCaseFormat : public TextFormatter {
//     string format(string& text) override {}
// };

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
    string text = "this is the text to be formatted";
    TextEditor editor (upper_formatter);
    cout << editor.publish_text(text);

    editor.set_formatter(lower_formatter);
    cout << editor.publish_text(text);


    return 0;
}
