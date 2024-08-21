# Structural Patterns - Part I

Overview: 

- [Adapter](#adapter)
- [Bridge](#bridge)
- [Composite](#composite)

---

## Adapter


> **Intent**: Convert the interface of a class into another interface clients expect (i.e. implements interfaces compatibility).

---

Applicability:

- use an existing class whose interface does not match the needed one
- create a reusable class that cooperates with unrelated or unforeseen classes that not necessarily have compatible interface
- (*object adapter only*) use several existing subclasses, but it's impractical to adapt their interface by subclassing every one. -> *the object adapter can adapt the interfaces of its parent class*

---

Structure:

- **Class Adapter**: uses multiple inheritance to adapt one interface to another

![[Pasted image 20240708114204.png]]

| Who       | What                                                           |
| --------- | -------------------------------------------------------------- |
| `Target`  | defines the domain-specific interface used by the `Client`     |
| `Client`  | collaborates with objects conforming to the `Target` interface |
| `Adaptee` | defines an existing interface that needs adapting              |
| `Adapter` | adapts the interface of `Adaptee` to the `Target` interface    |
 
---

- **Object Adapter**: relies on object composition

![[Pasted image 20240708114217.png]]

| Who       | What                                                           |
| --------- | -------------------------------------------------------------- |
| `Target`  | defines the domain-specific interface used by the `Client`     |
| `Client`  | collaborates with objects conforming to the `Target` interface |
| `Adaptee` | defines an existing interface that needs adapting              |
| `Adapter` | adapts the interface of `Adaptee` to the `Target` interface    |

---

Collaborations:

- Client calls `Adapter` that in turn calls `Adaptee`

---

Consequences: **class** adapter
- adapts `Adaptee` to `Target` by committing to a concrete `Adapter` class. As a consequence, a class adapter won't work when we want to adapt a class and all its subclasses.
- lets `Adapter` override some of `Adaptee`'s behavior, since `Adapter` is a subclass of `Adaptee`.
- introduces only one object, and no additional pointer indirection is needed to get to the adaptee.

---

Consequences:  **object** adapter
- lets a single Adapter work with many `Adaptee`s—that is, the `Adaptee` itself and all of its subclasses (if any). The Adapter can also add functionality to all `Adaptee`s at once. 
- makes it harder to override `Adaptee` behavior. It will require subclassing `Adaptee` and making Adapter refer to the subclass rather than the `Adaptee` itself.

---

Implementation:

- The amount of work Adapter does depends on how similar the Target interface is to `Adaptee`'s.
- *Pluggable adapters*: interface adaptation lets us incorporate our class into existing systems that might expect different interfaces to the class.
- Using two-way adapters to provide transparency. Adapters are not transparent to all clients.

---


Related patterns:

- `Bridge`
- `Decorator`
- `Proxy`

---
## Bridge

> **Intent**: decouple an abstraction from its implementation so that the two can vary independently.

---

Applicability:

- avoid permanent binding between an abstraction and its implementation (e.g. implementation to be selected/switched at runtime)
- both abstractions and their implementations should be extensible by subclassing
- abstraction implementation changes should have no impact on clients
- (C++) hide the implementation of an abstraction completely from clients
- in case of proliferation of classes
- share an implementation among multiple objects, and this should be hidden from the client

---

![[Pasted image 20240708114315.png]]

| Who                   | What                                                                                                                       |
| --------------------- | -------------------------------------------------------------------------------------------------------------------------- |
| `Abstraction`         | - defines the abstraction interface<br>- maintains a reference to an object of type `Implementor`                          |
| `RefinedAbstraction`  | extends the interface defined by `Abstraction`                                                                             |
| `Implementor`         | defines the interface for implementation classes, this interface does not have to correspond exactly to `Abstraction`s one |
| `ConcreteImplementor` | implements the `Implementor` interface and defines its concrete implementation                                             |

---

Collaborations:

- `Abstraction` forwards client requests to its `Implementor` object

---

Consequences:

- *Decoupling interface and implementation*: the implementation is not bound permanently to an interface.
	- abstraction implementation can be configured at run-time
	- an object can change its implementation at run-time
	- eliminates compile-time dependencies: changing an implementation does not require recompiling the `Abstraction` class and its client (i.e. binary compatibility between different versions of a class library)
	- layering that can lead to a better structured system

---

- *Improved extensibility*: `Abstraction` and `Implementor` hierarchies can be extended independently
- *Hiding implementation details from clients*

---


Implementation:

- *Only one `Implementor`*: the `Bridge` pattern is not needed in situations where there is only one implementation (no abstract class needed)

---

- *Creating the right `Implementor` object*: approaches to instantiate the right `Implementor` class:
	1. decide between multiple `ConcreteImplementor` classes by passing dedicated parameters to the `Abstraction` constructor
	2. choose a default implementation initially and change it later according to usage
	3. delegate the decision to another object altogether

---

- *Sharing `Implementor`s
- *Using multiple inheritance*: to combine and interface with its implementation.

---

Related patterns:

- `AbstractFactory`
- `Adapter` 

---
## Composite

> **Intent**: composes objects into tree structures to represent part-whole hierarchies. `Composite` lets clients treat individual objects and compositions of objects uniformly.

---
![[Pasted image 20240712183132.png]]

---

![[Pasted image 20240708114610.png]]

| Who         | What                                                                                                                                                                                                                                                                                                                                                   |
| ----------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `Component` | - declares the interface for objects in the composition<br>- implements default behavior fo the interface common to all classes<br>- declares an interface for accessing and managing its child components<br>- (optional) defines an interface for accessing a component's parent in the recursive structure, and implements it if that's appropriate |
| `Leaf`      | - represents leaf objects in the composition (a leaf has no children)<br>- defines behavior for primitive objects in the composition                                                                                                                                                                                                                   |
| `Composite` | - defines behavior for components having children<br>- stores child components<br>- implements child-related operations in the `Component` interface                                                                                                                                                                                                   |
| `Client`    | - manipulates objects in the composition through the `Component` interface                                                                                                                                                                                                                                                                             |

---

Collaborations:

- `Client`s use the `Component` class interface to interact with objects in the composite structure
	- recipient is a **Leaf**: the request is handled directly
	- recipient is a **Composite**: the request is forwarded to its child components, possibly performing additional operations before and/or after forwarding

---

Consequences:

- defines class hierarchies consisting of primitive objects and composite objects. Primitive objects can be composed recursively to create more complex (i.e. composite) objects
- makes the client simple since it can treat composite structures and individual objects uniformly
- easy to add new kind of components (the structure is defined yet)
- can make the design overly general: making it easy to add new components brings disadvantages in restricting their number.

---

Implementation:

- *Explicit parent references*: references from child components to their parent is maintained. Such reference is usually placed into the `Component` class.
- *Sharing components*: It is often useful to share components (e.g. reduce storage requirements). A possible solution is for children to store multiple parents, can lead to ambiguities.

---

- *Maximizing the `Component` interface*: to make clients unaware of the specific Leaf or Composite classes they are using, the `Component` class should define as many common operations for `Composite` and `Leaf` classes as possible.
- *Declaring the child management operations*: the `Add` and `Remove` operations for managing children must be declared in the `Composite` class hierarchy:
	- defined in the root of the class hierarchy (i.e. methods defined externally to the class): transparency, but costs safety
	- defined in the `Composite` class (i.e. methods defined into the class): safety, loose of transparency

---

- *Should `Component` implement a list of `Component`s?*: putting the child pointer in the base class incurs a space penalty for every leaf. Convenient only when there are few children in the structure.
- *Child ordering*: designs that specify ordering on the `Composite` children (e.g. GUI front-to-back). When child ordering is an issue, child access and management interfaces must be designed carefully.

---

- *Caching to improve performance*: cache traversal or search information about its children in the `Composite` class if there is the need for traverse/search compositions frequently. Changes to a component will require invalidating the caches of its parents.
- *Who should delete components?*: in languages without garbage collection, it's usually best to make a `Composite` responsible for deleting its children when it's destroyed.
- *What's the best data structure for storing components?*: the choice for data structure depends on efficiency.

---

Related patterns:

- `Chain of Responsibility`
- `Decorator`
- `Flyweight`
- `Iterator`
- `Visitor`