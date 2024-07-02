# Readme

- [Readme](#readme)
- [Tasks](#tasks)
- [Content](#content)
  - [Playground](#playground)
- [References](#references)

---

# Tasks

- [ ] exercises (see book [Practical Python Design Patterns](./src/lnk/[book]%20Practical%20Python%20Design%20Patterns_%20Pythonic%20Solutions%20to%20Common%20Problems.pdf%20-%20Shortcut.lnk))
- [ ] [Notebook](./ntb/practicalPythonDesignPatterns.ipynb)  explode into multiple interconnected files

# Content

- [Development](./dev/): scripts and notebooks for the development of classes and functions.
- [Documentation](./doc/): some notes reported into documentation files.
- [Notebooks](./ntb/): a collection of design patterns from the book `Practical Python Design Patterns`. Some exercises for practicing are provided.
- [Objects](./obj/): classes and functions to be imported into other scripts.
- [Playground](./plg/): a playground to practice design patterns.
- [Sources](./src/): sources and utilities:
  - [python-patterns](./src/python-patterns/): a collection of design patterns and idioms, including their testing. More details into [readme.md](./src/python-patterns/README.md).
  - [Slides for the Training](./src/slides/): slides of the training on design patterns.

## Playground

Prefixes: `[pattern-calssification]_[progressive-index]_[filename].ipynb` where `pattern-classification`:

- `00`: general
- `01`: creational
- `02`: structral
- `03`: behavioral

List:

- [00 Abstract Classes](./plg/00_01_abstract_classes.ipynb): playing with *abstract classes*.
- [00 `cls` Argument](./plg/00_02_cls.ipynb): examples related to `cls` argument, i.e. class methods, metaclass methods, and alternate constructors.
- [00 Metaclasses](./plg/00_03_metaclasses.ipynb): some examples of *metaclasses* implementation with Python.
- [01 Maze with Creational Patterns](./plg/01_00_maze_creational_example.ipynb): an example of a class building a maze, upgraded by all the creational patterns here described.
- [01 Maze with Abstract Factory and Builder](./plg/01_00_maze_abstract_factory_builder.ipynb): an example of a class building a maze, it is upgraded by `Abstract Factory` and `Builder`.
- [01 Abstract Factory](./plg/01_02_abstract_factory.ipynb): `Abstract Factory` implementation of a GUI's generating multiple graphical components for different opertaing ssytems.
- [01 Builder](./plg/01_03_builder.ipynb): `Builder` implementation of a house builder.
- [01 Factory Method](./plg/01_04_factory_method.ipynb): `Factory Method` implementation of a vehicle factory. Direct comparison vs `Abstraact Factory` is also reporeted.
- [01 Prototype](./plg/01_05_prototype.ipynb): `Prototype` implementation explained by a simple example.
- [01 Singleton](./plg/01_06_singleton.ipynb): `Singleton` implementation, two examples: a standard one and another one based on *metaclasses*.
- [02 Adapter](./plg/02_01_adapter.ipynb): `Adapter` implementation dealing with formatting weather data.
- [02 Bridge](./plg/02_02_bridge.ipynb): `Bridge` implementation of a drawing application.
- [02 Composite](./plg/02_03_composite.ipynb): `Composite` implementation of a file system structure.
- [02 Decorator](./plg/02_04_decorator.ipynb): `Decorator` implemenatation of a simple cofee ordering system.

# References

- [Design Patterns - Gang of Four](./lnk/src/[book]%20Design%20Patterns_%20Elements%20of%20Reusable%20Object-Oriented%20Software.pdf%20-%20Shortcut.lnk)
- [Practical Python Design Patterns](./src/lnk/[book]%20Practical%20Python%20Design%20Patterns_%20Pythonic%20Solutions%20to%20Common%20Problems.pdf%20-%20Shortcut.lnk)