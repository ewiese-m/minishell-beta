#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

int main() {
    int pipefd[2];
    pid_t pid1, pid2, pid3;

    // Crear primer pipe para env | sort
    if (pipe(pipefd) == -1) {
        perror("pipe1");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork1");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // Proceso hijo 1 (env)
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        char *args[] = {"/bin/env", NULL};
        execve("/bin/env", args, environ);
        perror("execve env");
        exit(EXIT_FAILURE);
    }

    // Crear segundo pipe para sort | grep
    int pipefd2[2];
    if (pipe(pipefd2) == -1) {
        perror("pipe2");
        exit(EXIT_FAILURE);
    }

    pid2 = fork();
    if (pid2 == -1) {
        perror("fork2");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // Proceso hijo 2 (sort)
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        close(pipefd2[0]);
        dup2(pipefd2[1], STDOUT_FILENO);
        close(pipefd2[1]);

        char *args[] = {"/usr/bin/sort", NULL};
        execve("/usr/bin/sort", args, environ);
        perror("execve sort");
        exit(EXIT_FAILURE);
    }

    // Tercer fork para primer grep
    pid3 = fork();
    if (pid3 == -1) {
        perror("fork3");
        exit(EXIT_FAILURE);
    }

    if (pid3 == 0) {
        // Proceso hijo 3 (primer grep: -v SHLVL)
        close(pipefd[1]);
        close(pipefd2[1]);

        dup2(pipefd2[0], STDIN_FILENO);
        close(pipefd2[0]);

        char *args[] = {"/usr/bin/grep", "-v", "SHLVL", NULL};
        execve("/usr/bin/grep", args, environ);
        perror("execve grep1");
        exit(EXIT_FAILURE);
    }

    // Proceso padre
    close(pipefd[0]);
    close(pipefd[1]);
    close(pipefd2[0]);
    close(pipefd2[1]);

    // Crear último pipe para segundo grep
    int pipefd3[2];
    if (pipe(pipefd3) == -1) {
        perror("pipe3");
        exit(EXIT_FAILURE);
    }

    pid_t pid4 = fork();
    if (pid4 == -1) {
        perror("fork4");
        exit(EXIT_FAILURE);
    }

    if (pid4 == 0) {
        // Proceso hijo 4 (segundo grep: -v ^_)
        dup2(pipefd3[1], STDOUT_FILENO);
        close(pipefd3[0]);
        close(pipefd3[1]);

        char *args[] = {"/usr/bin/grep", "-v", "^_", NULL};
        execve("/usr/bin/grep", args, environ);
        perror("execve grep2");
        exit(EXIT_FAILURE);
    }

    // Cerrar pipes en el padre
    close(pipefd3[1]);

    // Esperar a todos los procesos hijos
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);
    waitpid(pid4, NULL, 0);

    return 0;
}
