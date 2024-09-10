#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct FileSystemComponent {
    virtual int get_size()=0;
    virtual void display(int indent=0)=0;
};

struct File: public FileSystemComponent {
    int _size;
    string _name;
    File(string name, int size): _name(name), _size(size) {};
    int get_size() override {
        return _size;
    }
    void display(int indent=0) {
        cout << string(indent, ' ') << "File: " << _name << " - Size: " << _size << endl;
    }  
};

struct Directory : public FileSystemComponent {
    string _name;
    Directory(string name): _name(name) {};
    vector<FileSystemComponent*> children;
    void add(FileSystemComponent* child) {
        children.push_back(child);
    }

    int get_size() override {
        int size = 0;
        for (int i=0; i<children.size(); i++) size += children[i]->get_size();
        return size;
    }

    void display(int indent=0) override {
        cout << string(indent, ' ') << "Directory: " << _name << " - Size: " << get_size() << endl;
        for (int i=0; i<children.size(); i++) children[i]->display(indent+2);
    }
};

int main() {
    File* f1 = new File("abc.txt", 123);
    File* f2 = new File("abc.txt", 21);
    File* f3 = new File("abc.txt", 423);
    File* f4 = new File("abc.txt", 5);
    File* f5 = new File("abc.txt", 43);
    File* f6 = new File("abc.txt", 567);
    Directory* d1 = new Directory("dir-1");
    Directory* d2 = new Directory("dir-2");
    Directory* d3 = new Directory("dir-3");
    d1->add(f1);
    d1->add(f2);
    d2->add(d1);
    d2->add(d3);
    d2->add(f3);
    d2->add(f4);
    d2->add(f5);
    d3->add(f6);
    d2->display();
    return 0;
}