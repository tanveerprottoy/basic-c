#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

/*
What does fork() do?
It creates a new process by duplicating the calling process.
The new process is called the child, and the original is the parent.

Behavior:
Returns 0 to the child
Returns PID of child to the parent
Returns -1 on error
*/

void fork_ex() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
    } else if (pid == 0) {
        printf("Child process: PID=%d\n", getpid());
    } else {
        printf("Parent process: PID=%d, Child PID=%d\n", getpid(), pid);
    }

    // Both processes run concurrently after fork().
}

/*
What is exec()?
It replaces the current process image with a new program.
After a successful exec(), the old code never resumes.

There are many variants:
execl(), execp(), execv(), execvp(), etc.
*/

// Common: execl()
int execl_ex() {
    printf("Running ls...\n");
    execl("/bin/ls", "ls", "-l", NULL);
    perror("execl failed");  // only prints if exec fails

    /*
    If exec() succeeds, it does not return.
    If it fails, it returns -1.
    */
}

/*
Process Control
Functions:
getpid() / getppid()
 Get current process ID / parent process ID

wait() / waitpid()
 Wait for child processes to finish

exit()
 Terminates a process with a status code

kill(pid, sig)
 Send a signal to a process
*/
int process_ctl() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child PID: %d\n", getpid());
    } else {
        int status;
        wait(&status);
        printf("Child exited with status %d\n", WEXITSTATUS(status));
    }

    // send a signal to a process
    kill(getpid(), SIGTERM);
}

/*
summary:
| Feature             | Function(s)                    | Purpose                              |
| ------------------- | ------------------------------ | ------------------------------------ |
| Signal              | `signal()`, `sigaction()`      | Handle asynchronous events           |
| Process creation    | `fork()`                       | Duplicate process                    |
| Program replacement | `exec()`                       | Run a new program in current process |
| Process control     | `getpid()`, `wait()`, `kill()` | Manage and interact with processes   |

*/