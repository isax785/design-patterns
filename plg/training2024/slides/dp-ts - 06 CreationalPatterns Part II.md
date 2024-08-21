# Creational Patterns - Part II

Overview:

- [[#Factory Method|Factory Method]]
- [[#Prototype|Prototype]]

---

# Factory Method

> **Intent**: Define an interface for creating an object, but let subclasses decide which class to instantiate. Factory Method lets a class defer instantiation to subclasses.

---

Applicability:

 - a class can't anticipate the class of objects it must create.
 - a class wants its subclasses to specify the objects it creates.
 - classes delegate responsibility to one of several helper subclasses, and you want to localize the knowledge of which helper subclass is the delegate.

---

![[Pasted image 20240610121408.png]]

| Who               | What                                                                                                                                                                                                                                                         |
| ----------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `Product`         | defines the interface of objects the factory method creates.                                                                                                                                                                                                 |
| `ConcreteProduct` | implements the Product interface.                                                                                                                                                                                                                            |
| `Creator`         | - declares the factory method, which returns an object of type Product. Creator may also define a default implementation of the factory method that returns a default `ConcreteProduct` object.<br>- may call the factory method to create a Product object. |
| `ConcreteCreator` | overrides the factory method to return an instance of a ConcreteProduct.                                                                                                                                                                                     |

---

![[Pasted image 20240610121408.png]]

Collaborations:

- `Creator` relies on its subclasses to define the factory method so that it returns an instance of the appropriate `ConcreteProduct`.

---

Consequences:

- Factory methods eliminate the need to bind application-specific classes into your code. The code only deals with the `Product` interface; therefore it can work with any user-defined `ConcreteProduct` classes.
- Potential disadvantage: clients might have to subclass the `Creator` class just to create a particular `ConcreteProduct` object.

---

- Provides hooks for subclasses. The factory method could also provide a reasonable default implementation.
- Connects parallel class hierarchies. Parallel class hierarchies result when a class delegates some of its responsibilities to a separate class. The factory method defines the connection between the two class hierarchies. It localizes knowledge of which classes belong together

---

Implementation:

- Two major varieties: (1) `Creator` class is abstract and does not provide any default implementation (2) `Creator` is a concrete class providing a default implementation.
- Parametrized Factory Methods. Create multiple kinds of products, an input parameter identifies the kind of object to create. All the created products will share the the `Product` interface.
- Language-specific variants and issues.
- Using templates to avoid subclassing.

---

Related patterns:

- `Abstract Factory`
- `Template Methods`
- `Prototypes`

---

|            | `Abstract Factory`                                                                                                                                           | `Factory Method`                                                                                                                                |
| ---------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------ | ----------------------------------------------------------------------------------------------------------------------------------------------- |
| Purpose    | Provides an interface for creating families of related or dependent objects without specifying their concrete classes.                                       | Provides an interface for creating an instance of a class, but allows subclasses to alter the type of objects that will be created.             |
| Structure  | Involves multiple factory methods to create a variety of related objects, grouped together into families.                                                    | Involves a single method in a base class that is overridden by subclasses to create objects.                                                    |
| Focus      | Focuses on creating a family of related products.                                                                                                            | Focuses on creating a single product.                                                                                                           |
| Complexity | More complex as it involves multiple factory methods and interfaces for different product types.                                                             | Simpler in structure and usually deals with one level of inheritance.                                                                           |
| Use Case   | Used when a system must be independent of the way its products are created, or when a system should be configured with one of multiple families of products. | Used when a class cannot anticipate the class of objects it must create or when a class wants its subclasses to specify the objects it creates. |

---
# Prototype

> **Intent**: Specify the kinds of objects to create using a prototypical instance, and create new objects by copying this prototype.

---

Applicability:

- use when a system should be independent of how its products are created, composed, and represented
- the classes to instantiate are specified at run-time
- to avoid building a class hierarchy of factories that parallels the class hierarchy of products
- when instances of a class can have one of only a few different combinations of state (it's more conveniente to have a number of prototypes and clone them rather than instantiating the class manually with the appropriate state)

---

![[Pasted image 20240610125648.png]]

| Who                 | What                                                       |
| ------------------- | ---------------------------------------------------------- |
| `Prototype`         | declares an interface for cloning itself                   |
| `ConcretePrototype` | implements an operation for cloning itself                 |
| `Client`            | creates a new object by asking a prototype to clone itself |

---

![[Pasted image 20240610125648.png]]

Collaborations:

- a client asks a prototype to clone itself

---

Consequences:

- hides the concrete product classes from the client, thereby reducing the number of names clients know about
- lets a client work with application-specific classes without modification
- Adding and removing products at run-time: a prototypical instance is registered with the client
- Specifying new objects by varying values
- Specifying new objects by varying structure
- Reduced subclassing
- Configuring an application with classes dynamically

---

Implementation:

- particularly useful with static languages like C++, where classes are not objects, and little or no type information is available at run-time
- Using a prototype manager
- Implementing the Clone operation: it's particularly tricky when object structures contain circular references
- Initializing clones

---

Related patterns:

- `Abstract Factory`
- `Composite`
- `Decorator`