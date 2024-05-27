# Utilities and Various Notes

A miscellanea of notes that support the development and enhance the comprehension of the topics contained in this repo.

## Shallow Copy vs Deep Copy

**Python variables are esentially pointers to addresses in memory where the relevant values are stored**.

```python
from copy import deepcopy

sample_list = [1, 2, 3, [4, 5]]
same_list = sample_list  # points to the same list
shallow_copy = sample_list[:]  # copy of the list content
deep_copy = deepcpy(sample_list)
```

- **Shallow Copy** : copy of the first level of the object. Only the [1,2,3] part of the `sample_list` is copied, while [4,5] points to the same list.
- **Deep Copy** : all the levels of the object are copied.

## Virtualenv

`virtualenv` package allows setting the proper environment for the project under development, without superposing to other environments.

1. install `virtualenv` package: 
    - `$ pip install virtualenv`
    

2. create an environment: in terminal, go to the directory you will be working in. Next, create a virtual environment where you will install the packages needed for the projects (e.g. new virtualenv called _ppdenv_).

    - Linux: `$ virtualenv -p python3 ppdpenv`
    
    - Win: `$ virtualenv -p python ppdpenv`
    
    If Python 3 is not part of your PATH, you can use the full path to the Python executable you want to use inside your virtualenv. 

3. Activate the virtual environment

    - Linux: `$ source ./ppdpenv/bin/activate`
    
    - Win (CMD): `$ ppdpenv\Scripts\activate`
    
    Whenever we have this environment active and install a new package using the pip command, the new package will only be installed in this environment, and will only be available to programs while this environment is active. Check Python version with `python3 --version`.
    
4. Exit virtual environment: `$ deactivate`

<u>Note</u>: when activating on Win Powershell/Terminal, check the execution policy of the terminal with `Get-ExecutionPolcy`. If `Restricted`, set it to another state in order to activate the virtualenv:
- `Set-ExecutionPolicy unrestricted`
- `Set-ExecutionPolicy restricted`
- `Set-ExecutionPolicy remotesigned`
- `Set-ExecutionPolicy allsigned`


## Metaclasses

- **Metaclass**: In object-oriented programming, a metaclass is a class whose instances are classes. Just as an ordinary class defines the behavior of certain objects, a metaclass defines the behavior of certain classes and their instances. Not all object-oriented programming languages support metaclasses. Among those that do, the extent to which metaclasses can override any given aspect of class behavior varies. Metaclasses can be implemented by having classes be first-class citizens, in which case a metaclass is simply an object that constructs classes. Each language has its own metaobject protocol, a set of rules that govern how objects, classes, and metaclasses interact.
- **Abstract Type**: In programming languages, an abstract type is a type in a nominative type system that cannot be instantiated directly; a type that is not abstract – which can be instantiated – is called a **Concrete Type**. <u>Every instance of an abstract type is an instance of some concrete subtype</u>. Abstract types are also known as existential types.
An abstract type may provide no implementation, or an incomplete implementation. In some languages, abstract types with no implementation (rather than an incomplete implementation) are known as protocols, interfaces, signatures, or class types. In class-based object-oriented programming, abstract types are implemented as abstract classes (also known as abstract base classes), and concrete types as concrete classes. In generic programming, the analogous notion is a concept, which similarly specifies syntax and semantics, but does not require a subtype relationship: two unrelated types may satisfy the same concept.
Often, abstract types will have one or more implementations provided separately, for example, in the form of concrete subtypes that can be instantiated. In object-oriented programming, an abstract class may include abstract methods or abstract properties that are shared by its subclasses. Other names for language features that are (or may be) used to implement abstract types include traits, mixins, flavors, roles, or type classes.

### `abc` module.

Metaclass:

```python
from abc import ABCMeta

class ABCMeta(type):
    """Metaclass for defining Abstract Base Classes (ABCs).

    Use this metaclass to create an ABC.  An ABC can be subclassed
    directly, and then acts as a mix-in class.  You can also register
    unrelated concrete classes (even built-in classes) and unrelated
    ABCs as 'virtual subclasses' -- these and their descendants will
    be considered subclasses of the registering ABC by the built-in
    issubclass() function, but the registering ABC won't show up in
    their MRO (Method Resolution Order) nor will method
    implementations defined by the registering ABC be callable (not
    even via super()).
    """

```

Abstract method as decorator:

```python
def abstractmethod(funcobj):
    """A decorator indicating abstract methods.

    Requires that the metaclass is ABCMeta or derived from it.  A
    class that has a metaclass derived from ABCMeta cannot be
    instantiated unless all of its abstract methods are overridden.
    The abstract methods can be called using any of the normal
    'super' call mechanisms.

    Usage:

        class C(metaclass=ABCMeta):
            @abstractmethod
            def my_abstract_method(self, ...):
                ...
    """
    funcobj.__isabstractmethod__ = True
    return funcobj
```