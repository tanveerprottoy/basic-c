#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

// Function taking a function pointer as argument
int operate(int x, int y, int (*op)(int, int)) {
    return op(x, y);
}

/*
In C programming, a function pointer is a variable that stores the memory address of a
function. This allows you to treat functions as values, enabling dynamic function calls,
callbacks, and more flexible program design
The syntax for declaring a function pointer is:
return_type (*pointer_name)(parameter_types);
example:
int (*func_ptr)(int, int); // pointer to a function taking two ints and returning an int
*/
void function_pointer() {
    int (*func_ptr)(int, int);

    func_ptr = add;

    func_ptr = &add;  // alternative way

    // calling exmaples
    int result = func_ptr(3, 4);  // works
    // or
    int result = (*func_ptr)(3, 4);  // also works
}

// Passing Function Pointers to Other Functions
// You can pass function pointers as arguments to implement callbacks or behavior customization
void pass_funcion_to_other_function() {
    printf("Add: %d\n", operate(10, 5, add));
    printf("Subtract: %d\n", operate(10, 5, subtract));
}

/*
Using Arrays of Function Pointers
Useful for implementing jump tables or replacing switch-case:
*/
void arrays_of_function_pointers() {
    int (*ops[2])(int, int);  // array of function pointers
    ops[0] = add;
    ops[1] = subtract;

    printf("Add: %d\n", ops[0](3, 2));
    printf("Subtract: %d\n", ops[1](3, 2));
}

// function Pointers as Return Types
int (*get_func())(int, int) {
    return add;
}

void function_pointer_as_return_type() {
    int (*func)(int, int) = get_func();
    printf("Result: %d\n", func(2, 5));
}
