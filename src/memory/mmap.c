#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

/*
In C, memory-mapped files using mmap() allow you to map a file or device into memory so that the contents of the file can be accessed just like an array in your program — without needing to call read() or write() repeatedly.

This is efficient, especially for large files, because it allows direct memory access to file contents and can reduce system call overhead.

Use cases
Efficient file I/O for large files

Shared memory between processes

Memory-efficient read/write of files

Executing code directly from disk (used by OS loaders)

How it works
When you use mmap():

The OS maps a portion (or the whole) of a file into the virtual address space of your process.

This memory region behaves like an array: you can read, write, memcpy, etc.

Changes made in memory can be synced back to disk (depending on flags).

mmap() Function Prototype
#include <sys/mman.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
Parameters:
| Argument | Meaning                                                                    |
| -------- | -------------------------------------------------------------------------- |
| `addr`   | Optional starting address in memory (usually `NULL`)                       |
| `length` | How many bytes to map                                                      |
| `prot`   | Memory protection: read/write/exec (`PROT_READ`, `PROT_WRITE`, etc.)       |
| `flags`  | Behavior flags (`MAP_SHARED`, `MAP_PRIVATE`, etc.)                         |
| `fd`     | File descriptor (opened with `open()`)                                     |
| `offset` | Offset in the file to start mapping from (must be a multiple of page size) |

Common prot values:
| Flag         | Description              |
| ------------ | ------------------------ |
| `PROT_READ`  | Pages can be read        |
| `PROT_WRITE` | Pages can be written     |
| `PROT_EXEC`  | Pages can be executed    |
| `PROT_NONE`  | Pages cannot be accessed |

Common flags values:
| Flag            | Description                                                        |
| --------------- | ------------------------------------------------------------------ |
| `MAP_SHARED`    | Changes are visible to other processes and written to file         |
| `MAP_PRIVATE`   | Changes are private (copy-on-write)                                |
| `MAP_ANONYMOUS` | Not backed by any file (used for shared memory or scratch buffers) |

munmap()
To unmap a region, use:
int munmap(void *addr, size_t length);
*/

void read_file() {
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("fstat");
        close(fd);
        return 1;
    }

    size_t size = st.st_size;

    char* data = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    write(STDOUT_FILENO, data, size);  // Output file content

    munmap(data, size);
    close(fd);
}

// Modify a file using mmap()
void mod_file() {
    int fd = open("example.txt", O_RDWR);
    char* data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    data[0] = 'X';               // Modify first byte
    msync(data, size, MS_SYNC);  // Ensure changes written to disk
    munmap(data, size);
}

/*
Caveats
The offset must be page-aligned (usually 4096 bytes).
You should msync() if you want to guarantee changes are flushed to disk.
mmap() can fail if file size is zero or not accessible.
Writing to a MAP_PRIVATE mapping won't affect the underlying file.
Be careful with concurrent access; for shared memory, you need semaphores or mutexes.

Page alignment (for offset)
Use sysconf(_SC_PAGE_SIZE) to get the system's page size.

Advanced Uses
Shared memory between processes using MAP_SHARED and MAP_ANONYMOUS.
File-backed memory for large databases or caches.
Memory-based IPC between unrelated processes.
*/