#include <iostream>
#include <string>

using namespace std;

enum LEVEL {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    UNHANDLED
};

struct Logger {
    Logger* _next_logger;
    // Logger() { _next_logger=nullptr; };
    Logger(Logger* nl=nullptr) : _next_logger(nl) {};

    bool virtual can_handle(LEVEL lvl)=0;
    void virtual write(string message)=0;

    void set_next(Logger* nl) { _next_logger=nl; };
    void handle(string message, LEVEL lvl) {
        if (can_handle(lvl)) write(message);
        else if (_next_logger) _next_logger->handle(message, lvl);
        else cout << "No one can handle this message: " << message << endl;
    }
};

struct DebugLogger : public Logger {
    DebugLogger(Logger* nl=nullptr) : Logger(nl) {};
    bool can_handle(LEVEL lvl) override {
        if (lvl==DEBUG) return true;
        return false;
    }
    void write(string message) override {
        cout << "[DEBUG]: " << message << endl;
    }
};
struct InfoLogger : public Logger {
    InfoLogger(Logger* nl=nullptr) : Logger(nl) {};
    bool can_handle(LEVEL lvl) override {
        if (lvl==INFO) return true;
        return false;
    }
    void write(string message) override {
        cout << "[INFO]: " << message << endl;
    }
};
struct WarningLogger : public Logger {
    WarningLogger(Logger* nl=nullptr) : Logger(nl) {};
    bool can_handle(LEVEL lvl) override {
        if (lvl==WARNING) return true;
        return false;
    }
    void write(string message) override {
        cout << "[WARNING]: " << message << endl;
    }
};
struct ErrorLogger : public Logger {
    ErrorLogger(Logger* nl=nullptr) : Logger(nl) {};
    bool can_handle(LEVEL lvl) override {
        if (lvl==ERROR) return true;
        return false;
    }
    void write(string message) override {
        cout << "[ERROR]: " << message << endl;
    }
};

int NM = 5;

int main() {

    ErrorLogger* error_logger = new ErrorLogger();
    WarningLogger* warning_logger = new WarningLogger(error_logger);
    InfoLogger* info_logger = new InfoLogger(warning_logger);
    DebugLogger* debug_logger = new DebugLogger(info_logger);
    string msg[NM] = {"Debug Message!",
                      "Info Message!", 
                      "Warning Message!", 
                      "Error Message!", 
                      "Unhandled!"
                      };
    LEVEL lvls[NM] = {DEBUG,
                      INFO,
                      WARNING,
                      ERROR,
                      UNHANDLED
                      };
    for (int i=0; i<NM; i++) {
        // cout << i << endl;
        debug_logger->handle(msg[i], lvls[i]);
        }
}