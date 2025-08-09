#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

/* CUSTOM TYPES */
typedef enum { FALSE, TRUE } bool_t;

/* FORWARD DECLARATIONS */
int update_shared_val();
int shared_file();

int main() {
    int* shared_value = (int*)mmap(
        NULL,
        sizeof(int),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1,
        0
    );

    printf("attempting p1\n");
    /* TODO: these are not returning correctly... */
    /* when a process finishes, it just continues... */
    if (update_shared_val(shared_value) == EXIT_FAILURE) {
        printf("p1 failed\n");
    }
    /*
    printf("\nattempting p2\n");
    if (!shared_file() == EXIT_FAILURE) {
        printf("p2 failed\n");
    }
    */
    return 0;
}

/* FUNCTION DEFINITIONS */
/* problem 1 */
int update_shared_val(int* shared_value) {
    pid_t pid = fork();

    const int CHILD_VALUE = 50;
    const int PARENT_VALUE = 75;

    if (pid < 0) {
        /* failure */
        perror("fork failed");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        /* child process */
        printf("child before: %d\n", *shared_value);
        *shared_value += CHILD_VALUE;
        printf("child after: %d\n", *shared_value);
    } else {
        /* parent process */
        int status;
        pid_t child_pid = waitpid(pid, &status, 0);
        if (child_pid < 0) {
            perror("waitpid failed");
            return EXIT_FAILURE;
        }
        if (!WIFEXITED(status)) {
            printf("child process did not terminate normally\n");
            return EXIT_FAILURE;
        }
        printf("parent before: %d\n", *shared_value);
        *shared_value += PARENT_VALUE;
        printf("parent after: %d\n", *shared_value);
    }
    return EXIT_SUCCESS;
}

/* TODO: problem 2 */
int shared_file() {
    pid_t pid = fork();

    /* error check fork */
    if (pid < 0) {
        perror("unable to fork");
        return EXIT_FAILURE;
    }

    /* open sample file */
    int fd = open("public/justdoit.txt", O_RDONLY);
    if (fd < 0) {
        perror("unable to open file");
        return EXIT_FAILURE;
    }

    /* processes */
    if (pid == 0) {
        /* TODO: child process */

        /* access shared file */

    } else {
        /* TODO: parent process */
        int status;
        pid_t child_pid = waitpid(0, &status, 0);

        /* error check waitpid */
        if (child_pid < 0) {
            perror("waitpid failed");
            return EXIT_FAILURE;
        }
        if (!WIFEXITED(status)) {
            fprintf(stderr, "child process did not terminate normally\n");
            return EXIT_FAILURE;
        }

        /* access shared file */
    }

    /* clean-up open file descriptor */
    if (close(fd) < 0) {
        perror("unable to close file descriptor");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
