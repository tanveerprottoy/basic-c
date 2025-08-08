#include <stdio.h>

/*
 What are they header files?
Header files contain declarations (not definitions) of functions, variables, macros,
structs, etc. They allow separation of interface (API) from implementation.

Linkage in C:
Linkage refers to the visibility and binding of identifiers (functions or variables)
across translation units (source files).

Types of Linkage:
| Linkage Type | Keyword            | Meaning                                                                |
| ------------ | ------------------ | ---------------------------------------------------------------------- |
| **External** | default / `extern` | Identifier is visible across different source files                    |
| **Internal** | `static`           | Identifier is only visible within the file it's defined in             |
| **None**     | local variables    | Identifier is only visible within a block (function scope, no linkage) |


summary:
| Concept         | Static Library          | Dynamic Library          | Header File               |
| --------------- | ----------------------- | ------------------------ | ------------------------- |
| Usage           | Code copied into binary | Code loaded at runtime   | Used for declarations     |
| File Extensions | `.a` / `.lib`           | `.so` / `.dll`           | `.h`                      |
| Linking Time    | Compile time            | Runtime                  | Preprocessing/compilation |
| Portability     | Self-contained          | Needs runtime dependency | Not compiled              |
| Linkage Keyword | —                       | —                        | `extern`, `static`, etc.  |

*/

// Variables declared extern are not definitions. Definitions allocate storage.
// Declarations only tell the compiler about existence.
extern int global_var;  // Declaration to link to file1.c's definition

static int helper_func() {  // Only visible in this file
    return 42;
}
