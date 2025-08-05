/*
Flexible Array Members (FAM):
A flexible array member is an array with no size declared at the end of a struct.
It allows the structure to have a variable-length array whose size is determined at runtime.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Packet {
    int length;
    char data[];  // FAM
};

void fam() {
    const char* msg = "Hello, world!";
    int msg_len = strlen(msg) + 1;  // +1 for null terminator

    // Allocate memory for struct + actual data
    struct Packet* p = malloc(sizeof(struct Packet) + msg_len);

    p->length = msg_len;
    memcpy(p->data, msg, msg_len);

    printf("Packet length: %d\n", p->length);
    printf("Packet data: %s\n", p->data);

    free(p);

    /*
    FAM must always be the last member of the struct.
    You must manually allocate extra memory after the struct to use it.
    Commonly used in networking, file parsers, dynamic data structures, etc.
    Introduced in C99. Before that, people used a trick like char data[1]; instead.
    */
}

int main() {
    fam();

    return 0;
}