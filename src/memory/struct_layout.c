#include <stddef.h>
#include <stdio.h>

/*
 Memory Layout of Structs
In C, structs are laid out in memory according to:

The order of their fields.

Their individual alignment requirements.

Any padding inserted to satisfy those requirements.

What Are Alignment and Padding?
Alignment: Each data type typically needs to be aligned in memory to addresses that
are multiples of its size (or alignment requirement). For example, int (4 bytes) should ideally start at an address divisible by 4.

Padding: The compiler may insert unused bytes between members to maintain proper
alignment of the following members.
*/
struct LayoutNotGood {
    char c;   // 1 byte
    short s;  // 2 bytes
    char c2;  // 1 byte
    long l;   // 8 bytes (on 64 bit)
    int i;    // 4 bytes
    /*
    Let’s break it down assuming we're on a 64-bit machine with the following alignment rules (common for x86_64):
    | Type  | Size | Alignment |
    | ----- | ---- | --------- |
    | char  | 1    | 1         |
    | short | 2    | 2         |
    | int   | 4    | 4         |
    | long  | 8    | 8         |

    Alignment requirement is typically equal to the size of the type (with some exceptions)
    Structs are aligned to the size of their largest member (here, long = 8 bytes)

    Key Concepts
    Alignment:
    Each data member in a struct must be stored at a memory address that's a multiple of its alignment.
    Compiler inserts padding bytes between fields if needed to satisfy alignment requirements.

    Padding:
    Extra bytes added by compiler to ensure proper alignment of each member.
    May occur between members and at the end of the struct (called tail padding) to align the whole struct.

    Let’s compute the offsets, alignment, and padding step-by-step.
    | Member | Type  | Size | Required Alignment | Actual Offset | Padding Before?  | Notes                                        |
    | ------ | ----- | ---- | ------------------ | ------------- | ---------------- | -------------------------------------------- |
    | `c`    | char  | 1    | 1                  | 0             | No               | Starts at byte 0                             |
    |        |       |      |                    |               | +1 byte padding  | To align next `short`                        |
    | `s`    | short | 2    | 2                  | 2             | Yes              | Needs to start at even offset                |
    | `c2`   | char  | 1    | 1                  | 4             | No               | Starts at offset 4                           |
    |        |       |      |                    |               | +3 bytes padding | To align next `long` to offset 8             |
    | `l`    | long  | 8    | 8                  | 8             | Yes              | Aligned to 8-byte boundary                   |
    | `i`    | int   | 4    | 4                  | 16            | No               | Starts at offset 16                          |
    |        |       |      |                    |               | +4 bytes padding | Tail padding to align struct size to 8 bytes |

    Final Layout Summary:
    | Field | Offset | Size | Description           |
    | ----- | ------ | ---- | --------------------- |
    | `c`   | 0      | 1    | char                  |
    |       | 1–1    | 1    | padding               |
    | `s`   | 2      | 2    | short                 |
    | `c2`  | 4      | 1    | char                  |
    |       | 5–7    | 3    | padding               |
    | `l`   | 8      | 8    | long                  |
    | `i`   | 16     | 4    | int                   |
    |       | 20–23  | 4    | padding (struct tail) |
    Total size = 24 bytes

    */
};

void not_good_layout_checker() {
    printf("%lu\n", sizeof(struct LayoutNotGood));  // will likely print 24

    printf("Alignment of struct Layout: %zu bytes\n", _Alignof(struct LayoutNotGood));

    // Using offsetof to see the offsets of each member
    printf("Offset of c: %zu\n", offsetof(struct LayoutNotGood, c));
    printf("Offset of s: %zu\n", offsetof(struct LayoutNotGood, s));
    printf("Offset of c2: %zu\n", offsetof(struct LayoutNotGood, c2));
    printf("Offset of l: %zu\n", offsetof(struct LayoutNotGood, l));
    printf("Offset of i: %zu\n", offsetof(struct LayoutNotGood, i));
}

// How to Minimize Padding
// Reorder members from largest to smallest:
struct LayoutGood {
    long l;   // 8 bytes
    int i;    // 4 bytes
    short s;  // 2 bytes
    char c;   // 1 byte
    char c2;  // 1 byte
    /*
    Always group larger types first to reduce padding and save memory when designing structs.
    Total size = 16 bytes (no internal padding, just tail padding)

    Alignment ensures each member starts at a properly aligned address.
    Padding is added to maintain alignment.
    The order of members affects struct size.
    */
};

void good_layout_checker() {
    printf("%lu\n", sizeof(struct LayoutGood));  // will likely print 16

    printf("Alignment of struct Layout: %zu bytes\n", _Alignof(struct LayoutGood));

    // Using offsetof to see the offsets of each member
    printf("Offset of l: %zu\n", offsetof(struct LayoutGood, l));
    printf("Offset of i: %zu\n", offsetof(struct LayoutGood, i));
    printf("Offset of s: %zu\n", offsetof(struct LayoutGood, s));
    printf("Offset of c: %zu\n", offsetof(struct LayoutGood, c));
    printf("Offset of c2: %zu\n", offsetof(struct LayoutGood, c2));
}

// another way can be to group similar type together
// Group Similar Types Together
// Group same-size or similarly aligned types together to minimize internal gaps.
struct LayoutGrouped {
    long l;   // 8
    int i;    // 4
    char c;   // 1
    char c2;  // 1
    short s;  // 2

    /*
    This is still compact:
    l at 0
    i at 8
    c, c2 at 12,  13
    s at 14
    Size: 16 bytes
    Still optimal.Just different grouping.
    */
};

// Manual Packing with #pragma pack (Not always safe)
#pragma pack(push, 1)  // Save current alignment, then set to 1 byte
struct PackedLayout {
    char c;
    short s;
    char c2;
    long l;
    int i;

    /*
    Size: 16 bytes
    This disables alignment padding and can lead to unaligned access, which is unsafe or slow on some architectures.
    */
};
#pragma pack(pop)  // Restore previous alignment

int main() {
    not_good_layout_checker();

    good_layout_checker();

    return 0;
}