# Behavioral Patterns - Part VI

Overview:

- [[#Visitor]]
- [[#Behavioral Patterns Discussion]]


---

# Visitor


> **Intent**: Represent an operation to be performed on the elements of an object structure. It allows defining a new operation without changing the classes of the elements on which it operates.

---

Applicability:

- dealing with an object structure that contains many classes of objects with differing interfaces and the operations on these objects depend on their concrete class
- the class defining the object structure rarely change, but new operations over the structure are to be defined

---

- many distinct and unrelated operations need to be performed on objects in an object structure, and avoiding "polluting" the classes with these operations
	- keep related operations together into one class

---

![[Pasted image 20240828161246.png]]

| Who               | What                                                                                                                                                                                     |
| ----------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `Visitor`         | declares a `Visit` operation for each class of `ConcreteElement` in the object structure                                                                                                 |
| `ConcreteVisitor` | implements each operation declared by `Visitor`                                                                                                                                          |
| `Element`         | defines an `Accept` operation that takes a visitor as an argument                                                                                                                        |
| `ConcreteElement` | implements an `Accept` operation that takes a visitor as an argument                                                                                                                     |
| `ObjectStructure` | - can enumerate its elements<br>- may provide a high-level interface to allow the visitor to visit its elements<br>- may either be a `Composite` or a collection such as a list or a set |
 
---

Collaborations:

- client creates `ConcreteVisitors` object and then traverse the object structure, by visiting each element with the visitor
- when an `Element` is visited, it calls the `Visitor` operation corresponding to its class.
- if needed, the `Element` supplies itself as an argument to this operation to let the visitor access its state

---

Consequences (benefits and liabilities):

- *Visitor makes adding new operations easy*: new operations that depend on the components of complex objects can be added easily. It is possible to define new operation over an object structure simply by adding a new visitor (instead of upgrading all the classes)

---

- *A visitor gathers related operations and separates unrelated ones*: related behavior is localized into the visitor (and not spread over the classes). Unrelated behaviors are partitioned in their own visitor subclasses.

---

- *Adding new `ConcreteElement` classes is hard*: because each new `ConcreteElement` gives rise to new abstract operation on `Visitor` and corresponding implementation in every `ConcreteVisitor` class (default can be provided whenever acceptable).

---

- *Visiting across class hierarchies*: while an `Iterator` can only visit objects belonging to the same type, `Visitor` can visit objects that do not have common parent class.
- *Accumulating state*: `Visitor`s can accumulate state as they visit each element.

---

- *Breaking encapsulation*: `ConcreteElement` encapsulation can be compromised because they must provide public operations to access the internal state.

---

Implementation (issues):

- *Double dispatch*: `Visitor` pattern lets adding operations to classes without changing them via **double-dispatch** technique (i.e. the operation that gets executed depends on the request kind and types of two receivers) for the languages that allow it. 
	- `C++` support **single-dispatch** only, i.e. which operation will fulfill the request depends on the name of the request and the type of the receiver.

---

- *Who is responsible for traversing the object structure?*: the responsibility for traversal can be put in any of three places: in the object structure (often responsible for iteration), in the visitor, or in a separate iterator object.

---

Related patterns:

- `Composite`: `Visitor` can apply an operation over a `Composite` object structure
- `Interpreter`: `Visitor` can be applied to do the interpretation

---

# Behavioral Patterns Discussion

- [[#Encapsulation Variation]]
- [[#Object as Argument]]
- [[#Communication Encapsulated or Distributed?]]
- [[#Decoupling Senders and Receivers]]

---
## Encapsulation Variation

Encapsulating variation is a theme of many behavioral patterns. When an aspect of a program changes frequently, these patterns define an object that encapsulates that aspect.

---

Encapsulations:

- `Strategy` object -> algorithm
- `State` object -> state-dependent behavior
- `Mediator` object -> protocol between objects
- `Iterator` object -> the way accessing and traversing components of an aggregate object

---

These patterns describe aspects of a program that are likely to change. Most patterns have two kinds of objects: 

- the new object(s) that encapsulate the aspect
- the existing object(s) that use the new ones

---

`Chain of Responsibility` is different since it does not define static communication relationships between classes. Differently, it prescribes communication between an open-ended number of objects. Other patterns involve objects that are passed around as arguments.

---

## Object as Argument

Several patterns introduce an object that's *always* used as an argument (e.g. `Visitor`).

Other patterns define objects that act as magic tokens to be passed around and invoked at a later time (e.g. `Command`, `Memento`).

---

## Communication: Encapsulated or Distributed?

- `Observer` distributes communication by introducing `Observer` and `Subject` objects
- `Mediator` object encapsulates the communication between other objects

---

Communication patterns are determined by the way observers and subjects are interconnected: a single subject usually has many observers, and sometimes the observer of one subject is a subject of another observer.

---

The `Mediator` pattern centralizes rather than distributes. It places the responsibility for maintaining a constraint squarely in the mediator.

---

The `Observer` pattern promotes partitioning and loose coupling between Observer and Subject, and that leads to finer-grained classes that are more apt to be reused.

---
## Decoupling Senders and Receivers

When collaborating objects refer to each other directly, they become dependent on each other, and that can have an adverse impact on the layering and reusability of a system. 

---

- `Command` supports decoupling by using a `Command` object to define the binding between a sender and receiver, defining the sender-receiver connection in a separate object lets the sender work with different receivers (keeps the sender decoupled from the receivers, easy to reuse)

---

- `Observer` decouples senders (subjects) from receivers (observers) by defining an interface for signaling changes in subjects, best for decoupling objects when there are data dependencies between them since it is designed for communicating changes

---

- `Mediator` decouples objects by having them refer to each other indirectly through a `Mediator` object, it routes requests between Colleague objects and centralizes their communication. It reduces subclassing.

---

- `Chain of Responsiblity` decouples the sender from the receiver by passing the request along a chain of potential receivers

---