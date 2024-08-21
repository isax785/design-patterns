# Behavioral Patterns - Part II

Overview:

- [[#Interpreter]]
- [[#Iterator]]

---
# Interpreter


> **Intent**: Given a language, define a representation for its grammar along with an interpreter that uses the representation to interpret sentences in the language.

---

Applicability:

- a language to interpret and the statements can be represented in the language as abstract syntax trees
	- simple grammar: it works well
	- complex grammar: the grammar class hierarchy becomes large and unmanageable (use **parser generators** instead)
- efficiency is not critical: the most efficient interpreters usually translate parse trees into another form, then interpret them directly (i.e. 2 steps)

---

![[Pasted image 20240806101642.png]]

| Who                     | What                                                                                                                                                                                                                                                                                                                                                                     |
| ----------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `AbstractExpression`    | declares an abstract Interpret operation that is common to all nodes in the abstract syntax tree.                                                                                                                                                                                                                                                                        |
| `TerminalExpression`    | - implements an Interpret operation associated with terminal symbols in the grammar. <br>- an instance is required for every terminal symbol in a sentence.                                                                                                                                                                                                              |
| `NonterminalExpression` | - one such class is required for every rule $R ::= R1 R2 ... Rn$ in the grammar.<br>- maintains instance variables of type `AbstractExpression` for each of the symbols $R1$ through $Rn$. <br>- implements an Interpret operation for nonterminal symbols in the grammar. Interpret typically calls itself recursively on the variables representing $R1$ through $Rn$. |
| `Context`               | contains information that's global to the interpreter.                                                                                                                                                                                                                                                                                                                   |
| `Client`                | - builds (or is given) an abstract syntax tree representing a particular sentence in the language that the grammar defines. The abstract syntax tree is assembled from instances of the `NonterminalExpression` and `TerminalExpression` classes. <br>- invokes the Interpret operation.                                                                                 |

---
 
Collaborations:

- the `Client`  builds (or is given) the sentence as an abstract syntax tree of `NonterminalExpression` and `TerminalExpression` instances. 
	- Then the `Client` initializes the context and invokes the `Interpret` operation
- Each `NonterminalExpression` node defines `Interpret` in terms of `Interpret` on each subexpression. The `Interpret` operation of each `TerminalExpression` defines the base case in the recursion.
- The `Interpret` operations at each node use the context to store and access the state of the interpreter.

---

Consequences:

- *Grammar easy to change/extend*: the pattern uses classes to represent the grammar rules, inheritance can be used.
- *Easy implementation of the grammar*: classes defining the nodes in the abstract syntax tree have similar implementations. They are easy to write, and often their generation can be automated.

---

- *Complex grammars are hard to maintain*: usually, at least one class is defined for every grammar rule. Grammars with many rules can be hard to manage/maintain.
- *Adding new ways to interpret expressions*: it is easy to evaluate an expression in a new way.

---

Implementation (issues):

- *Creating the abstract syntax tree*: the `Interpreter` pattern does not explain how to create an abstract syntax tree, i.e. it does not address parsing. `AST` should be created by:
	- table-driven parser
	- hand-crafted parser
	- provided directly by client

---

- *Defining the `Interpret` operation*: the `Interpret` operation does not have to be defined in the expression classes.
- *Sharing terminal symbols with the `Flyweight` pattern*: grammars whose sentences contain many occurrences of a terminal symbol might benefit from sharing a single copy of that symbol.

---

Related patterns:

- `Composite`: abstract syntax tree is a `Composite` instance
- `Flyweight`: share terminal symbols within abstract syntax tree
- `Iterator`: use `Iterator` to traverse the structure
- `Visitor`: maintain each node behavior in the abstract syntax tree in one class

---
# Iterator

> **Intent**: Provide a way to access the elements of an aggregate object sequentially without exposing its underlying representation.

---

Applicability:

- access an aggregate object's contents without exposing its internal representation. 
- to support multiple traversals of aggregate objects. 
- provide a uniform interface for traversing different aggregate structures (i.e. *polymorphic iteration*).

---

![[Pasted image 20240808101115.png]]

| Who                 | What                                                                                                              |
| ------------------- | ----------------------------------------------------------------------------------------------------------------- |
| `Iterator`          | defines an interface for accessing and traversing elements.                                                       |
| `ConcreteIterator`  | - implements the Iterator interface. <br>- keeps track of the current position in the traversal of the aggregate. |
| `Aggregate`         | defines an interface for creating an Iterator object.                                                             |
| `ConcreteAggregate` | implements the Iterator creation interface to return an instance of the proper `ConcreteIterator`.                |

---

Collaborations:

- A `ConcreteIterator` keeps track of the current object in the aggregate and can compute the succeeding object in the traversal.

---

Consequences:

- *It supports variations in the traversal of an aggregate*: `Iterator`s make it easy to change the traversal algorithm by replacing the iterator instance.
- *`Iterator`s simplify the `Aggregate` interface*: the `Iterator`'s traversal interface obviates the need for a similar interface in `Aggregator`, that will be simplified.
- *More than one traversal can be pending on an aggregate*: an iterator keeps track of its own traversal state, so it is possible to have more than one traversal in progress at once.

---

Implementation - variants and alternatives:

- *Who control the iteration?*: 
	- external iterator: the client controls the iteration. More flexible.
	- internal iterator: the iterator controls the iteration. Easier ot use.

---

- *Who defines the traversal algorithm?* The traversal algorithm can be defined:
	- into the aggregate: 
		- it uses the iterator just to store the state of the iteration, the iterator is called **cursor**.
		- a client will invoke the `Next` operation on the aggregate with the *cursor* as argument
		- the `Next` operation will change the state of the cursor
	- into the iterator: 
		- easy to use different iteration algorithms on the same aggregate
		- easy to use the same algorithm on different aggregates
		- the traversal algorithm might need to access the private variables of the aggregate (encapsulation violation)

---

- *How robust is the iterator?* Modifying an aggregate while traversing it could be dangerous, a simple solution is to copy (too expensive). A **robust iterator** ensures that insertions and removal won't interfere with traversal, without copying the aggregate. 
- *Additional `Iterator` operations*: minimal `Iterator` interface: `First`, `Next`, `IsDone`, and `CurrentItem`. Additional operations: `Previous` and `SkipTo`.

---

- *Using polymorphic iterators in C++*: drawbacks:
	- require the iterator object to be allocated dynamically by a factory method
	- the client is responsible for deleting them. It is error prone, since there is the risk the iterator is not deleted.
- *Iterators may have privileged access*: it can be viewed as an extension of the aggregate that created it (`friend` in C++).

---

- *Iterators for composites*: *external* iterators can be difficult to implement over recursive aggregate structures like `Composite`s' ones. sometimes it is easier to use an *internal* iterator.
- *Null iterators*: a degenerate iterator that's helpful for handling boundary conditions (it is always done with traversal, so its `IsDone` operation always evaluates to `true`).

---

Related patterns:

- `Composite`: `Iterator`s are often applied to recursive structures.
- `FactoryMethod`: polymorphic iterators rely on factory methods to instantiate the appropriate `Iterator` subclass.
- `Memento`: used in conjunction, `Iterator` uses `Memento` (that is stored internally) to capture the state of an iteration.