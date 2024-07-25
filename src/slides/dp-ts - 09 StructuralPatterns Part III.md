
# Structural Patterns - Part III

Overview:

- [Structural Patterns - Part III](#structural-patterns---part-iii)
- [Facade](#facade)
- [Flyweight](#flyweight)
- [Proxy](#proxy)

---

# Facade

> **Intent**: Provide a unified interface to a set of interfaces in a subsystem. Facade defines a higher-level interface that makes the subsystem easier to use.

![[Pasted image 20240722111439.png]]

---

Applicability:

- provide a simple interface to a complex system. Subsystems often become more complex while evolving, by adding more smaller classes to ease reusability and customization. This leads also to a more complex usage (i.e. interface).
- when there are many dependencies between clients and the implementation classes of an abstraction.  The system can be decoupled from clients, promoting subsystem independence and portability.
- layering the subsystems, by defining an entry point for them.

---

![[Pasted image 20240722111419.png]]

| Who                 | What                                                                                                                                                                 |
| ------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `Facade`            | - knows which subsystem classes are responsible for a request.<br>- delegates client requests to appropriate subsystem objects.                                      |
| `subsystem classes` | - implement subsystem functionality. <br>- handle work assigned by the Facade object. <br>- have no knowledge of the facade; that is, they keep no references to it. |

---

Collaborations:

- `Client`s communicate with the subsystem by sending requests to `Facade`, which forwards them to the appropriate subsystem object(s)
- `Client`s that use the facade don't have to access its subsystem objects directly.

---

Consequences (benefits):

- shields client from subsystem components: clients deal with a reduced number of objects and the subsystem is easier to use.
- promotes weak coupling between the subsystem and its clients (i.e. the subsystem components can be varied without affecting its clients).
- does not prevent applications from using subsystem classes.

---

Implementation (issues):

- *Reducing client-subsystem coupling*: making the Facade an abstract class with concrete subclasses for different implementations reduces further the client-subsystem coupling.
  An alternative to subclassing is to configure a Facade object with different subsystem objects.
- *Public versus private subsystem classes*: subsystem and classes are analogous since both have interfaces and encapsulate something. So, there can be both private and public interface also for a subsystem.

---

Related patterns:

- `Abstract Factory`: can be used with `Facade` to provide an interface for creating subsystem objects in a subsystem-independent way. Can be used also as alternative.
- `Mediator`: similar to `Facade` since it abstracts functionalities of existing classes.

---

# Flyweight

> **Intent**: Use sharing to support large numbers of fine-grained objects efficiently.

![[Pasted image 20240722111521.png]]

---

Applicability:

- An application uses a large number of objects. 
- Storage costs are high because of the sheer quantity of objects. 
- Most object state can be made extrinsic. 
- Many groups of objects may be replaced by relatively few shared objects once extrinsic state is removed. 
- The application doesn't depend on object identity. Since flyweight objects may be shared, identity tests will return true for conceptually distinct objects.

---

Structure:

![[Pasted image 20240722111506.png]]

| Who                         | What                                                                                                                                                                                                                                                                                                        |
| --------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `Flyweight`                 | declares an interface through which flyweights can receive and act on extrinsic state.                                                                                                                                                                                                                      |
| `ConcreteFlyweight`         | implements the `Flyweight` interface and adds storage for intrinsic state, if any. A `ConcreteFlyweight` object must be sharable. Any state it stores must be intrinsic; that is, it must be independent of the `ConcreteFlyweight` object's context                                                        |
| `UnsharedConcreteFlyweight` | not all `Flyweight` subclasses need to be shared. The Flyweight interface enables sharing; it doesn't enforce it. It's common for `UnsharedConcreteFlyweight` objects to have `ConcreteFlyweight` objects as children at some level in the flyweight object structure (as the Row and Column classes have). |
| `FlyweightFactory`          | - creates and manages flyweight objects. <br>- ensures that flyweights are shared properly. When a client requests a flyweight, the `FlyweightFactory` object supplies an existing instance or creates one, if none exists.                                                                                 |
| `Client`                    | - maintains a reference to flyweight(s). <br>- computes or stores the extrinsic state of flyweight(s).                                                                                                                                                                                                      |

---
 
Collaborations:

- the state that a `Flyweight` must be characterized as either intrinsic (stored into the `ConcreteFlyweight` object) or extrinsic (computed by `Client` object). Clients pass this state to the flyweight when they invoke its operations.
- `Client`s should not instantiate `ConcreteFlyweight`s directly. `Client`s must obtain `ConcreteFlyweight` objects exclusively from the `FlyweightFactory` object to ensure they are shared properly.

---

Consequences (benefits):

> Sharing reduces the cost of intrinsic state, and you trade extrinsic state for computation time

- (cons) may introduce run-time costs associated with transferring, finding, and/or computing extrinsic state (especially if formerly stored as intrinsic state)
- space saving
	- reduction in total number of instances
	- amount of intrinsic state per object
	- whether extrinsic state is computed or stored
- the greatest savings occur when the objects use substantial quantities of both intrinsic and extrinsic state, and the extrinsic state can be computed rather than stored

---

Implementation (issues):

- *Removing extrinsic state*: the pattern's applicability is determined largely by how easy it is to identify extrinsic state and remove it from shared objects
- *Managing shared objects*: clients shouldn't instantiate shared objects directly. `FlyweightFactory` lets clients locate a particular flyweight, and it is often uses an associative store to let clients look up flyweights of interest.
  Sharability also implies some form of reference counting or garbage collection to reclaim a flyweight's storage when it's no longer needed (not needed if the number of flyweights is fixed and small).

---

Related patterns:

- `Comoposite`: often combined together to implement a logically hierarchical structure in terms of a directed-acyclic graph with shared leaf nodes.
- `State` and `Strategy`: objects that are better to be implemented as flyweights.


---
# Proxy


> **Intent**: Provide a surrogate or placeholder for another object to control access to it.

![[Pasted image 20240722111615.png]]

---

Applicability:

> whenever there is a need fo a more versatile or sophisticated reference to an object than a simple pointer.

- A remote proxy provides a local representative for an object in a different address space.
- A virtual proxy creates expensive objects on demand.
- A protection proxy controls access to the original object.
- A smart reference is a replacement for a bare pointer that performs additional actions when an object is accessed. Uses:
	- counting the number of references to the real object
	- loading a persistent object into memory when it's first referenced
	- checking that the real object is locked before it's accessed to ensure that no other object can change it

---

![[Pasted image 20240722111558.png]]

| Who           | What                                                                                                                                                                                                                                                                                                                                                                                                                                                |
| ------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `Proxy`       | - maintains a reference that lets the proxy access the real subject (reference is possible if they have the same interface)<br>- provides an interface identical to Subject's so that a proxy can by substituted for the real subject<br>- controls access to the real subject and may be responsible for creating and deleting it<br>- other responsibilities depend on the kind of proxy: *remote proxy*, *virtual proxies*, *protection proxies* |
| `Subject`     | defines the common interface for RealSubject and Proxy so that a Proxy can be used anywhere a RealSubject is expected                                                                                                                                                                                                                                                                                                                               |
| `RealSubject` | defines the real object that the proxy represents                                                                                                                                                                                                                                                                                                                                                                                                   |

---
 
Collaborations:

- Proxy forwards requests to `RealSubject` when appropriate, depending on the kind of proxy.

---

Consequences:

- introduces a level of indirection when accessing an object
	- A remote proxy can hide the fact that an object resides in a different address space. 
	- A virtual proxy can perform optimizations such as creating an object on demand. 
	- Both protection proxies and smart references allow additional housekeeping tasks when an object is accessed.
- **copy-on-write** (creation on demand): by using a proxy to postpone the copying process, we ensure that we pay the price of copying the object only if it's modified

---

Implementation:

- *overloading the member access operator (`->`) in C++*: such overloading allows performing additional work whenever an object is dereferenced. Overloading the member access operator isn't a good solution for every kind of proxy. Some proxies need to know precisely which operation is called, and overloading the member access operator doesn't work in those cases.
- *Proxy doesn't always have to know the type of real subject.*: If a Proxy class can deal with its subject solely through an abstract interface, then there's no need to make a Proxy class for each `RealSubject` class. The proxy can deal with all `RealSubjects` classes uniformly.
- Issue: *how to refer to the subject before it's instantiated.* Some proxies have to refer to their subject whether it's on disk or in memory.

---

Related patterns:

- `Adapter`: An adapter provides a different interface to the object it adapts. In contrast, a proxy provides the same interface as its subject. A proxy used for access protection might refuse to perform an operation that the subject will perform, so its interface may be effectively a subset of the subject's.
- `Decorator`: A decorator adds one or more responsibilities to an object, whereas a proxy controls access to an object.


