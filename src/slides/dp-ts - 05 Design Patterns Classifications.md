# DP Classifications

Overview:

- [[#Creational Patterns|Creational Patterns]]
- [[#Structural Patterns|Structural Patterns]]
- [[#Behavioral Patterns|Behavioral Patterns]]

---

![[Pasted image 20231212145112.png]]

---
## Creational Patterns

> <u>Creational design patterns abstract the instantiation process</u>. They help make a system independent of how its objects are created, composed, and represented.

---

- Class creational pattern -> inheritance to vary the instantiated class.
- Object creational pattern -> instantiation delegated to another object.

---

> Creational patterns become important as systems evolve<u> to depend more on object composition</u> than class inheritance. 

The focus shifts to define a smaller set of fundamental behaviors that can be composed into any number of more complex ones.

---

Creational patterns (`CP`) recurring themes:
1. they all encapsulates knowledge about which concrete classes the system uses
2. they hide how instances of these classes are created and put together

---

`CP`s:
- give a lot of flexibility in 
	- *what* gets created
	- *who* creates it
	- *how* it gets created
	- *when*
- configure a system with *product objects* that vary widely in structure and functionality
- configuration can be **static** (compile-time) or **dynamic** (run-time)

---
## Structural Patterns

> Structural patterns (`SP`) are concerned with how classes and objects are composed to form larger structures.

---

- Class `SP` -> inheritance to compose interfaces or implementations (e.g. multiple inheritance mixing two or more classes into one, independently developed class libraries work together, adapter, etc.).

---

- Object `SP` -> ways to compose object to realize new functionalities (composition changed at run-time).

---
## Behavioral Patterns

> Behavioral patterns (`BP`s) are concerned with algorithms and the assignment of responsibilities between objects.

---

`BP`s:
- describe:
	- patterns of objects or classes;
	- patterns of communication between them.
- allow concentrate just on the way objects are interconnected.

---

- Class `BP` -> use inheritance to distribute behavior between classes.

---

- Object `BP` -> use object composition rather than inheritance.
	- Some describe how a group of peer objects cooperate to perform a task that no single object can carry out by itself. 
	- An issue is how peer objects know about each other.
	- Other `BP`s are concerned with encapsulating behavior in an object and delegating requests to it.

---
