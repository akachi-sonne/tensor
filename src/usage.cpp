
  /*********************************************************************************\
 *                                                                                  *
 * @file: usage.cpp                                                                 *
 * @author: Doug Palmer                                                             *
 *                                                                                  *
 *----------------------------------------------------------------------------------*
 *                                                                                  *
 * Description:                                                                     *
 *                                                                                  *
 * The tensor library allows for the creation and manipulation of an N-dimensional  *
 * tensor object. Tensors are stored in a contiguous array on the heap to allow for *
 * relatively large objects to be created without any worry of stack overflow.      *
 *                                                                                  *
 * Member variables include size, rank, shape, and container.  Size is the total    *
 * amount of elements in the tensor, rank is the amount of dimensions, and shape is *
 * the length of each dimension. Container is the linear array that stores all the  *
 * elements. Size, rank and shape can be accessed with methods of the same name,    *
 * while container remains private and can only be accessed indirectly using        *
 * operators and public methods.                                                    *
 *                                                                                  *
 * It includes basic array methods such as sort(), reverse(), and print(). It also  *
 * has a variety of overloaded operators to both make element access intuitive as   *
 * well as perform complex operations.                                              *
 *                                                                                  *
 * Following is a basic walkthrough of usage of this library. Feel free to          *
 * copy/paste or edit, play, and break this file to your heart's delight. It can    *
 * always be cloned from the repository again!                                      *
 *                                                                                  *
  \********************************************************************************/


// includes //
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include "tensor.hpp"

