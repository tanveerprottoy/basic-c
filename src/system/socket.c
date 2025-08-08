#include <arpa/inet.h>   // For htons(), inet_addr()
#include <netinet/in.h>  // For struct sockaddr_in
#include <stdio.h>       // For perror()
#include <stdlib.h>      // For exit()
#include <string.h>      // For memset()
#include <sys/socket.h>  // For socket(), bind(), listen(), accept()
#include <unistd.h>      // For close(), write()

/*
What is a Socket?
An endpoint for communication.
Supports network I/O (TCP/UDP over IP).
Represented by a file descriptor — yes, sockets use FDs too.

Socket System Calls:
| Function                                | Purpose                             |
| --------------------------------------- | ----------------------------------- |
| `socket()`                              | Create a socket (returns FD)        |
| `bind()`                                | Assign IP + port to the socket      |
| `listen()`                              | Mark the socket as passive (server) |
| `accept()`                              | Accept incoming connection          |
| `connect()`                             | Initiate connection (client)        |
| `read()`/`write()` or `recv()`/`send()` | Data I/O                            |
| `close()`                               | Close socket                        |
*/

void tcp_server_simple() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 10);

    int client_fd = accept(server_fd, NULL, NULL);
    write(client_fd, "Hello\n", 6);
    close(client_fd);
}

void tcp_server_simple2() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));  // Optional: clear memory
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);  // Host to network byte order
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) == -1) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    int client_fd = accept(server_fd, NULL, NULL);
    if (client_fd == -1) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    write(client_fd, "Hello\n", 6);
    close(client_fd);
    close(server_fd);
}