#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/*
What are signals?
Signals are software interrupts sent to a process to notify it of events like exceptions (e.g., division by zero), user actions (Ctrl+C), or IPC (Inter-Process Communication).

Common Signals:
| Signal    | Name | Meaning                            |
| --------- | ---- | ---------------------------------- |
| `SIGINT`  | 2    | Interrupt (Ctrl+C)                 |
| `SIGTERM` | 15   | Termination request                |
| `SIGKILL` | 9    | Kill (cannot be caught or ignored) |
| `SIGSEGV` | 11   | Segmentation fault                 |
| `SIGCHLD` | 17   | Child process terminated           |
| `SIGALRM` | 14   | Alarm clock                        |
| `SIGHUP`  | 1    | Hangup detected                    |
*/

// Handling Signals
// You can handle signals using:
// 1. signal()(older, simple)
void handle_sigint(int sig) {
    printf("Caught SIGINT (Ctrl+C), signal %d\n", sig);
}

void handle_signal() {
    signal(SIGINT, handle_sigint);  // set handler
    while (1)
        ;  // loop forever
}

// 2. sigaction() (modern, preferred)
void handler(int sig) {
    printf("Received signal %d\n", sig);
}

int handle_sigaction() {
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGTERM, &sa, NULL);
    pause();  // Wait for signal
}
