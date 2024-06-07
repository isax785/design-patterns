# Creational Patterns - Part I

Overview:

- Abstract Classes with Python
- [[#Abstract Factory|Abstract Factory]]
- [[#Builder|Builder]]

---

## Abstract Factory

> **Intent**: Provide an interface for creating families of related or dependent objects without specifying their concrete classes.

---

Use when:

- a system should be independent of how its products are created, composed, and represented. 
- a system should be configured with one of multiple families of products. 
- a family of related product objects is designed to be used together, and you need to enforce this constraint. 
- you want to provide a class library of products, and you want to reveal just their interfaces, not their implementations.

---

![[Pasted image 20240606091702.png]]

| Who               | What                                                                                                                          |
| ----------------- | ----------------------------------------------------------------------------------------------------------------------------- |
| `AbstractFactory` | declares an interface for operations that create abstract product objects.                                                    |
| `ConcreteFactory` | implements the operations to create concrete product objects.                                                                 |
| `AbstractProduct` | declares an interface for a type of product object.                                                                           |
| `ConcreteProduct` | defines a product object to be created by the corresponding concrete factory. <br>implements the `AbstractProduct` interface. |
| `Client`          | uses only interfaces declared by AbstractFactory and AbstractProduct classes.                                                 |

---

![[Pasted image 20240606091702.png]]

Collaborations:

- Normally a single instance of a `ConcreteFactory` class is created at run-time. This concrete factory creates product objects having a particular implementation. To create different product objects, clients should use a different concrete factory.
- `AbstractFactory` defers creation of product objects to its `ConcreteFactory` subclass.

---

Consequences:

- it isolates concrete classes
- It makes exchanging product families easy
- It promotes consistency among products
- Supporting new kinds of products is difficult

---

Implementation:

- Factories as singletons: since a single instance of `ConcreteFactory` per product family is needed, it's usually best implemented as a `Singleton`.
- Creating the products: `ConcreteProduct` subclasses create products. 
	- Usually, a factory method (`Factory Method`) for each product is defined. 
	- If many families are possible, the concrete factory can be implemented using the `Prototype` (i.e. a prototypical instance of each product is created, then it is cloned to create new products). The need for multiple `ConcreteFactory`s is eliminated.

---

- Define extensible factories. `AbstractFactory` usually defines a different operation for each king of product it can produce.  Adding new products requires changing the interface and all the classes that depend on it. 
	- By adding a parameter to operations that create objects, the kind of object to be created can be specified.

---

Related patterns:

- `Factory Method`
- `Prototype`
- `Singleton`

---

## Builder

> **Intent**: <u>Separate</u> the construction of a complex object from its representation so that the same construction process can create different representations.

---

Applicability:

- the algorithm for creating a complex object should be independent of the parts that make up the object and how they're assembled.
- the construction process must allow different representations for the object that's constructed.

---

![[Pasted image 20240606093624.png]]

| Who               | What                                                                                                                                                                                                                                                                                              |
| ----------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `Builder`         | specifies an abstract interface for creating parts of a Product object.                                                                                                                                                                                                                           |
| `ConcreteBuilder` | - constructs and assembles parts of the product by implementing the Builder interface.<br>- defines and keeps track of the representation it creates.<br>- provides an interface for retrieving the product.                                                                                      |
| `Director`        | constructs an object using the Builder interface.                                                                                                                                                                                                                                                 |
| `Product`         | - represents the complex object under construction. `ConcreteBuilder` builds the product's internal representation and defines the process by which it's assembled.<br>- includes classes that define the constituent parts, including interfaces for assembling the parts into the final result. |

---

![[Pasted image 20240606093624.png]]

Collaborations:

- The client creates the `Director` object and configures it with the desired `Builder` object.
- `Director` notifies the builder whenever a part of the product should be built.
- `Builder` handles requests from the director and adds parts to the product.
- The client retrieves the product from the builder.

---

Consequences:

- It lets you vary a product's internal representation.
- It isolates code for construction and representation. (Each `ConcreteBuilder` contains all the code to create and assemble a particular kind of product.)
- It gives you finer control over the construction process. (the `Builder` pattern constructs the product step by step under the director's control)

---

Implementation:

- Typically there's an abstract Builder class that defines an operation for each component that a director may ask it to create. A `ConcreteBuilder` class overrides operations for components it's interested in creating.

---

- Issues:
	- Assembly and construction interface: since `Builder`s construct their product step-by-step, the interface must be general enough to allow the construction of products for all kinds of concrete builders.
	- Why no abstract class for products? Usually products differ so greatly in their representation that there is no much gain in giving them a common parent class.
	- Empty methods as default in `Builder`. `C++`, instead of pure virtual member functions, letting the clients override only the operations they're interested in.

---

Related patterns:

- `Abstract Factory`
- `Composite`