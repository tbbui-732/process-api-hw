#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/* CUSTOM TYPES */
typedef enum { FALSE, TRUE } bool_t;

/* FORWARD DECLARATIONS */
bool_t change_value(const pid_t pid);

int main() {
    pid_t pid = fork();
    bool_t change_value_state = change_value(pid);
    if (!change_value_state) {
        perror("unable to fork program");
    }
    return 0;
}


/* FUNCTION DEFINITIONS */
bool_t change_value(const pid_t pid) {
    int shared_value = 100;
    const int CHILD_VALUE = 50;
    const int PARENT_VALUE = 75;

    if (pid < 0) { /* failure, just like you*/
        return FALSE;
    }

    if (pid == 0) { /* child */
        printf("child before: %d\n", shared_value);
        shared_value += CHILD_VALUE;
        printf("child after: %d (expecting 150)\n", shared_value);
    } else { /* parent */
        wait();
        printf("parent before: %d\n", shared_value);
        shared_value += PARENT_VALUE;
        printf("parent after: %d (expecting 175)\n", shared_value);
    }

    return TRUE;
}
