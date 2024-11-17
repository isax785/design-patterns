#include "dp_includes.h"

struct Observer {
    virtual void update()=0;
};

struct Subject {
    virtual void register_observer()=0;
    virtual void remove_observer()=0;
    virtual void notify_observer()=0;
};

struct ConcreteObserver {

};

struct ConcreteSubject {

};

int main() {

}