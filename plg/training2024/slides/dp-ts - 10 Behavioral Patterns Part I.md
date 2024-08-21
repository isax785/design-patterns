# Behavioral Patterns - Part I

Overview:

- [[#Chain of Responsibility]]
- [[#Command]]

---

# Chain of Responsibility


> **Intent**: Avoid coupling the sender of a request to its receiver by giving more than one object a chance to handle the request. Chain the receiving objects and pass the request along the chain until an object handles it.

---

Applicability:

- more than one object may handle a request, and the handler isn't known a priori. The handler should be ascertained automatically.
- to issue a request to one of several objects without specifying the receiver explicitly. 
- the set of objects that can handle a request should be specified dynamically.

---

![[Pasted image 20240805112701.png]]

| Who               | What                                                                                                                                                  |
| ----------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------- |
| `Handler`         | - defines an interface for handling requests.<br>- (optional) implements the successor link.                                                          |
| `ConcreteHandler` | - handles requests it is responsible for.<br>- can access its successor. <br>- if the `ConcreteHandler` can handle the request, it does so; otherwise |
| `Client`          | initiates the request to a ConcreteHandler object on the chain.                                                                                       |

---

Typical object structure:

![[Pasted image 20240805112753.png]]

---

Collaborations:

- When a client issues a request, the request propagates along the chain until a `ConcreteHandler` object takes responsibility for handling it.

---

Consequences (benefits and liabilities):

- *Reduced coupling*: both the receiver and the sender have no explicit knowledge of each other, and each object in the chain does not have to know the chain structure

---

- *Added flexibility in assigning responsibilities to objects*: it is possibile to add or change responsibilities for handling a request by adding to or changing the chain at run-time. Combine with subclassing to specialize handlers statically.
- *Receipt isn't guaranteed*: since the request has no explicit receiver, it can fall off the end of the chain without ever being handled.

---

Implementation (issues):

- *Implementing the successor chain*: two possible ways:
	1. define new links: the structure does not reflect the chain required, redundant links are needed.
	2. use existing links: when the links support the needed chain, it saves space.
- *Connecting successors*: references needs to be introduced when there are no preexisting references for defining the chain. In that case, the `Handler` defines the interface for the requests and maintains the successor.

---

- *Representing requests*: multiple options:
	- the request is a hard-coded operation invocation: simplest form, convenient, and safe, by only the fixed set of requests defined by `Handler` class can be forwarded;
	- use single handler function that takes the request code as parameter: supports open-ended set of requests. Sender and receiver must agree on how the request should be coded. More flexible approach, but requires conditional statements. 

---

Related patterns:

- `Composite`: often applied in conjunction.

---

# Command

> **Intent**: Encapsulate a request as an object, thereby letting you parameterize clients with different requests, queue or log requests, and support undoable operations.

---

Applicability:

- parameterize objects by an action to perform
- specify, queue, and execute requests at different times
- support undo (the `Command`'s `Execute` operation can store state for reversing its effects in the command itself, the `Command` interface must have an added `Unexecute` operation that reverses the effects of a previous call to `Execute`)
- support logging changes
- structure a system around high-level operations built on primitives operations (e.g. with transactions, that encapsulates a set of changes to data)

---

![[Pasted image 20240805171605.png]]

| Who               | What                                                                                                                                             |
| ----------------- | ------------------------------------------------------------------------------------------------------------------------------------------------ |
| `Command`         | declares an interface for executing an operation                                                                                                 |
| `ConcreteCommand` | - defines a binding between a `Receiver` object and an action<br>- implements `Execute` by invoking the corresponding operation(s) on `Receiver` |
| `Client`          | creates a `ConcreteCommand` object and sets its receiver                                                                                         |
| `Invoker`         | asks the command to carry out the request                                                                                                        |
| `Receiver`        | knows how to perform the operations associated with carrying out a request. Any class may serve as a `Receiver`                                  |

---

Collaborations:

- The client creates a `ConcreteCommand` object and specifies its receiver. 
- An `Invoker` object stores the `ConcreteCommand` object.
- The invoker issues a request by calling `Execute` on the command. When commands are undoable, `ConcreteCommand` stores state for undoing the command prior to invoking `Execute`. 
- The `ConcreteCommand` object invokes operations on its receiver to carry out the request.

---

Consequences:

1. `Command` decouples the object that invokes the operation from the one that knows how to perform it. 
2. `Command`s are first-class objects. They can be manipulated and extended like any other object. 
3. `Command`s can be assembled into a composite command. An example is the `MacroCommand` class described earlier. In general, composite commands are an instance of the `Composite` pattern. 
4. It's easy to add new `Command`s, because you don't have to change existing classes.

---

Implementation (issues):

- *Command intelligence*: in the middle between:
	- defining a binding between a receiver and the actions that carry out the request
	- implementing everything itself without delegating to a receiver at all
- *Supporting undo and redo*: if they provide a way to reverse their execution (e.g. `Unexecute` or `Undo` operation). A `ConcreteCommand` may need to store additional states to do so. For multiple undo levels, a **history list** is needed.
- *Avoiding error accumulation in the undo process*: errors can accumulate as commands are executed/unexecuted repeatedly.
- *Using C++ templates*

---

Related patterns:

- `Composite` can be used to implement `MacroCommands`
- `Memento` can keep state the command requires to undo its effect
- `Prototype` for a command that must be copied before being placed on the history list

