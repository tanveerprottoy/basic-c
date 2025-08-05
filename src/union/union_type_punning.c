#include <stdio.h>

/*
A union is like a struct where all members share the same memory. At any time,
only one member should be considered "active".
Memory Layout:
The union's size is equal to the size of its largest member.
All members start at the same memory address.
*/
union Data {
    int i;
    float f;
};

void union_example() {
    union Data d;

    d.i = 42;
    printf("int: %d\n", d.i);

    d.f = 3.14;
    printf("float: %f\n", d.f);

    // Accessing d.i now is undefined behavior
    printf("int after float: %d\n", d.i);  // Type punning
}

/*
Type punning is a technique where you access the same memory location using different
types—often through union, pointer casts, or memcpy.
*/
union Pun {
    float f;
    int i;
};

void type_punning_unsafe() {
    union Pun p;
    p.f = 3.14f;

    printf("Float as int: %x\n", p.i);  // Reinterpret float bits as int

    /*
    Portability Warning:
    Type punning via unions may invoke undefined behavior per strict aliasing rules in
    modern C standards (especially C99+), though most compilers (GCC, Clang) support it
    as an extension.
    */
}

void type_punning_safe() {
    float f = 3.14f;
    int i;

    // Safer Alternative: memcpy Type Punning
    memcpy(&i, &f, sizeof(i));  // Safe reinterpretation

    // This avoids violating aliasing rules and is safe across platforms.
}

/*
summary:
| Feature | Union                                | Type Punning                   |
| ------- | ------------------------------------ | ------------------------------ |
| Memory  | Shared among members                 | Reinterpreting memory          |
| Usage   | Efficient storage for multiple types | Bit-level reinterpretation     |
| Safe?   | Yes if used correctly                | Risky if aliasing rules broken |
*/