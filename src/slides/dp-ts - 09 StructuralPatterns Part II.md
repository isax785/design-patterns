# Structural Patterns - Part II

Overview:

- [Decorator](#decorator)
- Decorator Playground (Jupyter Notebooks)

---

## Decorator

> **Intent**: Attach additional responsibilities to an object dynamically. `Decorator`s provide a flexible alternative to subclassing for extending functionality.

---
Applicability:

- add responsibilities to individual objects dynamically and transparently (i.e. without affecting their objects)
- responsibilities that can be withdrawn
- when extension by subclassing is impractical

---

![[Pasted image 20240708115356.png]]

| Who                 | What                                                                                                            |
| ------------------- | --------------------------------------------------------------------------------------------------------------- |
| `Component`         | defines the interface for objects that can have responsibilities added to them dynamically                      |
| `ConcreteComponent` | defines an object to which additional responsibilities can be attached                                          |
| `Decorator`         | maintains a reference to a `Component` object and defines an interface that conforms to `Component`'s interface |
| `ConcreteDecorator` | add responsibilities to the component                                                                           |

---

 Collaborations:

- `Decorator` forwards requests to its `Component` object. Additional operations may be performed before/after forwarding the request.

---

Consequences:

- *More flexibility than static inheritance*: responsibilities can be added/removed at run-time simply by attaching/detaching them (while inheritance requires creating a new class for each additional responsibility). Moreover, a property can be easily added twice.
- *Avoids feature-laden classes high up in the hierarchy*: functionalities can be added incrementally with `Decorator` objects
- *A decorator and its component aren't identical*: from an object identity point of view, a decorated component is not identical to the component itself.
- *List of little objects*: a design using `Decorator` often results in systems composed of lots o little objects that all look alike.

---

Implementation:

- *Interface conformance*: `Decorator` and decorated object interfaces are conform
- *Omitting the abstract `Decorator` class*: no need to define an abstract `Decorator` class when there is the need for one responsibility only.
- *Keeping `Component` classes lightweight*: to ensure a conforming interface, components and decorators must descend from a common `Component` class.
- *Changing the skin of an object versus changing its guts*

---

Related patterns:

- `Adapter`: while `Decorator` changes object responsibilities only, `Adapter` also changes its interface
- `Composite`: a `Decorator` can be viewed as a degenerate composite with only one component.
- `Strategy`: while `Decorator` allows changing the skin of an object, `Strategy` allows changing its gut.
 
