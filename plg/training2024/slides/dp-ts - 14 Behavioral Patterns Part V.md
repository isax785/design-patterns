# Behavioral Patterns - Part V

Overview:

- [[#Observer]]
- [[#State]]

---

# Observer

> **Intent**: Define a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated automatically.

---

Applicability:

- whenever an abstraction has two aspects, one dependent on the other
	- the two aspects will be encapsulated into separated objects
- a change to an object needs to change also others
- an object needing for notifying other objects without knowing them

---

![[Pasted image 20240813151820.png]]

| Who                | What                                                                                                                                                                                                                   |
| ------------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `Subject`          | - know its observers (any number of `Observer` objects may observe a subject)<br>- provides an interface for attaching/detaching `Observer` objects                                                                    |
| `Observer`         | defines an updating interface for objects that should be notified of changes in a subject                                                                                                                              |
| `ConcreteSubject`  | - stores state of interest to `ConcreteObserver` objects<br>- sends a notification to its observers when its state changes                                                                                             |
| `ConcreteObserver` | - maintains a reference to a `ConcreteSubject` object<br>- stores state that should stay consistent with the subject<br>- implements the `Observer` updating interface to keep its state consistent with the subject's |

---

Collaborations:

- `ConcreteSubject` notifies its observers whenever a change occurs that could make its observers' state inconsistent with its own.
- `ConcreteObserver` object may query the subject for information after receiving the information of a change from the subject.

*Notify is not always called by the subject, it can be called by another observer or by another kind of object*

---

Consequences (benefit and liabilities):

- *Abstract coupling between Subject and Observer*: the subject knows only the list of observers (conform to the interface of `Observer` abstract class), not their concrete classes -> **abstract and minimal** coupling:
	- Subject and Observer can belong to different layers of abstraction in a system
	- vary subjects and observer independently
		- reuse subjects without reusing their observers, and viceversa
		- add observers without modifying the subject / other observers

---

- *Support for broadcast communication*: the notification is broadcast automatically to all interested objects that subscribed to it
- *Unexpected updates*: observers have no knowledge of each other presence, so they can be blind to the cost of changes of the subject

---

Implementation (issues):

- *Mapping subjects to their observers*: subject usually stores explicit references to objects it should notify. It could be too expensive. An *associative look-up* that maintains the subject-to-observer mapping is a good solution: it saves spaces, while increasing the time for accessing the observers.

---

- *Observing more than one subject*: sometimes an observer could depend on more than one subject (e.g. more than one data source). `Update` interface should be extended to let the observer know *which* subject is sending the notification.

---

- *Who triggers the update?*: two options for calling `Notify` to trigger the update:
	1. state-settings operations on `Subject` call `Notify` after they change the subject's state
	2. client responsible for calling `Notify` at the right time

---

- *Dangling references to deleted subjects*: avoid dangling effects when deleting a subject by making the subject notify its observer as it is deleted so they can reset their reference to it.
- *Making sure Subject state is self-consistent before notification*: the state of the subject must be consistent before passing it to the observers.

---

- *Avoiding observer-specific update protocols: the push and pull models.* The amount of information that the subject broadcasts to objects via `Update` may vary widely.
	- Push Model: 
		- subject sends detailed information, whether objects want it or not.
		- subject knows something about observers' needs
		- less reusable
	- Pull Model: 
		- subject sends nothing but the most minimal notifications, observers will ask for details.
		- subject does not now anything about the observers
		- inefficiency, observers must check changes without help from the subject

---

- *Specifying modifications of interest explicitly*: update efficiency by allowing subject registering observers only for specific events of interest.
- *Encapsulating complex update semantics*: `ChangeManager` (i.e. instance of `Mediator` pattern), an object that maintains complex relationships between subject and observers by minimizing the work required to make observers reflect a change in their subject (e.g. several interdependent subjects to be modified, **then** the observers will be notified)

---

- `ChangeManager` responsibilities:
	- maps a subject to its observers and maintains this mapping
	- defines a particular update strategy
	- updates all dependent observers at request of a subject

![[Pasted image 20240827153538.png]]

---

- *Combining the Subject and Observer classes*: for languages that lack multiple inheritance, an object that acts as both a subject and an observer without multiple inheritance is defined.

---

Related patterns:

- `Mediator`: `ChangeManager` acts as a `Mediator` between `Subject`s and `Observer`s since it encapsulates complex update semantics
- `Singleton`: the `ChangeManager` may use `Singleton` to make it unique and globally accessible

---

# State

> **Intent**: Allow an object to alter its behavior when its internal state changes. The object will appear to change its class.

---

Applicability:

- an object behavior depends on its state, and it must be changed at run-time
- operations have large, multipart conditional statements that depend on the object's state

---


![[Pasted image 20240827153826.png]]

| Who             | What                                                                                                                                   |
| --------------- | -------------------------------------------------------------------------------------------------------------------------------------- |
| `Context`       | - defines the interface of interest to clients<br>- maintains an instance of a `ConcreteState` subclass that defines the current state |
| `State`         | defines an interface for encapsulating the behavior associated with a particular state of the `Context`                                |
| `ConcreteState` | each subclass implements a behavior associated with a state of the `Context`                                                           |

---
 
Collaborations:

- `Context` delegates state-specific requests to the current `ConcreteState` object
- a `Context` may pass itself as an argument to the `State` object handling the request
- `Context` is the primary interface for clients, that do not have to deal with the `State` object directly
- either `Context` or the `ConcreteState` subclasses can decide which state succeeds another and under what circumstances

---

Consequences:

- *It localizes state-specific behavior and partitions behavior for different states*: The `State` pattern puts all behavior associated with a particular state into one object. New states and transitions can be added easily by adding subclasses.
  Behaviors are distributed, it can result in a less compact implementation than a single class with large conditional statements (to be avoided!). But enhance flexibility and reusability.

---

- *It makes state transitions explicit*: introducing separate objects for different states makes the transitions more explicit (instead of define the object current state in terms of internal values only).
- *State objects can be shared*: as `Flyweight` in case states do not have intrinsic state, only behavior.

---

Implementation (issues):

- *Who defines the state transitions?*:`State` pattern does not specify which participant define the criteria for state transition:
	- Centralization: into `Context`, suitable for fixed criteria.
	- Decentralization: up to `State` subclasses, more flexibility, it requires a `Context` additional interface that lets `State` object set `Context` current state explicitly. Introduces implementation dependencies (`State` classes must know about each other to set the state).

---

 - *A table-based alternative*: (`C++`) use tables to map inputs to state transitions (conversion of conditional code into a table look-up)
	 - Pros: regularity
	 - Cons: less efficient, transition criteria not explicit, difficult to add actions for the state transitions

---

 > The `State` pattern models state-specific behavior, whereas the table-driven approach focuses on defining state transitions.
 
---
 
- *Creating and destroying `State` objects*: trade-off:
	- create `State` objects only when needed and destroy them once finished: states are unknown at run-time, context change state infrequently.
	- create `State` objects before using them and never destroy them: state changes occur rapidly.

---

- *Using dynamic inheritance*: Changing the behavior for a particular request could be accomplished by changing the object's class at run-time (not possible in most OOP languages).

---

Related patterns:

- `Flyweight`: explains when and how `State` objects can be shared.
- `Singletons`: `State` objects are often `Singletons`.

---

