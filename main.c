#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int shared_value = 100;
    const int CHILD_VALUE = 50;
    const int PARENT_VALUE = 75;
    pid_t pid = fork();
    if (pid < 0) { /* failure */
        perror("unable to fork program");
        return EXIT_FAILURE;
    } else if (pid == 0) { /* child */
        printf("child before: %d\n", shared_value);
        shared_value += CHILD_VALUE;
        printf("child after: %d (expecting 150)\n", shared_value);
    } else { /* parent */
        printf("parent before: %d\n", shared_value);
        shared_value += PARENT_VALUE;
        printf("parent after: %d (expecting 175)\n", shared_value);
    }
    return 0;
}
