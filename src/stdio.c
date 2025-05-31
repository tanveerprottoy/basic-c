#include <stdio.h>

// main function: This is the entry point of the program.
// It takes command line arguments and returns an integer.
int main(int argc, char **argv) {
    printf("length of args: %d\n", argc);

    // Loop through each command line argument
    for (int i = 0; i < argc; i++) {
        // Print the argument and its index
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    return 0;
}
