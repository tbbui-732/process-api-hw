#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/* CUSTOM TYPES */
typedef enum { FALSE, TRUE } bool_t;

/* FORWARD DECLARATIONS */
int update_shared_val();

int main() {
    if (!update_shared_val()) {
        return EXIT_FAILURE;
    }
    return 0;
}


/* FUNCTION DEFINITIONS */
int update_shared_val() {
    pid_t pid = fork();

    int shared_value = 100;
    const int CHILD_VALUE = 50;
    const int PARENT_VALUE = 75;

    if (pid < 0) {
        /* failure, just like you*/
        perror("");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        /* child process */
        printf("child before: %d\n", shared_value);
        shared_value += CHILD_VALUE;
        printf("child after: %d (expecting 150)\n", shared_value);
    } else {
        /* parent process */
        int status;
        pid_t child_pid = wait(&status);
        if (child_pid == -1) {
            perror("wait() failed");
            return EXIT_FAILURE;
        }
        printf("parent before: %d\n", shared_value);
        shared_value += PARENT_VALUE;
        printf("parent after: %d (expecting 175)\n", shared_value);
    }

    return EXIT_SUCCESS;
}
