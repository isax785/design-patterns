# OOP Design

Overview:

- [[#OOP Design General Aspects|OOP Design General Aspects]]
	- [[#OOP Design General Aspects#Graphical Notation|Graphical Notation]]
	- [[#OOP Design General Aspects#Programming to an Interface, not an Implementation|Programming to an Interface, not an Implementation]]
- [[#Reuse Mechanisms|Reuse Mechanisms]]
- [[#How to Select a `DP`|How to Select a `DP`]]
- [[#How to Use a `DP`|How to Use a `DP`]]
- [[#How NOT to use a `DP`|How NOT to use a `DP`]]
- [[#References|References]]

---

## OOP Design General Aspects

`OO` programs:

- are made up of **objects** (i.e. data + procedures | operations | methods);
- an object performs an operation only when it receives a **request | message** from a client;
- operations are the only way to change an object's internal data (i.e. the state is encapsulated).

---

OOP design methodologies:

- write a problem statement, single out nouns/verbs, and create corresponding classes/operations;
- focus on the collaboration and responsibilities in the system;
- model the real world and translate the objects found during the analysis into design.

---

`DP` helps in identifying less-obvious **abstractions** and the objects that can capture them.

---

Aspects and definitions:

- `Granularity`: depends on object size, it needs to be properly defined.
- `Operation's Signature`: name, inputs, and outputs.
- `Interface`: set of all signatures defined by the object operations. It is the complete set of requests that can be sent to the object. They can contain other interfaces as subsets. 

---

![[Pasted image 20240103160323.png]]


- `Type`: name used to denote a particular interface.  It is a description of a set of values and a set of allowed operations on those values.  
  An object may have **multiple** types. Multiple objects can share the same type.
	-  `Data Type`: an attribute of a piece of data that tells a device how the end-user might interact with the data.
- `Subtype`: its interface contains the interface of its super-type (*inheritance*).

---

- `Dynamic Binding`: the **run-time association** of a request to an object and one of its operations [^2]. Issuing a request doesn't commit to a particular implementation until run-time.
- `Polymorphism`: substitute objects that have identical interfaces for each other at run-time.
- `Abstract Class`: a class whose main purpose is to define a common interface for its subclasses.
- `Mixin (mix-in) Class`: a class that's intended to provide an optional interface or functionality to other classes, without having to be parent class of them.

[^2]: when a request is sent to an object, the particular operation that's performed depends on both the request and the receiving object.

---

- `Object's Class`: it defines how the object is implemented. It also defines the object's type.
- `Object's Type`: it refers to the object's interface (i.e. the set of requests to which it can respond).

---

- `Inheritance`[^3]
	- `Class Inheritance`: defines an object's implementation in terms of another object's implementation (a mechanism for code and representation sharing).
	- `Interface Inheritance` (`subtyping`): describes when an object can be used in place of another.

[^3]:  some languages do not make such a distinction.

---

> <u>Objects are known only through their interfaces</u>. There is no way to know anything about an object or to ask it to do anything without going through its interface. An object's interface says nothing about its implementation (i.e. two objects having completely different implementations can have identical interfaces).

---

`DP`s help you define interfaces by identifying their key elements and the kinds of data that get sent across an interface. A design pattern might also tell you what not to put in the interface. `DP`s also specify relationships between interfaces.

---
### Graphical Notation

![[Pasted image 20240529100511.png]]

`Type`s are optional, since the programming language can be *dynamically typed* (i.e. types are defined at runtime, e.g. Python, JS).

---

![[Pasted image 20240529100534.png]]

---

![[Pasted image 20240529100555.png]]

---

![[Pasted image 20240529100615.png]]

---

![[Pasted image 20240529100640.png]]

---

![[Pasted image 20240529115229.png]]

---

### Programming to an Interface, not an Implementation

**Class inheritance**:
- extends an application's functionality by reusing functionality in parent classes;
- defines a new kind of object rapidly in terms of an old one;
- gets new implementations almost for free, inheriting most of what you need from existing classes.

---

**Interface inheritance**:
- from an *abstract class*;
- all classes derived from an abstract class will share its interface (**polymorphism**).
- PROS of manipulating objects solely in terms of the interface:
	- Clients remain unaware of the specific types of objects they use, as long as the objects adhere to the interface that clients expect. 
	- Clients remain unaware of the classes that implement these objects. Clients only know about the abstract class(es) defining the interface.
- reduces implementation dependencies between subsystems.

---

> OOP Principle: <u>Program to an interface, not an implementation.</u>

*Don't declare variables to be instances of particular concrete classes. Instead, commit only to an interface defined by an abstract class.*

---

*By abstracting the process of object creation, **creational patterns** give you different ways to associate an interface with its implementation transparently at instantiation.*

Creational patterns ensure that your system is written in terms of interfaces, not implementations.

---
## Reuse Mechanisms

> OOP Principle: <u>favor object composition over class inheritance.</u>

Folow the proper application of concepts like objects, interfaces, classes, and inheritance to build flexible, reusable software.

---

**Inheritance vs Composition**: techniques for reusing functionalities.

- Inheritance (aka `white-box` reuse): define the implementation of one class in terms of another's, the internals of parent classes are often visible to subclasses. *Inheritance breaks encapsulation.*
- Object composition (aka `black-box` reuse): new functionality is obtained by assembling or composing objects to get more complex functionalities.

---

|                    | PROS                                                                                                                                                                                                                                                                                  | CONS                                                                                                                                                                                                              |
| ------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Class Inheritance  | - defined statically at compile-time<br>- straightforward to use (supported by the programming language)<br>- easier to modify the implementation being reused                                                                                                                        | - inherited implementations cannot be changed at run-time<br>- parent classes often define at least part of their subclasses' physical representation<br>- subclass implementation is bounded to its parent's one |
| Object Composition | - defined dynamically at run-time<br>- encapsulation is not broken since objects are accessed solely through their interface<br>- any object can be replaced at run-time by another<br>- fewer implementation dependencies<br>- keeps each class encapsulated and focused on one task | - interfaces of all the object must be designed carefully to ensure their mutual interaction                                                                                                                      |

---

**Delegation**: a way of making composition as powerful for reuse as inheritance. 

- In delegation, two objects are involved in handling a request: <u>a receiving object delegates operations to its delegate</u>. 
- The receiver passes itself to the delegate to let the delegated operation refer to the receiver.

---

  ![[Pasted image 20240108124756.png]]
- *A plain arrowhead line indicates that a class keeps a reference to an instance of another class. The reference has an optional name, "rectangle" in this case.*
- *instead of making class Window a subclass of Rectangle (because windows happen to be rectangular), the Window class might reuse the behavior of Rectangle by keeping a Rectangle instance variable and delegating Rectangle-specific behavior to it.*
---
  ![[Pasted image 20240108124756.png]]
- it makes it easy to compose behaviors at run-time and to change the way they're composed (e.g. replacing `Rectangle` with `Circle`).
- CONS: Dynamic, highly parameterized software is harder to understand than more static software.
- Delegation is an extreme example of object composition: it shows that you can always replace inheritance with object composition as a mechanism for code reuse.

---

**Inheritance vs Parametrized Types**

- Parametrized Types (aka `generics` or `templates`): 
	- define a type without specifying all the other types it uses.
	- a third way (in addition to class inheritance and object composition) to compose behavior in object-oriented systems.

```cpp
// standard
int sum_int(int a, int b) {
    return a + b;
};

// T is our template name, and it's a generic data type
template <class T>    
T sum(T a, T b) {
    return a + b;
};

```

---

**Relating Run-Time and Compile-Time Structures[^1]**

- The code structure is frozen at compile-time (it consists of classes in fixed inheritance relationships).
- An object-oriented program's run-time structure often bears little resemblance to its code structure. 
- A program's run-time structure consists of rapidly changing networks of communicating objects.

[^1]: Compile time is **the period when the programming code (for compiled languages) is converted to the machine code** (i.e. binary code). Runtime is the period of time when a program is running and generally occurs after compile time.

---

- Object relationships[^2]:
	- **Aggregation**: one object owns or is responsible for another object (an object having or being part of another object). An aggregate object and its owner have identical lifetimes.
	- **Acquaintance** (aka association/using relationship): an object merely knows of another object. Acquainted objects may request operations of each other, but they aren't responsible for each other. It is a weaker relationship than aggregation and suggests much looser coupling between objects.

[^2]: It's easy to confuse aggregation and acquaintance, because they are often implemented in the same way.

---

 **Designing for Change**

The key to maximizing reuse lies in anticipating new requirements and changes to existing requirements, and in designing the systems so that they can evolve accordingly (i.e. by considering how the system might need to change over its lifetime).

`DP`s ensure that a system can change in specific ways, by making a system more robust to a particular kind of change.

---

| Redesign Cause                                               | `DP`s                                                                                                                            |
| ------------------------------------------------------------ | -------------------------------------------------------------------------------------------------------------------------------- |
| 1 - Creating an object by specifying a class explicitly.     | Abstract Factory (99), Factory Method (121), Prototype (133).                                                                    |
| 2 - Dependence on specific operations.                       | Chain of Responsibility (251), Command (263).                                                                                    |
| 3 - Dependence on hardware and software platform.            | Abstract Factory (99), Bridge (171).                                                                                             |
| 4 - Dependence on object representations or implementations. | Abstract Factory (99), Bridge (171), Memento (316), Proxy (233).                                                                 |
| 5 - Algorithmic dependencies.                                | Builder (110), Iterator (289), Strategy (349), Template Method (360), Visitor (366).                                             |
| 6 - Tight coupling.                                          | Abstract Factory (99), Bridge (171), Chain of Responsibility (251), Command (263), Facade (208), Mediator (305), Observer (326). |
| 7 - Extending functionality by subclassing.                  | Bridge (171), Chain of Responsibility (251), Composite (183), Decorator (196), Observer (326), Strategy (349).                   |
| 8 - Inability to alter classes conveniently.                 | Adapter (157), Decorator (196), Visitor (366).                                                                                   |

---
## How to Select a `DP`

Multiple approaches:

1. consider how `DP`s solve design problems;
2. scan `DP` intent sections;
3. study how patterns interrelate;
4. study patterns of like purpose;
5. examine a cause of redesign;
6. consider what should be variable in the design.

---

| Purpose    | Design Pattern        | Aspect(s) That Can Vary                 |
| ---------- | --------------------- | --------------------------------------- |
| Creational | Abstract Factory (99) | families of product objects             |
|            | Builder (110)         | how a composite object gets created     |
|            | Factory Method (121)  | subclass of object that is instantiated |
|            | Prototype (133)       | class of object that is instantiated    |
|            | Singleton (144)       | the sole instance of a class            |

---

| Purpose    | Design Pattern                | Aspect(s) That Can Vary                                                                    |
| ---------- | ----------------------------- | ------------------------------------- |
| Structural | Adapter (157)                 | interface to an object                                                                     |
|            | Bridge (171)                  | implementation of an object                                                                |
|            | Composite (183)               | structure and composition of an object                                                     |
|            | Decorator (196)               | responsibilities of an object without subclassing                                          |
|            | Facade (208)                  | interface to a subsystem                                                                   |
|            | Flyweight (218                | storage costs of objects                                                                   |
|            | Proxy (233)                   | how an object is accessed; its location                                                    |

---

| Purpose    | Design Pattern                | Aspect(s) That Can Vary                                                                    |
| ---------- | ----------------------------- | ------------------------------------- |
| Behavioral | Chain of Responsibility (251) | object that can fulfill a request                                                          |
|            | Command (263)                 | when and how a request is fulfilled                                                        |
|            | Interpreter (274)             | grammar and interpretation of a language                                                   |
|            | Iterator (289)                | how an aggregate's elements are accessed, traversed                                        |
|            | Mediator (305)                | how and which objects interact with each other                                             |
|            | Memento (316)                 | what private information is stored outside an object, and when                             |
|            | Observer (326)                | number of objects that depend on another object; how the dependent objects stay up to date |
|            | State (338)                   | states of an object                                                                        |
|            | Strategy (349)                | an algorithm                                                                               |
|            | Template Method (360)         | steps of an algorithm                                                                      |
|            | Visitor (366)                 | operations that can be applied to object(s) without changing their class(es)               |

---
## How to Use a `DP`

Steps for an effective application:

1. Read the pattern once through for an overview (in particular Applicability and Consequences sections). 
2. Go back and study the Structure, Participants, and Collaborations sections.
3. Look at the Sample Code section.
4. Choose names for pattern participants that are meaningful in the application context. 
5. Define the classes.  
6. Define application-specific names for operations in the pattern. 
7. Implement the operations to carry out the responsibilities and collaborations in the pattern.

---
## How NOT to use a `DP`

`DP`s often achieve flexibility and variability by introducing additional levels of indirection, and that can complicate a design and/or cost you some performance. **A design pattern should only be applied when the flexibility it affords is actually needed.** 

---

## References

-  [Inheritance and Composition: A Python OOP Guide](https://realpython.com/inheritance-composition-python/) 