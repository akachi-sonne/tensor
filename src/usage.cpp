
 /********************************************************************************************************\
 * @file: usage.cpp                                                                                       *
 * @author: Doug Palmer                                                                                   *
 *                                                                                                        *
 *                                                                                                        *
 * Description:                                                                                           *
 *                                                                                                        *
 * The tensor library allows for the creation and manipulation of an N-dimensional tensor object.         *
 * Tensors are stored in a contiguous array on the heap to allow for relatively large objects to be       *
 * created without any worry of stack overflow.                                                           *
 *                                                                                                        *
 * Member variables include size, rank, shape, and container.  Size is the total amount of elements in    *
 * the tensor, rank is the amount of dimensions, and shape is the length of each dimension. Container     *
 * is the linear array that stores all the elements. Size, rank and shape can be accessed with methods    *
 * of the same name, while container remains private and can only be accessed indirectly using operators  *
 * and public methods.                                                                                    *
 *                                                                                                        *
 * It includes basic array methods such as sort(), reverse(), and print(). It also has a variety of over- *
 * loaded operators to both make element access intuitive as well as perform complex operations.          *
 *                                                                                                        *
 * Following is a basic walkthrough of usage of this library.                                             *
 *                                                                                                        *
 \********************************************************************************************************/


// includes
#include<iostream>
#include<stdlib>
#include<time.h>
#include "tensor.hpp"


 /*************************\
 * Instantiating an object *
 \*************************/

// Note: This is a template class, so any object must have type specified upon instantiation. //

// Default constructor //
{
    // Initializes size and rank to zero, shape to {}, and container to nullptr. //
    Tensor<int> object();
}

// Constructor with size as a parameter //
{
    // Takes an unsigned integer as a parameter //
    // This will create a standard linear array of length 25 //
    Tensor<double> object(25);
}

// Constructor with shape as a parameter //
{
    // Takes an std::vector of unsigned integers as a parameter //
    // This will create a 3x3x3 Tensor of rank 3 and size 27. //
    Tensor<float> object( {3, 3, 3} )
}

// Copy constructor //
{
    Tensor<int> objectA();
    // Makes deep copy of objectA into newly instantiated objectB //
    // Must be same data type. //
    Tensor<int> objectB(objectA);
}




