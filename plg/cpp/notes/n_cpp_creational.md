# C++ Creational Patterns

- [C++ Creational Patterns](#c-creational-patterns)
  - [Prototype](#prototype)

---

C++ scripts and snippets from the book **Design Patterns - Elements of Reusable Object-Oriented Software**.

## Prototype

Example based on `MazeFactory`. A `MazePrototypeFactory` augments the `MazeFactory` interface with a constructor that takes the prototypes as arguments: 

```cpp
class MazePrototypeFactory : public MazeFactory { 
    public: 
        MazePrototypeFactory(Maze*, Wall*, Room*, Door*); 
        virtual Maze* MakeMaze() const; 
        virtual Room* MakeRoom(int) const; 
        virtual Wall* MakeWall() const; 
        virtual Door* MakeDoor(Room*, Room*) const; 
    private: 
        vMaze* _prototypeMaze; Room* _prototypeRoom; 
        Wall* _prototypeWall; Door* _prototypeDoor; 
};
```

The new constructor simply initializes its prototypes: 

```cpp
MazePrototypeFactory::MazePrototypeFactory ( Maze* m, Wall* w, Room* r, Door* d ) {
    _prototypeMaze = m; 
    _prototypeWall = w; 
    _prototypeRoom = r; 
    _prototypeDoor = d; 
} 
```

The member functions for creating walls, rooms, and doors are similar: Each clones a prototype and then initializes it. Here are the definitions of MakeWall and MakeDoor: 

```cpp
Wall* MazePrototypeFactory::MakeWall () const { 
    return _prototypeWall->Clone(); 
    } 

Door* MazePrototypeFactory::MakeDoor (Room* r1, Room *r2) const { 
    Door* door = _prototypeDoor->Clone(); 
    door->Initialize(r1, r2); 
    return door; 
}
```

We can use `MazePrototypeFactory` to create a prototypical or default maze just by initializing it with prototypes of basic maze components: 

```cpp
MazeGame game; 
MazePrototypeFactory simpleMazeFactory( 
    new Maze, new Wall, new Room, new Door 
    );
```