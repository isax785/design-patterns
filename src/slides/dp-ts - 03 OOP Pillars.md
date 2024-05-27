# OOP Pillars

Overview:

- [[#Encapsulation|Encapsulation]]
- [[#Inheritance|Inheritance]]
- [[#Polymorphism|Polymorphism]]
- [[#Abstraction|Abstraction]]

---

OOP has 4 pillars: 

- Encapsulation
- Inheritance
- Polymorphism
- Abstraction

---

## Encapsulation

> The principle that seeks to **hide the implementation details for objects** from the outside world.

---

Statements:

- all important information is contained within the object;
- only selected data is available externally;
- each object's inner workings and states are stored privately within the specified class;
- other objects do not have access neither can make changes;
- other objects can only interact with public functions/methods.

---

This form of **data hiding** provides program security and control over object state changes, reduces the risk of errors, and makes the program more understandable.

---

- hides the implementation details of an object
- focuses on the implementation
- structure and implementation of the methods is hidden
- client only knows about the contract
- abstractions work only when encapsulated

---

- every class has two parts: **interface** and **implementation**
- interface captures the outside view and provides the behavior
- clients will make assumptions based on the outside view
- implementation is encapsulated
- abstraction is required to be accountable for its behavior

---

Advantages:

- clients don't need to see the implementation details
- change in internal implementation does not affect the client
- encapsulation decouples the client and the implementation

---

## Inheritance

> The principle that allows creating new classes based on existing (i.e. parents) ones, with the possibility of overriding or augmenting their properties and methods.

---

- `is a` relation or generalization
- represents a relationship where one class is a kind of other
- base class (parent) will share its structure and behavior with another class (child)
- any class can inherit the behavior from the base class (it may provide a specialized implementation of the behavior)
- inheritance implies generalization/specialization hierarchy

---

Advantages:

- simplifies maintenance;
- prevents code duplication;
- create objects that share code or logic;
- reduces the code complexity.

---

```python
class Person:
  	def __init__(self, fname, lname):
    	self.firstname = fname
    	self.lastname = lname

  	def printname(self):
    	print(self.firstname, self.lastname)


class Student(Person):
  def __init__(self, fname, lname):
    super().__init__(fname, lname) # keep the inheritance of the parent's __init__

x = Person("John", "Doe")
x.printname()
y = Student("Mike", "Olsen")
y.printname()
```

---

## Polymorphism

> The principle that complements inheritance by allowing objects of different classes to perform actions with the same name using different code.

---

Simplifies the development process as it allows for creation of common methods and functions to be used for multiple types of objects.

---

```python
# Built-in polymorphic functions
 
# len() being used for a string
print(len("geeks"))
 
# len() being used for a list
print(len([10, 20, 30]))
```

---

```python
# Polymorphism
def add(x, y, z=0): 
    return x + y + z
 
# Driver code 
print(add(2, 3))
print(add(2, 3, 4))
```

---

## Abstraction

> The principle that helps focusing on a system's essential elements and ignore the less important details that have no effect on its key features.

---

Abstraction can be thought of as an expansion of encapsulation. 

In a program, each object only reveals a specific mechanism for usage. Therefore, the code inside becomes largely independent of other objects.

---

It is the first step of OOP:

- denotes essential characteristics of an object
- simplified view or specification that emphasizes some details while suppressing/ignoring others (i.e. unnecessary ones)
- class/struct/interface is an abstraction
- it is performed based on the domain (domain expertise is fundamental)
- provides services or uses services of some other object
- resolves complexity
- makes it simpler to model a solution for a problem
- focuses on the details relevant to the problem domain
- represents real-life objects in software
- its elements provide a behavior


---

Sample concept: *in a program that stores information about movies, you can create a class "Movie" that provides access to only the most essential details, such as title, release year, and genre, while hiding the less important information, like shots or technical aspects.*

---

```python
from abc import ABC, abstractmethod
class Payment(ABC):
  	def print_slip(self, amount):
    	print('Purchase of amount- ', amount)
  	@abstractmethod
  	def payment(self, amount):
   	 	pass

class CreditCardPayment(Payment):
  	def payment(self, amount):
    	print('Credit card payment of- ', amount)

class MobileWalletPayment(Payment):
  	def payment(self, amount):
    	print('Mobile wallet payment of- ', amount)

obj = CreditCardPayment()
obj.payment(100)
obj.print_slip(100)
print(isinstance(obj, Payment))
obj = MobileWalletPayment()
obj.payment(200)
obj.print_slip(200)
print(isinstance(obj, Payment))
```

```text
 Credit card payment of-  100
 Purchase of amount-  100
 True
 Mobile wallet payment of-  200
 Purchase of amount-  200
 True
```