int main()
{
     /*************************\
     * Instantiating an object *
     \*************************/

    // Note: This is a template class, so any object must have type specified upon
    // instantiation.

    // Default constructor //
    {

        // Initializes size and rank to zero, shape to {}, and container to nullptr.
        Tensor<int> object;

    }

    // Constructor with size as a parameter //
    {

        // Takes an unsigned integer as a parameter
        // This will create a standard linear array of length 25
        // with all elements assigned to zero.
        Tensor<double> object(25);
        std::cout << "Constructor with size as a parameter: " << std::endl;

        // outputting elements via iterator and range based loop.
        for (double element : object )
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
        for ( int element : objectA )
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

     /*******************************\
    *  Element Access and Assignment  *
     \*******************************/

    // Both the [] and () operators and a bi-directional iterator is available
    // for indivdual element access.
    // The = operator is overloaded for fill, copy, and move assignment.

    { // [] and = operators to assign random values

        srand( time( NULL ) );

        // Initializing object of size 25
        Tensor<int> object(25);

        // Using the Assignment and Array Access Operator with a basic for loop
        // to assign every element to a random value of type T between 1 - 100.
        // Note: This same for loop will function identically on a Tensor of any rank
        for ( int i = 0; i < object.size(); i++ )
        {
            object[i] = rand() % 100;
        }

        std::cout << "Assigning each element to rand % 100: " << std::endl;
        object.print(); // printing object to terminal

        // Individual element access on linear array.
        std::cout << "object[3] = " << object[3] << std::endl;

        // Python style reverse iteration using negative indices
        std::cout << "object[-1] = " << object[-1] << std::endl;

    }

    { // () operator for element access of N-dimensional Tensor

        srand( time( NULL ) );

        // Initializing object of shape 3x3x3
        Tensor<int> object( {3, 3, 3} );

        // Using the Assignment and Array Access Operator with a basic for loop
        // to assign every element to a random value of type T between 1 - 100.
        for ( int i = 0; i < object.size(); i++ )
        {
            object[i] = rand() % 100;
        }

        std::cout << "Assigning each element to rand % 100: " << std::endl;
        object.print(); // printing object to terminal

        // Individual element access on ND Tensor using () operator.
        // Accepts an lvalue or rvalue std::vector.
        std::cout << "object( {0,1,2} ) = " << object( {0, 1, 2} ) << std::endl;

    }

    { // Bi-directional Iterator

        Tensor<int> object( {3,3,3} );

    }

    { // Fill Assignment Operator
        // Simply a light wrapper of std::fill using = operator

        // Initializing object of size 25
        Tensor<int> object(25);

        // Using Fill Assignment Operator to assign every element to the same value.
        object = 1;

        std::cout << "Assigning every element to the same value using Fill Assignment Operator: " << std::endl;
        object.print(); // printing object to terminal

    }

    { // Copy Assignment Operator

        // Initializing a 3x3x3 Tensor and assigning random values.
        srand ( time( NULL ) );
        Tensor<int> object( {3,3,3} );
        for ( int i = 0; i < object.size(); i++ )
        {
            object[i] = rand() % 1000;
        }

        // Making a deep copy of the object into a new object.
        Tensor<int> objectCopy = object;

        objectCopy.print(1); // Printing to terminal with verbose option set to true.

    }

    { // Move Assignment Operator

        // Initializing two 3x3 tensors to random values and printing objects.
        srand ( time ( NULL ) );
        Tensor<int> objectA( {3, 3} );
        Tensor<int> objectB( {3, 3} );
        for ( int i = 0; i < objectA.size(); i++ )
        {
            objectA[i] = rand() % 1000;
            objectB[i] = rand() % 1000;
        }

        std::cout << "objectA: " << std::endl;
        objectA.print();

        std::cout << "objectB: " << std::endl;
        objectB.print();

        // Matrix addition of objectA and objectB and
        // assigning the rvalue result to a new object.
        Tensor<int> objectResult = objectA + objectB;

        std::cout << "objectA + objectB: " << std::endl;
        objectResult.print();

    }

    // print() //
    // While an iterator is available with this library, this simple print 
    // method auto-formats to the objects shape and prints accordingly. There
    // is also a 'verbose' option which also prints out size, shape, and rank.
    {

        Tensor<int> objectA( {3,3,3} ); // 3x3x3 Tensor
        Tensor<int> objectB(25); // Simple linear array with 25 elements
        objectA = 0;
        std::cout << "objectA printing..." << std::endl;
        objectA.print();

        std::cout << "objectB printing..." << std::endl;
        objectB.print();

        // Simply pass any truthy argument as a parameter (preferable true or 1) for 
        // the verbose option.
        std::cout << "objectA printing verbose..." << std::endl;
        objectA.print(1);

        std::cout << "objectB printing verbose..." << std::endl;
        objectB.print(true);

    }

    // print_flat() //
    // Prints a Tensor of any dimension as a 1-dimensional array.
    // Does not include a verbose option.
    {

        Tensor<int> object( {3,3,3} );

        object.print_flat();

    }

    // sort() //
    // Sorts Tensor's linear array representation in memory using
    // the merge sort algorithm.
    {

        srand( time( NULL ) );

        Tensor<int> object(25); 

        for ( int i = 0; i < object.size(); i++ )
        {
            object[i] = rand() % 100;
        }

        std::cout << "object after random initialization: " << std::endl;
        object.print();
        std::cout << "bool is_sorted(): " << object.is_sorted() <<"\n" << std::endl;

        object.sort();
        std::cout << "object after sort method: " << std::endl;
        object.print();
        std::cout << "bool is_sorted(): " << object.is_sorted() << "\n" << std::endl;

        // pass a truthy value in the sort method to reverse sort. object.sort(1) is 
        // acceptable.
        object.sort(true);
        std::cout << "object after reverse sort: " << std::endl;
        object.print();
        std::cout << "bool is_sorted(): " << object.is_sorted() << "\n" << std::endl;

    }

    // reverse() //
    // reverses linear array representation in memory of tensor in place
    {
        srand( time( NULL ) );

        Tensor<int> object(25);

        for ( int i = 0; i < object.size(); i++ )
        {
            object[i] = rand() % 100;
        }

        std::cout << "Object after randome initialization: " << std::endl;
        object.print();

        std::cout << "Object after reverse method: " << std::endl;
        object.reverse();
        object.print();
    }

    return 0;
} // End main()

