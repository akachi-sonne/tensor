# Tensor
Tensor arithmetic library for c++
## UNDER CONSTRUCTION

## Description

Dynamically allocated virtual N-dimensional array class stored in contiguous
block of memory allowing for tensor arithmetic.

The tensor library allows for the creation and manipulation of an N-dimensional
tensor object. Tensors are stored in a contiguous array on the heap to allow for
relatively large objects to be created without any worry of stack overflow.

Member variables include size, rank, shape, and container.  Size is the total
amount of elements in the tensor, rank is the amount of dimensions, and shape is
the length of each dimension. Container is the linear array that stores all the
elements. Size, rank and shape can be accessed with methods of the same name,
while container remains private and can only be accessed indirectly using
operators and public methods.

It includes basic array methods such as sort(), reverse(), and print(). It also
has a variety of overloaded operators to both make element access intuitive as
well as perform complex operations.

## Usage
Following is a basic walkthrough of usage of this library. To view, run, or edit example code,
check out the [usage.cpp]()(https://github.com/akachi-sonne/tensor/blob/main/src/usage.cpp) file.

#### *Constructing a Tensor Object*

- Default constructor
Initializes size and rank to zero, shape to {}, and container to nullptr.
```````````````````````````````
