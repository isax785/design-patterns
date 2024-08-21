# Creational Patterns - Part III

Overview:

- Metaclasses with Python
- [[#Singleton]]
- [[#Creational Patterns Discussion]]
- Playground: the `Maze`

---
# Singleton

> **Intent**: Ensure a class only has one instance, and provide a global point of access to it.

---

Applicability:

- there must be exactly one instance of a class, and it must be accessible to clients from a well-known access point.
- when the sole instance should be extensible by subclassing, and clients should be able to use an extended instance without modifying their code.

---

Structure:

![[Pasted image 20240617121753.png]]

| Who         | What                                                                                                                                     |
| ----------- | ---------------------------------------------------------------------------------------------------------------------------------------- |
| `Singleton` | - defines an `Instance()` operation that lets clients access its unique instance.<br>- responsible for creating its own unique instance. |

---

Collaborations:

- clients access the Singleton instance solely through Singleton's `Instance` operation

---

Consequences:

- Controlled access to sole instance.
- Reduced name space (no additional global variables).
- Permits refinement of operations and representation: it may be sub-classed, and it's easy to configure an application with an instance of the extended class.
- Permits a variable number of instance: the pattern makes it easy to allow more than one instance of the Singleton class. The number of instances can be controlled.
- More flexible than class operations.

---

Implementation:

- ensuring a unique instance: the common way to restrict the number of instances created to a single one is to hide the instance operation behind a class operation (i.e. static member function or class method). the constructor is protected.
- Subclassing the Singleton class. Also a registry can be used.

---

```cpp
class Singleton {
	public:
		static Singleton* Instance();
	protected:
		Singleton();
	private:
		static Singleton* _instance;
};

// implementation
Singleton* Singleton::_instance = 0;
Singleton* Singleton::Instance () {
	if (_instance == 0) {
		_instance = new Singleton;
	}
	return _instance;
}
```

---

Related patterns:

- `Abstract Factory`
- `Builder`
- `Prototype`

---

# Creational Patterns: Discussion

There are two common ways to parametrize a system by the classes of objects it creates:

---

1. subclass the class that creates the objects (`Factory Method`)
	- Drawback: it can require creating a new subclass just to change the class of the product.

---

2. rely on object composition: define an object that's responsible for knowing the class of the product objects, and make it a parameter of the system (`Abstract Factory`, `Builder`, and `Prototype`)
	- `Abstract Factory` has the factory object producing objects of several classes.
	- `Builder` has the factory object building a complex product incrementally using a correspondingly complex protocol. 
	- `Prototype` has the factory object building a product by copying a prototype object.

---

1. Subclassing (i.e. inheritance)
2. Object Composition

`2.` is more flexible than `1.`, but also more complex. Usually, the development starts from `1.` switching to `2.` while more flexibility is needed.
