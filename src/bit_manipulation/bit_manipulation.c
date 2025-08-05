#include <stdio.h>

/*
Bitfields in Structs
Bitfields allow packing data into fewer bits than the full width of a data type (like an int).
Useful for low-memory systems or hardware registers.
0b is a prefix that denotes a binary literal
so the binary number is what comes after 0b prefix
*/
struct Flags {
    unsigned int flag1 : 1;  // 1 bit
    unsigned int flag2 : 3;  // 3 bits
    unsigned int flag3 : 4;  // 4 bits

    /*
    flag1 uses only 1 bit, flag2 uses 3 bits, etc.
    Total size of the struct may still be aligned by the compiler (to a byte or word boundary),
    so check with sizeof().
    Use Cases:
    Represent hardware status registers
    Compress multiple Boolean values
    */
};

void flags_checker() {
    printf("size of Flags: ", sizeof(struct Flags));
}

/*
Bitwise Operations
Used for direct manipulation of bits.
| Operation | Operator | Description                        |
| --------- | -------- | ---------------------------------- |
| AND       | `&`      | Set bits where both operands are 1 |
| OR        | `\|`     | Set bits where at least one is 1   |
| XOR       | `^`      | Set bits where one is 1, not both  |
| NOT       | `~`      | Flip all bits                      |
*/
void bitwise_operations() {
    // 0b is a prefix that denotes a binary literal
    // so the binary number is what comes after 0b prefix
    unsigned char a = 0b1100;  // 12 in decimal
    unsigned char b = 0b1010;  // 10 in decimal

    unsigned char and = a & b;  // 0b1000 = 8
    unsigned char or = a | b;   // 0b1110 = 14
    unsigned char xor = a ^ b;  // 0b0110 = 6
    unsigned char nota = ~a;    // 0b0011  -> actually: 0b11110011 (in 8-bit)

    printf("a     = 0x%02X\n", a);
    printf("b     = 0x%02X\n", b);
    printf("AND   = 0x%02X\n", and);
    printf("OR    = 0x%02X\n", or);
    printf("XOR   = 0x%02X\n", xor);
    printf("NOT a = 0x%02X\n", nota);

    /*
    Explanation of ~a
    Given:
    a = 0b00001100  // 12 in decimal
    Then:
    ~a = 0b11110011  // which is 243 in unsigned, or -13 if interpreted as signed
    So:
    Bitwise NOT (~) inverts every bit: 1 becomes 0, and 0 becomes 1.
    With unsigned char (8 bits), it’s safe to interpret as 8-bit: ~0b00001100 = 0b11110011 = 243
    If char (signed) is used, the result could be negative due to two's complement representation.
    Always use unsigned char when doing bitwise ops unless you want signed behavior.
    */
}

/*
Bit Shifting
| Operation   | Operator | Description                   |
| ----------- | -------- | ----------------------------- |
| Left shift  | `<<`     | Shifts bits to the left (×2)  |
| Right shift | `>>`     | Shifts bits to the right (÷2) |
*/
void bit_shifting() {
    // 0b is a prefix that denotes a binary literal
    // so the binary number is what comes after 0b prefix
    unsigned int x = 0b00000001;

    x = x << 1;  // 0b00000010 => 2
    x = x >> 1;  // 0b00000001 => 1

    /*
    Left shift fills with 0 on right.
    Right shift behavior on signed integers is implementation-defined (logical vs arithmetic shift).
    */
}

/*
Bit Masking
Used to set, clear, toggle, or test specific bits.
Example: Set/Clear/Test bit 3 (counting from 0)
*/

#define BIT3 (1 << 3)

void bit_masking() {
    unsigned char val = 0b00000000;

    // Set bit 3
    val |= BIT3;  // val = 0b00001000

    // Clear bit 3
    val &= ~BIT3;  // val = 0b00000000

    // Toggle bit 3
    val ^= BIT3;  // val = 0b00001000

    // Test bit 3
    if (val & BIT3) {
        // bit is set
        printf("BIT3: ", BIT3);
    }
}