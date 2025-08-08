/*
Header Files (.h files):
Header files contain declarations (not definitions) of functions, variables, macros, structs, etc.
They allow separation of interface (API) from implementation.

This header can be included in many .c files via #include "math.h".
Helps with modularity and code reuse
Avoids duplication of declarations
Ensures consistent declarations across source files
*/

#ifndef MATH_H
#define MATH_H

int add(int, int);      // Function declaration
extern int global_var;  // Variable declaration

#endif
