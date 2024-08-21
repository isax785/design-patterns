#include <iostream>

using namespace std;

enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

class MapSite {
    public:
        virtual void Enter() = 0;
};

class Wall : MapSite {
    public:
        void Enter() {cout << "You just ran into a wall." << endl;}
};

class Room : MapSite {
    private:
        int _roomNumber;
        MapSite* _sides[4] = {NULL};
    public:
        Room(int rn) : _roomNumber {rn} {} 
        MapSite* GetSide(Direction d) const {
            return _sides[d];
        }
        void SetSide(Direction d, MapSite* ms) {
            _sides[d] = ms;
        }
        void Enter() {cout << "Entering room " << _roomNumber << endl;}
};

class Door : MapSite {
    private:
        Room* _room1;
        Room* _room2;
        bool _isOpen = false;
    public:
        Door(Room *r1, Room *r2) : _room1 {r1}, _room2 {r2} {}
        Room * OtherSideFrom(Room * room) {
            if (room == _room1) return _room2;
            else if (room == _room2) return _room1;
            else return NULL;
        };
        void Enter() {
            if (_isOpen) cout << "You pass throught the door" << endl;
            else cout << "The door is closed." << endl;
        };
        void Open() {
            _isOpen = true;
        }
        void Close() {
            _isOpen = false;
        }
};

class Maze {
    private:
        Room * _rooms[10];
    public:
        void AddRoom(Room * room);
        Room* RoomNo(int rn);
};

int main() {
    Wall wall;
    wall.Enter();
    Room room {0};
    // cout << typeid(room.GetSide(EAST)).name();
}