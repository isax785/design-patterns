# Behavioral Patterns - Part IV

Overview:

- [[#Strategy]]
- [[#Template Method]]

---

# Strategy


> **Intent**: Define a family of algorithms, encapsulate each one, and make them interchangeable. Strategy lets the algorithm vary independently from clients that use it.

---

Applicability:

- many related classes differ only in their behavior
- different algorithm variants are needed
- an algorithm uses data that clients shouldn't know about (avoid exposing data structures)
- instead of multiple conditional statements for behaviors inside a single class 

---

![[Pasted image 20240828113447.png]]

| Who              | What                                                                                                                                                              |
| ---------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `Strategy`       | declares an interface common to all supported algorithms (the interface will be called by `Context`)                                                              |
| `ConcreteStrate` | implements the algorithm using the `Strategy` interface                                                                                                           |
| `Context`        | - configured with a `ConcreteStrategy` object<br>- maintains a reference to a `Strategy` object<br>- may define an interface that lets `Strategy` access its data |

---

 
Collaborations:

- `Strategy` and `Context` interact to implement the chosen algorithm. `Context` can pass data required by the algorithm, or pass itself.
- `Context` forward request from `Client` to `Strategy`. `Client`s usually create and pass a `ConcreteStrategy` object to the `Context`, then it interacts with the `Context` exclusively.

---

Consequences (benefits and drawbacks):

- *Families of related algorithms*: hierarchies of `Strategy` classes define a family of algorithms or behaviors for contexts to reuse, inheritance help factoring out common functionalities

---

- *An alternative to subclassing*: subclass a `Context` class directly to give it different behaviors. But this hard-wires the behavior into `Context`, making hit harder to understand, maintain, and extend. The algorithm cannot be varied dynamically. Encapsulating the algorithm in separate `Strategy` classes let vary the algorithm independently of its context.

---

- *Strategies eliminate conditional statements*: alternative to conditional statements for selecting the desired behavior.
- *A choice of implementations*: different implementation of the same behavior.

---

- *Clients must be aware of different strategies*: `Client` must understand how strategies differ before selecting the appropriate one.
- *Communication overhead between `Strategy` and `Context`*: `Strategy` interface is shared by all `ConcreteStrategy` classes, regardless of their complexity. Sometimes parameters that will never be used are created and initialized.

---

- *Increased number of objects*: Strategies increase the number of objects in an application. The overhead can be reduced by implementing strategies as stateless object that contexts can share. Any residual state is maintained by the context.

---

Implementation (issues):

- *Defining the `Strategy` and `Context` interfaces*: `ConcreteStrategy` must have efficient access to any data needed from the context.
	- `Context` passes data in parameters to `Strategy` operation, event not needed ones.
	- `Context` passes itself as an argument. Or `Strategy` can store a reference to its context. `Context` must define a more elaborated interface to its data.

---

- *Strategies as template parameters*: (`C++`) use template to configure a class with a strategy (no need for abstract class). It works only if `Strategy` can be selected at compile-time and it does not have to change at run-time:

```cpp
template <class AStrategy> 
class Context { 
	void Operation() { theStrategy.DoAlgorithm(); } 
	// ... 
	private: 
	AStrategy theStrategy; };

class MyStrategy { 
	public: 
		void DoAlgorithm(); 
}; 

Context<MyStrategy> aContext;
```

---

- *Making `Strategy` objects optional*: `Context` checks for `Strategy` object before accessing it. If there is one, it is used normally. Otherwise a default behavior is carried out. `Client`s do not have to deal with Strategies at all, unless the default behavior is not acceptable.

---

Related patterns:

- `Flyweight`: `Strategy` objects often make good flyweights.

---

# Template Method


> **Intent**: Define the skeleton of an algorithm in an operation, deferring some steps to subclasses. Subclasses can redefine certain steps of an algorithm without changing the algorithm's structure.

---

Applicability:

- implement the invariant parts of an algorithm once and leave it up to subclasses to implement the behavior that can vary
- common behavior among subclasses should be factored and localized in a common class to avoid code duplication
- control subclasses extensions that are permitted only at specific points

---

![[Pasted image 20240828161039.png]]

| Who             | What                                                                                                                                                                                                                                                                                                             |
| --------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `AbstractClass` | - defines abstract primitive operations that concrete subclasses define to implement steps of an algorithm. <br>- implements a template method defining the skeleton of an algorithm. The template method calls primitive operations as well as operations defined in `AbstractClass` or those of other objects. |
| `ConcreteClass` | implements the primitive operations to carry out subclass-specific steps of the algorithm.                                                                                                                                                                                                                       |

---
 
Collaborations:

- `ConcreteClass` relies on `AbstractClass` to implement the invariant steps of the algorithm.

---

Consequences:

- code reuse (particularly important in class libraries for factoring common behavior)
- lead to an inverted control structure: parent class calls the operations of a subclass and not the other way around

---

- kind of operations called by `Template Method`:
	- concrete operations
	- concrete `AbstractClass` operations
	- primitive operations (i.e. abstract)
	- factory methods
	- **hook operations**: provide default behavior (do nothing by default) that can be extend by subclasses

---

Implementation (issues):

- *Using `C++` access control*: primitive operations can be `protected` members, so they are called by `Template Method` only.
- *Minimizing primitive operations*: operations to be overridden (i.e. primitive) should be minimized in order to ease things for the clients.
- *Naming conventions*: (suggestion) identify the operations to be overridden by adding a prefix to their names.

---

Related patterns:

- `Factory Method`s: often called by `Template Method`s
- `Strategy`: while `Template Method`s use inheritance to vary part of an algorithm, `Strategies` use delegation to vary the entire algorithm.

---

