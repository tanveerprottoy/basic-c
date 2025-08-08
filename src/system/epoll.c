#include <stdio.h>
#include <sys/epoll.h>
#include <unistd.h>

/*
epoll in C (Linux only)
What is epoll?
An I/O event notification mechanism.
More scalable than older mechanisms like select() and poll().
Used to handle many FDs efficiently, especially in servers.

epoll APIs:
| Function          | Purpose                                          |
| ----------------- | ------------------------------------------------ |
| `epoll_create1()` | Create an epoll instance (returns FD)            |
| `epoll_ctl()`     | Add, modify, or remove FDs to/from interest list |
| `epoll_wait()`    | Block until events are ready                     |

Advantages of epoll:
| Feature                 | Benefit                              |
| ----------------------- | ------------------------------------ |
| Edge/Level triggered    | Fine-grained control                 |
| O(1) event polling      | Constant time regardless of # of FDs |
| Supports large # of FDs | Ideal for high-perf servers          |

*/

// epoll_event Structure
struct epoll_event {
    uint32_t events;  // EPOLLIN, EPOLLOUT, EPOLLET, etc.
    void* data;       // Can store FD or custom pointer
};

int monitor_stdin() {
    int epfd = epoll_create1(0);

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = 0;  // STDIN

    epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &ev);

    struct epoll_event events[10];
    int n = epoll_wait(epfd, events, 10, -1);

    for (int i = 0; i < n; i++) {
        if (events[i].data.fd == 0) {
            char buf[100];
            int len = read(0, buf, sizeof(buf));
            write(1, buf, len);
        }
    }

    close(epfd);

    /*
    Monitors file descriptor 0 (stdin) for input.
    epoll_wait() blocks until input is available.
    */
}

/*
Summary:
| Concept         | Key Idea                                       |
| --------------- | ---------------------------------------------- |
| File Descriptor | Abstract handle to a file/socket/device        |
| Socket          | File descriptor used for network communication |
| epoll           | Efficiently monitor many FDs for I/O events    |

*/