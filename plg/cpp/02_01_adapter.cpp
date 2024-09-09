#include <iostream>

using namespace std;

using namespace std;

struct LegacyService {
    LegacyService() {};
    int return_ten() {
        return 10;
    };
    int return_twenty() {
        return 20;
    }
};
struct LegacyClient {
    LegacyService * _ls;
    LegacyClient(LegacyService * ls) : _ls(ls) {
        cout << "Instantiating a Legacy Client" << endl;
        cout << "Ten:    " << _ls->return_ten() << endl;
        cout << "Twenty: " << _ls->return_twenty() << endl;
    };
};

struct NewService {
    virtual void fetch_data()=0;
};

struct AdapterObject : public NewService {
    LegacyService* _ls;
    AdapterObject(LegacyService* ls): _ls(ls) {
        cout << "Instantiating a New Client (Object)" << endl;
    };
    void fetch_data() override {
        int ten = _ls->return_ten();
        int twenty = _ls->return_twenty();
        cout << "Ten:    " << ten * 100 << endl;
        cout << "Twenty: " << twenty * 100 << endl;
    };
};

struct AdapterClass : public NewService, public LegacyService {
    AdapterClass() {
        cout << "Instantiating a New Client (Class)" << endl;
    };
    void fetch_data() override {
        int ten = return_ten();
        int twenty = return_twenty();
        cout << "Ten:    " << ten * 1000 << endl;
        cout << "Twenty: " << twenty * 1000 << endl;
    };
};

int main() {
    LegacyService* ls = new LegacyService();
    LegacyClient* lc = new LegacyClient(ls);
    NewService* ao = new AdapterObject(ls);
    ao->fetch_data();
    NewService* ac = new AdapterClass();
    ac->fetch_data();
    return 0;
}