#include "dp_includes.h"

struct TCPConnection;

struct TCPState {
    virtual void open(TCPConnection &context)=0;
    virtual void close(TCPConnection &context)=0;
    virtual void aknowledge(TCPConnection &context)=0;
};

struct TCPOpen: public TCPState {
    void open(TCPConnection &context) override {
        cout << "TCP connection is already open." << endl;
    };
    void close(TCPConnection &context);
    void aknowledge(TCPConnection &context) override {
        cout << "Acknowledging data in TCP connection." << endl;
    };
};

struct TCPClosed: public TCPState {   
    void open(TCPConnection &context);
    void close(TCPConnection &context) override {
        cout << "TCP connection is already closed." << endl;
    };
    void aknowledge(TCPConnection &context) override {
        cout << "Can't aknowledge, TCP connection is closed." << endl;
    };
};

struct TCPListen: public TCPState {
    void open(TCPConnection &context) override {
        cout << "TCP connection is already open and listening." << endl;
    };
    void close(TCPConnection &context);
    void aknowledge(TCPConnection &context);
};

struct TCPConnection {
    TCPState *_state;
    TCPConnection() : _state(new TCPClosed()) {};
    void set_state(TCPState &state) { _state = &state; }
    void open() { _state->open(*this); }
    void close() { _state->close(*this); }
    void aknowledge() { _state->aknowledge(*this); }
};

void TCPOpen::close(TCPConnection &context) {
        cout << "Closing TCP connection." << endl;
        TCPClosed new_state = TCPClosed();
        context.set_state(new_state);
};

void TCPClosed::open(TCPConnection &context) {
        cout << "Opening TCP connection." << endl;
        TCPListen new_state = TCPListen();
        context.set_state(new_state);
};

void TCPListen::close(TCPConnection &context) {
        cout << "Closing TCP connection from listening state." << endl;
        TCPClosed new_state = TCPClosed();
        context.set_state(new_state);
};

void TCPListen::aknowledge(TCPConnection &context) {
        cout << "Acknowledging data in TCP connection from listening state." << endl;
        TCPOpen new_state = TCPOpen();
        context.set_state(new_state);
};


int main() {
    TCPConnection connection = TCPConnection();
    connection.open();
    connection.aknowledge();

}