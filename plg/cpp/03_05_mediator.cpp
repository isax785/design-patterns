#include "dp_includes.h"
#include <chrono>
#include <ctime>  

string current_datetime() {
    auto now = std::chrono::system_clock::now();
    std::time_t datetime = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&datetime);
}

// to be declared first to avoid circular-reference issues
struct ChatRoom; 

struct User {
    string _name;
    ChatRoom* _chat;
    User(string name, ChatRoom* chat) : _name(name), _chat(chat) {}
    string get_name() { return _name; }
    void send(string message);
};

struct ChatRoom {
    void show_message(User &user, string message) {
        string sender = user.get_name();
        string datetime = current_datetime();
        cout << datetime << sender << ": " << message << endl;
    }
};

void User::send(string message) { _chat->show_message(*this, message); };

int main() {
    ChatRoom *chat = new ChatRoom();
    User user1 ("Batman", chat);
    User user2 ("Robin", chat);

    user2.send("Hello Bat!");
    user1.send("WTF r u doin?!");
}