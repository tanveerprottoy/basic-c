#include <fcntl.h>
#include <unistd.h>

/*
What is a File Descriptor?
An integer handle used by the operating system to abstract file, socket, pipe, or device access.

Every time you open a file (or socket, or pipe), the kernel gives you a file descriptor.

Common File Descriptors
0  -> STDIN
1  -> STDOUT
2  -> STDERR
*/

void fd() {
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buffer[100];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead > 0) {
        write(1, buffer, bytesRead);  // write to STDOUT (fd = 1)
    }

    close(fd);
    /*
    open() returns a file descriptor.
    read() and write() use file descriptors to perform I/O.
    close() releases the FD.

    File Descriptor Table
    Each process has its own file descriptor table.
    The kernel maps file descriptors to actual file or socket objects internally.
    */
}
