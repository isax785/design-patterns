# Behavioral Patterns - Part III

Overview:

- [[#Mediator]]
- [[#Memento]]

---

# Mediator

> **Intent**: Define an object that encapsulates how a set of objects interact. Mediator promotes loose coupling by keeping objects from referring to each other explicitly, and it lets you vary their interaction independently.

---

Applicability:

- a set of objects communicate in well-defined but complex ways (interdependencies are unstructured and difficult to understand)
- reusing an object is difficult because it refers to and communicates with many other objects.
- a behavior that's distributed between several classes should be customizable without a lot of subclassing.

---

![[Pasted image 20240812143205.png]]

| Who                | What                                                                                                                                                                         |
| ------------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `Mediator`         | defines an interface for communicating with `Colleague` objects                                                                                                              |
| `ConcreteMediator` | - implements cooperative behavior by coordinating `Colleague` objects <br>- knows and maintains its colleagues.                                                              |
| `Colleague Class`  | - each `Colleague` class knows its` Mediator` object<br>- each colleague communicates with its mediator whenever it would have otherwise communicated with another colleague |

---

![[Pasted image 20240812143737.png]]

---
 
Collaborations:

- `Colleague`s send and receive requests from a `Mediator` object that implements the cooperative behavior by routing requests between the appropriate colleague(s).

---

Consequences (benefits and drawbacks):

- *It limits subclassing*: `Mediator` localizes behaviors instead of distributing them among several objects. Changes to such behaviors requires subclassing `Mediator` only.
- *It decouples colleagues*: `Mediator` promotes loose coupling between colleagues (`Mediator` and `Colleague` classes can be varied independently).

---

- *It simplifies object protocols*: `Mediator` replaces many-to-many interactions with one-to-many interaction (easier to understand, maintain, and extend).
- *It abstracts how objects cooperate*: `Mediator` encapsulates mediation by making it an independent concept. It allows focusing on how objects interact apart from their individual behavior.
- *It centralizes control*: complexity of interaction is traded for complexity in the `Mediator`.

---

Implementation (issues):

- *Omitting the abstract Mediator class*: no need for an abstract class if colleagues work with one only mediator.
- *Colleague-Mediator communication*: colleagues need to communicate with the mediator when an event occurs, `Mediator` could be implemented as `Observer` that receives the notifications about colleagues state change and propagates the effect of the change to other colleagues.
  Otherwise a specialized notification interface in `Mediator` can be defined.

---

Related patterns:

- `Facade`: it abstracts a subsystem of objects to provide a more convenient interface, its protocol is unidirectional.
- `Observer`: allows the colleagues communicating with the `Mediator`.

---
# Memento

> **Intent**: Without violating encapsulation, capture and externalize an object's internal state so that the object can be restored to this state later.

---

Applicability:

- a snapshot (or a portion of) of an object's state must be saved to be restored later
- a direct interface to obtaining the state would expose implementation details and break the encapsulation

---

![[Pasted image 20240812160530.png]]

| Who          | What                                                                                                                         |
| ------------ | ---------------------------------------------------------------------------------------------------------------------------- |
| `Memento`    | - stores internal state of the `Originator` object<br>- protects against access by objects other than the `Originator`       |
| `Originator` | - creates a memento containing a snapshot of its current internal state<br>- uses the memento to restore its internal state. |
| `Caretaker`  | - is responsible for the memento's safekeeping<br>- never operates on or examines the contents of a memento                  |

---

Collaborations:

- `Caretaker` request `Memento` from `Orginator`, holds it for a time, then passes it back to the `Originator`
	- `Caretaker` won't pass `Memento` back to `Originator` because it might never need to revert to an earlier state
- `Memento`s are passive. `Originator` that created `Memento` will retrieve or assign its state

---

Consequences:

- *Preserving encapsulation boundaries*: `Memento` avoids exposing information that should be managed by `Originator` only.
- *Simplify `Originator`*: `Originator` state to be versioned is external.
- *Using `Memento`s might be expensive*: if large amount of information to store is large, `Memento` might incur overhead.

---

- *Define narrow and wide interfaces*: some languages can make it difficult to allow access to `Memento` only to `Originator`.
- *Hidden costs in caring for `Memento`s*: `Caretaker` can incur large storage costs when it stores `Memento`s.

---

Implementation (issues):

- *Language support*: `Memento`s have two interfaces
	- wide one for `Originator`s
	- narrow one for other objects
- *Storing incremental changes*: `Memento` can save just the *incremental change* to the `Originator`'s internal state.

---

Related patterns:

- `Command`: it can use mementos to maintains the for undoable operations
- `Iterator`: mementos can be used for iteration.

