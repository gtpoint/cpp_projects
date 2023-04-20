# Calculator Project

The objective is to build a stack-based calculator for complex numbers and provide it with a text-based menu interface. The stack management will be similar to a calculator with a stack capacity of 4.
Using a `stack` allows for the elimination of parentheses through potential reorganization of calculations. Instead of writing in infix form `where the operator is placed between operands`, the calculator will use postfix form `where the operator is placed after operands`.

**The possible operations on the calculator include:**

Entering a new complex number, which becomes the top element of the stack.
Performing a unary operation `such as inverting or negating...` on the value at the top of the stack.
Performing a binary operation `such as addition...` on the top two values of the stack.
Displaying the complete contents of the stack `starting with the top element`.
The characteristics of the stack are as follows:

It has a fixed size and can hold four values.
Upon initial startup, the stack contains only null values.
When the user enters a new value, the bottom value of the stack is lost.
When the user removes a value from the stack `e.g., after a binary arithmetic operation`, the remaining values in the stack move up, and the bottom value of the stack is duplicated.


## 1-Complex Numbers:
A complex number is defined as a pair of real numbers, the first one called its real part and the second one called its imaginary part. Arithmetic operations are defined on complex numbers. For this programming assignment (TP), we will focus on the following operations:
Initializing a complex number: A complex number can be initialized with values for its real and imaginary parts, or with a real number where the imaginary part is zero. If no information is provided, the complex number is initialized to zero.
+ Adding two complex numbers: This can be done by adding a complex number to an existing complex number, or by creating a new complex number that is the sum of two existing complex numbers.
+ Multiplying by `i`: This is a standard multiplication, for example: `(10+4i)*i = -4+10i`.
+ Displaying a complex number in the form of real part + imaginary part.

## 2-Stack:
The stack will have a fixed size of 4.
Initially, it contains 4 complex numbers with zero values. The operations that can be performed on the stack are: displaying the stack starting from the top, pushing a new complex number onto the stack `the complex number at the bottom of the stack is lost`, popping the complex number from the top of the stack `the value from the bottom of the stack moves up`, and getting the complex number from the top of the stack.

## 3-Calculator:
The calculator will consist of a stack of complex numbers and a single memory to store a complex number. The available operations on the calculator are: displaying the stack, entering a new real number, multiplying the value at the top of the stack by 'i', performing the sum of two complex numbers at the top of the stack and replacing them with the result, storing the value at the top of the stack in memory, and adding the stored value to the top of the stack.

## 4-Text-based Menus:
The user interface will be based on text-based menus that provide access to the operations of the calculator `such as adding a real number, multiplying by `i`, performing a sum ...` .
