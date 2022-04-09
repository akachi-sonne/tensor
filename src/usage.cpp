
  /******************************************************************************************************\
 *                                                                                                        *
 * @file: usage.cpp                                                                                       *
 * @author: Doug Palmer                                                                                   *
 *                                                                                                        *
 *--------------------------------------------------------------------------------------------------------*
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
 * Following is a basic walkthrough of usage of this library. Feel free to copy/paste or edit, play, and  *
 * break this file to your heart's delight. It can always be cloned from the repository again!            *
 *                                                                                                        *
  \******************************************************************************************************/


// includes //
#include<iostream>
#include<stdlib>
#include<time.h>
#include "tensor.hpp"

int main()
{
     /*************************\
     * Instantiating an object *
     \*************************/

    // Note: This is a template class, so any object must have type specified upon instantiation.

    // Default constructor //
    {

        // Initializes size and rank to zero, shape to {}, and container to nullptr.
        Tensor<int> object();

    }

    // Constructor with size as a parameter //
    {

        // Takes an unsigned integer as a parameter
        // This will create a standard linear array of length 25
        // with all elements assigned to zero.
        Tensor<double> object(25);
        std::cout << "Constructor with size as a parameter: " << std::endl;

        // outputting elements via iterator and range based loop.
        for ( element : object )
            std::cout << element << " ";
        std::cout << std::endl;

    }

    // Constructor with shape as a parameter //
    {

        // Takes an std::vector of unsigned integers as a parameter
        // This will create a 3x3x3 Tensor of rank 3 and size 27. 
        Tensor<float> object( {3, 3, 3} );
        std::cout << "Constructor with shape as a parameter: " << std::endl;

        // built in print method
        object.print();

    }

    // Copy constructor //
    {

        Tensor<int> objectA(25);
        // Makes deep copy of objectA into newly instantiated objectB
        // Must be same data type.
        Tensor<int> objectB(objectA);

        std::cout << "Constructor with shape as a parameter: " << std::endl;
        std::cout << "objectA: " << std::endl;
        for ( element : objectA )
            std::cout << element << " ";
        std::cout << std::endl;

    }


      /********************\
     *    Member methods    *
      \********************/

    // Access member variables
    // Get size, shape, and rank.
    {

        // Instantiating object of shape 3x3x3.
        Tensor<int> object( {3,3,3} );

        // Get size. //
        int size = object.size();
        // Get rank //
        int rank = object.rank();
        // Get shape //
        std::string shape = object.shape();

    }

    // index() //
    // Get the 1-dimensional equivalent to an N-dimensional coordinate.
    {

        Tensor<int> object( {3,3,3} );
        // Returns single integer //
        int index = object.index( {0,1,0} );

    }

    // print() //
    // While am iterator is available with this library, this simple print 
    // method auto-formats to the objects shape and prints accordingly. There
    // is also a 'verbose' option which also prints out size, shape, and rank.
    {

        Tensor<int> objectA( {3,3,3} ); // 3x3x3 Tensor
        Tensor<int> objectB(25); // Simple linear array with 25 elements

        objectA.print();
        objectB.print();

        // Simply pass any truthy argument for the verbose option.
        objectA.print(1);
        objectB.print(1);

    }

    // print_flat() //
    // Prints a Tensor of any dimension as a 1-dimensional array.
    // Does not include a verbose option.
    {

        Tensor<int> object( {3,3,3} );

        object.print_flat();

    }



    return 0;
} // End main()

